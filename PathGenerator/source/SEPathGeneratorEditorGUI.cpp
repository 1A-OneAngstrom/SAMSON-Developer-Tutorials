#include "SEPathGeneratorEditorGUI.hpp"
#include "SEPathGeneratorEditor.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEPathGeneratorEditorGUI::SEPathGeneratorEditorGUI(SEPathGeneratorEditor* editor) {

	ui.setupUi( this );
	this->editor = editor;

}

SEPathGeneratorEditorGUI::~SEPathGeneratorEditorGUI() {

}

SEPathGeneratorEditor* SEPathGeneratorEditorGUI::getEditor() const { return editor; }

void SEPathGeneratorEditorGUI::loadSettings(SBGSettings* settings) {

	if (settings == nullptr) return;
	
	// SAMSON Extension generator pro tip: complete this function so your editor can save its GUI state from one session to the next

}

void SEPathGeneratorEditorGUI::saveSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so your editor can save its GUI state from one session to the next

}

SBCContainerUUID SEPathGeneratorEditorGUI::getUUID() const { return SBCContainerUUID( "252ED790-DCE0-721C-E4BF-640A6FAB22D8" );}

QPixmap SEPathGeneratorEditorGUI::getLogo() const { 
	
	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your editor.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEPathGeneratorEditorIcon.png"));

}

QString SEPathGeneratorEditorGUI::getName() const { 

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your editor inside SAMSON

	return "DevTutorial: Path Generator Editor"; 

}

int SEPathGeneratorEditorGUI::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEPathGeneratorEditorGUI::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this editor in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}
