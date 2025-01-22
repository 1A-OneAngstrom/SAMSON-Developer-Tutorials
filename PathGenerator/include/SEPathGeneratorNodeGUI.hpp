#pragma once 

#include "SBGDataGraphNode.hpp"


/// This class implements the GUI of a node

class SB_EXPORT SEPathGeneratorNodeGUI : public SBGDataGraphNode {

	SB_CLASS

public:

	/// \name Constructors and destructors
	//@{

	SEPathGeneratorNodeGUI();																																	///< Builds a GUI class for a node
	virtual ~SEPathGeneratorNodeGUI();																															///< Destructs the GUI class of a node

	//@}

	/// \name Actions
	//@{

	virtual bool												isSelectionDependent() const;																	///< Returns true when the node's context menu actions depend on the current selection
	virtual void												getContextMenuActions(SBVector<SBAction*>& actionVector);										///< Returns the node's context menu actions

	//@}

	/// \name Event
	//@{

	virtual void												mousePressEvent(SBNode* node, QMouseEvent* event, const SBPosition3& pickedPosition);			///< Handles mouse press event
	virtual void												mouseReleaseEvent(SBNode* node, QMouseEvent* event, const SBPosition3& pickedPosition);			///< Handles mouse release event
	virtual void												mouseDoubleClickEvent(SBNode* node, QMouseEvent* event, const SBPosition3& pickedPosition);		///< Handles mouse double click event

	virtual void												mouseMoveEvent(SBNode* node, QMouseEvent* event, const SBPosition3& position);					///< Handles mouse move event

	virtual void												wheelEvent(SBNode* node, QWheelEvent* event, const SBPosition3& position);						///< Handles wheel event

	virtual void												keyPressEvent(SBNode* node, QKeyEvent* event, const SBPosition3& position);						///< Handles key press event
	virtual void												keyReleaseEvent(SBNode* node, QKeyEvent* event, const SBPosition3& position);					///< Handles key release event

	//@}

};


SB_REGISTER_TYPE(SEPathGeneratorNodeGUI, "SEPathGeneratorNodeGUI", "078D41F4-2F90-81F3-4E54-49312D1AEBB8");
SB_DECLARE_BASE_TYPE(SEPathGeneratorNodeGUI, SBGDataGraphNode);
