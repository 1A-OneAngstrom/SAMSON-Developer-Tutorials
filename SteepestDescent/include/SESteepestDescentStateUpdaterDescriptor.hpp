/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SESteepestDescentStateUpdater.hpp "SESteepestDescentStateUpdater.hpp"
#include "SESteepestDescentStateUpdater.hpp"


// Class descriptor

// SAMSON Element generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Elements

SB_CLASS_BEGIN(SESteepestDescentStateUpdater);

	SB_CLASS_TYPE(SBCClass::StateUpdaterParticleSystem);
	SB_CLASS_DESCRIPTION("DevTutorial: Steepest descent");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_2(SESteepestDescentStateUpdater, SBParticleSystem*, SBMInteractionModelParticleSystem*);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SESteepestDescentStateUpdater);

