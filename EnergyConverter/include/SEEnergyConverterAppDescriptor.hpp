/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEEnergyConverterApp.hpp "SEEnergyConverterApp.hpp"
#include "SEEnergyConverterApp.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEEnergyConverterApp);

	SB_CLASS_TYPE(SBCClass::App);

		SB_CLASS_DESCRIPTION("DevTutorial: Energy converter");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEEnergyConverterApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEEnergyConverterApp);

