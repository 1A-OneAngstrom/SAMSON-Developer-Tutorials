#pragma once

#ifdef CREATE_PYTHON_BINDINGS

// include pybind11 headers
#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/embed.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"
namespace py = pybind11;

#include <string>
#include <iostream>

// To decrease the compilation time in case of many exposed classes,
// functions in which the exposure is done are placed in .cpp files and listed here
void exposeCustomStructuralModel(py::module& m);
void exposeCustomStructuralGroup(py::module& m);
void exposeSEPyBindTutorialApp(py::module& m);

std::string pythonModuleName() {

	return "pybindtutorial";

}

/*
	For now, we recommend naming your python module based on the UUID of your SAMSON Element.
	In this case there will be no clashes between modules from different SAMSON Elements named the same.
	For example, if SAMSON Element A has an exposed python module named "mymodule" and
	SAMSON Element B has an exposed python module named "mymodule",
	then there will be a clash and it will not be possible to use one of the modules.

	The UUID of your SAMSON Element can be found in the CMakeLists.txt of your SAMSON Element, see the line: SET( OUTPUT_UUID F2078F9E-F2CB-BA72-EE86-1E01A10B63D4 )
	For this SAMSON Element UUID is F2078F9E-F2CB-BA72-EE86-1E01A10B63D4
	The name of the module will be: SE_F2078F9E_F2CB_BA72_EE86_1E01A10B63D4
 */
PYBIND11_EMBEDDED_MODULE(SE_F2078F9E_F2CB_BA72_EE86_1E01A10B63D4, m) {

	m.doc() = "SEPyBindTutorial";			// module docstring

	m.def("moduleName", &pythonModuleName);	// module name - preferably the SAMSON Element name

	// call functions that expose functionality of your SAMSON Element
	exposeCustomStructuralModel(m);
	exposeCustomStructuralGroup(m);
	exposeSEPyBindTutorialApp(m);

}

#endif //CREATE_PYTHON_BINDINGS
