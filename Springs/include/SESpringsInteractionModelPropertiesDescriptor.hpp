/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SESpringsInteractionModelProperties.hpp "SESpringsInteractionModelProperties.hpp"
#include "SESpringsInteractionModelProperties.hpp"


// Class descriptor

// SAMSON Element generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Elements

SB_CLASS_BEGIN(SESpringsInteractionModelProperties);

	SB_CLASS_TYPE(SBCClass::Properties);
	SB_CLASS_DESCRIPTION("DevTutorial: Springs");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SESpringsInteractionModelProperties);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SESpringsInteractionModelProperties);

