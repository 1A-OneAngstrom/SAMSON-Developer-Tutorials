#include "SEEnergyConverterApp.hpp"
#include "SEEnergyConverterAppGUI.hpp"
#include "SBQuantity.hpp"

SEEnergyConverterApp::SEEnergyConverterApp() {

	setGUI(new SEEnergyConverterAppGUI(this));
	getGUI()->loadDefaultSettings();

}

SEEnergyConverterApp::~SEEnergyConverterApp() {

	getGUI()->saveDefaultSettings();
	delete getGUI();

}

SEEnergyConverterAppGUI* SEEnergyConverterApp::getGUI() const { return static_cast<SEEnergyConverterAppGUI*>(SBDApp::getGUI()); }

double SEEnergyConverterApp::convert(const double sourceEnergy, const int sourceUnit, const int destinationUnit) {

	SBQuantity::energy source(0.0);

	if (sourceUnit == 0) source = SBQuantity::eV(sourceEnergy);
	else if (sourceUnit == 1) source = SBQuantity::Eh(sourceEnergy);
	else if (sourceUnit == 2) source = SBQuantity::kcalPerMol(sourceEnergy);
	else if (sourceUnit == 3) source = SBQuantity::zJ(sourceEnergy);

	if (destinationUnit == 0) return (SBQuantity::eV(source)).getValue();
	if (destinationUnit == 1) return (SBQuantity::Eh(source)).getValue();
	if (destinationUnit == 2) return (SBQuantity::kcalPerMol(source)).getValue();
	if (destinationUnit == 3) return (SBQuantity::zJ(source)).getValue();

	return 0.0;

}
