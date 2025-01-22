#include "SEPathGeneratorNodeGUI.hpp"


SEPathGeneratorNodeGUI::SEPathGeneratorNodeGUI() {}
SEPathGeneratorNodeGUI::~SEPathGeneratorNodeGUI() {}

bool SEPathGeneratorNodeGUI::isSelectionDependent() const {
	
	// SAMSON Extension generator pro tip: return true when the node's context menu actions depend on the current selection
	
	return false;

}

void SEPathGeneratorNodeGUI::getContextMenuActions(SBVector<SBAction*>& actionVector) {
	
	// SAMSON Extension generator pro tip: add actions to actionVector if you want your node to have context menu actions

}

void SEPathGeneratorNodeGUI::mousePressEvent(SBNode* node, QMouseEvent* event, const SBPosition3& pickedPosition) {
	
	// SAMSON Extension generator pro tip: complete this function if you want your node to react to mouse press events 

}

void SEPathGeneratorNodeGUI::mouseReleaseEvent(SBNode* node, QMouseEvent* event, const SBPosition3& pickedPosition) {
	
	// SAMSON Extension generator pro tip: complete this function if you want your node to react to mouse release events 

}

void SEPathGeneratorNodeGUI::mouseDoubleClickEvent(SBNode* node, QMouseEvent* event, const SBPosition3& pickedPosition) {

	// SAMSON Extension generator pro tip: complete this function if you want your node to react to mouse double click events

}

void SEPathGeneratorNodeGUI::mouseMoveEvent(SBNode* node, QMouseEvent* event, const SBPosition3& position) {
	
	// SAMSON Extension generator pro tip: complete this function if you want your node to react to mouse move events 

}

void SEPathGeneratorNodeGUI::wheelEvent(SBNode* node, QWheelEvent* event, const SBPosition3& position) {
	
	// SAMSON Extension generator pro tip: complete this function if you want your node to react to wheel events 

}

void SEPathGeneratorNodeGUI::keyPressEvent(SBNode* node, QKeyEvent* event, const SBPosition3& position) {
	
	// SAMSON Extension generator pro tip: complete this function if you want your node to react to key press events 

}

void SEPathGeneratorNodeGUI::keyReleaseEvent(SBNode* node, QKeyEvent* event, const SBPosition3& position) {
	
	// SAMSON Extension generator pro tip: complete this function if you want your node to react to key release events 

}

