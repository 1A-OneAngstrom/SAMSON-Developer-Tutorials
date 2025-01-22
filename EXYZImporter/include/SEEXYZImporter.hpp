#pragma once 

#include "SBIFileImporter.hpp"
#include "SEEXYZImporterGUI.hpp"
#include "SBStructuralModel.hpp"


/// This class implements the functionality of the importer

// SAMSON Extension generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEEXYZImporterGUI class

class SB_EXPORT SEEXYZImporter : public SBIFileImporter {

	SB_CLASS

public:

	/// \name Constructors and destructors
	//@{

	SEEXYZImporter();																													///< Constructs an importer
	virtual ~SEEXYZImporter();																											///< Destructs the importer

	//@}

	/// \name Properties
	//@{

	virtual std::string											getFilter() const override;												///< Returns the filter of the importer
	virtual std::string											getExtension() const override;											///< Returns the extension of the importer

	//@}

	/// \name Parsing
	//@{

	virtual bool												importFromFile(const std::string& fileName, const std::unordered_map<std::string, SBValue>* parameters = nullptr, SBDDocumentFolder* preferredFolder = nullptr) override;			///< Imports data into SAMSON from a file

	//@}

private:

	void														initializeParameters(const std::unordered_map<std::string, SBValue>* parameters);		///< Initializes import parameters
	void														parseParameters(const std::unordered_map<std::string, SBValue>* parameters);			///< Parse the parameters list

	bool														parseEXYZ(const std::string& fileName, SBDDocumentFolder* preferredFolder = nullptr);	///< Parse the format

	// Add to SAMSON's data graph

	bool														addToDataGraph(SBStructuralModel* structuralModel, SBDDocumentFolder* preferredFolder = nullptr);

private:

	bool														createCovalentBonds{ true };

};


SB_REGISTER_TARGET_TYPE(SEEXYZImporter, "SEEXYZImporter", "36BCA661-C273-3A9E-AD55-35274D3BF9BC");
SB_DECLARE_BASE_TYPE(SEEXYZImporter, SBIFileImporter);
