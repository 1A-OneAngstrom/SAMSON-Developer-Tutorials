/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEPyBindTutorialApp.hpp "SEPyBindTutorialApp.hpp"
#include "SEPyBindTutorialApp.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEPyBindTutorialApp);

	SB_CLASS_TYPE(SBCClass::App);
		SB_CLASS_DESCRIPTION("SEPyBindTutorialApp : an App from the Tutorial on creation of python bindings");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEPyBindTutorialApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEPyBindTutorialApp);
