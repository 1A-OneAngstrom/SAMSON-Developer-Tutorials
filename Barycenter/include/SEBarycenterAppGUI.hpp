#pragma once


#include "SBGApp.hpp" 
#include "ui_SEBarycenterAppGUI.h"

class SEBarycenterApp;

/// This class implements the GUI of the app

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEBarycenterApp class

class SB_EXPORT SEBarycenterAppGUI : public SBGApp {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEBarycenterAppGUI(SEBarycenterApp* t);																								///< Constructs a GUI for the app
	virtual ~SEBarycenterAppGUI();																										///< Destructs the GUI of the app

	//@}

	/// \name App
	//@{

	SEBarycenterApp*											getApp() const;															///< Returns a pointer to the app

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const override;												///< Returns the widget UUID
	virtual QString												getName() const override;												///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const override;												///< Returns the widget logo
	virtual int													getFormat() const override;												///< Returns the widget format
	virtual QString												getCitation() const override;											///< Returns the citation information
	virtual QKeySequence										getShortcut() const override;											///< Returns the shortcut
	virtual QString												getToolTip() const override;											///< Returns the tool tip

	//@}

	///\name Settings
	//@{

	virtual void												loadSettings(SBGSettings* settings) override;							///< Load GUI settings
	virtual void												saveSettings(SBGSettings* settings) override;							///< Save GUI settings

	virtual bool												getVerticalSpacerFlag() const override;									///< Returns whether the GUI should have a vertical spacer added
	virtual Qt::DockWidgetArea									getDockWidgetArea() const override;										///< Returns the preferred dock widget area
	
	//@}

public slots:

	// SAMSON Extension generator pro tip: add slots here to interact with your app

	void														onCompute();

private:

	Ui::SEBarycenterAppGUIClass									ui;

};

