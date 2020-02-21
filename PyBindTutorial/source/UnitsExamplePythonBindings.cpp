#ifdef CREATE_PYTHON_BINDINGS

// include pybind11 headers
#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"

namespace py = pybind11;

#include "UnitsExample.hpp"

// include headers with wrappers for SBQuantity, SBType* for use in Python
#include "SBDQuantityWrapper.hpp"
#include "SBDTypePhysicalVector3Wrapper.hpp"
#include "SBDTypePhysicalVector6Wrapper.hpp"
#include "SBDTypePhysicalIntervalWrapper.hpp"
#include "SBDTypePhysicalIAVector3Wrapper.hpp"
#include "SBDTypePhysicalMatrix33Wrapper.hpp"
#include "SBDTypePhysicalMatrix66Wrapper.hpp"
#include "SBDTypeSpatialDomainWrapper.hpp"
#include "SBDTypeSpatialTransformWrapper.hpp"
#include "SBDToolsConvert.hpp"

namespace UnitsExample_pybind_namespace {

SBDQuantityWrapper<SBUnitSystemSI> getDimensionlessWrapper(UnitsExample& obj) {

	// create a SBDQuantityWrapper<SBUnitSystemSI> object from SBQuantity and return it
	return SBDQuantityWrapper<SBUnitSystemSI>(obj.getDimensionless());

}

void setDimensionlessWrapper(UnitsExample& obj, SBDQuantityWrapper<SBUnitSystemSI>& u) {

	// create a SBQuantity object from SBDQuantityWrapper and pass it into a specific function
	obj.setDimensionless( getSBQuantity<SBQuantity::dimensionless>(u) );

}

SBQuantityWrapperSI getLengthWrapper(UnitsExample& obj) {

	// create a SBDQuantityWrapper<SBUnitSystemSI> object from SBQuantity and return it
	return SBQuantityWrapperSI(obj.getLength());

}

void setLengthWrapper(UnitsExample& obj, SBQuantityWrapperSI& u) {

	// create a SBQuantity object from SBDQuantityWrapper and pass it into a specific function
	obj.setLength( getSBQuantity<SBQuantity::length>(u) );

}

SBQuantityWrapperSI getMassWrapper(UnitsExample& obj) {

	// create a SBDQuantityWrapper<SBUnitSystemSI> object from SBQuantity and return it
	return SBQuantityWrapperSI(obj.getMass());

}

void setMassWrapper(UnitsExample& obj, SBQuantityWrapperSI& u) {

	// create a SBQuantity object from SBDQuantityWrapper and pass it into a specific function
	obj.setMass( getSBQuantity<SBQuantity::mass>(u) );

}

SBDQuantityWrapper<SBUnitSystemAU> getAuMassWrapper(UnitsExample& obj) {

	// create a SBDQuantityWrapper<SBUnitSystemAU> object from SBQuantity and return it
	return SBDQuantityWrapper<SBUnitSystemAU>(obj.getAuMass());

}

void setAuMassWrapper(UnitsExample& obj, SBDQuantityWrapper<SBUnitSystemAU>& u) {

	// create a SBQuantity object from SBDQuantityWrapper and pass it into a specific function
	obj.setAuMass( getSBQuantity<SBQuantity::auMass>(u) );

}

SBDQuantityWrapper<SBUnitSystemDalton> getDaltonWrapper(UnitsExample& obj) {

	// create a SBDQuantityWrapper<SBUnitSystemDalton> object from SBQuantity and return it
	return SBDQuantityWrapper<SBUnitSystemDalton>(obj.getDalton());

}

void setDaltonWrapper(UnitsExample& obj, SBDQuantityWrapper<SBUnitSystemDalton>& u) {

	// create a SBQuantity object from SBDQuantityWrapper and pass it into a specific function
	obj.setDalton( getSBQuantity<SBQuantity::dalton>(u) );

}

SBDQuantityWrapper<SBUnitSystemElectronvolt> getEnergyEvWrapper(UnitsExample& obj) {

	// create a SBDQuantityWrapper<SBUnitSystemElectronvolt> object from SBQuantity and return it
	return SBDQuantityWrapper<SBUnitSystemElectronvolt>(obj.getEnergyEv());

}

void setEnergyEvWrapper(UnitsExample& obj, SBDQuantityWrapper<SBUnitSystemElectronvolt>& u) {

	// create a SBQuantity object from SBDQuantityWrapper and pass it into a specific function
	obj.setEnergyEv( getSBQuantity<SBQuantity::electronvolt>(u) );

}

SBDQuantityWrapper<SBUnitSystemKilocaloriePerMole> getEnergyKcalPerMolWrapper(UnitsExample& obj) {

	// create a SBDQuantityWrapper<SBUnitSystemKilocaloriePerMole> object from SBQuantity and return it
	return SBDQuantityWrapper<SBUnitSystemKilocaloriePerMole>(obj.getEnergyKcalPerMol());

}

void setEnergyKcalPerMolWrapper(UnitsExample& obj, SBDQuantityWrapper<SBUnitSystemKilocaloriePerMole>& u) {

	// create a SBQuantity object from SBDQuantityWrapper and pass it into a specific function
	obj.setEnergyKcalPerMol( getSBQuantity<SBQuantity::kcalPerMol>(u) );

}

SBPhysicalVector3WrapperSI getVector3Wrapper(UnitsExample& obj) {

	// create a SBDTypePhysicalVector3Wrapper<SBUnitSystemSI> object from SBDTypePhysicalVector3 and return it
	return SBPhysicalVector3WrapperSI(obj.getVector3());

}

void setVector3Wrapper(UnitsExample& obj, SBPhysicalVector3WrapperSI& u) {

	// create a SBDTypePhysicalVector3 object from SBDTypePhysicalVector3Wrapper and pass it into a specific function
	obj.setVector3( getSBPhysicalVector3<SBQuantity::dimensionless>(u) );

}

SBPhysicalVector3WrapperSI getPosition3Wrapper(UnitsExample& obj) {

	// create a SBDTypePhysicalVector3Wrapper<SBUnitSystemSI> object from SBDTypePhysicalVector3 and return it
	return SBPhysicalVector3WrapperSI(obj.getPosition3());

}

void setPosition3Wrapper(UnitsExample& obj, SBPhysicalVector3WrapperSI& u) {

	// create a SBDTypePhysicalVector3 object from SBDTypePhysicalVector3Wrapper and pass it into a specific function
	obj.setPosition3( getSBPhysicalVector3<SBQuantity::position>(u) );

}

SBPhysicalVector6WrapperSI getVelocity6Wrapper(UnitsExample& obj) {

	// create a SBPhysicalVector6WrapperSI object from SBDTypePhysicalVector6 and return it
	return SBPhysicalVector6WrapperSI(obj.getVelocity6());

}

void setVelocity6Wrapper(UnitsExample& obj, SBPhysicalVector6WrapperSI& u) {

	// create a SBDTypePhysicalVector6 object from SBPhysicalVector6WrapperSI and pass it into a specific function
	obj.setVelocity6( getSBPhysicalVector6<SBQuantity::inverseTime, SBQuantity::velocity>(u) );

}

SBPhysicalIntervalWrapperSI getLengthIntervalWrapper(UnitsExample& obj) {

	// create a SBPhysicalIntervalWrapperSI object from SBDTypePhysicalInterval and return it
	return SBPhysicalIntervalWrapperSI(obj.getLengthInterval());

}

void setLengthIntervalWrapper(UnitsExample& obj, SBPhysicalIntervalWrapperSI& u) {

	// create a SBDTypePhysicalInterval object from SBDTypePhysicalIntervalWrapper and pass it into a specific function
	obj.setLengthInterval( getSBPhysicalInterval<SBQuantity::length>(u) );

}

SBPhysicalIAVector3WrapperSI getForceInterval3Wrapper(UnitsExample& obj) {

	return SBPhysicalIAVector3WrapperSI(obj.getForceInterval3());

}

void setForceInterval3Wrapper(UnitsExample& obj, SBPhysicalIAVector3WrapperSI& u) {

	obj.setForceInterval3( getSBPhysicalIAVector3<SBQuantity::nanonewton>(u) );

}

SBPhysicalMatrix33WrapperSI getInverseMass33Wrapper(UnitsExample& obj) {

	return SBPhysicalMatrix33WrapperSI(obj.getInverseMass33());

}

void setInverseMass33Wrapper(UnitsExample& obj, SBPhysicalMatrix33WrapperSI& u) {

	obj.setInverseMass33( getSBPhysicalMatrix33<SBQuantity::inverseMass>(u) );

}

SBPhysicalMatrix66WrapperSI getInertia66Wrapper(UnitsExample& obj) {

	return SBPhysicalMatrix66WrapperSI(obj.getInertia66());

}

void setInertia66Wrapper(UnitsExample& obj, SBPhysicalMatrix66WrapperSI& u) {

	obj.setInertia66( getSBPhysicalMatrix66<SBQuantity::momentOfInertia, SBQuantity::lengthMass, SBQuantity::lengthMass, SBQuantity::mass>(u) );

}

SBSpatialTransformWrapper getSpatialTransformWrapper(UnitsExample& obj) {

	return SBSpatialTransformWrapper(obj.getSpatialTransform());

}

void setSpatialTransformWrapper(UnitsExample& obj, SBSpatialTransformWrapper& u) {

	obj.setSpatialTransform( u.toSBSpatialTransform() );

}

}

// Create python bindings for the UnitsExample class and its functionality
void exposeUnitsExample(py::module& m) {

	using namespace UnitsExample_pybind_namespace;

	// The py::class_ creates bindings for a C++ class
	py::class_<
			UnitsExample									/* the class */
			>
			c(m,											/* pybind11::module */
			  "UnitsExample",								/* the class name in python*/
			  R"(An example of a class which has functions that return/receive SAMSON Units and Types)" /* docstring */
			  );

	// constructors

	c.def(py::init<>(), "Constructor");

	// functions

	/*
	 * Warning:
	 * Since there is no connection between a SBQuantityWrapper object and a SBQuantity object that it wraps (the same for SBPhysicalVector3Wrapper, etc),
	 * getter and setter functions for SBQuantityWrapper, SBPhysicalVector3Wrapper, etc, should not be exposed to Python as an attribute via 'def_property()'
	 * but as functions via 'def()'
	 * But you may expose getter functions as read-only attributes via 'def_property_readonly'
	 */

	/* Example bindings for functions that return/receive SBQuantity units
	 * SBQuantity provides you with several different unit systems:
	 * SI, Dalton, AU, Electronvolt, KilocaloriePerMole
	 */
	c.def("getDimensionless", &getDimensionlessWrapper);
	c.def("setDimensionless", &setDimensionlessWrapper);
	c.def("getLength", &getLengthWrapper);
	c.def("setLength", &setLengthWrapper);
	c.def("getMass", &getMassWrapper);
	c.def("setMass", &setMassWrapper);

	c.def("getAuMass", &getAuMassWrapper);
	c.def("setAuMass", &setAuMassWrapper);

	c.def("getDalton", &getDaltonWrapper);
	c.def("setDalton", &setDaltonWrapper);

	c.def("getEnergyEv", &getEnergyEvWrapper);
	c.def("setEnergyEv", &setEnergyEvWrapper);

	c.def("getEnergyKcalPerMol", &getEnergyKcalPerMolWrapper);
	c.def("setEnergyKcalPerMol", &setEnergyKcalPerMolWrapper);

	/* Example bindings for functions that return/receive SBVector3 objects
	 * Here we show SBVector3 objects only for SI units, for other units it can be done in the same way
	 */
	c.def("getVector3", &getVector3Wrapper);
	c.def("setVector3", &setVector3Wrapper);

	c.def("getPosition3", &getPosition3Wrapper);
	c.def("setPosition3", &setPosition3Wrapper);

	/* Example bindings for functions that return/receive SBVector6 objects
	 * Here we show SBVector6 objects only for SI units, for other units it can be done in the same way
	 */
	c.def("getVelocity6", &getVelocity6Wrapper);
	c.def("setVelocity6", &setVelocity6Wrapper);

	/* Example bindings for functions that return/receive SBPhysicalInterval objects
	 * Here we show SBPhysicalInterval objects only for SI units, for other units it can be done in the same way
	 */
	c.def("getLengthInterval", &getLengthIntervalWrapper);
	c.def("setLengthInterval", &setLengthIntervalWrapper);

	/* Example bindings for functions that return/receive SBDTypePhysicalIAVector3 objects
	 * Here we show SBDTypePhysicalIAVector3 objects only for SI units, for other units it can be done in the same way
	 */
	c.def("getForceInterval3", &getForceInterval3Wrapper);
	c.def("setForceInterval3", &setForceInterval3Wrapper);

	/* Example bindings for functions that return/receive SBDTypePhysicalMatrix33 objects
	 * Here we show SBDTypePhysicalMatrix33 objects only for SI units, for other units it can be done in the same way
	 */
	c.def("getInverseMass33", &getInverseMass33Wrapper);
	c.def("setInverseMass33", &setInverseMass33Wrapper);

	/* Example bindings for functions that return/receive SBDTypePhysicalMatrix66 objects
	 * Here we show SBDTypePhysicalMatrix66 objects only for SI units, for other units it can be done in the same way
	 */
	c.def("getInertia66", &getInertia66Wrapper);
	c.def("setInertia66", &setInertia66Wrapper);

	/* Example bindings for functions that return/receive SBSpatialTransform objects
	 */
	c.def("getSpatialTransform", &getSpatialTransformWrapper);
	c.def("setSpatialTransform", &setSpatialTransformWrapper);

}

#endif // CREATE_PYTHON_BINDINGS
