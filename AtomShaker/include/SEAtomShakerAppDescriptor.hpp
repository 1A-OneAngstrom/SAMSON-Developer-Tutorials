/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEAtomShakerApp.hpp "SEAtomShakerApp.hpp"
#include "SEAtomShakerApp.hpp"


// Class descriptor

// SAMSON Element generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Elements

SB_CLASS_BEGIN(SEAtomShakerApp);

	SB_CLASS_TYPE(SBCClass::App);
	SB_CLASS_DESCRIPTION("DevTutorial: Atom shaker");
	SB_CLASS_VERSION_NUMBER("0.10.0");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEAtomShakerApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEAtomShakerApp);

