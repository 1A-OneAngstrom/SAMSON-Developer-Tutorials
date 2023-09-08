#include "SEAtomPusherEditor.hpp"
#include "SAMSON.hpp"


SEAtomPusherEditor::SEAtomPusherEditor() {

	// SAMSON Extension generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	//propertyWidget = new SEAtomPusherEditorGUI(this);
	//propertyWidget->loadDefaultSettings();
	//SAMSON::addWidget(propertyWidget);

	spherePosition = SBPosition3();
	sphereRadius   = SBQuantity::angstrom(2.0);
	sphereIsActive = false;

	SAMSON::requestViewportUpdate();

}

SEAtomPusherEditor::~SEAtomPusherEditor() {

	// SAMSON Extension generator pro tip: disconnect from signals you might have connected to.

	//propertyWidget->saveDefaultSettings();
	//delete propertyWidget;

}

SEAtomPusherEditorGUI* SEAtomPusherEditor::getPropertyWidget() const { return static_cast<SEAtomPusherEditorGUI*>(propertyWidget); }

SBCContainerUUID SEAtomPusherEditor::getUUID() const { return SBCContainerUUID("C0FAC9D5-E704-ACFA-A352-C4A0DF81F365"); }

QString SEAtomPusherEditor::getName() const { 

	// SAMSON Extension generator pro tip: this name should not be changed

	return "DevTutorial: Atom pusher";

}

QString SEAtomPusherEditor::getDescription() const {

	// SAMSON Extension generator pro tip: modify this function to return a user-friendly string that will be displayed in menus

	return QObject::tr("DevTutorial: Atom pusher");

}

QPixmap SEAtomPusherEditor::getLogo() const {

	// SAMSON Extension generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your editor.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEAtomPusherEditorIcon.png"));

}

QKeySequence SEAtomPusherEditor::getShortcut() const { 
	
	// SAMSON Extension generator pro tip: modify this function to associate a tentative shortcut to your editor

	return QKeySequence(""); 

}

QString SEAtomPusherEditor::getToolTip() const { 
	
	// SAMSON Extension generator pro tip: modify this function to have your editor display a tool tip in the SAMSON GUI when the mouse hovers the editor's icon

	return QObject::tr("Pushes atoms when pressed");

}

void SEAtomPusherEditor::beginEditing() {

	// SAMSON Extension generator pro tip: SAMSON calls this function when your editor becomes active. 
	// Implement this function if you need to prepare some data structures in order to be able to handle GUI or SAMSON events.

}

void SEAtomPusherEditor::endEditing() {

	// SAMSON Extension generator pro tip: SAMSON calls this function immediately before your editor becomes inactive (for example when another editor becomes active). 
	// Implement this function if you need to clean some data structures.

}

void SEAtomPusherEditor::getActions(SBVector<SBAction*>& actionVector) {

	// SAMSON Extension generator pro tip: SAMSON calls this function to show the user actions associated to your editor in context menus.
	// Append actions to the actionVector if necessary.
	// Please refer to tutorials for examples.

}

void SEAtomPusherEditor::display(SBNode::RenderingPass renderingPass) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

	if (renderingPass == SBNode::RenderingPass::OpaqueGeometry || renderingPass == SBNode::RenderingPass::ShadowingGeometry) {

		float positionData[3];
		float radiusData[1];

		positionData[0] = static_cast<float>(spherePosition[0].getValue());
		positionData[1] = static_cast<float>(spherePosition[1].getValue());
		positionData[2] = static_cast<float>(spherePosition[2].getValue());

		radiusData[0] = static_cast<float>(sphereRadius.getValue());

		if (renderingPass == SBNode::RenderingPass::OpaqueGeometry) {

			float colorData[4];
			unsigned int flagData[1];

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
		else if (renderingPass == SBNode::RenderingPass::ShadowingGeometry) {

			// display for shadows

			SAMSON::displaySpheres(1, positionData, radiusData, nullptr, nullptr, true);

		}

	}

}

void SEAtomPusherEditor::mousePressEvent(QMouseEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	if (event->button() == Qt::MouseButton::LeftButton) {

		sphereIsActive = true;
		SAMSON::requestViewportUpdate();

	}

	// accept the event to not pass it to the parent class

	event->accept();

}

void SEAtomPusherEditor::mouseReleaseEvent(QMouseEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
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
	SAMSON::getActiveDocument()->getNodes(nodeIndexer, SBNode::Atom);

	// start the undoable operation
	SAMSON::beginHolding("Pushed atoms");

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

	// end the undoable operation
	SAMSON::endHolding();

}

void SEAtomPusherEditor::mouseMoveEvent(QMouseEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	SBPosition3 nodePosition;
	SBNode* pickedNode = SAMSON::getNode(event->pos(), nodePosition);

	if (pickedNode == nullptr)
		spherePosition = SAMSON::getWorldPositionFromViewportPosition(event->pos());
	else
		spherePosition = SAMSON::getWorldPositionFromViewportPosition(event->pos(), nodePosition);

	SAMSON::requestViewportUpdate();

	pushAtoms();

}

void SEAtomPusherEditor::mouseDoubleClickEvent(QMouseEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEAtomPusherEditor::wheelEvent(QWheelEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

	int angle = event->angleDelta().y();
	sphereRadius = sphereRadius * pow(1.002, angle);
	// check for the minimal size of the sphere
	if (sphereRadius < SBQuantity::angstrom(0.1)) sphereRadius = SBQuantity::angstrom(0.1);

	SAMSON::requestViewportUpdate();

	pushAtoms();

	// accept the event to not pass it to the parent class

	event->accept();

}

void SEAtomPusherEditor::keyPressEvent(QKeyEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEAtomPusherEditor::keyReleaseEvent(QKeyEvent* event) {

	// SAMSON Extension generator pro tip: SAMSON redirects Qt events to the active editor. 
	// Implement this function to handle this event with your editor.

}

void SEAtomPusherEditor::onBaseEvent(SBBaseEvent* baseEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle base events

}

void SEAtomPusherEditor::onDocumentEvent(SBDocumentEvent* documentEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle document events 

}

void SEAtomPusherEditor::onDynamicalEvent(SBDynamicalEvent* dynamicalEvent) {

	// SAMSON Extension generator pro tip: implement this function if you need to handle dynamical events 

}

void SEAtomPusherEditor::onStructuralEvent(SBStructuralEvent* documentEvent) {
	
	// SAMSON Extension generator pro tip: implement this function if you need to handle structural events

}
