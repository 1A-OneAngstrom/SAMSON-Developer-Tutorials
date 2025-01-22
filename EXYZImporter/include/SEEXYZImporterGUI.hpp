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

	virtual SBCContainerUUID									getUUID() const override;												///< Returns the widget UUID
	virtual QString												getName() const override;												///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const override;												///< Returns the widget logo
	virtual int													getFormat() const override;												///< Returns the widget format

	//@}

	///\name Settings
	//@{

	virtual void												loadSettings(SBGSettings* settings) override;							///< Load GUI settings
	virtual void												saveSettings(SBGSettings* settings) override;							///< Save GUI settings

	//@}

	/// \name Parameters
	//@{

	void														getParameters(bool& createCovalentBonds);

	//@}

private:

	Ui::SEEXYZImporterGUIClass									ui;

};

