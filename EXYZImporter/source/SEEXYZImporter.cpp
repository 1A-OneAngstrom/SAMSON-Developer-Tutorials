#include "SEEXYZImporter.hpp"
#include "SEEXYZImporterGUI.hpp"
#include "SAMSON.hpp"
#include "SBIFileReader.hpp"

SEEXYZImporter::SEEXYZImporter() {

	propertyDialog = new SEEXYZImporterGUI(this);
	propertyDialog->loadDefaultSettings();

}

SEEXYZImporter::~SEEXYZImporter() {

	propertyDialog->saveDefaultSettings();
	delete propertyDialog;

}

std::string SEEXYZImporter::getFilter() const {

	// SAMSON Extension generator pro tip: modify this function to return the filter of the importer

	return std::string("EXYZ format (*.exyz)");

}

std::string SEEXYZImporter::getExtension() const {

	// SAMSON Extension generator pro tip: modify this function to return the extension of the importer

	return std::string("exyz");

}

/// Parse parameters
void SEEXYZImporter::parseParameters(const SBList<std::string>* cparameters) {

	SBList<std::string> *parameters = 0;
	if (cparameters) parameters = new SBList<std::string>(*cparameters);

	if ((*parameters->begin()) == "1")
		createCovalentBonds = true;
	else
		createCovalentBonds = false;
	parameters->pop_front();

	if (parameters) delete parameters;

}

/// This function initializes variables for the parser
void SEEXYZImporter::initializeParameters(const SBList<std::string>* parameters) {

	const int nparams = 1;	// total number of parameters

	// no parameters or only one parameter "default" => take from form
	if (!parameters || (parameters->size() == 1 && (*parameters->begin()) == "default") || parameters->size() != nparams) {

		// get parameters of the parser from the window
		static_cast<SEEXYZImporterGUI*>(propertyDialog)->getParameters(createCovalentBonds);

	}
	// analyze parameters
	else {

		parseParameters(parameters);

	}

}

bool SEEXYZImporter::parseEXYZ(const std::string& fileName, SBDDocumentFolder *preferredFolder) {

	// get file lines

	std::vector<std::string> fileLineVector;
	SBIFileReader::getFileLines(fileName, fileLineVector);

	// read the number of atoms from the first line

	unsigned int numberOfAtoms = 0;
	std::stringstream numberOfAtomsParser(fileLineVector[0]);
	numberOfAtomsParser >> numberOfAtoms;

	// create a new structural model

	std::string name = fileLineVector[1];
	SBMStructuralModel* structuralModel = new SBMStructuralModel();
	structuralModel->setName(name);

	// read atoms

	int currentSerialNumber = 0;

	for (unsigned int i = 2; i < fileLineVector.size(); i++) {

		// parse the current line

		double x, y, z;
		std::string atomType;

		std::stringstream atomParser(fileLineVector[i]);

		atomParser >> atomType >> x >> y >> z;

		// add a new atom to the model

		SBElement::Type element = SAMSON::getElementTypeBySymbol(atomType);
		if (element != SBElement::Unknown) {

			SBAtom* newAtom = new SBAtom(element,
										 SBQuantity::angstrom(x),
										 SBQuantity::angstrom(y),
										 SBQuantity::angstrom(z));
			newAtom->setSerialNumber(currentSerialNumber++);
			structuralModel->getStructuralRoot()->addChild(newAtom);

		}

	}

	// create covalent bonds

	if (createCovalentBonds)
		structuralModel->createCovalentBonds();

	// add data to the data graph

	if ( !addToDataGraph(structuralModel, preferredFolder) ) {

		std::string msg = "EXYZImporter: ";
		msg += "Could not add to the data graph " + fileName;
		std::cerr << msg << "\n";

		SAMSON::setStatusMessage(QString::fromStdString(msg));

		return false;

	}

	return true;

}

bool SEEXYZImporter::addToDataGraph(SBStructuralModel* structuralModel, SBDDocumentFolder *preferredFolder) {

	SAMSON::beginHolding("Import EXYZ model");						// start the undoable operation

	SAMSON::hold(structuralModel);									// the undoable operation

	// Create the structural model before adding it into the data graph.
	// This will also create all its children (e.g., atoms).
	structuralModel->create();

	bool ret = false;
	if (preferredFolder)											// add to the preferred folder
		ret = preferredFolder->addChild(structuralModel);
	else															// if there is no preferred folder, add to the active document
		ret = SAMSON::getActiveDocument()->addChild(structuralModel);

	SAMSON::endHolding();											// end the undoable operation

	return ret;

}

bool SEEXYZImporter::importFromFile(const std::string& fileName, const SBList<std::string>* parameters, SBDDocumentFolder *preferredFolder) {

	// SAMSON Extension generator pro tip: modify this function to parse the contents of a file and add new nodes to SAMSON's data graph.
	// Please refer to tutorials for examples.

	initializeParameters(parameters);

	// check if file exists and valid

	QString qfileName = QString::fromStdString(fileName);
	QFileInfo checkFile(qfileName);

	// check the file

	if (!QFileInfo::exists(qfileName) || !checkFile.isFile() ||
		!checkFile.isReadable() || checkFile.size() == 0) {

		std::string msg = "EXYZImporter: Could not open EXYZ file " + fileName;

		if (!QFileInfo::exists(qfileName)) msg += " - file does not exist";
		else if (!checkFile.isFile())      msg += " - not a file";
		else if (!checkFile.isReadable())  msg += " - not readable";
		else if (checkFile.size() == 0)    msg += " - zero size";

		std::cerr << msg << "\n";
		SAMSON::setStatusMessage(QString::fromStdString(msg));

		return false;

	}

	// parse the file and add to data graph

	bool ret = parseEXYZ(fileName, preferredFolder);

	std::string msg = "EXYZImporter: ";
	if (ret)
		msg += "Successfully read " + fileName;
	else
		msg += "Could not parse " + fileName;
	std::cerr << msg << ".\n";

	SAMSON::setStatusMessage(QString::fromStdString(msg));

	return ret;

}
