#include "SESteepestDescentStateUpdaterProperties.hpp"
#include "SESteepestDescentStateUpdater.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SESteepestDescentStateUpdaterProperties::SESteepestDescentStateUpdaterProperties() {

	stateUpdater = nullptr;
	ui.setupUi(this);
	observer = new Observer(this);

}

SESteepestDescentStateUpdaterProperties::~SESteepestDescentStateUpdaterProperties() {

	if (!stateUpdater.isValid()) return;

	stateUpdater->disconnectBaseSignalFromSlot(observer(), SB_SLOT(&SESteepestDescentStateUpdaterProperties::Observer::onBaseEvent));
	stateUpdater->disconnectStateUpdaterSignalFromSlot(observer(), SB_SLOT(&SESteepestDescentStateUpdaterProperties::Observer::onStateUpdaterEvent));

}

void SESteepestDescentStateUpdaterProperties::loadSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	ui.spinBoxSteps->setValue(settings->loadIntValue("Steps", 1));
	double v = settings->loadDoubleValue("StepSize", 1.0);
	ui.doubleSpinBoxStepSize->setValue(v);

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

void SESteepestDescentStateUpdaterProperties::saveSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	settings->saveValue("Steps", ui.spinBoxSteps->value());
	settings->saveValue("StepSize", ui.doubleSpinBoxStepSize->value());

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

SBCContainerUUID SESteepestDescentStateUpdaterProperties::getUUID() const { return SBCContainerUUID("5DEE681E-E3F2-03BD-2EDD-893100C2FDF0"); }

QPixmap SESteepestDescentStateUpdaterProperties::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your state updater.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/Icons/SESteepestDescentStateUpdaterPropertiesIcon.png"));

}

QString SESteepestDescentStateUpdaterProperties::getName() const {

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your state updater inside SAMSON

	return "DevTutorial: Steepest Descent";

}

int SESteepestDescentStateUpdaterProperties::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SESteepestDescentStateUpdaterProperties::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this state updater in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

void SESteepestDescentStateUpdaterProperties::onStepsChanged(int i) { stateUpdater->setNumberOfSteps(i); }
void SESteepestDescentStateUpdaterProperties::onStepSizeChanged(double d) { stateUpdater->setStepSize(SBQuantity::femtosecond(d)); }

bool SESteepestDescentStateUpdaterProperties::setup() {

	SBNodeIndexer nodeIndexer;
	SB_FOR(SBNode * node, *SAMSON::getActiveDocument()->getSelectedNodes()) node->getNodes(nodeIndexer, SBNode::GetClass() == std::string("SESteepestDescentStateUpdater") && SBNode::GetElement() == std::string("SESteepestDescent") && SBNode::GetElementUUID() == SBUUID(SB_ELEMENT_UUID));

	if (nodeIndexer.size() == 1) {

		stateUpdater = static_cast<SESteepestDescentStateUpdater*>(nodeIndexer[0]);
		stateUpdater->connectBaseSignalToSlot(observer(), SB_SLOT(&SESteepestDescentStateUpdaterProperties::Observer::onBaseEvent));
		stateUpdater->connectStateUpdaterSignalToSlot(observer(), SB_SLOT(&SESteepestDescentStateUpdaterProperties::Observer::onStateUpdaterEvent));

		stateUpdater->setStepSize(SBQuantity::femtosecond(ui.doubleSpinBoxStepSize->value()));
		stateUpdater->setNumberOfSteps(ui.spinBoxSteps->value());

		return true;

	}

	return false;

}

bool SESteepestDescentStateUpdaterProperties::setup(SBNode* node) {

	if (node->getProxy()->getName() != "SESteepestDescentStateUpdater") return false;
	if (node->getProxy()->getElement() != "SESteepestDescent") return false;
	if (node->getProxy()->getElementUUID() != SBUUID(SB_ELEMENT_UUID)) return false;

	stateUpdater = static_cast<SESteepestDescentStateUpdater*>(node);
	stateUpdater->connectBaseSignalToSlot(observer(), SB_SLOT(&SESteepestDescentStateUpdaterProperties::Observer::onBaseEvent));
	stateUpdater->connectStateUpdaterSignalToSlot(observer(), SB_SLOT(&SESteepestDescentStateUpdaterProperties::Observer::onStateUpdaterEvent));

	stateUpdater->setStepSize(SBQuantity::femtosecond(ui.doubleSpinBoxStepSize->value()));
	stateUpdater->setNumberOfSteps(ui.spinBoxSteps->value());

	return true;

}


SESteepestDescentStateUpdaterProperties::Observer::Observer(SESteepestDescentStateUpdaterProperties* properties) : properties(properties) {}
SESteepestDescentStateUpdaterProperties::Observer::~Observer() {}

void SESteepestDescentStateUpdaterProperties::Observer::onBaseEvent(SBBaseEvent* baseEvent) {

	if (baseEvent->getType() == SBBaseEvent::NodeEraseBegin) properties->hide();

}

void SESteepestDescentStateUpdaterProperties::Observer::onStateUpdaterEvent(SBStateUpdaterEvent* stateUpdaterEvent) {

	if (stateUpdaterEvent->getType() == SBStateUpdaterEvent::StateUpdaterChanged) {

	}

}
