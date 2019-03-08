#pragma once 

#include "SBIFileImporter.hpp"
#include "SEEXYZImporterGUI.hpp"
#include "SBStructuralModel.hpp"


/// This class implements the functionality of the importer

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEEXYZImporterGUI class

class SEEXYZImporter : public SBIFileImporter {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEEXYZImporter();																													///< Constructs an importer
	virtual ~SEEXYZImporter();																											///< Destructs the importer

	//@}

	/// \name Properties
	//@{

	virtual std::string											getFilter() const;														///< Returns the filter of the importer
	virtual std::string											getExtension() const;													///< Returns the extension of the importer

	//@}

	/// \name Parsing
	//@{

	virtual bool												importFromFile(const std::string& fileName, const SBList<std::string>* parameters = 0, SBDDocumentLayer* preferredLayer = 0);			///< Imports data into SAMSON from a file

	//@}

private:

	void														initializeParameters(const SBList<std::string>* parameters);			///< Initializes import parameters
	void														parseParameters(const SBList<std::string>* parameters);					///< Parse the parameters list

	bool														parseEXYZ(const std::string& fileName, SBDDocumentLayer* preferredLayer = 0);	///< Parse the format

	// Add to SAMSON's data graph

	bool														addToDataGraph(SBStructuralModel* structuralModel, SBDDocumentLayer* preferredLayer = nullptr);

private:

	bool														createCovalentBonds;

};


SB_REGISTER_TARGET_TYPE(SEEXYZImporter, "SEEXYZImporter", "36BCA661-C273-3A9E-AD55-35274D3BF9BC");
SB_DECLARE_BASE_TYPE(SEEXYZImporter, SBIFileImporter);
