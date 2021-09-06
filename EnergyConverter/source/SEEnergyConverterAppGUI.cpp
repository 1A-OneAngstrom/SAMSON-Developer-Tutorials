#include "SEEnergyConverterAppGUI.hpp"
#include "SEEnergyConverterApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEEnergyConverterAppGUI::SEEnergyConverterAppGUI( SEEnergyConverterApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

}

SEEnergyConverterAppGUI::~SEEnergyConverterAppGUI() {

}

SEEnergyConverterApp* SEEnergyConverterAppGUI::getApp() const { return static_cast<SEEnergyConverterApp*>(SBGApp::getApp()); }

void SEEnergyConverterAppGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;
	
	// SAMSON Extension generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

void SEEnergyConverterAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;

	// SAMSON Extension generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

SBCContainerUUID SEEnergyConverterAppGUI::getUUID() const { return SBCContainerUUID( "19EDF709-C04F-AF56-8B21-C0FC96B004E5" );}

QPixmap SEEnergyConverterAppGUI::getLogo() const { 
	
	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEEnergyConverterAppIcon.png"));

}

QString SEEnergyConverterAppGUI::getName() const { 

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "DevTutorial: Energy converter";

}

int SEEnergyConverterAppGUI::getFormat() const { 
	
	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)
	
	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEEnergyConverterAppGUI::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this app in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";
	
}

void SEEnergyConverterAppGUI::onLeftChanged() {

	// convert the string from the line edit to a double
	// with checking for valid numerical characters (including the scientific notation)
	bool ok;
	double source = ui.lineEditLeft->text().toDouble(&ok);

	if (ok) {

		// convert units

		const int sourceUnit = ui.comboBoxLeft->currentIndex();
		const int destinationUnit = ui.comboBoxRight->currentIndex();

		double destination = getApp()->convert(source, sourceUnit, destinationUnit);

		// set the destination value
		// QString::number will use float or scientific notation format, whichever is the most concise
		ui.lineEditRight->setText(QString::number(destination));

	}
	else {

		// in the case when the line edit contained invalid characters clear another line edit
		ui.lineEditRight->setText("");

	}

}

void SEEnergyConverterAppGUI::onRightChanged() {

	// convert the string from the line edit to a double
	// with checking for valid numerical characters (including the scientific notation)
	bool ok;
	double source = ui.lineEditRight->text().toDouble(&ok);

	if (ok) {

		// convert units

		const int sourceUnit = ui.comboBoxRight->currentIndex();
		const int destinationUnit = ui.comboBoxLeft->currentIndex();

		double destination = getApp()->convert(source, sourceUnit, destinationUnit);

		// set the destination value
		// QString::number will use float or scientific notation format, whichever is the most concise
		ui.lineEditLeft->setText(QString::number(destination));

	}
	else {

		// in the case when the line edit contained invalid characters clear another line edit
		ui.lineEditLeft->setText("");

	}

}
