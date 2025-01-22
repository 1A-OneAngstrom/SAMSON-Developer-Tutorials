/// \headerfile SAMSON.hpp "SAMSON.hpp"
#include "SAMSON.hpp"

/// \headerfile SEAtomShakerApp.hpp "SEAtomShakerApp.hpp"
#include "SEAtomShakerApp.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEAtomShakerApp);

	SB_CLASS_TYPE(SBCClass::App);
	SB_CLASS_DESCRIPTION("DevTutorial: Atom shaker");
	SB_CLASS_PUBLIC_NAME("DevTutorial: Atom shaker");
	SB_CLASS_TOOL_TIP("DevTutorial: Atom shaker tooltip.");
	SB_CLASS_GUI_UUID("8B972823-F315-E2BF-2D51-9AE1DD24F333");
	SB_CLASS_ICON_FILE_NAME(SB_ELEMENT_PATH + "/Resource/icons/SEAtomShakerAppIcon.png");
	SB_CLASS_VERSION_NUMBER("2.0.0");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEAtomShakerApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEAtomShakerApp);

