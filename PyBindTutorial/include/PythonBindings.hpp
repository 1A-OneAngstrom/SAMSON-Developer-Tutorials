#pragma once

#ifdef CREATE_PYTHON_BINDINGS

// include pybind11 headers
#include "pybind11/pybind11.h"
#include "pybind11/embed.h"
#include "pybind11/operators.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"
namespace py = pybind11;

#include <string>
#include <iostream>

// To reduce the build time in case of many exposed classes,
// the functions in which the exposure is done are placed in separate .cpp files and listed here
void exposeSEPyBindTutorialApp(py::module& m);
void exposeCustomStructuralModel(py::module& m);
void exposeCustomStructuralGroup(py::module& m);
void exposeUnitsExample(py::module& m);

/*
	For now, we recommend naming your python module based on the UUID of your SAMSON Extension.
	In this case, there will be no clashes between modules from different SAMSON Extensions named the same.
	For example, if a SAMSON Extension A has an embedded python module named "mymodule" and
	a SAMSON Extension B has an embedded python module named "mymodule",
	then there will be a clash and it will not be possible to use one of the modules.

	The UUID of your SAMSON Extension can be found in the CMakeLists.txt of your SAMSON Extension, see the line: SET( OUTPUT_UUID F2078F9E-F2CB-BA72-EE86-1E01A10B63D4 )
	For this SAMSON Extension, its UUID is F2078F9E-F2CB-BA72-EE86-1E01A10B63D4.
	The name of the module will be: SE_F2078F9E_F2CB_BA72_EE86_1E01A10B63D4
 */

// Must be defined in global scope.
// The first parameter is the name of the module (without quotes)
// The second parameter is the variable which will be used as the interface to add functions and classes to the module.
PYBIND11_EMBEDDED_MODULE(SE_F2078F9E_F2CB_BA72_EE86_1E01A10B63D4, m) {

	// module docstring
	m.doc() = "SEPyBindTutorial from SAMSON Developers tutorial";

	// the module name - preferably the SAMSON Extension name
	m.def("moduleName", [](){ return "pybindtutorial"; });

	// call functions that expose functionality of the SAMSON Extension
	exposeSEPyBindTutorialApp(m);
	exposeCustomStructuralModel(m);
	exposeCustomStructuralGroup(m);
	exposeUnitsExample(m);

}

#endif //CREATE_PYTHON_BINDINGS
