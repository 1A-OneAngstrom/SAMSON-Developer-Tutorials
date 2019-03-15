/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEVanDerWaalsVisualModel.hpp "SEVanDerWaalsVisualModel.hpp"
#include "SEVanDerWaalsVisualModel.hpp"


// Class descriptor

// SAMSON Element generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Elements

SB_CLASS_BEGIN(SEVanDerWaalsVisualModel);

	SB_CLASS_TYPE(SBCClass::VisualModel);
	SB_CLASS_DESCRIPTION("Dev tutorial: Van der Waals visual model");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEVanDerWaalsVisualModel);
		SB_CONSTRUCTOR_1(SEVanDerWaalsVisualModel, const SBNodeIndexer&);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

		SB_ATTRIBUTE_READ_WRITE(const float&, SEVanDerWaalsVisualModel, RadiusFactor, "Radius factor", "Geometry");

	SB_INTERFACE_END;

SB_CLASS_END(SEVanDerWaalsVisualModel);

