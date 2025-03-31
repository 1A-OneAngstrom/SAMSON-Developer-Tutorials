#include "SEPathGeneratorVisualModelProperties.hpp"
#include "SEPathGeneratorVisualModel.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEPathGeneratorVisualModelProperties::SEPathGeneratorVisualModelProperties() {

	visualModel = nullptr;
	ui.setupUi(this);
	observer = new Observer(this);

}

SEPathGeneratorVisualModelProperties::~SEPathGeneratorVisualModelProperties() {

	if (!visualModel.isValid()) return;

	visualModel->disconnectBaseSignalFromSlot(observer(), SB_SLOT(&SEPathGeneratorVisualModelProperties::Observer::onBaseEvent));
	visualModel->disconnectVisualSignalFromSlot(observer(), SB_SLOT(&SEPathGeneratorVisualModelProperties::Observer::onVisualEvent));

}

void SEPathGeneratorVisualModelProperties::loadSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

void SEPathGeneratorVisualModelProperties::saveSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

SBCContainerUUID SEPathGeneratorVisualModelProperties::getUUID() const { return SBCContainerUUID("DF4F4338-C8C8-DABE-2820-1CB94BAB2AB3"); }

QPixmap SEPathGeneratorVisualModelProperties::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your visual model.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEPathGeneratorVisualModelPropertiesIcon.png"));

}

QString SEPathGeneratorVisualModelProperties::getName() const {

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your visual model inside SAMSON

	return "SEPathGeneratorVisualModel properties";

}

int SEPathGeneratorVisualModelProperties::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEPathGeneratorVisualModelProperties::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this visual model in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

bool SEPathGeneratorVisualModelProperties::setup() {

	SBNodeIndexer nodeIndexer;
	SB_FOR(SBNode * node, *SAMSON::getActiveDocument()->getSelectedNodes()) node->getNodes(nodeIndexer, SBNode::GetClass() == std::string("SEPathGeneratorVisualModel") && SBNode::GetElement() == std::string("SEPathGenerator") && SBNode::GetElementUUID() == SBUUID(SB_ELEMENT_UUID));

	if (nodeIndexer.size() == 1) {

		visualModel = static_cast<SEPathGeneratorVisualModel*>((nodeIndexer)[0]);
		visualModel->connectBaseSignalToSlot(observer(), SB_SLOT(&SEPathGeneratorVisualModelProperties::Observer::onBaseEvent));
		visualModel->connectVisualSignalToSlot(observer(), SB_SLOT(&SEPathGeneratorVisualModelProperties::Observer::onVisualEvent));

		return true;

	}

	return false;

}

bool SEPathGeneratorVisualModelProperties::setup(SBNode* node) {

	if (node->getProxy()->getName() != "SEPathGeneratorVisualModel") return false;
	if (node->getProxy()->getElement() != "SEPathGenerator") return false;
	if (node->getProxy()->getElementUUID() != SBUUID(SB_ELEMENT_UUID)) return false;

	visualModel = static_cast<SEPathGeneratorVisualModel*>(node);
	visualModel->connectBaseSignalToSlot(observer(), SB_SLOT(&SEPathGeneratorVisualModelProperties::Observer::onBaseEvent));
	visualModel->connectVisualSignalToSlot(observer(), SB_SLOT(&SEPathGeneratorVisualModelProperties::Observer::onVisualEvent));

	return true;

}

SEPathGeneratorVisualModelProperties::Observer::Observer(SEPathGeneratorVisualModelProperties* properties) { this->properties = properties; }
SEPathGeneratorVisualModelProperties::Observer::~Observer() {}

void SEPathGeneratorVisualModelProperties::Observer::onBaseEvent(SBBaseEvent* baseEvent) {

	if (baseEvent->getType() == SBBaseEvent::NodeErased) properties->hide();
	if (baseEvent->getType() == SBBaseEvent::NodeEraseBegin) properties->hide();
	if (baseEvent->getType() == SBBaseEvent::NodeDeleteBegin) properties->hide();

}

void SEPathGeneratorVisualModelProperties::Observer::onVisualEvent(SBVisualEvent* visualEvent) {

	if (visualEvent->getType() == SBVisualEvent::VisualModelChanged) {

		// SAMSON Extension generator pro tip: modify this function if the property window
		// needs to be updated when the VisualModelChanged event is sent

	}

}
