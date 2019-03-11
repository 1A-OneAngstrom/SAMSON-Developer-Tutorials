#pragma once


#include "SBGFileExporter.hpp" 
#include "ui_SEEXYZExporterGUI.h"

class SEEXYZExporter;

/// This class implements the GUI of the exporter

// SAMSON Element generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEEXYZExporter class

class SEEXYZExporterGUI : public SBGFileExporter {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEEXYZExporterGUI(SEEXYZExporter* t);																			///< Constructs a GUI for the exporter
	~SEEXYZExporterGUI();																												///< Destructs the GUI of the exporter

	//@}

	/// \name Exporter
	//@{

	SEEXYZExporter*												getExporter() const;													///< Returns a pointer to the exporter

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

	void														loadSettings(SBGSettings* settings);										///< Load GUI settings
	void														saveSettings(SBGSettings* settings);										///< Save GUI settings

	//@}

private:

	Ui::SEEXYZExporterGUIClass									ui;

};

