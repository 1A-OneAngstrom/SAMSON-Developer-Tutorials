/// \headerfile SAMSON.hpp "SAMSON.hpp"
#include "SAMSON.hpp"

/// \headerfile SEPyBindTutorialApp.hpp "SEPyBindTutorialApp.hpp"
#include "SEPyBindTutorialApp.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEPyBindTutorialApp);

	SB_CLASS_TYPE(SBCClass::App);
	SB_CLASS_DESCRIPTION("SEPyBindTutorialApp : an App from the Tutorial on creation of python bindings");
	SB_CLASS_PUBLIC_NAME("DevTutorial: SEPyBindTutorialApp");
	SB_CLASS_TOOL_TIP("");
	SB_CLASS_GUI_UUID("773131DA-41CF-B5D1-E97D-70C9EAD9EADE");
	SB_CLASS_ICON_FILE_NAME(SB_ELEMENT_PATH + "/Resource/icons/SEPyBindTutorialAppIcon.png");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEPyBindTutorialApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEPyBindTutorialApp);
