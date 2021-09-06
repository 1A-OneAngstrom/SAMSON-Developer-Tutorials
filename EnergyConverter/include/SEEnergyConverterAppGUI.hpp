#pragma once


#include "SBGApp.hpp" 
#include "ui_SEEnergyConverterAppGUI.h"

class SEEnergyConverterApp;

/// This class implements the GUI of the app

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEEnergyConverterApp class

class SB_EXPORT SEEnergyConverterAppGUI : public SBGApp {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEEnergyConverterAppGUI(SEEnergyConverterApp* t);																					///< Constructs a GUI for the app
	virtual ~SEEnergyConverterAppGUI();																									///< Destructs the GUI of the app

	//@}

	/// \name App
	//@{

	SEEnergyConverterApp*										getApp() const;															///< Returns a pointer to the app

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

public slots:

	// SAMSON Extension generator pro tip: add slots here to interact with your app

	void														onLeftChanged();
	void														onRightChanged();

private:

	Ui::SEEnergyConverterAppGUIClass							ui;

};

