/// \headerfile SAMSON.hpp "SAMSON.hpp"
#include "SAMSON.hpp"

/// \headerfile SEBarycenterApp.hpp "SEBarycenterApp.hpp"
#include "SEBarycenterApp.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEBarycenterApp);

	SB_CLASS_TYPE(SBCClass::App);
	SB_CLASS_DESCRIPTION("DevTutorial: Barycenter");
	SB_CLASS_PUBLIC_NAME("DevTutorial: Barycenter");
	SB_CLASS_GUI_UUID("8E7E1027-BDF6-0E28-1B1E-C5095602C7DF");
	SB_CLASS_GUI_SHORTCUT("");
	SB_CLASS_ICON_FILE_NAME(SB_ELEMENT_PATH + "/Resource/icons/SEBarycenterAppIcon.png");
	SB_CLASS_TOOL_TIP("<b>DevTutorial: Barycenter</b><br/><br/>SAMSON Extension generator pro tip: modify the tooltip.");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEBarycenterApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEBarycenterApp);

