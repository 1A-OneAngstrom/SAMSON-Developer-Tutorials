#pragma once 

#include "SBIFileExporter.hpp"
#include "SEEXYZExporterGUI.hpp"


/// This class implements the functionality of the exporter

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEEXYZExporterGUI class

class SEEXYZExporter : public SBIFileExporter {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEEXYZExporter();																													///< Constructs an exporter
	virtual ~SEEXYZExporter();																											///< Destructs the exporter

	//@}

	/// \name Properties
	//@{

	virtual std::string											getFilter() const;														///< Returns the filter of the exporter
	virtual std::string											getExtension() const;													///< Returns the extension of the exporter

	//@}

	/// \name Parsing
	//@{

	virtual bool												exportToFile(const SBNodeIndexer& nodeIndexer, const std::string& fileName, const SBList<std::string>* parameters = 0);		///< Exports data from SAMSON to a file

	//@}

};


SB_REGISTER_TARGET_TYPE(SEEXYZExporter, "SEEXYZExporter", "0E11A0BC-4F10-A5CC-1285-4634D77A4207");
SB_DECLARE_BASE_TYPE(SEEXYZExporter, SBIFileExporter);
