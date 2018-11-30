#ifdef CREATE_PYTHON_BINDINGS

#include "Bind.hpp"

#endif

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

	SAMSON::beginHolding("Add a custom structural model with a custom group");

	CustomStructuralModel* customStructuralModel = new CustomStructuralModel();
	customStructuralModel->setName("Custom structural model");
	SAMSON::hold(customStructuralModel);
	customStructuralModel->create();
	SAMSON::getActiveLayer()->addChild(customStructuralModel);

	CustomStructuralGroup* customGroup = new CustomStructuralGroup("Custom group");
	SAMSON::hold(customGroup);
	customGroup->create();
	customStructuralModel->getStructuralRoot()->addChild(customGroup);

	SAMSON::endHolding();

}

#ifdef CREATE_PYTHON_BINDINGS

void exposeSEPyBindTutorialApp(py::module& m) {

	/* You can create bindings for a function from the SEPyBindTutorialApp class without creating bindings for the class itself
	 * In this case, you can call it in Python scripting as follow:
	 *	import SE_F2078F9E_F2CB_BA72_EE86_1E01A10B63D4 as tutorial
	 *	tutorial.addCustomStructuralModel()
	 */

	m.def("addCustomStructuralModel", [](){
			SEPyBindTutorialApp* app = new SEPyBindTutorialApp();
			app->addCustomStructuralModel();
		},
		"Add a custom structural model with a custom group");

	/* Or you can create bindings for the class and its functionality
	 * In this case, you can call it in Python scripting as follow:
	 *	import SE_F2078F9E_F2CB_BA72_EE86_1E01A10B63D4 as tutorial
	 *	tutorialApp = tutorial.SEPyBindTutorialApp()
	 *	tutorialApp.addCustomStructuralModel()
	 */

	py::class_<SEPyBindTutorialApp> c(m, "SEPyBindTutorialApp", "The SEPyBindTutorialApp class");
	// constructor
	c.def(py::init<>(), "Constructs a custom structural group");
	// functions
	c.def("addCustomStructuralModel", &SEPyBindTutorialApp::addCustomStructuralModel, "Add a custom structural model with a custom group");

}

#endif
