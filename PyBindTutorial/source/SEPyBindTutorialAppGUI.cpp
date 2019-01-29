#include "SEPyBindTutorialAppGUI.hpp"
#include "SEPyBindTutorialApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEPyBindTutorialAppGUI::SEPyBindTutorialAppGUI( SEPyBindTutorialApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

	connect(ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(onAddCustomStructuralModelPressed()));		// connect the pushButtonAdd with a slot

}

SEPyBindTutorialAppGUI::~SEPyBindTutorialAppGUI() {

}

SEPyBindTutorialApp* SEPyBindTutorialAppGUI::getApp() const { return static_cast<SEPyBindTutorialApp*>(SBGApp::getApp()); }

void SEPyBindTutorialAppGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;
	
	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

void SEPyBindTutorialAppGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == NULL ) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

SBCContainerUUID SEPyBindTutorialAppGUI::getUUID() const { return SBCContainerUUID( "773131DA-41CF-B5D1-E97D-70C9EAD9EADE" );}

QPixmap SEPyBindTutorialAppGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEPyBindTutorialAppIcon.png"));

}

QString SEPyBindTutorialAppGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "PyBind Tutorial App";

}

int SEPyBindTutorialAppGUI::getFormat() const { 
	
	// SAMSON Element generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)
	
	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEPyBindTutorialAppGUI::getCitation() const {

	// SAMSON Element generator pro tip: modify this function to add citation information

	return
		"If you use this app in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";
	
}

// Adds a custom structural group into the data graph
void SEPyBindTutorialAppGUI::onAddCustomStructuralModelPressed() {

	getApp()->addCustomStructuralModel();		// call a function from the App (all non-GUI functionality should be placed in an App)

}
