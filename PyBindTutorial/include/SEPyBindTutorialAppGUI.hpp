#pragma once

#include "SBGApp.hpp" 
#include "ui_SEPyBindTutorialAppGUI.h"

#include "CustomStructuralModel.hpp"
#include "CustomStructuralGroup.hpp"

class SEPyBindTutorialApp;

/// This class implements the GUI of the app

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEPyBindTutorialApp class

class SEPyBindTutorialAppGUI : public SBGApp {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEPyBindTutorialAppGUI(SEPyBindTutorialApp* t);														///< Constructs a GUI for the app
	virtual ~SEPyBindTutorialAppGUI();																	///< Destructs the GUI of the app

	//@}

	/// \name App
	//@{

	SEPyBindTutorialApp*										getApp() const;							///< Returns a pointer to the app

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const override;				///< Returns the widget UUID
	virtual QString												getName() const override;				///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const override;				///< Returns the widget logo
	virtual int													getFormat() const override;				///< Returns the widget format
	virtual QString												getCitation() const override;			///< Returns the citation information

	//@}

	///\name Settings
	//@{

	virtual void												loadSettings(SBGSettings* settings) override;	///< Load GUI settings
	virtual void												saveSettings(SBGSettings* settings) override;	///< Save GUI settings

	//@}

public slots:

	///\name Slots

	void														onAddCustomStructuralModelPressed();

private:

	Ui::SEPyBindTutorialAppGUIClass								ui;

};
