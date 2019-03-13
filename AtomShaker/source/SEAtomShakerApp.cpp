#include "SEAtomShakerApp.hpp"
#include "SEAtomShakerAppGUI.hpp"
#include "SAMSON.hpp"
#include "SBRandom.hpp"

SEAtomShakerApp::SEAtomShakerApp() {

	setGUI(new SEAtomShakerAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEAtomShakerApp::~SEAtomShakerApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEAtomShakerAppGUI* SEAtomShakerApp::getGUI() const { return static_cast<SEAtomShakerAppGUI*>(SBDApp::getGUI()); }

void SEAtomShakerApp::shakeAtoms(const SBQuantity::length& distance) {

	SBNodeIndexer nodeIndexer;
	// collect all selected atoms in the active document
	SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Atom) && SBNode::IsSelected());

	SAMSON::setStatusMessage(QString("We found " + QString::number(nodeIndexer.size()) + QString(" atom(s).")), 0);

	// create a random generator with custom seed
	SBRandom randomGenerator(SAMSON::getTime());

	// turn the holding mechanism on
	SAMSON::beginHolding("Shake atoms");

	SB_FOR(SBNode* node, nodeIndexer) {

		SBAtom* currentAtom = static_cast<SBAtom*>(node);
		SBPosition3 position = currentAtom->getPosition();

		position.v[0] += distance * (randomGenerator.randDouble1() - 0.5);
		position.v[1] += distance * (randomGenerator.randDouble1() - 0.5);
		position.v[2] += distance * (randomGenerator.randDouble1() - 0.5);

		currentAtom->setPosition(position);

	}

	// turn the holding mechanism off
	SAMSON::endHolding();

}
