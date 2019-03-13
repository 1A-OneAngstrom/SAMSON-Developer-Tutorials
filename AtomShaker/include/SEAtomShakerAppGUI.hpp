#pragma once


#include "SBGApp.hpp" 
#include "ui_SEAtomShakerAppGUI.h"

class SEAtomShakerApp;

/// This class implements the GUI of the app

// SAMSON Element generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEAtomShakerApp class

class SEAtomShakerAppGUI : public SBGApp {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEAtomShakerAppGUI(SEAtomShakerApp* t);																								///< Constructs a GUI for the app
	virtual ~SEAtomShakerAppGUI();																										///< Destructs the GUI of the app

	//@}

	/// \name App
	//@{

	SEAtomShakerApp*											getApp() const;															///< Returns a pointer to the app

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const;														///< Returns the widget UUID
	virtual QString												getName() const;														///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const;														///< Returns the widget logo
	int															getFormat() const;														///< Returns the widget format

	QString														getCitation() const;													///< Returns a reference 

	//@}

	///\name Settings
	//@{

	void														loadSettings(SBGSettings* settings);									///< Load GUI settings
	void														saveSettings(SBGSettings* settings);									///< Save GUI settings

	//@}

public slots:

	void														onShakeAtoms();

private:

	Ui::SEAtomShakerAppGUIClass									ui;

};

