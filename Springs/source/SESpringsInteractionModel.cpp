#include "SESpringsInteractionModel.hpp"
#include "SAMSON.hpp"


SESpringsInteractionModel::SESpringsInteractionModel() : SBMInteractionModelParticleSystem(nullptr) {

	// SAMSON Extension generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	bondSpringStiffness = 1.0;

}

SESpringsInteractionModel::SESpringsInteractionModel(SBParticleSystem* particleSystem) : SBMInteractionModelParticleSystem(particleSystem) {

	// SAMSON Extension generator pro tip: implement this function if you want your interaction model to be applied to a particle system (the general case).
	// You might want to connect to various signals and handle the corresponding events (for example to erase this interaction model when the dynamical model it is applied to is erased).

	bondSpringStiffness = 1.0;

}

SESpringsInteractionModel::~SESpringsInteractionModel() {

	// SAMSON Extension generator pro tip: disconnect from signals you might have connected to.

}

 bool SESpringsInteractionModel::isSerializable() const {

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Modify the line below to "return true;" if you want this interaction model be serializable (hence copyable, savable, etc.)

	return false;
	
}

 void SESpringsInteractionModel::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) const {

	SBMInteractionModelParticleSystem::serialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to serialize your interaction model.

}

void SESpringsInteractionModel::unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) {

	SBMInteractionModelParticleSystem::unserialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);
	
	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to unserialize your interaction model.

}

void SESpringsInteractionModel::eraseImplementation() {

	// SAMSON Extension generator pro tip: modify this function when you need to perform special tasks when your interaction model is erased (e.g. disconnect from nodes you are connected to).
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

}

void SESpringsInteractionModel::initializeInteractions() {

	// SAMSON Extension generator pro tip: this function is called to initialize the energy and forces. Unless everything is computed from scratch at each
	// time step in updateInteractions, you should implement this function to set your interaction model up.

	// Initialize the bond springs model

	initializeBondSpringsModel();

	// Signal that the energy and forces of the interaction model have been changed

	changed();

}

void SESpringsInteractionModel::initializeBondSpringsModel() {

	// Clear vectors

	springBondVector.clear();
	springLengthVector.clear();

	// Initialize the set of atoms: the selected atoms are stored in particleIndexer

	particleIndexer = (*particleSystem)->getStructuralParticleIndexer();

	// Get the all the bonds in the active document

	SBNodeIndexer nodeIndexer;
	SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::Bond);

	// Initialize bond springs

	SB_FOR(SBNode* node, nodeIndexer) {

		SBPointer<SBBond> bond = static_cast<SBBond*>(node);
		if (!bond.isValid()) continue;

		SBPointer<SBAtom> atomI = bond->getLeftAtom();
		SBPointer<SBAtom> atomJ = bond->getRightAtom();
		if (!atomI.isValid() || !atomJ.isValid()) continue;

		// The spring is considered only if the two bonded atoms are selected
		// Check if the selected atoms are connected through a bond
		if (!particleIndexer->hasIndex(atomI()) || !particleIndexer->hasIndex(atomJ())) continue;

		// Add the bond to the bond vector
		springBondVector.push_back(bond());

		// Add the equilibrium length to the springLength vector
		springLengthVector.push_back(bond->getLength());

	}

	// Set energy and forces to zero

	*energy = SBQuantity::energy(0.0);
	for (unsigned int i = 0; i < particleIndexer->size(); ++i)
		setForce(i, SBForce3(SBQuantity::force(0)));

}

void SESpringsInteractionModel::setBondSpringStiffness(double stiffness) { bondSpringStiffness = stiffness; }

void SESpringsInteractionModel::updateInteractions() {

	// SAMSON Extension generator pro tip: this function is called to update the energy and forces. It is the most important function of your interaction model. 
	// Incremental interaction model algorithms take advantage of passive signalling functionalities of dynamical models, which store information about the degrees of freedom that have been updated,
	// to only update the forces which changed since the previous time step.

	// Reset energy and forces of the system

	*energy = SBQuantity::energy(0.0);
	for (unsigned int i = 0; i < particleIndexer->size(); ++i)
		setForce(i, SBForce3(SBQuantity::force(0.0)));

	// Apply the bond springs interaction model

	updateBondSpringsInteractions();

	// Signal that the energy and forces of the interaction model has been changed

	changed();

}

void SESpringsInteractionModel::updateBondSpringsInteractions() {

	SBQuantity::kJPerMol energyBondSprings = SBQuantity::energy(0.0); // Store the bond stretch energy

	// Conversion for the bond spring stiffness coefficient
	SBQuantity::forcePerLength forceFactor = bondSpringStiffness * SBQuantity::zeptojoule(690.0) / SBQuantity::squareAngstrom(0.5);

	for (unsigned int i = 0; i < springBondVector.size(); ++i) {

		SBPointer<SBBond> bond = static_cast<SBBond*>(springBondVector[i]);
		if (!bond.isValid()) continue;

		// Get atoms connected through the bond
		SBPointer<SBAtom> atomI = springBondVector[i]->getLeftAtom();
		SBPointer<SBAtom> atomJ = springBondVector[i]->getRightAtom();
		if (!atomI.isValid() || !atomJ.isValid()) continue;

		unsigned int indexI = particleIndexer->getIndex(atomI());
		unsigned int indexJ = particleIndexer->getIndex(atomJ());

		const SBPosition3& positionI = (*particleSystem)->getPosition(indexI);
		const SBPosition3& positionJ = (*particleSystem)->getPosition(indexJ);

		// The force intensity depends on the shift with respect to the equilibrium length
		SBQuantity::length forceIntensity(0.0);
		forceIntensity = (positionJ - positionI).norm() - springLengthVector[i];

		// Compute the forces acting on both atoms connected through the bond
		SBForce3 force = forceFactor * forceIntensity * (positionJ - positionI).normalizedVersion();
		SBForce3 forceI = getForce(indexI);
		SBForce3 forceJ = getForce(indexJ);

		setForce(indexI, forceI + force);
		setForce(indexJ, forceJ - force);

		// Compute the energy
		energyBondSprings += 0.5 * forceFactor * forceIntensity * forceIntensity;

	}

	// Update the energy of the system

	*energy += energyBondSprings;

}

void SESpringsInteractionModel::display(RenderingPass renderingPass) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SESpringsInteractionModel::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Extension generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the interaction model. 
	// This should be implemented if your interaction model displays something in viewports. 

}

void SESpringsInteractionModel::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON to determine your model's influence on ambient occlusion (in case your interaction model displays something in viewports).
	// Implement this function if you want your interaction model to occlude other objects in ambient occlusion calculations.
	//
	// The ambientOcclusionData represents a nCellsX x nCellsY x nCellsZ grid of occlusion densities over the spatial region (boxOrigin, boxSize).
	// If your model represents geometry at position (x, y, z), then the occlusion density in corresponding grid nodes should be increased.
	//
	// Assuming x, y and z are given in length units (SBQuantity::length, SBQuantity::angstrom, etc.), the grid coordinates are:
	// SBQuantity::dimensionless xGrid = nCellsX * (x - boxOrigin.v[0]) / boxSize.v[0];
	// SBQuantity::dimensionless yGrid = nCellsY * (x - boxOrigin.v[1]) / boxSize.v[1];
	// SBQuantity::dimensionless zGrid = nCellsZ * (x - boxOrigin.v[2]) / boxSize.v[2];
	//
	// The corresponding density can be found at ambientOcclusionData[((int)zGrid.getValue() + 0)*nCellsY*nCellsX + ((int)yGrid.getValue() + 0)*nCellsX + ((int)xGrid.getValue() + 0)] (beware of grid bounds).
	// For higher-quality results, the influence of a point can be spread over neighboring grid nodes.

}

void SESpringsInteractionModel::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle base events

}

void SESpringsInteractionModel::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle document events 

}

void SESpringsInteractionModel::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle dynamical events 

}

void SESpringsInteractionModel::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Extension generator pro tip: implement this function if you need to handle structural events

}
