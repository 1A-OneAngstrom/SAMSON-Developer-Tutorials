/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEEnergyConverterApp.hpp "SEEnergyConverterApp.hpp"
#include "SEEnergyConverterApp.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEEnergyConverterApp);

	SB_CLASS_TYPE(SBCClass::App);
	SB_CLASS_DESCRIPTION("DevTutorial: Energy converter");
	SB_CLASS_PUBLIC_NAME("DevTutorial: Energy converter");
	SB_CLASS_TOOL_TIP("DevTutorial: Energy converter tooltip.");
	SB_CLASS_GUI_UUID("19EDF709-C04F-AF56-8B21-C0FC96B004E5");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEEnergyConverterApp);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEEnergyConverterApp);

