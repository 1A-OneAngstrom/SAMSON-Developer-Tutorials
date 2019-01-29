#include "SESpringsInteractionModel.hpp"
#include "SAMSON.hpp"


SESpringsInteractionModel::SESpringsInteractionModel() : SBMInteractionModelParticleSystem(0) {

	// SAMSON Element generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	initializeNeeded = true;
	isSpringModelSet = false;
	bondSpringStiffness = 1.0;

}

SESpringsInteractionModel::SESpringsInteractionModel(SBParticleSystem* particleSystem) : SBMInteractionModelParticleSystem(particleSystem) {

	// SAMSON Element generator pro tip: implement this function if you want your interaction model to be applied to a particle system (the general case).
	// You might want to connect to various signals and handle the corresponding events (for example to erase this interaction model when the dynamical model it is applied to is erased).

	initializeNeeded = true;
	isSpringModelSet = false;
	bondSpringStiffness = 1.0;

}

SESpringsInteractionModel::~SESpringsInteractionModel() {

	// SAMSON Element generator pro tip: disconnect from signals you might have connected to.

}

 bool SESpringsInteractionModel::isSerializable() const {

	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Modify the line below to "return true;" if you want this interaction model be serializable (hence copyable, savable, etc.)

	return false;
	
}

 void SESpringsInteractionModel::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) const {

	SBMInteractionModelParticleSystem::serialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);

	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to serialize your interaction model.

}

void SESpringsInteractionModel::unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) {

	SBMInteractionModelParticleSystem::unserialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);
	
	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to unserialize your interaction model.

}

void SESpringsInteractionModel::eraseImplementation() {

	// SAMSON Element generator pro tip: modify this function when you need to perform special tasks when your interaction model is erased (e.g. disconnect from nodes you are connected to).
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

}

void SESpringsInteractionModel::initializeInteractions() {

	// SAMSON Element generator pro tip: this function is called to initialize the energy and forces. Unless everything is computed from scratch at each
	// time step in updateInteractions, you should implement this function to set your interaction model up.

	initializeNeeded = true;

	// initialize the bond springs model
	setBondSpringsModel();

	initializeNeeded = false;

	updateInteractions();

}

unsigned int SESpringsInteractionModel::setBondSpringsModel() {

	isSpringModelSet = false;

	// clear vectors

	springBondVector.clear();
	springLengthVector.clear();

	// init the set of atoms: the selected atoms are stored in particleIndex

	particleIndex = (*particleSystem)->getStructuralParticleIndexer();
	int nParticles = particleIndex->size();
	if (nParticles <= 0) return 0;

	// get the all the bonds in the active document

	SBNodeIndexer nodeIndexer;
	SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Bond));

	// initializes bond springs

	SB_FOR(SBNode* node, nodeIndexer) {

		SBBond* bond = static_cast<SBBond*>(node);

		SBAtom* atomI = bond->getLeftAtom();
		SBAtom* atomJ = bond->getRightAtom();

		// the spring is considered only if the two bonded atoms are selected
		// check if the selected atoms are connected through a bond
		if (!particleIndex->hasIndex(atomI) || !particleIndex->hasIndex(atomJ)) continue;

		// add the atoms to the atoms Vectors
		springBondVector.push_back(bond);

		// add the equilibrium length to the springLength vector
		springLengthVector.push_back(bond->getLength());

	}

	// set energy and forces to zero

	*energy = SBQuantity::energy(0.0);
	for (unsigned int i = 0; i < nParticles; ++i)
		setForce(i, SBForce3(SBQuantity::force(0)));

	isSpringModelSet = true;

	return nParticles;

}

void SESpringsInteractionModel::updateInteractions() {

	// SAMSON Element generator pro tip: this function is called to update the energy and forces. It is the most important function of your interaction model. 
	// Incremental interaction model algorithms take advantage of passive signalling functionalities of dynamical models, which store information about the degrees of freedom that have been updated,
	// to only update the forces which changed since the previous time step.

	// check whether the model has been initialized

	if (initializeNeeded) initializeInteractions();
	if (!isSpringModelSet) return;

	SBPointerIndexer<SBStructuralParticle> const* particleIndex = (*particleSystem)->getStructuralParticleIndexer();
	int nParticles = particleIndex->size();
	if (nParticles <= 0) return;

	// reset energy and forces of the system

	*energy = SBQuantity::energy(0.0);
	energyBondSprings = SBQuantity::energy(0.0);
	for (unsigned int i = 0; i < nParticles; ++i)
		setForce(i, SBForce3(SBQuantity::force(0.0)));

	// apply bond springs interaction model

	computeBondSpringsInteractions();

	// update the energy of the system

	*energy = energyBondSprings;

	// emit the changed signal

	changed();

}

void SESpringsInteractionModel::computeBondSpringsInteractions() {

	energyBondSprings = SBQuantity::energy(0.0);

	if (!isSpringModelSet) return;

	// some conversion for the bond spring stiffness coefficient
	SBQuantity::forcePerLength forceFactor = bondSpringStiffness * SBQuantity::zeptojoule(690.0) / SBQuantity::squareAngstrom(0.5);

	for (unsigned int i = 0; i < springBondVector.size(); ++i) {

		// get atoms connected through the bond
		SBAtom* atomI = springBondVector[i]->getLeftAtom();
		SBAtom* atomJ = springBondVector[i]->getRightAtom();

		unsigned int indexI = particleIndex->getIndex(atomI);
		unsigned int indexJ = particleIndex->getIndex(atomJ);

		const SBPosition3& positionI = (*particleSystem)->getPosition(indexI);
		const SBPosition3& positionJ = (*particleSystem)->getPosition(indexJ);

		// the force intensity depends on the shift respect to the equilibrium
		SBQuantity::length forceIntensity(0);
		forceIntensity = (positionJ - positionI).norm() - springLengthVector[i];

		// compute the forces acting on both atoms connected through the bond
		SBForce3  force = forceFactor * forceIntensity * (positionJ - positionI).normalizedVersion();
		SBForce3 forceI = getForce(indexI);
		SBForce3 forceJ = getForce(indexJ);

		setForce(indexI, forceI + force);
		setForce(indexJ, forceJ - force);

		// compute the energy
		energyBondSprings += 0.5 * forceFactor * forceIntensity * forceIntensity;

	}

}

void SESpringsInteractionModel::display() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SESpringsInteractionModel::displayForShadow() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to compute shadows. 
	// Implement this function if your interaction model displays things in viewports, so that your interaction model can cast shadows
	// to other objects in SAMSON, for example thanks to the utility
	// functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SESpringsInteractionModel::displayForSelection() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to perform object picking.
	// Instead of rendering colors, your interaction model is expected to write the index of a data graph node (obtained with getIndex()).
	// Implement this function so that your interaction model can be selected (if you render its own index) or can be used to select other objects (if you render 
	// the other objects' indices), for example thanks to the utility functions provided by SAMSON (e.g. displaySpheresSelection, displayTrianglesSelection, etc.)
	// This should be implemented if your interaction model displays something in viewports (and you want the user to be able to select your interaction model
	// by picking its visual representation in viewports). 

}

void SESpringsInteractionModel::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Element generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the interaction model. 
	// This should be implemented if your interaction model displays something in viewports. 

}

void SESpringsInteractionModel::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

	// SAMSON Element generator pro tip: this function is called by SAMSON to determine your model's influence on ambient occlusion (in case your interaction model displays something in viewports).
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

	// SAMSON Element generator pro tip: implement this function if you need to handle base events

}

void SESpringsInteractionModel::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle document events 

}

void SESpringsInteractionModel::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle dynamical events 

}

void SESpringsInteractionModel::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Element generator pro tip: implement this function if you need to handle structural events

}

void SESpringsInteractionModel::setBondSpringStiffness(double stiffness) {

	bondSpringStiffness = stiffness;

}
