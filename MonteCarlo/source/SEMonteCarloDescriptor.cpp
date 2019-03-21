/// \headerfile SEMonteCarloStateUpdaterDescriptor.hpp "SEMonteCarloStateUpdaterDescriptor.hpp"
#include "SEMonteCarloStateUpdaterDescriptor.hpp"

/// \headerfile SEMonteCarloStateUpdaterPropertiesDescriptor.hpp "SEMonteCarloStateUpdaterPropertiesDescriptor.hpp"
#include "SEMonteCarloStateUpdaterPropertiesDescriptor.hpp"



// Describe the SAMSON Element

// SAMSON Element generator pro tip: modify the information below if necessary
// (for example when a new class is added, when the version number changes, to describe categories more precisely, etc.)

SB_ELEMENT_DESCRIPTION("This SAMSON Element implements a Monte Carlo state updater.");
SB_ELEMENT_DOCUMENTATION("Resource/Documentation/doc.html");
SB_ELEMENT_VERSION_NUMBER("0.7.0");

SB_ELEMENT_CLASSES_BEGIN;

	SB_ELEMENT_CLASS(SEMonteCarloStateUpdater);
	SB_ELEMENT_CLASS(SEMonteCarloStateUpdaterProperties);

SB_ELEMENT_CLASSES_END;

SB_ELEMENT_CATEGORIES_BEGIN;

	SB_ELEMENT_CATEGORY(SBClass::Category::General);

SB_ELEMENT_CATEGORIES_END;
