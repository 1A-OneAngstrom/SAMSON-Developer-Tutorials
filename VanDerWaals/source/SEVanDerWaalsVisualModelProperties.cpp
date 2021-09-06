#include "SEVanDerWaalsVisualModelProperties.hpp"
#include "SEVanDerWaalsVisualModel.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEVanDerWaalsVisualModelProperties::SEVanDerWaalsVisualModelProperties() {

	visualModel = 0;
	ui.setupUi( this );
	observer = new Observer(this);

}

SEVanDerWaalsVisualModelProperties::~SEVanDerWaalsVisualModelProperties() {

	if (!visualModel.isValid()) return;

	visualModel->disconnectBaseSignalFromSlot(observer(), SB_SLOT(&SEVanDerWaalsVisualModelProperties::Observer::onBaseEvent));
	visualModel->disconnectVisualSignalFromSlot(observer(), SB_SLOT(&SEVanDerWaalsVisualModelProperties::Observer::onVisualEvent));

}

void SEVanDerWaalsVisualModelProperties::loadSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;
	
	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

void SEVanDerWaalsVisualModelProperties::saveSettings( SBGSettings *settings ) {

	if ( settings == nullptr ) return;

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

SBCContainerUUID SEVanDerWaalsVisualModelProperties::getUUID() const { return SBCContainerUUID( "91E8D450-7244-19EA-2987-C60D6159D39F" );}

QPixmap SEVanDerWaalsVisualModelProperties::getLogo() const { 
	
	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your visual model.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/Icons/SEVanDerWaalsVisualModelPropertiesIcon.png"));

}

QString SEVanDerWaalsVisualModelProperties::getName() const { 

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your visual model inside SAMSON

	return "Dev tutorial: Van Der Waals Visual Model";

}

int SEVanDerWaalsVisualModelProperties::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEVanDerWaalsVisualModelProperties::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this visual model in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

bool SEVanDerWaalsVisualModelProperties::setup() {

	SBNodeIndexer nodeIndexer;
	SB_FOR(SBNode* node, *SAMSON::getActiveDocument()->getSelectedNodes()) node->getNodes(nodeIndexer, SBNode::GetClass() == std::string("SEVanDerWaalsVisualModel") && SBNode::GetElement() == std::string("SEVanDerWaals") && SBNode::GetElementUUID() == SBUUID(SB_ELEMENT_UUID));

	if (nodeIndexer.size() == 1) {

		visualModel = static_cast<SEVanDerWaalsVisualModel*>((nodeIndexer)[0]);
		visualModel->connectBaseSignalToSlot(observer(), SB_SLOT(&SEVanDerWaalsVisualModelProperties::Observer::onBaseEvent));
		visualModel->connectVisualSignalToSlot(observer(), SB_SLOT(&SEVanDerWaalsVisualModelProperties::Observer::onVisualEvent));

		return true;

	}

	return false;

}

bool SEVanDerWaalsVisualModelProperties::setup(SBNode* node) {

	if (node->getProxy()->getName() != "SEVanDerWaalsVisualModel") return false;
	if (node->getProxy()->getElement() != "SEVanDerWaals") return false;
	if (node->getProxy()->getElementUUID() != SBUUID(SB_ELEMENT_UUID)) return false;

	visualModel = static_cast<SEVanDerWaalsVisualModel*>(node);
	visualModel->connectBaseSignalToSlot(observer(), SB_SLOT(&SEVanDerWaalsVisualModelProperties::Observer::onBaseEvent));
	visualModel->connectVisualSignalToSlot(observer(), SB_SLOT(&SEVanDerWaalsVisualModelProperties::Observer::onVisualEvent));

	return true;

}

void SEVanDerWaalsVisualModelProperties::onRadiusFactorChanged(double radiusFactor) {

	if (!visualModel.isValid()) return;

	// set the radius factor for the visual model
	visualModel->setRadiusFactor(radiusFactor);

	// request re-rendering of the viewport
	SAMSON::requestViewportUpdate();

}

SEVanDerWaalsVisualModelProperties::Observer::Observer(SEVanDerWaalsVisualModelProperties* properties) { this->properties = properties; }
SEVanDerWaalsVisualModelProperties::Observer::~Observer() {}

void SEVanDerWaalsVisualModelProperties::Observer::onBaseEvent(SBBaseEvent* baseEvent) {

	if (baseEvent->getType() == SBBaseEvent::NodeEraseBegin) properties->hide();

}

void SEVanDerWaalsVisualModelProperties::Observer::onVisualEvent(SBVisualEvent* visualEvent) {

	if (visualEvent->getType() == SBVisualEvent::VisualModelChanged) {
		
		// SAMSON Extension generator pro tip: modify this function if the property window
		// needs to be updated when the VisualModelChanged event is sent
				
	}

}
