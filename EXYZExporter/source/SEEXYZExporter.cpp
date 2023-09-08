#include "SEEXYZExporter.hpp"
#include "SEEXYZExporterGUI.hpp"
#include <fstream>
#include "SAMSON.hpp"
#include "SBStructuralModel.hpp"
#include "SBAtom.hpp"

SEEXYZExporter::SEEXYZExporter() {

	// remove the options window

	propertyDialog = nullptr;

	//propertyDialog = new SEEXYZExporterGUI(this);
	//propertyDialog->loadDefaultSettings();

}

SEEXYZExporter::~SEEXYZExporter() {

	// remove the options window

	//propertyDialog->saveDefaultSettings();
	//delete propertyDialog;

}

std::string SEEXYZExporter::getFilter() const {

	// SAMSON Extension generator pro tip: modify this function to return the filter of the exporter

	return std::string("EXYZ format (*.exyz)");

}

std::string SEEXYZExporter::getExtension() const {

	// SAMSON Extension generator pro tip: modify this function to return the extension of the exporter

	return std::string("exyz");

}

bool SEEXYZExporter::exportToFile(const SBNodeIndexer& nodeIndexer, const std::string& fileName, const std::unordered_map<std::string, SBValue>* parameters) {

	// SAMSON Extension generator pro tip: modify this function to export the nodes contained in nodeIndexer to a file.
	// Please refer to tutorials for examples.

	// retrieve all atoms

	SBNodeIndexer atomIndexer;
	SB_FOR(SBNode * node, nodeIndexer) {

		node->getNodes(atomIndexer, SBNode::Atom);
		// the line above produces the same result as the line below which uses the SBNode::IsType() predicate but it is optimized for getting nodes based on node types
		//node->getNodes(atomIndexer, SBNode::IsType(SBNode::Atom));

	}

	// create file

	std::ofstream file;
	file.open(fileName.c_str());

	// write the header

	file << atomIndexer.size() << std::endl; // number of atoms
	file << "SAMSON Export" << std::endl;

	// write atoms

	for (unsigned int i = 0; i < atomIndexer.size(); i++) {

		SBAtom* currentAtom = static_cast<SBAtom*>(atomIndexer[i]);
		SBPosition3 const& currentAtomPosition = currentAtom->getPosition();

		file << SAMSON::getElementSymbol(currentAtom->getElementType())
			<< " " << SBQuantity::angstrom(currentAtomPosition.v[0]).getValue()
			<< " " << SBQuantity::angstrom(currentAtomPosition.v[1]).getValue()
			<< " " << SBQuantity::angstrom(currentAtomPosition.v[2]).getValue() << "\n";

	}

	// close the file

	file.close();

	return true;

}

