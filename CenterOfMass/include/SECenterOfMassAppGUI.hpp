#pragma once


#include "SBGApp.hpp" 
#include "ui_SECenterOfMassAppGUI.h"
#include "SBVector3.hpp"

class SECenterOfMassApp;

/// This class implements the GUI of the app

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SECenterOfMassApp class

class SB_EXPORT SECenterOfMassAppGUI : public SBGApp {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SECenterOfMassAppGUI(SECenterOfMassApp* t);																							///< Constructs a GUI for the app
	virtual ~SECenterOfMassAppGUI();																									///< Destructs the GUI of the app

	//@}

	/// \name App
	//@{

	SECenterOfMassApp*											getApp() const;															///< Returns a pointer to the app

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

	virtual void												loadSettings(SBGSettings* settings) override;							///< Load GUI settings
	virtual void												saveSettings(SBGSettings* settings) override;							///< Save GUI settings

	//@}

	void														updateCenterOfMass(const SBPosition3& centerOfMass);

public slots:

	// SAMSON Extension generator pro tip: add slots here to interact with your app

	void														onComputeCenterOfMass();

private:

	Ui::SECenterOfMassAppGUIClass								ui;

};

