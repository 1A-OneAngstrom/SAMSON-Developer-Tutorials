#pragma once


#include "SBGDataGraphNodeProperties.hpp" 
#include "ui_SESpringsInteractionModelProperties.h"
#include "SBPointer.hpp"
#include "SESpringsInteractionModel.hpp"


/// This class implements the GUI of the interaction model

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SESpringsInteractionModel class

class SB_EXPORT SESpringsInteractionModelProperties : public SBGDataGraphNodeProperties {

	SB_CLASS
	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SESpringsInteractionModelProperties();																								///< Constructs a widget to show the properties of the interaction model
	virtual ~SESpringsInteractionModelProperties();																						///< Destructs the widget

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

		Observer(SESpringsInteractionModelProperties* properties);
		virtual ~Observer();

		friend class SESpringsInteractionModelProperties;

		void														onBaseEvent(SBBaseEvent* baseEvent);									///< Base event management
		void														onInteractionEvent(SBInteractionEvent* interactionEvent);				///< Interaction event management

		SESpringsInteractionModelProperties* properties;

	};

public slots:

	void														onBondSpringStiffnessChanged(double);									///< Change the bond spring stiffness
	void														onResetSpringsClicked();												///< Reset the spring model to the current conformation

private:

	friend class SESpringsInteractionModel;
	Ui::SESpringsInteractionModelPropertiesClass				ui;
	SBPointer<SESpringsInteractionModel>						interactionModel;

	void														updateEnergies();
	SBPointer<Observer>											observer;

};

SB_REGISTER_TYPE(SESpringsInteractionModelProperties, "SESpringsInteractionModelProperties", "FAACD9E7-B389-245A-276B-922FE8B78954");
SB_DECLARE_BASE_TYPE(SESpringsInteractionModelProperties, SBGDataGraphNodeProperties);
