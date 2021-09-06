/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SESpringsInteractionModel.hpp "SESpringsInteractionModel.hpp"
#include "SESpringsInteractionModel.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SESpringsInteractionModel);

	SB_CLASS_TYPE(SBCClass::InteractionModelParticleSystem);
	SB_CLASS_DESCRIPTION("DevTutorial: Springs");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SESpringsInteractionModel);
		SB_CONSTRUCTOR_1(SESpringsInteractionModel, SBParticleSystem*);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SESpringsInteractionModel);

