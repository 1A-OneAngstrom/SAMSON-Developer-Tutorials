#include "SEPyBindTutorialApp.hpp"
#include "SEPyBindTutorialAppGUI.hpp"
#include "SAMSON.hpp"

SEPyBindTutorialApp::SEPyBindTutorialApp() {

	setGUI(new SEPyBindTutorialAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEPyBindTutorialApp::~SEPyBindTutorialApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEPyBindTutorialAppGUI* SEPyBindTutorialApp::getGUI() const { return static_cast<SEPyBindTutorialAppGUI*>(SBDApp::getGUI()); }

// Adds a custom structural group into the data graph
void SEPyBindTutorialApp::addCustomStructuralModel() {

	SAMSON::beginHolding("Add a custom structural model");

	CustomStructuralModel* customStructuralModel = new CustomStructuralModel();
	customStructuralModel->setName("Custom structural model");
	SAMSON::hold(customStructuralModel);
	customStructuralModel->create();
	SAMSON::getActiveDocument()->addChild(customStructuralModel);

	CustomStructuralGroup* customGroup = new CustomStructuralGroup("Custom group");
	SAMSON::hold(customGroup);
	customGroup->create();
	customStructuralModel->addChild(customGroup);

	SAMSON::endHolding();

}
