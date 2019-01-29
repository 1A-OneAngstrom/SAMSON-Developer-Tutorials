#ifdef CREATE_PYTHON_BINDINGS

// include pybind11 headers
#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"

namespace py = pybind11;

#include "CustomStructuralGroup.hpp"

// create python bindings for the CustomStructuralGroup class and its functionality
void exposeCustomStructuralGroup(py::module& m) {

	/* Since the CustomStructuralGroup class is based on the CustomStructuralGroup class,
	 * you do not need to create python bindings for functionality of the CustomStructuralGroup class,
	 * because they are already exposed thanks to the Python Scripting Element.
	 */
	py::class_<CustomStructuralGroup,
			std::unique_ptr<CustomStructuralGroup, py::nodelete>,
			SBStructuralGroup> c(m, "CustomStructuralGroup",
								 R"(This class describes a custom structural group from SEPyBindTutorial Element)");

	// constructors

	c.def(py::init<>(), "Constructs a custom structural group");
	c.def(py::init<std::string&>(), "Constructs a custom structural group with the given name");

	// attributes

	c.def_property_readonly("hasCustomComment", &CustomStructuralGroup::hasCustomComment, "Returns true when the custom group's custom comment is set");
	c.def_property("customComment", &CustomStructuralGroup::getCustomComment, &CustomStructuralGroup::setCustomComment, "A custom comment");

	// functions

	c.def("clearCustomComment", &CustomStructuralGroup::clearCustomComment, "Clears the custom comment");

}

#endif // CREATE_PYTHON_BINDINGS
