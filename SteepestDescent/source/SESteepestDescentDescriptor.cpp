/// \headerfile SESteepestDescentStateUpdaterDescriptor.hpp "SESteepestDescentStateUpdaterDescriptor.hpp"
#include "SESteepestDescentStateUpdaterDescriptor.hpp"

/// \headerfile SESteepestDescentStateUpdaterPropertiesDescriptor.hpp "SESteepestDescentStateUpdaterPropertiesDescriptor.hpp"
#include "SESteepestDescentStateUpdaterPropertiesDescriptor.hpp"



// Describe the SAMSON Element

// SAMSON Element generator pro tip: modify the information below if necessary
// (for example when a new class is added, when the version number changes, to describe categories more precisely, etc.)

SB_ELEMENT_DESCRIPTION("This SAMSON Element implements the steepest descent state updater.");
SB_ELEMENT_DOCUMENTATION("Resource/Documentation/doc.html");
SB_ELEMENT_VERSION_NUMBER("0.10.0");

SB_ELEMENT_CLASSES_BEGIN;

	SB_ELEMENT_CLASS(SESteepestDescentStateUpdater);
	SB_ELEMENT_CLASS(SESteepestDescentStateUpdaterProperties);

SB_ELEMENT_CLASSES_END;

SB_ELEMENT_CATEGORIES_BEGIN;

	SB_ELEMENT_CATEGORY(SBClass::Category::General);

SB_ELEMENT_CATEGORIES_END;
