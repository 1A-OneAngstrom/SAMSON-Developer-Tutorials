#include "SEPathGeneratorVisualModel.hpp"
#include "SAMSON.hpp"


SEPathGeneratorVisualModel::SEPathGeneratorVisualModel() {

	// SAMSON Extension generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

}

SEPathGeneratorVisualModel::SEPathGeneratorVisualModel(const SBNodeIndexer& nodeIndexer) {

	// SAMSON Extension generator pro tip: implement this function if you want your visual model to be applied to a set of data graph nodes.
	// You might want to connect to various signals and handle the corresponding events. For example, if your visual model represents a sphere positioned at
	// the center of mass of a group of atoms, you might want to connect to the atoms' base signals (e.g. to update the center of mass when an atom is erased) and
	// the atoms' structural signals (e.g. to update the center of mass when an atom is moved).

}

SEPathGeneratorVisualModel::~SEPathGeneratorVisualModel() {

	// SAMSON Extension generator pro tip: disconnect from signals you might have connected to.

}

 bool SEPathGeneratorVisualModel::isSerializable() const {

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Modify the line below to "return true;" if you want this visual model be serializable (hence copyable, savable, etc.)

	return false;
	
}

void SEPathGeneratorVisualModel::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) const {

	SBMVisualModel::serialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to serialize your visual model.

}

void SEPathGeneratorVisualModel::unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) {

	SBMVisualModel::unserialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);
	
	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to unserialize your visual model.

}

void SEPathGeneratorVisualModel::onErase() {

	// SAMSON Extension generator pro tip: modify this function when you need to perform special tasks when your visual model is erased (e.g. disconnect from nodes you are connected to).
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

}

void SEPathGeneratorVisualModel::display(SBNode::RenderingPass renderingPass) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON during the main rendering loop. This is the main function of your visual model. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

    if (pathNodeList.empty()) return;

    const unsigned int numberOfPathNodes = pathNodeList.size();
    const unsigned int numberOfPathLines = numberOfPathNodes - 1;

	const unsigned int inheritedFlags = getInheritedFlags();
	const float nodeRadius = (float)SBQuantity::length(SBQuantity::angstrom(0.1)).getValue();
	const float lineRadius = 0.5 * nodeRadius;

    // allocate arrays and initialize them to zeros

    float* positionData = new float[3 * numberOfPathNodes]();
    float* pathNodeRadiusData = new float[numberOfPathNodes]();
    float* pathLineRadiusData = new float[numberOfPathNodes]();
    float* colorData = new float[4 * numberOfPathNodes]();
    unsigned int* capData = new unsigned int[numberOfPathNodes]();
    unsigned int* flagData = new unsigned int[numberOfPathNodes]();
    unsigned int* indexData = new unsigned int[2 * numberOfPathLines]();
	unsigned int* nodeIndexData = new unsigned int[numberOfPathNodes]();

    // fill in the arrays

    unsigned int i = 0;

    SB_FOR(SEPathGeneratorNode * currentPathNode, pathNodeList) {

       const SBPosition3& position = currentPathNode->getPosition();
        positionData[3 * i + 0] = (float)position.v[0].getValue();
        positionData[3 * i + 1] = (float)position.v[1].getValue();
        positionData[3 * i + 2] = (float)position.v[2].getValue();
		nodeIndexData[i] = currentPathNode->getNodeIndex();

        if (i < numberOfPathLines) {

            indexData[2 * i + 0] = i;
            indexData[2 * i + 1] = i + 1;

        }

        pathNodeRadiusData[i] = nodeRadius;
		pathLineRadiusData[i] = lineRadius;
        colorData[4 * i + 0] = 1.0f;
        colorData[4 * i + 1] = 1.0f;
        colorData[4 * i + 2] = 0.0f;
        colorData[4 * i + 3] = 1.0f;
        capData[i] = 0;
        flagData[i] = currentPathNode->getInheritedFlags() | inheritedFlags;

        i++;

    }

    // display

	if (renderingPass == SBNode::RenderingPass::OpaqueGeometry) {

		SAMSON::displaySpheres(numberOfPathNodes, positionData, pathNodeRadiusData, colorData, flagData);
		SAMSON::displayCylinders(numberOfPathLines, numberOfPathNodes, indexData, positionData, pathLineRadiusData, capData, colorData, flagData);

	}
	else if (renderingPass == SBNode::RenderingPass::ShadowingGeometry) {

		// display for shadows

		SAMSON::displaySpheres(numberOfPathNodes, positionData, pathNodeRadiusData, colorData, flagData, true);
		SAMSON::displayCylinders(numberOfPathLines, numberOfPathNodes, indexData, positionData, pathLineRadiusData, capData, colorData, flagData, true);

	}
	else if (renderingPass == SBNode::RenderingPass::SelectableGeometry) {

		// display in the selectable mode in order to make path nodes movable

		SAMSON::displaySpheresSelection(numberOfPathNodes, positionData, pathNodeRadiusData, nodeIndexData);

	}

    // clean

    delete[] positionData;
    delete[] indexData;
	delete[] nodeIndexData;
    delete[] pathNodeRadiusData;
    delete[] pathLineRadiusData;
    delete[] capData;
    delete[] colorData;
    delete[] flagData;

}

void SEPathGeneratorVisualModel::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Extension generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the visual model. 

}

void SEPathGeneratorVisualModel::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON to determine your model's influence on ambient occlusion.
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

void SEPathGeneratorVisualModel::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle base events (e.g. when a node for which you provide a visual representation emits a base signal, such as when it is erased)

}

void SEPathGeneratorVisualModel::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle document events 

}

void SEPathGeneratorVisualModel::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Extension generator pro tip: implement this function if you need to handle structural events (e.g. when a structural node for which you provide a visual representation is updated)

}

void SEPathGeneratorVisualModel::addNode(SEPathGeneratorNode* pathNode) {

	if (pathNode)
		pathNodeList.addReferenceTarget(pathNode);

}

void SEPathGeneratorVisualModel::removeNode(SEPathGeneratorNode* pathNode) {

	if (pathNode)
		pathNodeList.removeReferenceTarget(pathNode);

}
