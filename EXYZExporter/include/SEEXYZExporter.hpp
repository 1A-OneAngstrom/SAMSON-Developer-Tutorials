#pragma once 

#include "SBIFileExporter.hpp"
#include "SEEXYZExporterGUI.hpp"


/// This class implements the functionality of the exporter

// SAMSON Extension generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEEXYZExporterGUI class

class SB_EXPORT SEEXYZExporter : public SBIFileExporter {

	SB_CLASS

public:

	/// \name Constructors and destructors
	//@{

	SEEXYZExporter();																													///< Constructs an exporter
	virtual ~SEEXYZExporter();																											///< Destructs the exporter

	//@}

	/// \name Properties
	//@{

	virtual std::string											getFilter() const override;												///< Returns the filter of the exporter
	virtual std::string											getExtension() const override;											///< Returns the extension of the exporter

	//@}

	/// \name Parsing
	//@{

	virtual bool												exportToFile(const SBNodeIndexer& nodeIndexer, const std::string& fileName, const std::unordered_map<std::string, SBValue>* parameters = nullptr) override;		///< Exports data from SAMSON to a file

	//@}

};


SB_REGISTER_TARGET_TYPE(SEEXYZExporter, "SEEXYZExporter", "0E11A0BC-4F10-A5CC-1285-4634D77A4207");
SB_DECLARE_BASE_TYPE(SEEXYZExporter, SBIFileExporter);
