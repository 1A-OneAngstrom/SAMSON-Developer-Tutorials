#pragma once


#include "SBGDataGraphNodeProperties.hpp" 
#include "ui_SEPathGeneratorVisualModelProperties.h"
#include "SBPointer.hpp"
#include "SEPathGeneratorVisualModel.hpp"


/// This class implements the property window of the visual model

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEPathGeneratorVisualModel class

// SAMSON Extension generator pro tip: if you do not want to have a property window associated to your visual model, do not expose it in the descriptor. 
// Precisely, remove the line SB_ELEMENT_CLASS(SEPathGeneratorVisualModelProperties); from the file SEPathGeneratorDescriptor.cpp

class SB_EXPORT SEPathGeneratorVisualModelProperties : public SBGDataGraphNodeProperties {

	SB_CLASS
	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEPathGeneratorVisualModelProperties();																								///< Constructs a widget to show the properties of the visual model
	virtual ~SEPathGeneratorVisualModelProperties();																						///< Destructs the widget

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const override;												///< Returns the widget UUID
	virtual QString												getName() const override;												///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const override;												///< Returns the widget logo
	virtual int													getFormat() const override;												///< Returns the widget format
	virtual QString												getCitation() const override;											///< Returns the citation information

	//@}

	///\name Settings
	//@{

	virtual void												loadSettings(SBGSettings* setting) override;							///< Loads \p settings
	virtual void												saveSettings(SBGSettings* setting) override;							///< Saves \p settings

	//@}

	///\name Setup
	//@{

	virtual bool												setup() override;														///< Initializes the properties widget
	virtual bool												setup(SBNode* node) override;											///< Initializes the properties widget

	//@}

	class Observer : public SBCReferenceTarget {

		Observer(SEPathGeneratorVisualModelProperties* properties);
		virtual ~Observer();

		friend class SEPathGeneratorVisualModelProperties;

		void														onBaseEvent(SBBaseEvent* baseEvent);								///< Base event management
		void														onVisualEvent(SBVisualEvent* visualEvent);							///< Visual event management

		SEPathGeneratorVisualModelProperties* properties;

	};

private:

	friend class SEPathGeneratorVisualModel;
	Ui::SEPathGeneratorVisualModelPropertiesClass							ui;
	SBPointer<SEPathGeneratorVisualModel>									visualModel;

	SBPointer<Observer>											observer;

};

SB_REGISTER_TYPE(SEPathGeneratorVisualModelProperties, "SEPathGeneratorVisualModelProperties", "91D7BB5A-21B9-D0B5-A78A-A4039A7A2F7D");
SB_DECLARE_BASE_TYPE(SEPathGeneratorVisualModelProperties, SBGDataGraphNodeProperties);
