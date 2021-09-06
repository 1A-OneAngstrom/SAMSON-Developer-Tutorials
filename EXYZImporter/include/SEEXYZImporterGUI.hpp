#pragma once


#include "SBGFileImporter.hpp" 
#include "ui_SEEXYZImporterGUI.h"

class SEEXYZImporter;

/// This class implements the GUI of the importer

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEEXYZImporter class

class SB_EXPORT SEEXYZImporterGUI : public SBGFileImporter {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEEXYZImporterGUI(SEEXYZImporter* t);																								///< Constructs a GUI for the importer
	~SEEXYZImporterGUI();																												///< Destructs the GUI of the importer

	//@}

	/// \name Importer
	//@{

	SEEXYZImporter*												getImporter() const;													///< Returns a pointer to the importer

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

	/// \name Parameters
	//@{

	void														getParameters(bool& createCovalentBonds);

	//@}

private:

	Ui::SEEXYZImporterGUIClass									ui;

};

