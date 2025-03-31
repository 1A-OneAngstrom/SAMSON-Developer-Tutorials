#pragma once


#include "SBGDataGraphNodeProperties.hpp" 
#include "ui_SEMonteCarloStateUpdaterProperties.h"
#include "SBPointer.hpp"
#include "SEMonteCarloStateUpdater.hpp"


/// This class implements the property window of the state updater

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEMonteCarloStateUpdater class

class SB_EXPORT SEMonteCarloStateUpdaterProperties : public SBGDataGraphNodeProperties {

	SB_CLASS
	Q_OBJECT

public:

	SEMonteCarloStateUpdaterProperties();
	virtual ~SEMonteCarloStateUpdaterProperties();

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const override;												///< Returns the widget UUID
	virtual int													getFormat() const override;												///< Returns the widget name (used as a title for the embedding window)
	virtual QString												getName() const override;												///< Returns the widget logo
	virtual QPixmap												getLogo() const override;												///< Returns the widget format
	virtual QString												getCitation() const override;											///< Returns the citation information

	//@}

	///\name Settings
	//@{

	virtual void												loadSettings(SBGSettings *setting) override;							///< Loads GUI settings
	virtual void												saveSettings(SBGSettings* setting) override;							///< Saves GUI settings

	//@}
	
	///\name Setup
	//@{

	virtual bool												setup() override;														///< Initializes the properties widget
	virtual bool												setup(SBNode* node) override;											///< Initializes the properties widget

	//@}

	class Observer : public SBCReferenceTarget {

		Observer(SEMonteCarloStateUpdaterProperties* properties);
		virtual ~Observer();

		friend class SEMonteCarloStateUpdaterProperties;

		void														onBaseEvent(SBBaseEvent* baseEvent);									///< Base event management
		void														onStateUpdaterEvent(SBStateUpdaterEvent* stateUpdaterEvent);			///< State updater event management

		SEMonteCarloStateUpdaterProperties*							properties;

	};

public slots:

	void														onStepsChanged(int);
	void														onStepSizeChanged(double);

	void														onNumberOfMovingParticlesChanged(int);
	void														onTemperatureChanged(double);

private:

	friend class SEMonteCarloStateUpdater;

	Ui::SEMonteCarloStateUpdaterPropertiesClass					ui;
	SBPointer<SEMonteCarloStateUpdater>							stateUpdater;

	SBPointer<Observer>											observer;

};

SB_REGISTER_TYPE(SEMonteCarloStateUpdaterProperties, "SEMonteCarloStateUpdaterProperties", "BBC696BD-CF12-B881-CC76-BA8CE4945BB2");
SB_DECLARE_BASE_TYPE(SEMonteCarloStateUpdaterProperties, SBGDataGraphNodeProperties);
