/// \headerfile SEPathGeneratorEditorDescriptor.hpp "SEPathGeneratorEditorDescriptor.hpp"
#include "SEPathGeneratorEditorDescriptor.hpp"

/// \headerfile SEPathGeneratorVisualModelDescriptor.hpp "SEPathGeneratorVisualModelDescriptor.hpp"
#include "SEPathGeneratorVisualModelDescriptor.hpp"

/// \headerfile SEPathGeneratorVisualModelPropertiesDescriptor.hpp "SEPathGeneratorVisualModelPropertiesDescriptor.hpp"
#include "SEPathGeneratorVisualModelPropertiesDescriptor.hpp"

/// \headerfile SEPathGeneratorNodeDescriptor.hpp "SEPathGeneratorNodeDescriptor.hpp"
#include "SEPathGeneratorNodeDescriptor.hpp"

/// \headerfile SEPathGeneratorNodeGUIDescriptor.hpp "SEPathGeneratorNodeGUIDescriptor.hpp"
#include "SEPathGeneratorNodeGUIDescriptor.hpp"

/// \headerfile SEPathGeneratorNodePropertiesDescriptor.hpp "SEPathGeneratorNodePropertiesDescriptor.hpp"
#include "SEPathGeneratorNodePropertiesDescriptor.hpp"



// Describe the SAMSON Extension

// SAMSON Extension generator pro tip: modify the information below if necessary
// (for example when a new class is added, when the version number changes, to describe categories more precisely, etc.)

SB_ELEMENT_DESCRIPTION("This extension demonstrates how to create and editor to create paths in the viewport.");
SB_ELEMENT_DOCUMENTATION("Resource/Documentation/doc.html");
SB_ELEMENT_VERSION_NUMBER("1.0.0");

SB_ELEMENT_CLASSES_BEGIN;

	SB_ELEMENT_CLASS(SEPathGeneratorEditor);
	//SB_ELEMENT_CLASS(SEPathGeneratorVisualModel);
	//SB_ELEMENT_CLASS(SEPathGeneratorVisualModelProperties);
	//SB_ELEMENT_CLASS(SEPathGeneratorNode);
	SB_ELEMENT_CLASS(SEPathGeneratorNodeGUI);
	//SB_ELEMENT_CLASS(SEPathGeneratorNodeProperties);

SB_ELEMENT_CLASSES_END;

SB_ELEMENT_CATEGORIES_BEGIN;

	SB_ELEMENT_CATEGORY(SBClass::Category::General);

SB_ELEMENT_CATEGORIES_END;
