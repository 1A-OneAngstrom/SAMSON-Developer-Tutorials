#ifdef CREATE_PYTHON_BINDINGS

#include "PythonBindings.hpp"

#include "SEPyBindTutorialApp.hpp"

void exposeSEPyBindTutorialApp(py::module& m) {

	/* You can create bindings for a function from the SEPyBindTutorialApp class without creating bindings for the class itself
	 * In this case, you can call it in Python scripting as follows:
	 *	import SE_F2078F9E_F2CB_BA72_EE86_1E01A10B63D4 as pybindtutorial
	 *	pybindtutorial.addCustomStructuralModel()
	 */

	m.def("addCustomStructuralModel", [](){
			SEPyBindTutorialApp* app = new SEPyBindTutorialApp();
			app->addCustomStructuralModel();
		},
		"Add a custom structural model with a custom group");

	/* Or you can create bindings for the class and its functionality
	 * In this case, you can call it in Python scripting as follows:
	 *	import SE_F2078F9E_F2CB_BA72_EE86_1E01A10B63D4 as pybindtutorial
	 *	tutorialApp = pybindtutorial.SEPyBindTutorialApp() # create a class instance
	 *	tutorialApp.addCustomStructuralModel()             # call a function on this instance
	 */

	py::class_<SEPyBindTutorialApp> c(m, "SEPyBindTutorialApp", "The SEPyBindTutorialApp class");

	// constructor

	c.def(py::init<>(), "Constructs a custom structural group");

	// functions

	c.def("addCustomStructuralModel", &SEPyBindTutorialApp::addCustomStructuralModel, "Add a custom structural model with a custom group");

}

#endif // CREATE_PYTHON_BINDINGS
