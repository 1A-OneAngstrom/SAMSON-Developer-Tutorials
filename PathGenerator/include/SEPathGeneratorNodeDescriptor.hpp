/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEPathGeneratorNode.hpp "SEPathGeneratorNode.hpp"
#include "SEPathGeneratorNode.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEPathGeneratorNode);

	SB_CLASS_TYPE(SBCClass::Custom);
	SB_CLASS_DESCRIPTION("SEPathGeneratorNode : SAMSON Extension generator pro tip: modify me");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_1(SEPathGeneratorNode, const SBPosition3&);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEPathGeneratorNode);

