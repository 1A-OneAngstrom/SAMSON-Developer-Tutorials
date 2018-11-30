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

	SBNodeIndexer atomIndexer;
	SAMSON::getActiveDocument()->getNodes(atomIndexer, SBNode::IsType(SBNode::Atom));

	SAMSON::setStatusMessage(QString("We found " + QString::number(atomIndexer.size()) + QString(" atom(s).")), 0);

	SAMSON::beginHolding("Shake atoms");

	SBRandom randomGenerator(SAMSON::getTime());

	SB_FOR(SBNode* node, atomIndexer) {

		SBAtom* currentAtom = static_cast<SBAtom*>(node);

		SBPosition3 position = currentAtom->getPosition();
		position.v[0] += (0.5 - randomGenerator.randDouble1())*distance;
		position.v[1] += (0.5 - randomGenerator.randDouble1())*distance;
		position.v[2] += (0.5 - randomGenerator.randDouble1())*distance;
		currentAtom->setPosition(position);

	}

	SAMSON::endHolding();

}
