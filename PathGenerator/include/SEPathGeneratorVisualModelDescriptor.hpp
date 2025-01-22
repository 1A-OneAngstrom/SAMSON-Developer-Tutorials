/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEPathGeneratorVisualModel.hpp "SEPathGeneratorVisualModel.hpp"
#include "SEPathGeneratorVisualModel.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEPathGeneratorVisualModel);

	SB_CLASS_TYPE(SBCClass::VisualModel);
	SB_CLASS_DESCRIPTION("SEPathGeneratorVisualModel : SAMSON Extension generator pro tip: modify me");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEPathGeneratorVisualModel);
		SB_CONSTRUCTOR_1(SEPathGeneratorVisualModel, const SBNodeIndexer&);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEPathGeneratorVisualModel);

