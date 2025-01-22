#include "SEPathGeneratorEditor.hpp"
#include "SAMSON.hpp"


SEPathGeneratorEditor::SEPathGeneratorEditor() {

	// SAMSON Extension generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	propertyWidget = nullptr;
	//propertyWidget = new SEPathGeneratorEditorGUI(this);
	//propertyWidget->loadDefaultSettings();

}

SEPathGeneratorEditor::~SEPathGeneratorEditor() {

	// SAMSON Extension generator pro tip: disconnect from signals you might have connected to.

	if (propertyWidget) {

		propertyWidget->saveDefaultSettings();
		delete propertyWidget;

	}

}

SEPathGeneratorEditorGUI* SEPathGeneratorEditor::getPropertyWidget() const { return static_cast<SEPathGeneratorEditorGUI*>(propertyWidget); }

SBCContainerUUID SEPathGeneratorEditor::getUUID() const { return SBCContainerUUID("EA6AFDF9-FB1E-10AE-94F9-C98D913ABD26"); }

QString SEPathGeneratorEditor::getName() const { 

	// SAMSON Extension generator pro tip: this name should not be changed

	return "DevTutorial: Path Generator Editor"; 

}

QString SEPathGeneratorEditor::getDescription() const { 
	
	// SAMSON Extension generator pro tip: modify this function to return a user-friendly string that will be displayed in menus

	return QObject::tr("DevTutorial: Path Generator Editor"); 

}

QPixmap SEPathGeneratorEditor::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your editor.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEPathGeneratorEditorIcon.png"));

}

int SEPathGeneratorEditor::getFormat() const { 
	
	// SAMSON Extension generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)
	
	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QKeySequence SEPathGeneratorEditor::getShortcut() const { 
	
	// SAMSON Extension generator pro tip: modify this function to associate a tentative shortcut to your editor

	return QKeySequence(""); 

}

QString SEPathGeneratorEditor::getToolTip() const { 
	
	// SAMSON Extension generator pro tip: modify this function to have your editor display a tool tip in the SAMSON GUI when the mouse hovers the editor's icon

	return QObject::tr("Click in the viewport to create a path and add nodes to it.<br>Press Escape to end the path.");

}

void SEPathGeneratorEditor::loadSettings(SBGSettings* settings) {

	if (settings == nullptr) return;
	
	// SAMSON Extension generator pro tip: complete this function so your importer can save its GUI state from one session to the next

}

void SEPathGeneratorEditor::saveSettings(SBGSettings* settings) {

	if (settings == nullptr) return;

	// SAMSON Extension generator pro tip: complete this function so your importer can save its GUI state from one session to the next

}

void SEPathGeneratorEditor::beginEditing() {

	// SAMSON Extension generator pro tip: SAMSON calls this function when your editor becomes active. 
	// Implement this function if you need to prepare some data structures in order to be able to handle GUI or SAMSON events.

	path = nullptr;
	selectedPathNode = nullptr;

}

void SEPathGeneratorEditor::endEditing() {

	// SAMSON Extension generator pro tip: SAMSON calls this function immediately before your editor becomes inactive (for example when another editor becomes active). 
	// Implement this function if you need to clean some data structures.

	path = nullptr;
	selectedPathNode = nullptr;

}

bool SEPathGeneratorEditor::isSelectionDependent() const {

	// SAMSON Extension generator pro tip: return true when the editor's context menu actions depend on the current selection

	return false;

}

void SEPathGeneratorEditor::getQuickAccessActions(SBVector<SBAction*>& actionVector) {

	// SAMSON Extension generator pro tip: SAMSON calls this function to determine which actions should be shown to the user for quick access (typically in the viewport).
	// Append actions to the actionVector if necessary.
	// Please refer to tutorials for examples.

}

void SEPathGeneratorEditor::getContextMenuActions(SBVector<SBAction*>& actionVector) {

	// SAMSON Extension generator pro tip: SAMSON calls this function to determine which actions should be shown to the user actions in the context menu.
	// Append actions to the actionVector if necessary.
	// Please refer to tutorials for examples.

}

void SEPathGeneratorEditor::display(SBNode::RenderingPass renderingPass) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SEPathGeneratorEditor::mousePressEvent(QMouseEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	// find whether the user clicked on a node path

	SBNode* node = SAMSON::getNode(event->pos(),
		(SBNode::GetClass() == std::string("SEPathGeneratorNode")) &&
		(SBNode::GetElementUUID() == SBUUID(SB_ELEMENT_UUID)));

	if (node) selectedPathNode = static_cast<SEPathGeneratorNode*>(node);
	else selectedPathNode = nullptr;

}

void SEPathGeneratorEditor::mouseReleaseEvent(QMouseEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	if (selectedPathNode != nullptr) {

		selectedPathNode = nullptr;
		return;

	}

	// create the path if necessary, i.e. if we don't have a valid pointer or
	// if our pointer points to an erased path

	if (path == nullptr || (path != nullptr && path->isErased())) {

		path = new SEPathGeneratorVisualModel();
		path->create();
		SAMSON::getActiveDocument()->addChild(path());

	}

	// get a world position from the mouse position when the user clicked

	SBPosition3 position = SAMSON::getWorldPositionFromViewportPosition(event->pos());

	// add a path node

	SEPathGeneratorNode* pathNode = new SEPathGeneratorNode(position);
	path->addNode(pathNode);

	SAMSON::requestViewportUpdate(); // refresh the viewport

}

void SEPathGeneratorEditor::mouseMoveEvent(QMouseEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	if (selectedPathNode != nullptr) {

		// get a world position from the mouse position when the user clicked

		SBPosition3 position = SAMSON::getWorldPositionFromViewportPosition(event->pos());

		// move the path node

		selectedPathNode->setPosition(position);

		// refresh the viewport

		SAMSON::requestViewportUpdate();

	}

}

void SEPathGeneratorEditor::mouseDoubleClickEvent(QMouseEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEPathGeneratorEditor::wheelEvent(QWheelEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEPathGeneratorEditor::keyPressEvent(QKeyEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	if (event->key() == Qt::Key_Escape) {

		path = nullptr;
		selectedPathNode = nullptr;
		event->accept();

	}

}

void SEPathGeneratorEditor::keyReleaseEvent(QKeyEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEPathGeneratorEditor::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle base events

}

void SEPathGeneratorEditor::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle document events 

}

void SEPathGeneratorEditor::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle dynamical events 

}

void SEPathGeneratorEditor::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Extension generator pro tip: implement this function if you need to handle structural events

}
