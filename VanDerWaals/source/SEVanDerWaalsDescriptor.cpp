/// \headerfile SEVanDerWaalsVisualModelDescriptor.hpp "SEVanDerWaalsVisualModelDescriptor.hpp"
#include "SEVanDerWaalsVisualModelDescriptor.hpp"

/// \headerfile SEVanDerWaalsVisualModelPropertiesDescriptor.hpp "SEVanDerWaalsVisualModelPropertiesDescriptor.hpp"
#include "SEVanDerWaalsVisualModelPropertiesDescriptor.hpp"



// Describe the SAMSON Element

// SAMSON Element generator pro tip: modify the information below if necessary
// (for example when a new class is added, when the version number changes, to describe categories more precisely, etc.)

SB_ELEMENT_DESCRIPTION("This SAMSON Element demonstrates Van der Waals visual model.");
SB_ELEMENT_DOCUMENTATION("Resource/Documentation/doc.html");
SB_ELEMENT_VERSION_NUMBER("0.10.0");

SB_ELEMENT_CLASSES_BEGIN;

	SB_ELEMENT_CLASS(SEVanDerWaalsVisualModel);
	SB_ELEMENT_CLASS(SEVanDerWaalsVisualModelProperties);

SB_ELEMENT_CLASSES_END;

SB_ELEMENT_CATEGORIES_BEGIN;

	SB_ELEMENT_CATEGORY(SBClass::Category::Visualization);

SB_ELEMENT_CATEGORIES_END;
