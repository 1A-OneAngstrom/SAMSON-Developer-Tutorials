/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SECenterOfMassApp.hpp "SECenterOfMassApp.hpp"
#include "SECenterOfMassApp.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SECenterOfMassApp);

	SB_CLASS_TYPE(SBCClass::App);
	SB_CLASS_DESCRIPTION("DevTutorial: Center of mass");
	SB_CLASS_PUBLIC_NAME("DevTutorial: Center of mass");
	SB_CLASS_TOOL_TIP("DevTutorial: Center of mass tooltip.");
	SB_CLASS_GUI_UUID("9E140A22-134A-8C41-EDB5-57D896016345");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SECenterOfMassApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SECenterOfMassApp);

