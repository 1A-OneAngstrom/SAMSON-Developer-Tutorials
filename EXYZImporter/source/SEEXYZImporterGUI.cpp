#include "SEEXYZImporterGUI.hpp"
#include "SEEXYZImporter.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"
#include <QShortcut>

SEEXYZImporterGUI::SEEXYZImporterGUI( SEEXYZImporter* t ) : SBGFileImporter( t ) {

	ui.setupUi( this );

}

SEEXYZImporterGUI::~SEEXYZImporterGUI() {

}

SEEXYZImporter* SEEXYZImporterGUI::getImporter() const { return static_cast<SEEXYZImporter*>(importer); }

void SEEXYZImporterGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;
	
	// SAMSON Element generator pro tip: complete this function so your importer can save its GUI state from one session to the next

	ui.checkBoxCreateCovalentBonds->setChecked( settings->loadBoolValue("checkBoxCreateCovalentBonds", true) );

}

void SEEXYZImporterGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;

	// SAMSON Element generator pro tip: complete this function so your importer can save its GUI state from one session to the next

	settings->saveValue("checkBoxCreateCovalentBonds", ui.checkBoxCreateCovalentBonds->isChecked());

}

SBCContainerUUID SEEXYZImporterGUI::getUUID() const { return SBCContainerUUID( "25D11718-9241-65A2-2875-6DBF998792DB" );}

QPixmap SEEXYZImporterGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your importer.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEEXYZImporterIcon.png"));

}

QString SEEXYZImporterGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your importer inside SAMSON

	return "DevTutorial: EXYZ Importer";

}

int SEEXYZImporterGUI::getFormat() const {

	// SAMSON Element generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Lockable);

}

QString SEEXYZImporterGUI::getCitation() const {

	// SAMSON Element generator pro tip: modify this function to add citation information

	return
		"If you use this importer in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

void SEEXYZImporterGUI::getParameters(bool &createCovalentBonds) {

	createCovalentBonds = ui.checkBoxCreateCovalentBonds->isChecked();

}
