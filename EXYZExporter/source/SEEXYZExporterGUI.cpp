#include "SEEXYZExporterGUI.hpp"
#include "SEEXYZExporter.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"
#include <QShortcut>

SEEXYZExporterGUI::SEEXYZExporterGUI(SEEXYZExporter* t) : SBGFileExporter(t) {

	ui.setupUi(this);

}

SEEXYZExporterGUI::~SEEXYZExporterGUI() {

}

SEEXYZExporter* SEEXYZExporterGUI::getExporter() const { return static_cast<SEEXYZExporter*>(exporter); }

void SEEXYZExporterGUI::loadSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so your exporter can save its GUI state from one session to the next

}

void SEEXYZExporterGUI::saveSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so your exporter can save its GUI state from one session to the next

}

SBCContainerUUID SEEXYZExporterGUI::getUUID() const { return SBCContainerUUID("FF55FF0A-2D36-5FEE-0133-69BEAB5D44F9"); }

QPixmap SEEXYZExporterGUI::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your exporter.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEEXYZExporterIcon.png"));

}

QString SEEXYZExporterGUI::getName() const {

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your exporter inside SAMSON

	return "SEEXYZExporter";

}

int SEEXYZExporterGUI::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Lockable);

}
