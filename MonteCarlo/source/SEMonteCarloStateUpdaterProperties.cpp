#include "SEMonteCarloStateUpdaterProperties.hpp"
#include "SEMonteCarloStateUpdater.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEMonteCarloStateUpdaterProperties::SEMonteCarloStateUpdaterProperties() {

	stateUpdater = nullptr;
	ui.setupUi(this);
	observer = new Observer(this);

}

SEMonteCarloStateUpdaterProperties::~SEMonteCarloStateUpdaterProperties() {

	if (!stateUpdater.isValid()) return;

	stateUpdater->disconnectBaseSignalFromSlot(observer(), SB_SLOT(&SEMonteCarloStateUpdaterProperties::Observer::onBaseEvent));
	stateUpdater->disconnectStateUpdaterSignalFromSlot(observer(), SB_SLOT(&SEMonteCarloStateUpdaterProperties::Observer::onStateUpdaterEvent));

}

void SEMonteCarloStateUpdaterProperties::loadSettings(SBGSettings *settings) {

	if (settings == nullptr) return;

	ui.spinBoxNumberOfMovingParticles->setValue(settings->loadIntValue("spinBoxNumberOfMovingParticles", 1));
	double v = settings->loadDoubleValue("doubleSpinBoxTemperature", 1.0);
	ui.doubleSpinBoxTemperature->setValue(v);

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

void SEMonteCarloStateUpdaterProperties::saveSettings(SBGSettings *settings) {

	if (settings == nullptr) return;

	settings->saveValue("doubleSpinBoxTemperature", ui.doubleSpinBoxTemperature->value());
	settings->saveValue("spinBoxNumberOfMovingParticles", ui.spinBoxNumberOfMovingParticles->value());

	// SAMSON Extension generator pro tip: complete this function so this property window can save its GUI state from one session to the next

}

SBCContainerUUID SEMonteCarloStateUpdaterProperties::getUUID() const { return SBCContainerUUID("B0B21B55-EBE1-1342-FE8B-BE185F3E4DDE"); }

QPixmap SEMonteCarloStateUpdaterProperties::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your state updater.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/Icons/SEMonteCarloStateUpdaterPropertiesIcon.png"));

}

QString SEMonteCarloStateUpdaterProperties::getName() const {

	// SAMSON Extension generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your state updater inside SAMSON

	return "DevTutorial: Monte Carlo";

}

int SEMonteCarloStateUpdaterProperties::getFormat() const {

	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)

	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEMonteCarloStateUpdaterProperties::getCitation() const {

	// SAMSON Extension generator pro tip: modify this function to add citation information

	return
		"If you use this state updater in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";

}

void SEMonteCarloStateUpdaterProperties::onStepsChanged(int i) { stateUpdater->setNumberOfSteps(i); }
void SEMonteCarloStateUpdaterProperties::onStepSizeChanged(double d) { stateUpdater->setStepSize(SBQuantity::femtosecond(d)); }

void SEMonteCarloStateUpdaterProperties::onNumberOfMovingParticlesChanged(int i) {

	stateUpdater->setNumberOfMovingParticles(i);

}

void SEMonteCarloStateUpdaterProperties::onTemperatureChanged(double d) {

	stateUpdater->setTemperature(SBQuantity::kelvin(d));

}

bool SEMonteCarloStateUpdaterProperties::setup() {

	SBNodeIndexer nodeIndexer;
	SB_FOR(SBNode* node, *SAMSON::getActiveDocument()->getSelectedNodes()) node->getNodes(nodeIndexer, SBNode::GetClass() == std::string("SEMonteCarloStateUpdater") && SBNode::GetElement() == std::string("SEMonteCarlo") && SBNode::GetElementUUID() == SBUUID(SB_ELEMENT_UUID));

	if (nodeIndexer.size() == 1) {

		stateUpdater = static_cast<SEMonteCarloStateUpdater*>(nodeIndexer[0]);
		stateUpdater->connectBaseSignalToSlot(observer(), SB_SLOT(&SEMonteCarloStateUpdaterProperties::Observer::onBaseEvent));
		stateUpdater->connectStateUpdaterSignalToSlot(observer(), SB_SLOT(&SEMonteCarloStateUpdaterProperties::Observer::onStateUpdaterEvent));

		stateUpdater->setTemperature(SBQuantity::kelvin(ui.doubleSpinBoxTemperature->value()));
		stateUpdater->setNumberOfMovingParticles(ui.spinBoxNumberOfMovingParticles->value());

		return true;

	}

	return false;

}

bool SEMonteCarloStateUpdaterProperties::setup(SBNode* node) {

	if (node->getProxy()->getName() != "SEMonteCarloStateUpdater") return false;
	if (node->getProxy()->getElement() != "SEMonteCarlo") return false;
	if (node->getProxy()->getElementUUID() != SBUUID(SB_ELEMENT_UUID)) return false;

	stateUpdater = static_cast<SEMonteCarloStateUpdater*>(node);
	stateUpdater->connectBaseSignalToSlot(observer(), SB_SLOT(&SEMonteCarloStateUpdaterProperties::Observer::onBaseEvent));
	stateUpdater->connectStateUpdaterSignalToSlot(observer(), SB_SLOT(&SEMonteCarloStateUpdaterProperties::Observer::onStateUpdaterEvent));

	stateUpdater->setTemperature(SBQuantity::kelvin(ui.doubleSpinBoxTemperature->value()));
	stateUpdater->setNumberOfMovingParticles(ui.spinBoxNumberOfMovingParticles->value());

	return true;

}


SEMonteCarloStateUpdaterProperties::Observer::Observer(SEMonteCarloStateUpdaterProperties* properties) { this->properties = properties; }
SEMonteCarloStateUpdaterProperties::Observer::~Observer() {}

void SEMonteCarloStateUpdaterProperties::Observer::onBaseEvent(SBBaseEvent* baseEvent) {

	if (baseEvent->getType() == SBBaseEvent::NodeEraseBegin) properties->hide();
	
}

void SEMonteCarloStateUpdaterProperties::Observer::onStateUpdaterEvent(SBStateUpdaterEvent* stateUpdaterEvent) {

	if (stateUpdaterEvent->getType() == SBStateUpdaterEvent::StateUpdaterChanged) {

	}

}
