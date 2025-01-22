#pragma once


#include "SBGFileExporter.hpp" 
#include "ui_SEEXYZExporterGUI.h"

class SEEXYZExporter;

/// This class implements the GUI of the exporter

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEEXYZExporter class

class SB_EXPORT SEEXYZExporterGUI : public SBGFileExporter {

	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEEXYZExporterGUI(SEEXYZExporter* t);																								///< Constructs a GUI for the exporter
	~SEEXYZExporterGUI();																												///< Destructs the GUI of the exporter

	//@}

	/// \name Exporter
	//@{

	SEEXYZExporter*												getExporter() const;													///< Returns a pointer to the exporter

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

private:

	Ui::SEEXYZExporterGUIClass									ui;

};

