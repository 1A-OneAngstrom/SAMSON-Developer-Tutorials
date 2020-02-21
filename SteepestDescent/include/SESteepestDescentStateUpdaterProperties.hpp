#pragma once


#include "SBGDataGraphNodeProperties.hpp" 
#include "ui_SESteepestDescentStateUpdaterProperties.h"
#include "SBPointer.hpp"
#include "SESteepestDescentStateUpdater.hpp"


/// This class implements the property window of the state updater

// SAMSON Element generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SESteepestDescentStateUpdater class

class SESteepestDescentStateUpdaterProperties : public SBGDataGraphNodeProperties {

	SB_CLASS
	Q_OBJECT

public:

	SESteepestDescentStateUpdaterProperties();
	virtual ~SESteepestDescentStateUpdaterProperties();

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const;														///< Returns the widget UUID
	virtual int													getFormat() const;														///< Returns the widget name (used as a title for the embedding window)
	virtual QString												getName() const;														///< Returns the widget logo
	virtual QPixmap												getLogo() const;														///< Returns the widget format
	virtual QString												getCitation() const;													///< Returns the citation information

	//@}

	///\name Settings
	//@{

	void														loadSettings(SBGSettings *setting);										///< Loads GUI settings
	void														saveSettings(SBGSettings *setting);										///< Saves GUI settings

	//@}
	
	///\name Setup
	//@{

	virtual bool												setup();																///< Initializes the properties widget
	virtual bool												setup(SBNode* node);													///< Initializes the properties widget

	//@}

	class Observer : public SBCReferenceTarget {

		Observer(SESteepestDescentStateUpdaterProperties* properties);
		virtual ~Observer();

		friend class SESteepestDescentStateUpdaterProperties;

		void														onBaseEvent(SBBaseEvent* baseEvent);									///< Base event management
		void														onStateUpdaterEvent(SBStateUpdaterEvent* stateUpdaterEvent);			///< State updater event management

		SESteepestDescentStateUpdaterProperties* properties;

	};

	public slots:

	void														onStepsChanged(int);
	void														onStepSizeChanged(double);

private:

	friend class SESteepestDescentStateUpdater;

	Ui::SESteepestDescentStateUpdaterPropertiesClass			ui;
	SBPointer<SESteepestDescentStateUpdater>					stateUpdater;

	SBPointer<Observer>											observer;

};

SB_REGISTER_TYPE(SESteepestDescentStateUpdaterProperties, "SESteepestDescentStateUpdaterProperties", "7D8E9B73-2A5E-0E92-07DB-B84783E6AC90");
SB_DECLARE_BASE_TYPE(SESteepestDescentStateUpdaterProperties, SBGDataGraphNodeProperties);
