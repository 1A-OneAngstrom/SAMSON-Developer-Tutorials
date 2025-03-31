#include "SEVanDerWaalsVisualModel.hpp"
#include "SAMSON.hpp"
#include "SBElementTable.hpp"

#include <QOpenGLShaderProgram>


SB_OPENGL_FUNCTIONS* SEVanDerWaalsVisualModel::gl = nullptr;

SEVanDerWaalsVisualModel::SEVanDerWaalsVisualModel() {

	// SAMSON Extension generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	if (!gl) gl = SAMSON::getOpenGLFunctions();

}

SEVanDerWaalsVisualModel::SEVanDerWaalsVisualModel(const SBNodeIndexer& nodeIndexer) {

	// SAMSON Extension generator pro tip: implement this function if you want your visual model to be applied to a set of data graph nodes.
	// You might want to connect to various signals and handle the corresponding events. For example, if your visual model represents a sphere positioned at
	// the center of mass of a group of atoms, you might want to connect to the atoms' base signals (e.g. to update the center of mass when an atom is erased) and
	// the atoms' structural signals (e.g. to update the center of mass when an atom is moved).

	if (!gl) gl = SAMSON::getOpenGLFunctions();

	SBNodeIndexer temporaryIndexer;
	SB_FOR(SBNode * node, nodeIndexer)
		node->getNodes(temporaryIndexer, SBNode::Atom);

	SB_FOR(SBNode * node, temporaryIndexer)
		atomIndexer.addReferenceTarget(node);

	temporaryIndexer.clear();

	// connect to the base signals

	SB_FOR(SBNode * node, atomIndexer) node->connectBaseSignalToSlot(this, SB_SLOT(&SEVanDerWaalsVisualModel::onBaseEvent));

	// connect to the structural signals

	SB_FOR(SBNode * node, atomIndexer) static_cast<SBAtom*>(node)->connectStructuralSignalToSlot(this, SB_SLOT(&SEVanDerWaalsVisualModel::onStructuralEvent));

	SAMSON::setStatusMessage(QString("Van der Waals visual model: added for ") + QString::number(atomIndexer.size()), 0);

}

SEVanDerWaalsVisualModel::~SEVanDerWaalsVisualModel() {

	// SAMSON Extension generator pro tip: disconnect from signals you might have connected to.

	// disconnect from the base signals

	SB_FOR(SBNode * node, atomIndexer) node->disconnectBaseSignalFromSlot(this, SB_SLOT(&SEVanDerWaalsVisualModel::onBaseEvent));

	// disconnect from the structural signals

	SB_FOR(SBNode * node, atomIndexer) static_cast<SBAtom*>(node)->disconnectStructuralSignalFromSlot(this, SB_SLOT(&SEVanDerWaalsVisualModel::onStructuralEvent));

	// clean up the memory

	if (positionData) delete[] positionData;
	if (radiusData) delete[] radiusData;
	if (colorData) delete[] colorData;
	if (flagData) delete[] flagData;
	if (nodeIndexData) delete[] nodeIndexData;

}

bool SEVanDerWaalsVisualModel::isSerializable() const {

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Modify the line below to "return true;" if you want this visual model be serializable (hence copyable, savable, etc.)

	return true;

}

void SEVanDerWaalsVisualModel::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) const {

	// Serialization of the parent class

	SBMVisualModel::serialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.

	// Write the radius factor

	serializer->writeFloatElement("radiusFactor", radiusFactor);

	// Write opacity

	if (classVersionNumber >= SBVersionNumber(0, 10, 0) && sdkVersionNumber < SBVersionNumber(2, 0, 0)) {

		// This attribute was introduced in the class v. 0.10.0
		// Starting from SAMSON SDK 2.0.0 opacity/transparency are node attributes and serialized with a model/node

		serializer->writeUnsignedIntElement("opacity", getOpacity());

	}

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

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.

	// Read the radius factor

	setRadiusFactor(serializer->readFloatElement());

	// Read opacity

	if (classVersionNumber >= SBVersionNumber(0, 10, 0) && sdkVersionNumber < SBVersionNumber(2, 0, 0)) {

		// This attribute was introduced in the class v. 0.10.0
		// Starting from SAMSON SDK 2.0.0 opacity/transparency are node attributes and serialized with a model/node

		setOpacity(serializer->readUnsignedIntElement());

	}

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

	updateRequired = true;

}

void SEVanDerWaalsVisualModel::onErase() {

	// SAMSON Extension generator pro tip: modify this function when you need to perform special tasks when your visual model is erased (e.g. disconnect from nodes you are connected to).
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

}

void SEVanDerWaalsVisualModel::updateDisplayData() {

	updateRequired = false;

	// modify the size of display data arrays if necessary

	if (numberOfAtoms != atomIndexer.size()) {

		numberOfAtoms = atomIndexer.size();

		// delete arrays

		if (positionData) delete[] positionData;
		if (radiusData) delete[] radiusData;
		if (colorData) delete[] colorData;
		if (flagData) delete[] flagData;
		if (nodeIndexData) delete[] nodeIndexData;

		if (numberOfAtoms == 0) {

			positionData = nullptr;
			radiusData = nullptr;
			colorData = nullptr;
			flagData = nullptr;
			nodeIndexData = nullptr;

		}
		else {

			// allocate arrays and initialize them [to zeros]

			positionData = new float[3 * numberOfAtoms]();
			radiusData = new float[numberOfAtoms]();
			colorData = new float[4 * numberOfAtoms]();
			flagData = new unsigned int[numberOfAtoms]();
			nodeIndexData = new unsigned int[numberOfAtoms]();

		}

	}

	// fill in the common arrays

	for (unsigned int i = 0; i < numberOfAtoms; i++) {

		SBPointer<SBAtom> currentAtom = atomIndexer[i];
		// check if the atom is not null
		if (!currentAtom.isValid()) continue;
		// check if the atom is not erased
		if (currentAtom->isErased()) continue;

		// fill the position array
		SBPosition3 position = currentAtom->getPosition();
		positionData[3 * i + 0] = static_cast<float>(position.v[0].getValue());
		positionData[3 * i + 1] = static_cast<float>(position.v[1].getValue());
		positionData[3 * i + 2] = static_cast<float>(position.v[2].getValue());

		// fill the radius array
		radiusData[i] = radiusFactor * static_cast<float>(currentAtom->getVanDerWaalsRadius().getValue());

	}

	changed();

}

void SEVanDerWaalsVisualModel::display(RenderingPass renderingPass) {

	const float inheritedOpacity = getInheritedOpacity();

	// SAMSON Extension generator pro tip: this function is called by SAMSON during the main rendering loop. This is the main function of your visual model. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

	if (renderingPass == SBNode::RenderingPass::Setup) {

		// update display data arrays

		if (updateRequired)
			updateDisplayData();

	}
	else if (renderingPass == SBNode::RenderingPass::OpaqueGeometry && (inheritedOpacity == 1.0f)) {

		// retrieve the pointer to the material applied to the visual model

		SBNodeMaterial* material = getMaterial();

		// fill in the arrays

		for (unsigned int i = 0; i < numberOfAtoms; i++) {

			SBPointer<SBAtom> currentAtom = atomIndexer[i];
			// check if the atom is not null
			if (!currentAtom.isValid()) continue;
			// check if the atom is not erased
			if (currentAtom->isErased()) continue;

			// fill the color array based on the material applied to the visual model, if any
			if (material) {

				// if a material is applied to the visual model use its color scheme
				material->getColorScheme()->getColor(colorData + 4 * i, currentAtom(), currentAtom()->getPosition());

			}
			else if (currentAtom->getMaterial()) {

				// else if a material is applied to the current atom use its color scheme
				currentAtom->getMaterial()->getColorScheme()->getColor(colorData + 4 * i, currentAtom(), currentAtom()->getPosition());

			}
			else {

				// else set the default color based on CPK color
				memcpy(&colorData[4 * i], SBElementTable::getElement(currentAtom->getElementType()).getColorCPK(), 4 * sizeof(float));

			}

			// fill the flag array based on the combination of the flags for the visual model and the current atom
			flagData[i] = currentAtom->getInheritedFlags() | getInheritedFlags();

		}

		// display spheres for atoms

		if (numberOfAtoms) SAMSON::displaySpheres(numberOfAtoms, positionData, radiusData, colorData, flagData);

	}
	else if ((renderingPass == SBNode::RenderingPass::TransparentGeometry) && (inheritedOpacity != 1.0f)) {

		// retrieve the pointer to the material applied to the visual model

		SBNodeMaterial* material = getMaterial();

		// fill in the arrays

		for (unsigned int i = 0; i < numberOfAtoms; i++) {

			SBPointer<SBAtom> currentAtom = atomIndexer[i];
			// check if the atom is not null
			if (!currentAtom.isValid()) continue;
			// check if the atom is not erased
			if (currentAtom->isErased()) continue;

			// fill the color array based on the material applied to the visual model, if any
			if (material) {

				// if a material is applied to the visual model use its color scheme
				material->getColorScheme()->getColor(colorData + 4 * i, currentAtom(), currentAtom()->getPosition());

			}
			else if (currentAtom->getMaterial()) {

				// else if a material is applied to the current atom use its color scheme
				currentAtom->getMaterial()->getColorScheme()->getColor(colorData + 4 * i, currentAtom(), currentAtom()->getPosition());

			}
			else {

				// else set the default color based on CPK color
				memcpy(&colorData[4 * i], SBElementTable::getElement(currentAtom->getElementType()).getColorCPK(), 4 * sizeof(float));

			}

			// fill the flag array based on the combination of the flags for the visual model and the current atom
			flagData[i] = currentAtom->getInheritedFlags() | getInheritedFlags();

		}

		if (numberOfAtoms) {

			gl->glColorMask(false, false, false, false);

			SAMSON::displaySpheres(numberOfAtoms, positionData, radiusData, colorData, flagData, false, SBSpatialTransform::identity, inheritedOpacity);

			gl->glColorMask(true, true, true, true);

			SAMSON::displaySpheres(numberOfAtoms, positionData, radiusData, colorData, flagData, false, SBSpatialTransform::identity, inheritedOpacity);

		}

	}
	else if (renderingPass == SBNode::RenderingPass::ShadowingGeometry) {

		// display for shadows

		if (numberOfAtoms) SAMSON::displaySpheres(numberOfAtoms, positionData, radiusData, colorData, flagData, true);

	}
	else if (renderingPass == SBNode::RenderingPass::SelectableGeometry) {

		// display for selection

		// fill in the arrays

		for (unsigned int i = 0; i < numberOfAtoms; i++) {

			SBPointer<SBAtom> currentAtom = atomIndexer[i];
			// check if the atom is not null
			if (!currentAtom.isValid()) continue;
			// check if the atom is not erased
			if (currentAtom->isErased()) continue;

			// fill the node index array
			nodeIndexData[i] = currentAtom->getNodeIndex();

		}

		// display spheres for atoms

		if (numberOfAtoms) SAMSON::displaySpheresSelection(numberOfAtoms, positionData, radiusData, nodeIndexData);

	}

}

void SEVanDerWaalsVisualModel::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Extension generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the visual model. 

}

void SEVanDerWaalsVisualModel::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

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

class removeAtomCommand final : public SBCUndoCommand {

public:

	removeAtomCommand(SEVanDerWaalsVisualModel* visualModel, SBAtom* atom) { this->visualModel = visualModel; this->atom = atom; }
	virtual ~removeAtomCommand() {}

	virtual std::string getName() const override { return "Remove atom from visual model"; }

	void redo() override { if (visualModel.isValid() && atom.isValid()) visualModel->atomIndexer.removeReferenceTarget(atom()); visualModel->updateRequired = true; }
	void undo() override { if (visualModel.isValid() && atom.isValid()) visualModel->atomIndexer.addReferenceTarget(atom()); visualModel->updateRequired = true; }

private:

	SBPointer<SEVanDerWaalsVisualModel>							visualModel;
	SBPointer<SBAtom>											atom;

};

void SEVanDerWaalsVisualModel::onBaseEvent(SBBaseEvent* event) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle base events (e.g. when a node for which you provide a visual representation emits a base signal, such as when it is erased)

	switch (event->getType()) {

	case SBBaseEvent::Type::NodeDeleteBegin:

		SAMSON::disableHolding();
		event->getSender()->disconnectBaseSignalFromSlot(this, SB_SLOT(&SEVanDerWaalsVisualModel::onBaseEvent));
		SAMSON::enableHolding();

		break;

	case SBBaseEvent::Type::NodeEraseBegin:

		if (SAMSON::isHolding()) SAMSON::hold(new removeAtomCommand(this, static_cast<SBAtom*>(event->getSender())));

		atomIndexer.removeReferenceTarget(event->getSender());
		updateRequired = true;

		event->getSender()->disconnectBaseSignalFromSlot(this, SB_SLOT(&SEVanDerWaalsVisualModel::onBaseEvent));
		if (atomIndexer.empty()) this->erase();
		break;

	case SBBaseEvent::Type::IndexChanged:
	case SBBaseEvent::Type::MaterialAdded:
	case SBBaseEvent::Type::MaterialChanged:
	case SBBaseEvent::Type::MaterialRemoved:

		updateRequired = true;
		break;

	default:
		break;

	}

}

void SEVanDerWaalsVisualModel::onDocumentEvent(SBDocumentEvent* event) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle document events 

}

void SEVanDerWaalsVisualModel::onStructuralEvent(SBStructuralEvent* event) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle structural events (e.g. when a structural node for which you provide a visual representation is updated)

	switch (event->getType()) {

	case SBStructuralEvent::Type::AtomPositionChanged:
	case SBStructuralEvent::Type::AtomElementChanged:
	case SBStructuralEvent::Type::CoarseGrainedColorChanged:
	case SBStructuralEvent::Type::CoarseGrainedRadiusChanged:

		updateRequired = true;
		break;

	default:
		break;

	}

}

SB_HOLD_SET_IMPLEMENTATION(SEVanDerWaalsVisualModel, float, RadiusFactor, "radius factor");

float SEVanDerWaalsVisualModel::getRadiusFactor() const { return radiusFactor; }
void SEVanDerWaalsVisualModel::setRadiusFactor(const float value) {

	float newValue = value;
	if (hasRadiusFactorRange()) {

		if (newValue < getMinimumRadiusFactor()) newValue = getMinimumRadiusFactor();
		else if (newValue > getMaximumRadiusFactor()) newValue = getMaximumRadiusFactor();

	}

	if (this->radiusFactor != newValue) {

		// make the operation undoable
		SB_HOLD_SET(SEVanDerWaalsVisualModel, RadiusFactor, getRadiusFactor(), newValue, this);

		this->radiusFactor = newValue;

		updateRequired = true;
		changed();	// emit the VisualModelChanged event leading to the request for the viewport update

	}

}
bool SEVanDerWaalsVisualModel::hasRadiusFactorRange() const { return true; }
float SEVanDerWaalsVisualModel::getMinimumRadiusFactor() const { return 0.1f; }
float SEVanDerWaalsVisualModel::getMaximumRadiusFactor() const { return 2.5f; }
float SEVanDerWaalsVisualModel::getDefaultRadiusFactor() const { return 1.0f; }
float SEVanDerWaalsVisualModel::getRadiusFactorSingleStep() const { return 0.1f; }
std::string SEVanDerWaalsVisualModel::getRadiusFactorSuffix() const { return std::string(""); }
