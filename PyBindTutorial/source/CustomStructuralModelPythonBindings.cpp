#ifdef CREATE_PYTHON_BINDINGS

// include pybind11 headers
#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"

namespace py = pybind11;

#include "CustomStructuralModel.hpp"

// Create python bindings for the CustomStructuralModel class and its functionality
void exposeCustomStructuralModel(py::module& m) {

	/* Since the SBStructuralModel class is based on the SBStructuralModel class,
	 * you do not need to create python bindings for functionality of the SBStructuralModel class,
	 * because they are already exposed thanks to the Python Scripting Element.
	 */
	py::class_<CustomStructuralModel,
			std::unique_ptr<CustomStructuralModel, py::nodelete>,
			SBStructuralModel> c(m, "CustomStructuralModel",
								 R"(This class describes a custom structural model from SEPyBindTutorial Element)");

	// constructors

	c.def(py::init<>(), "Constructs a custom structural model");

	// functions

	c.def_property_readonly("hasCustomComment", &CustomStructuralModel::hasCustomComment, "Returns true when the custom model's custom comment is set");
	c.def_property("customComment", &CustomStructuralModel::getCustomComment, &CustomStructuralModel::setCustomComment, "A custom comment");
	c.def("clearCustomComment", &CustomStructuralModel::clearCustomComment, "Clears the custom comment");

}

#endif
