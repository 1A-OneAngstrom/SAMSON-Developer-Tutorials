/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEEXYZExporter.hpp "SEEXYZExporter.hpp"
#include "SEEXYZExporter.hpp"


// Class descriptor

// SAMSON Element generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Elements

SB_CLASS_BEGIN(SEEXYZExporter);

	SB_CLASS_TYPE(SBCClass::Exporter);
		SB_CLASS_DESCRIPTION("SAMSON Developer tutorials: EXYZ Exporter");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEEXYZExporter);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEEXYZExporter);

