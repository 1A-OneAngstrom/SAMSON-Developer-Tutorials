/// \headerfile SBProxy.hpp "SBProxy.hpp"
#include "SBProxy.hpp"

/// \headerfile SEEXYZImporter.hpp "SEEXYZImporter.hpp"
#include "SEEXYZImporter.hpp"


// Class descriptor

// SAMSON Extension generator pro tip: complete this descriptor to expose this class to SAMSON and other SAMSON Extensions

SB_CLASS_BEGIN(SEEXYZImporter);

	SB_CLASS_TYPE(SBCClass::Importer);
	SB_CLASS_DESCRIPTION("SAMSON Developer tutorials: EXYZ Importer");

	SB_FACTORY_BEGIN;

		SB_CONSTRUCTOR_0(SEEXYZImporter);

	SB_FACTORY_END;

	SB_INTERFACE_BEGIN;

	SB_INTERFACE_END;

SB_CLASS_END(SEEXYZImporter);

