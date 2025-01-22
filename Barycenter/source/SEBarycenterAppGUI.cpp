#include "SEBarycenterAppGUI.hpp"
#include "SEBarycenterApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEBarycenterAppGUI::SEBarycenterAppGUI(SEBarycenterApp* t) : SBGApp(t) {

	ui.setupUi(this);

	QObject::connect(ui.pushButtonCompute, &QPushButton::clicked, this, &SEBarycenterAppGUI::onCompute);

}

SEBarycenterAppGUI::~SEBarycenterAppGUI() {

}

SEBarycenterApp* SEBarycenterAppGUI::getApp() const { return static_cast<SEBarycenterApp*>(SBGApp::getApp()); }

void SEBarycenterAppGUI::loadSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

void SEBarycenterAppGUI::saveSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

bool SEBarycenterAppGUI::getVerticalSpacerFlag() const {

	// SAMSON Extension generator pro tip: return false when you want your GUI to take as much space as possible

	return true;

}

Qt::DockWidgetArea SEBarycenterAppGUI::getDockWidgetArea() const {

	// SAMSON Extension generator pro tip: modify this when you want your app to have a different default location

	return Qt::RightDockWidgetArea;

}

SBCContainerUUID SEBarycenterAppGUI::getUUID() const { return SBCContainerUUID("8E7E1027-BDF6-0E28-1B1E-C5095602C7DF"); }

QPixmap SEBarycenterAppGUI::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEBarycenterAppIcon.png"));

}

QString SEBarycenterAppGUI::getName() const {

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "DevTutorial: Barycenter";

}

int SEBarycenterAppGUI::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEBarycenterAppGUI::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this app in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

QKeySequence SEBarycenterAppGUI::getShortcut() const {

	// SAMSON Extension generator pro tip: modify this function to return a shortcut

	return QKeySequence("");

}

QString SEBarycenterAppGUI::getToolTip() const {

	// SAMSON Extension generator pro tip: modify this function to add a tooltip

	return QString("");

}

void SEBarycenterAppGUI::onCompute() {

	ui.labelResult->setText(QString("Result: ") + QString::fromStdString(getApp()->compute()));

}
