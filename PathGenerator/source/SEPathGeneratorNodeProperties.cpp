#include "SEPathGeneratorNodeProperties.hpp"
#include "SEPathGeneratorNode.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEPathGeneratorNodeProperties::SEPathGeneratorNodeProperties() {

	node = nullptr;
	ui.setupUi(this);
	observer = new Observer(this);

}

SEPathGeneratorNodeProperties::~SEPathGeneratorNodeProperties() {

	if (!node.isValid()) return;

	node->disconnectBaseSignalFromSlot(observer(), SB_SLOT(&SEPathGeneratorNodeProperties::Observer::onBaseEvent));

}

void SEPathGeneratorNodeProperties::loadSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

void SEPathGeneratorNodeProperties::saveSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

SBCContainerUUID SEPathGeneratorNodeProperties::getUUID() const { return SBCContainerUUID("FEB4B82C-72B4-8972-4D04-7402AB02ED9D"); }

QPixmap SEPathGeneratorNodeProperties::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your node.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEPathGeneratorNodePropertiesIcon.png"));

}

QString SEPathGeneratorNodeProperties::getName() const {

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your node inside SAMSON

	return "SEPathGeneratorNode properties";

}

int SEPathGeneratorNodeProperties::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEPathGeneratorNodeProperties::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this node in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

bool SEPathGeneratorNodeProperties::setup() {

	SBNodeIndexer nodeIndexer;
	SB_FOR(SBNode * node, *SAMSON::getActiveDocument()->getSelectedNodes()) node->getNodes(nodeIndexer, SBNode::GetClass() == std::string("SEPathGeneratorNode") && SBNode::GetElement() == std::string("SEPathGenerator") && SBNode::GetElementUUID() == SBUUID(SB_ELEMENT_UUID));

	if (nodeIndexer.size() == 1) {

		node = static_cast<SEPathGeneratorNode*>((nodeIndexer)[0]);
		node->connectBaseSignalToSlot(observer(), SB_SLOT(&SEPathGeneratorNodeProperties::Observer::onBaseEvent));

		return true;

	}

	return false;

}

bool SEPathGeneratorNodeProperties::setup(SBNode* node) {

	if (node->getProxy()->getName() != "SEPathGeneratorNode") return false;
	if (node->getProxy()->getElement() != "SEPathGenerator") return false;
	if (node->getProxy()->getElementUUID() != SBUUID(SB_ELEMENT_UUID)) return false;

	node = static_cast<SEPathGeneratorNode*>(node);
	node->connectBaseSignalToSlot(observer(), SB_SLOT(&SEPathGeneratorNodeProperties::Observer::onBaseEvent));

	return true;

}

SEPathGeneratorNodeProperties::Observer::Observer(SEPathGeneratorNodeProperties* properties) { this->properties = properties; }
SEPathGeneratorNodeProperties::Observer::~Observer() {}

void SEPathGeneratorNodeProperties::Observer::onBaseEvent(SBBaseEvent* baseEvent) {

	if (baseEvent->getType() == SBBaseEvent::NodeEraseBegin) properties->hide();

}
