#include "SEAtomPusherEditor.hpp"
#include "SAMSON.hpp"


SEAtomPusherEditor::SEAtomPusherEditor() {

	// SAMSON Element generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	//propertyWidget = new SEAtomPusherEditorGUI(this);
	//propertyWidget->loadDefaultSettings();
	//SAMSON::addWidget(propertyWidget);

	spherePosition = SBPosition3();
	sphereRadius   = SBQuantity::angstrom(2.0);
	sphereIsActive = false;

	SAMSON::requestViewportUpdate();

}

SEAtomPusherEditor::~SEAtomPusherEditor() {

	// SAMSON Element generator pro tip: disconnect from signals you might have connected to.

	//propertyWidget->saveDefaultSettings();
	//delete propertyWidget;

}

SEAtomPusherEditorGUI* SEAtomPusherEditor::getPropertyWidget() const { return static_cast<SEAtomPusherEditorGUI*>(propertyWidget); }

SBCContainerUUID SEAtomPusherEditor::getUUID() const { return SBCContainerUUID("C0FAC9D5-E704-ACFA-A352-C4A0DF81F365"); }

QString SEAtomPusherEditor::getName() const { 

	// SAMSON Element generator pro tip: this name should not be changed

	return "DevTutorial: Atom pusher";

}

QString SEAtomPusherEditor::getDescription() const {

	// SAMSON Element generator pro tip: modify this function to return a user-friendly string that will be displayed in menus

	return QObject::tr("DevTutorial: Atom pusher");

}

QPixmap SEAtomPusherEditor::getLogo() const {

	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your editor.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEAtomPusherEditorIcon.png"));

}

QKeySequence SEAtomPusherEditor::getShortcut() const { 
	
	// SAMSON Element generator pro tip: modify this function to associate a tentative shortcut to your editor

	return QKeySequence(""); 

}

QString SEAtomPusherEditor::getToolTip() const { 
	
	// SAMSON Element generator pro tip: modify this function to have your editor display a tool tip in the SAMSON GUI when the mouse hovers the editor's icon

	return QObject::tr("Pushes atoms when pressed");

}

void SEAtomPusherEditor::beginEditing() {

	// SAMSON Element generator pro tip: SAMSON calls this function when your editor becomes active. 
	// Implement this function if you need to prepare some data structures in order to be able to handle GUI or SAMSON events.

}

void SEAtomPusherEditor::endEditing() {

	// SAMSON Element generator pro tip: SAMSON calls this function immediately before your editor becomes inactive (for example when another editor becomes active). 
	// Implement this function if you need to clean some data structures.

}

void SEAtomPusherEditor::getActions(SBVector<SBAction*>& actionVector) {

	// SAMSON Element generator pro tip: SAMSON calls this function to show the user actions associated to your editor in context menus.
	// Append actions to the actionVector if necessary.
	// Please refer to tutorials for examples.

}

void SEAtomPusherEditor::display() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

	float positionData[3];
	float radiusData[1];
	float colorData[4];
	unsigned int flagData[1];

	positionData[0] = spherePosition[0].getValue();
	positionData[1] = spherePosition[1].getValue();
	positionData[2] = spherePosition[2].getValue();

	radiusData[0] = sphereRadius.getValue();

	if (sphereIsActive){

		// a white sphere
		colorData[0] = 1.0f;
		colorData[1] = 1.0f;
		colorData[2] = 1.0f;
		colorData[3] = 1.0f;

	}
	else {

		// a green sphere
		colorData[0] = 0.0f;
		colorData[1] = 1.0f;
		colorData[2] = 0.0f;
		colorData[3] = 1.0f;

	}

	flagData[0] = 0;

	SAMSON::displaySpheres(1, positionData, radiusData, colorData, flagData);

}

void SEAtomPusherEditor::displayForShadow() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to compute shadows. 
	// Implement this function if your editor displays things in viewports, so that your editor can cast shadows
	// to other objects in SAMSON, for example thanks to the utility
	// functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

	display();

}

void SEAtomPusherEditor::displayInterface() {

	// SAMSON Element generator pro tip: this function is called by SAMSON during the main rendering loop in order to display the editor 2D interface in viewports. 
	// Implement this function if your editor displays a 2D user interface. For example, a rectangle selection editor would display a 2D rectangle in the active viewport. 
	// You may use utility functions provided by SAMSON (e.g. displayLinesOrtho and displayTrianglesOrtho).

}

void SEAtomPusherEditor::mousePressEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	if (event->button() == Qt::MouseButton::LeftButton) {

		sphereIsActive = true;
		SAMSON::requestViewportUpdate();

	}

}

void SEAtomPusherEditor::mouseReleaseEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	if (event->button() == Qt::MouseButton::LeftButton) {

		sphereIsActive = false;
		SAMSON::requestViewportUpdate();

	}

}

void SEAtomPusherEditor::pushAtoms() {

	// check if the sphere is in active state
	if (!sphereIsActive) return;

	// get an indexer of all atoms in the active document
	SBNodeIndexer nodeIndexer;
	SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::IsType(SBNode::Atom));

	SB_FOR(SBNode * node, nodeIndexer){

		SBPointer<SBAtom> atom = static_cast<SBAtom*>(node);
		if (!atom.isValid()) continue;

		// get the atom's position
		SBPosition3 atomPosition = atom->getPosition();
		// compute the vector from the sphere's centers to the atom's center
		SBPosition3 vectorFromSphereCenter = atomPosition - spherePosition;
		// set the min distance between centers of the sphere and the atom by summing their radii
		SBQuantity::length minDistance = sphereRadius + SAMSON::getAtomRadius();

		// check if the sphere touches the atom
		if (vectorFromSphereCenter.norm() < minDistance){

			// push the atom in the direction from the sphere
			vectorFromSphereCenter = vectorFromSphereCenter * (minDistance / vectorFromSphereCenter.norm());
			atom->setPosition(spherePosition + vectorFromSphereCenter);

		}

	}

}

void SEAtomPusherEditor::mouseMoveEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	SBPosition3 nodePosition;
	SBNode* pickedNode = SAMSON::getNode(event->pos(), nodePosition);

	if (pickedNode == NULL)
		spherePosition = SAMSON::getWorldPositionFromViewportPosition(event->pos());
	else
		spherePosition = SAMSON::getWorldPositionFromViewportPosition(event->pos(), nodePosition);

	SAMSON::requestViewportUpdate();

	pushAtoms();

}

void SEAtomPusherEditor::mouseDoubleClickEvent(QMouseEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEAtomPusherEditor::wheelEvent(QWheelEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	int angle = event->delta();
	sphereRadius = sphereRadius * pow(1.002, angle);
	// check for the minimal size of the sphere
	if (sphereRadius < SBQuantity::angstrom(0.1)) sphereRadius = SBQuantity::angstrom(0.1);

	SAMSON::requestViewportUpdate();

	pushAtoms();

}

void SEAtomPusherEditor::keyPressEvent(QKeyEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEAtomPusherEditor::keyReleaseEvent(QKeyEvent* event) {

	// SAMSON Element generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEAtomPusherEditor::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle base events

}

void SEAtomPusherEditor::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle document events 

}

void SEAtomPusherEditor::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Element generator pro tip: implement this function if you need to handle dynamical events 

}

void SEAtomPusherEditor::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Element generator pro tip: implement this function if you need to handle structural events

}
