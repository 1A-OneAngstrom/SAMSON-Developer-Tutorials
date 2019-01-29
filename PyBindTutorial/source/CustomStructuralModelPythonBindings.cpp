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

	// The py::class_ creates bindings for a C++ class
	py::class_<
			CustomStructuralModel,									/* the class */
			std::unique_ptr<CustomStructuralModel, py::nodelete>,	/* the class type */
			SBStructuralModel										/* the base class */
			>
			c(m,													/* pybind11::module */
			  "CustomStructuralModel",								/* the class name in python*/
			  R"(This class describes a custom structural model from SEPyBindTutorial Element)" /* the docstring */
			  );

	// constructors

	c.def(py::init<>(), "Constructs a custom structural model");

	// attributes

	// read-only attributes
	c.def_property_readonly("hasCustomComment", &CustomStructuralModel::hasCustomComment, "Returns true when the custom model's custom comment is set");
	// read-and-write attributes
	c.def_property("customComment", &CustomStructuralModel::getCustomComment, &CustomStructuralModel::setCustomComment, "A custom comment");

	// functions

	c.def("clearCustomComment", &CustomStructuralModel::clearCustomComment, "Clears the custom comment");

}

#endif // CREATE_PYTHON_BINDINGS
