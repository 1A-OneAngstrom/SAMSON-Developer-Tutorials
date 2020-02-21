#include "SECenterOfMassAppGUI.hpp"
#include "SECenterOfMassApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SECenterOfMassAppGUI::SECenterOfMassAppGUI( SECenterOfMassApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

}

SECenterOfMassAppGUI::~SECenterOfMassAppGUI() {

}

SECenterOfMassApp* SECenterOfMassAppGUI::getApp() const { return static_cast<SECenterOfMassApp*>(SBGApp::getApp()); }

void SECenterOfMassAppGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;
	
	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

void SECenterOfMassAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

SBCContainerUUID SECenterOfMassAppGUI::getUUID() const { return SBCContainerUUID( "9E140A22-134A-8C41-EDB5-57D896016345" );}

QPixmap SECenterOfMassAppGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SECenterOfMassAppIcon.png"));

}

QString SECenterOfMassAppGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "DevTutorial: Center of mass";

}

int SECenterOfMassAppGUI::getFormat() const { 
	
	// SAMSON Element generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)
	
	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SECenterOfMassAppGUI::getCitation() const {

	// SAMSON Element generator pro tip: modify this function to add citation information

	return
		"If you use this app in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";
	
}

void SECenterOfMassAppGUI::onComputeCenterOfMass() {

	getApp()->computeCenterOfMass();

}

void SECenterOfMassAppGUI::updateCenterOfMass(const SBPosition3& centerOfMass) {

	// convert to angstrom
	// (else it will be in SBQuantity::length, which is picometers)

	SBQuantity::angstrom x = centerOfMass.v[0];
	SBQuantity::angstrom y = centerOfMass.v[1];
	SBQuantity::angstrom z = centerOfMass.v[2];

	// setup the label

	ui.label->setText(
		QString::fromStdString(x.toStdString()) + ", " +
		QString::fromStdString(y.toStdString()) + ", " +
		QString::fromStdString(z.toStdString())
		);

}
