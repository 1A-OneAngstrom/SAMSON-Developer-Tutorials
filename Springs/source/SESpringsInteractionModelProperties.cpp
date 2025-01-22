#include "SESpringsInteractionModelProperties.hpp"
#include "SESpringsInteractionModel.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SESpringsInteractionModelProperties::SESpringsInteractionModelProperties() {

	interactionModel = nullptr;
	ui.setupUi(this);
	observer = new Observer(this);

}

SESpringsInteractionModelProperties::~SESpringsInteractionModelProperties() {

	if (!interactionModel.isValid()) return;

	interactionModel->disconnectBaseSignalFromSlot(observer(), SB_SLOT(&SESpringsInteractionModelProperties::Observer::onBaseEvent));
	interactionModel->disconnectInteractionSignalFromSlot(observer(), SB_SLOT(&SESpringsInteractionModelProperties::Observer::onInteractionEvent));

}

void SESpringsInteractionModelProperties::loadSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

	double bondSpringStiffness = settings->loadDoubleValue("bondSpringStiffness", 1.0);
	ui.doubleSpinBoxSpringStiffness->setValue(bondSpringStiffness);
	onBondSpringStiffnessChanged(bondSpringStiffness);

}

void SESpringsInteractionModelProperties::saveSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

	settings->saveValue("bondSpringStiffness", ui.doubleSpinBoxSpringStiffness->value());

}

SBCContainerUUID SESpringsInteractionModelProperties::getUUID() const { return SBCContainerUUID("CED9EEE7-CC43-7555-521D-DA3E7CDBD16E"); }

QPixmap SESpringsInteractionModelProperties::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your interaction model.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/Icons/SESpringsInteractionModelPropertiesIcon.png"));

}

QString SESpringsInteractionModelProperties::getName() const {

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your interaction model inside SAMSON

	return "DevTutorial: Springs properties";

}

int SESpringsInteractionModelProperties::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable);

}

QString SESpringsInteractionModelProperties::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this interaction model in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

bool SESpringsInteractionModelProperties::setup() {

	SBNodeIndexer nodeIndexer;
	SB_FOR(SBNode * node, *SAMSON::getActiveDocument()->getSelectedNodes()) node->getNodes(nodeIndexer, SBNode::GetClass() == std::string("SESpringsInteractionModel") && SBNode::GetElement() == std::string("SESprings") && SBNode::GetElementUUID() == SBUUID(SB_ELEMENT_UUID));

	if (nodeIndexer.size() == 1) {

		interactionModel = static_cast<SESpringsInteractionModel*>((nodeIndexer)[0]);
		interactionModel->connectBaseSignalToSlot(observer(), SB_SLOT(&SESpringsInteractionModelProperties::Observer::onBaseEvent));
		interactionModel->connectInteractionSignalToSlot(observer(), SB_SLOT(&SESpringsInteractionModelProperties::Observer::onInteractionEvent));

		updateEnergies();

		return true;

	}

	return false;

}

bool SESpringsInteractionModelProperties::setup(SBNode* node) {

	if (node->getProxy()->getName() != "SESpringsInteractionModel") return false;
	if (node->getProxy()->getElement() != "SESprings") return false;
	if (node->getProxy()->getElementUUID() != SBUUID(SB_ELEMENT_UUID)) return false;

	interactionModel = static_cast<SESpringsInteractionModel*>(node);
	interactionModel->connectBaseSignalToSlot(observer(), SB_SLOT(&SESpringsInteractionModelProperties::Observer::onBaseEvent));
	interactionModel->connectInteractionSignalToSlot(observer(), SB_SLOT(&SESpringsInteractionModelProperties::Observer::onInteractionEvent));

	updateEnergies();

	return true;

}

void SESpringsInteractionModelProperties::updateEnergies() {

	ui.labelTotalEnergy->setText(QString(tr("Total energy: ")) + QString::fromStdString(SBQuantity::eV(interactionModel->getEnergy()).toStdString()));

}

SESpringsInteractionModelProperties::Observer::Observer(SESpringsInteractionModelProperties* properties) { this->properties = properties; }
SESpringsInteractionModelProperties::Observer::~Observer() {}

void SESpringsInteractionModelProperties::Observer::onBaseEvent(SBBaseEvent* baseEvent) {

	if (baseEvent->getType() == SBBaseEvent::NodeEraseBegin) properties->hide();

}

void SESpringsInteractionModelProperties::Observer::onInteractionEvent(SBInteractionEvent* interactionEvent) {

	if (interactionEvent->getType() == SBInteractionEvent::InteractionModelChanged) properties->updateEnergies();

}

void SESpringsInteractionModelProperties::onBondSpringStiffnessChanged(double stiffness) {

	interactionModel->setBondSpringStiffness(stiffness);

}

void SESpringsInteractionModelProperties::onResetSpringsClicked() {

	// Reinitialize the spring model with the current bond lengths

	interactionModel->initializeBondSpringsModel();

}
