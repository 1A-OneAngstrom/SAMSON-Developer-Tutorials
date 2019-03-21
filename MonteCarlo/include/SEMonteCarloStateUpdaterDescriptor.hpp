/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEMonteCarloStateUpdater.hpp "SEMonteCarloStateUpdater.hpp"
#include "SEMonteCarloStateUpdater.hpp"


// Class descriptor

// SAMSON Element generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Elements

SB_CLASS_BEGIN(SEMonteCarloStateUpdater);

	SB_CLASS_TYPE(SBCClass::StateUpdaterParticleSystem);
	SB_CLASS_DESCRIPTION("DevTutorial: Monte Carlo");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_2(SEMonteCarloStateUpdater, SBParticleSystem*, SBMInteractionModelParticleSystem*);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEMonteCarloStateUpdater);

