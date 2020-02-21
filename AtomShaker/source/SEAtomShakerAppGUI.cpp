#include "SEAtomShakerAppGUI.hpp"
#include "SEAtomShakerApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEAtomShakerAppGUI::SEAtomShakerAppGUI( SEAtomShakerApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

}

SEAtomShakerAppGUI::~SEAtomShakerAppGUI() {

}

SEAtomShakerApp* SEAtomShakerAppGUI::getApp() const { return static_cast<SEAtomShakerApp*>(SBGApp::getApp()); }

void SEAtomShakerAppGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;
	
	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

	ui.doubleSpinBoxMaximumDistance->setValue(settings->loadDoubleValue("MaximumDistance", 1.0));

}

void SEAtomShakerAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

	settings->saveValue("MaximumDistance", ui.doubleSpinBoxMaximumDistance->value());

}

SBCContainerUUID SEAtomShakerAppGUI::getUUID() const { return SBCContainerUUID( "8B972823-F315-E2BF-2D51-9AE1DD24F333" );}

QPixmap SEAtomShakerAppGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEAtomShakerAppIcon.png"));

}

QString SEAtomShakerAppGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "DevTutorial: Atom shaker";

}

int SEAtomShakerAppGUI::getFormat() const { 
	
	// SAMSON Element generator pro tip: modify these default settings if you want more options (see the documentation of SBGWindow)
	
	return SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Citable;

}

QString	SEAtomShakerAppGUI::getCitation() const {

	return
		"If you use this app in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

void SEAtomShakerAppGUI::onShakeAtoms() {

	getApp()->shakeAtoms(SBQuantity::angstrom(ui.doubleSpinBoxMaximumDistance->value()));

}

