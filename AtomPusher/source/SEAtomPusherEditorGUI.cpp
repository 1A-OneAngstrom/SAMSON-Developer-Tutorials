#include "SEAtomPusherEditorGUI.hpp"
#include "SEAtomPusherEditor.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEAtomPusherEditorGUI::SEAtomPusherEditorGUI(SEAtomPusherEditor* editor) {

	ui.setupUi( this );
	this->editor = editor;

}

SEAtomPusherEditorGUI::~SEAtomPusherEditorGUI() {

}

SEAtomPusherEditor* SEAtomPusherEditorGUI::getEditor() const { return editor; }

void SEAtomPusherEditorGUI::loadSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;
	
	// SAMSON Extension generator pro tip: complete this function so your editor can save its GUI state from one session to the next

}

void SEAtomPusherEditorGUI::saveSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;

	// SAMSON Extension generator pro tip: complete this function so your editor can save its GUI state from one session to the next

}

SBCContainerUUID SEAtomPusherEditorGUI::getUUID() const { return SBCContainerUUID( "BEF377BE-83A1-B62F-B669-AB84273886B6" );}

QPixmap SEAtomPusherEditorGUI::getLogo() const { 
	
	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your editor.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEAtomPusherEditorIcon.png"));

}

QString SEAtomPusherEditorGUI::getName() const { 

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your editor inside SAMSON

	return "DevTutorial: Atom pusher";

}

int SEAtomPusherEditorGUI::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEAtomPusherEditorGUI::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this editor in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}
