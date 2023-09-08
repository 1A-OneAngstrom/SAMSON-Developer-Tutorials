#include "SECenterOfMassApp.hpp"
#include "SECenterOfMassAppGUI.hpp"

SECenterOfMassApp::SECenterOfMassApp() {

	setGUI(new SECenterOfMassAppGUI(this));
	getGUI()->loadDefaultSettings();

	positionArray = nullptr;

}

SECenterOfMassApp::~SECenterOfMassApp() {

	// clear the position Array
	if (positionArray) delete[] positionArray;

	// disconnect from atoms
	SB_FOR(SBAtom* atom, atomIndexer)
		atom->disconnectStructuralSignalFromSlot(this, SB_SLOT(&SECenterOfMassApp::onStructuralEvent));

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SECenterOfMassAppGUI* SECenterOfMassApp::getGUI() const { return static_cast<SECenterOfMassAppGUI*>(SBDApp::getGUI()); }

void SECenterOfMassApp::computeCenterOfMass() {

	// clear the position Array

	if (positionArray) delete[] positionArray;

	// disconnect from atoms

	SB_FOR(SBAtom* atom, atomIndexer)
		atom->disconnectStructuralSignalFromSlot(this, SB_SLOT(&SECenterOfMassApp::onStructuralEvent));

	// get selected nodes and find atoms

	SBPointerIndexer<SBNode> const* selectedNodes = SAMSON::getActiveDocument()->getSelectedNodes();

	SBNodeIndexer temporaryIndexer;
	if (selectedNodes->size() > 0) {

		// if there are nodes that are selected then get atoms from the selected nodes

		SB_FOR(SBNode * node, *selectedNodes) {

			node->getNodes(temporaryIndexer, SBNode::Atom);

		}

	}
	else {

		// if nothing is selected then select all atoms in the active document

		SAMSON::getActiveDocument()->getNodes(temporaryIndexer, SBNode::Atom);

	}

	// store pointers to atoms

	atomIndexer.clear();
	SB_FOR(SBNode* node, temporaryIndexer) atomIndexer.addReferenceTarget(node);
	temporaryIndexer.clear();

	// connect to atoms

	positionArray = new SBPosition3[atomIndexer.size()];
	SB_FOR(SBAtom* atom, atomIndexer)
		positionArray[atomIndexer.getIndex(atom)] = atom->getPosition();

	SB_FOR(SBAtom* atom, atomIndexer)
		atom->connectStructuralSignalToSlot(this, SB_SLOT(&SECenterOfMassApp::onStructuralEvent));

	// compute the center of mass

	if (!atomIndexer.size()) return;

	centerOfMass.setZero();

	SB_FOR(SBAtom* atom, atomIndexer)
		centerOfMass += atom->getPosition();

	centerOfMass /= static_cast<double>(atomIndexer.size());

	// display the center of mass

	getGUI()->updateCenterOfMass(centerOfMass);

}

void SECenterOfMassApp::onStructuralEvent(SBStructuralEvent* event) {

	if (event->getType() == SBStructuralEvent::AtomPositionChanged) {

		SBAtom* atom = static_cast<SBAtom*>(event->getSender());

		// get the index of the atom in the atom indexer

		const unsigned int atomIndex = atomIndexer.getIndex(atom);

		// subtract the old position

		centerOfMass -= (positionArray[atomIndex] / atomIndexer.size());

		// add the new position

		centerOfMass += (atom->getPosition() / atomIndexer.size());

		// store the new position

		positionArray[atomIndex] = atom->getPosition();

		// display the center of mass

		getGUI()->updateCenterOfMass(centerOfMass);

	}

}
