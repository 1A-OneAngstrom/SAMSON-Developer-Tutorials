#pragma once


#include "SBGDataGraphNodeProperties.hpp" 
#include "ui_SEVanDerWaalsVisualModelProperties.h"
#include "SBPointer.hpp"
#include "SEVanDerWaalsVisualModel.hpp"


/// This class implements the property window of the visual model

// SAMSON Element generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEVanDerWaalsVisualModel class

// SAMSON Element generator pro tip: if you do not want to have a property window associated to you visual model, do not expose it in the descriptor. 
// Precisely, remove the line SB_ELEMENT_CLASS(SEVanDerWaalsVisualModelProperties); from the file SEVanDerWaalsDescriptor.cpp

class SEVanDerWaalsVisualModelProperties : public SBGDataGraphNodeProperties {

	SB_CLASS
	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEVanDerWaalsVisualModelProperties();																								///< Constructs a widget to show the properties of the visual model
	virtual ~SEVanDerWaalsVisualModelProperties();																						///< Destructs the widget

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const;														///< Returns the widget UUID
	virtual QString												getName() const;														///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const;														///< Returns the widget logo
	int															getFormat() const;														///< Returns the widget format
	virtual QString												getCitation() const;													///< Returns the citation information

	//@}

	///\name Settings
	//@{

	void														loadSettings(SBGSettings* settings);									///< Load GUI settings
	void														saveSettings(SBGSettings* settings);									///< Save GUI settings

	//@}

	///\name Setup
	//@{

	virtual bool												setup();																///< Initializes the properties widget
	virtual bool												setup(SBNode* node);													///< Initializes the properties widget

	//@}

	class Observer : public SBCReferenceTarget {

		Observer(SEVanDerWaalsVisualModelProperties* properties);
		virtual ~Observer();

		friend class SEVanDerWaalsVisualModelProperties;

		void														onBaseEvent(SBBaseEvent* baseEvent);								///< Base event management
		void														onVisualEvent(SBVisualEvent* visualEvent);							///< Visual event management

		SEVanDerWaalsVisualModelProperties* properties;

	};

public slots:

	/// \name Properties
	//@{

	void														onRadiusFactorChanged(double radiusFactor);

	//@}

private:

	friend class SEVanDerWaalsVisualModel;
	Ui::SEVanDerWaalsVisualModelPropertiesClass							ui;
	SBPointer<SEVanDerWaalsVisualModel>									visualModel;

	SBPointer<Observer>											observer;

};

SB_REGISTER_TYPE(SEVanDerWaalsVisualModelProperties, "SEVanDerWaalsVisualModelProperties", "391799D3-4EC0-7EAF-A89F-163FA57A34D6");
SB_DECLARE_BASE_TYPE(SEVanDerWaalsVisualModelProperties, SBGDataGraphNodeProperties);
