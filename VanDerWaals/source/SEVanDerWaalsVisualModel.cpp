#include "SEVanDerWaalsVisualModel.hpp"
#include "SAMSON.hpp"
#include "SBElementTable.hpp"


SEVanDerWaalsVisualModel::SEVanDerWaalsVisualModel() {

	// SAMSON Element generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

}

SEVanDerWaalsVisualModel::SEVanDerWaalsVisualModel(const SBNodeIndexer& nodeIndexer) {

	// SAMSON Element generator pro tip: implement this function if you want your visual model to be applied to a set of data graph nodes.
	// You might want to connect to various signals and handle the corresponding events. For example, if your visual model represents a sphere positioned at
	// the center of mass of a group of atoms, you might want to connect to the atoms' base signals (e.g. to update the center of mass when an atom is erased) and
	// the atoms' structural signals (e.g. to update the center of mass when an atom is moved).

	radiusFactor = 1.0f; // set a default radius factor

	SBNodeIndexer temporaryIndexer;
	SB_FOR(SBNode* node, nodeIndexer)
		node->getNodes(temporaryIndexer, SBNode::IsType(SBNode::Atom));

	SB_FOR(SBNode* node, temporaryIndexer)
		atomIndexer.addReferenceTarget(node);

	temporaryIndexer.clear();

	SAMSON::setStatusMessage(QString("Van der Waals visual model: added for ") + QString::number(atomIndexer.size()), 0);

}

SEVanDerWaalsVisualModel::~SEVanDerWaalsVisualModel() {

	// SAMSON Element generator pro tip: disconnect from signals you might have connected to.

}

bool SEVanDerWaalsVisualModel::isSerializable() const {

	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Modify the line below to "return true;" if you want this visual model be serializable (hence copyable, savable, etc.)

	return true;
	
}

void SEVanDerWaalsVisualModel::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) const {

	// Serialization of the parent class

	SBMVisualModel::serialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);

	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.

	// Write the radius factor

	serializer->writeFloatElement("radiusFactor", radiusFactor);

	// Write the number of atoms to which this visual model is applied

	serializer->writeUnsignedIntElement("numberOfAtoms", atomIndexer.size());

	unsigned int atomIndex = 0; // the index of the atom in the indexer

	// Write indices of the atoms to which this visual model is applied

	SB_FOR(SBPointer<SBAtom> atom, atomIndexer) {

		if (nodeIndexer.getIndex(atom(), atomIndex)) {

			// the atom is indexed

			serializer->writeBoolElement("atomIsIndexed", true);
			serializer->writeUnsignedIntElement("atomIndex", atomIndex);

		}
		else {

			// the atom is not indexed, the user must be copying just the visual model
			// so we serialize the atom address itself

			serializer->writeBoolElement("atomIsIndexed", false);
			serializer->writeUnsignedLongLongElement("atomIndex", (unsigned long long)atom());

		}

	}

}

void SEVanDerWaalsVisualModel::unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) {

	// Unserialization of the parent class

	SBMVisualModel::unserialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);
	
	// SAMSON Element generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.

	// Read the radius factor

	radiusFactor = serializer->readFloatElement();

	// Read the number of atoms to which this visual model is applied

	unsigned int numberOfAtoms = serializer->readUnsignedIntElement();

	bool atomIsIndexed;
	unsigned int atomIndex = 0; // the index of the atom in the indexer

	// Read indices of the atoms to which this visual model is applied and
	// add these node into the atom indexer of the visual model

	for (unsigned int i = 0; i < numberOfAtoms; ++i) {

		atomIsIndexed = serializer->readBoolElement();
		if (atomIsIndexed) {

			// the atom was serialized too

			atomIndex = serializer->readUnsignedIntElement();
			atomIndexer.addReferenceTarget(nodeIndexer[atomIndex]);

		}
		else {

			// the atom was not serialized, it must still exist in memory

			atomIndexer.addReferenceTarget((SBAtom*)serializer->readUnsignedLongLongElement());

		}

	}

}

void SEVanDerWaalsVisualModel::eraseImplementation() {

	// SAMSON Element generator pro tip: modify this function when you need to perform special tasks when your visual model is erased (e.g. disconnect from nodes you are connected to).
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

}

void SEVanDerWaalsVisualModel::display() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop. This is the main function of your visual model. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

	unsigned int numberOfAtoms = atomIndexer.size();

	// allocate arrays and initialize them to zeros

	float* positionData = new float[3 * numberOfAtoms]();
	float* radiusData = new float[numberOfAtoms]();
	float* colorData = new float[4 * numberOfAtoms]();
	unsigned int* flagData = new unsigned int[numberOfAtoms]();

	// retreive the pointer to the material applied to the visual model

	SBNodeMaterial* material = getMaterial();

	// fill in the arrays

	for (unsigned int i = 0; i < numberOfAtoms; i++) {

		SBPointer<SBAtom> currentAtom = atomIndexer[i];
		// check if the atom is not null
		if (!currentAtom.isValid()) continue;
		// check if the atom is not erased
		if (currentAtom->isErased()) continue;

		// fill the position array
		SBPosition3 position = currentAtom->getPosition();
		positionData[3 * i + 0] = (float)position.v[0].getValue();
		positionData[3 * i + 1] = (float)position.v[1].getValue();
		positionData[3 * i + 2] = (float)position.v[2].getValue();

		// fill the radius array
		radiusData[i] = radiusFactor * (float)currentAtom->getVanDerWaalsRadius().getValue();

		// fill the color array based on the material applied to the visual model, if any
		if (material) {

			// if a material is applied to the visual model use its color scheme
			material->getColorScheme()->getColor(colorData + 4 * i, currentAtom());

		}
		else if (currentAtom->getMaterial()) {

			// else if a material is applied to the current atom use its color scheme
			currentAtom->getMaterial()->getColorScheme()->getColor(colorData + 4 * i, currentAtom());

		}
		else {

			// else set the default color based on CPK color
			memcpy(&colorData[4 * i],
					SBElementTable::getElement(currentAtom->getElementType()).getColorCPK(),
					4 * sizeof(float));

		}

		// fill the flag array based on the combination of the flags for the visual model and the current atom
		flagData[i] = currentAtom->getInheritedFlags() | getInheritedFlags();

	}

	// display spheres for atoms

	SAMSON::displaySpheres(
		numberOfAtoms,
		positionData,
		radiusData,
		colorData,
		flagData);

	// clean up the memory

	delete[] positionData;
	delete[] radiusData;
	delete[] colorData;
	delete[] flagData;

}

void SEVanDerWaalsVisualModel::displayForShadow() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to compute shadows. 
	// Implement this function so that your visual model can cast shadows to other objects in SAMSON, for example thanks to the utility
	// functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

	display();

}

void SEVanDerWaalsVisualModel::displayForSelection() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to perform object picking.
	// Instead of rendering colors, your visual model is expected to write the index of a data graph node (obtained with getIndex()).
	// Implement this function so that your visual model can be selected (if you render its own index) or can be used to select other objects (if you render 
	// the other objects' indices), for example thanks to the utility functions provided by SAMSON (e.g. displaySpheresSelection, displayTrianglesSelection, etc.)

	unsigned int numberOfAtoms = atomIndexer.size();

	// allocate arrays and initialize them to zeros

	float* positionData = new float[3 * numberOfAtoms]();
	float* radiusData = new float[numberOfAtoms]();
	unsigned int* nodeIndexData = new unsigned int[numberOfAtoms]();

	// fill in the arrays

	for (unsigned int i = 0; i < numberOfAtoms; i++) {

		SBPointer<SBAtom> currentAtom = atomIndexer[i];
		// check if the atom is not null
		if (!currentAtom.isValid()) continue;
		// check if the atom is not erased
		if (currentAtom->isErased()) continue;

		// fill the position array
		SBPosition3 position = currentAtom->getPosition();
		positionData[3 * i + 0] = (float)position.v[0].getValue();
		positionData[3 * i + 1] = (float)position.v[1].getValue();
		positionData[3 * i + 2] = (float)position.v[2].getValue();

		// fill the radius array
		radiusData[i] = radiusFactor * (float)currentAtom->getVanDerWaalsRadius().getValue();

		// fill the node index array
		nodeIndexData[i] = currentAtom->getNodeIndex();

	}

	// display spheres for atoms

	SAMSON::displaySpheresSelection(
		numberOfAtoms,
		positionData,
		radiusData,
		nodeIndexData);

	// clean up the memory

	delete[] positionData;
	delete[] radiusData;
	delete[] nodeIndexData;

}

void SEVanDerWaalsVisualModel::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Element generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the visual model. 

}

void SEVanDerWaalsVisualModel::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

	// SAMSON Element generator pro tip: this function is called by SAMSON to determine your model's influence on ambient occlusion.
	// Implement this function if you want your visual model to occlude other objects in ambient occlusion calculations.
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

void SEVanDerWaalsVisualModel::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle base events (e.g. when a node for which you provide a visual representation emits a base signal, such as when it is erased)

}

void SEVanDerWaalsVisualModel::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle document events 

}

void SEVanDerWaalsVisualModel::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Element generator pro tip: implement this function if you need to handle structural events (e.g. when a structural node for which you provide a visual representation is updated)

}

const float& SEVanDerWaalsVisualModel::getRadiusFactor() const {

	return radiusFactor;

}

void SEVanDerWaalsVisualModel::setRadiusFactor(const float& r) {

	if (r < 0.0f) return;

	radiusFactor = r;

	// request re-rendering of the viewport
	SAMSON::requestViewportUpdate();

}
