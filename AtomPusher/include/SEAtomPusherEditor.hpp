#pragma once 

#include "SBGEditor.hpp"
#include "SEAtomPusherEditorGUI.hpp"

#include "SBBaseEvent.hpp"
#include "SBDocumentEvent.hpp"
#include "SBDynamicalEvent.hpp"
#include "SBStructuralEvent.hpp"
#include "SBAction.hpp"

/// This class implements an editor

class SB_EXPORT SEAtomPusherEditor : public SBGEditor {

	SB_CLASS
	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEAtomPusherEditor();																												///< Builds an editor
	virtual ~SEAtomPusherEditor();																										///< Destructs the editor

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const override;												///< Returns the widget UUID
	virtual QString												getName() const override;												///< Returns the class name
	virtual QString												getDescription() const override;										///< Returns the menu item text
	virtual QPixmap												getLogo() const override;												///< Returns the pixmap logo
	virtual QKeySequence										getShortcut() const override;											///< Returns the shortcut
	virtual QString												getToolTip() const override;											///< Returns the tool tip

	//@}

	/// \name Editing
	//@{

	virtual void												beginEditing() override;												///< Called when editing is about to begin
	virtual void												endEditing() override;													///< Called when editing is about to end

	//@}

	/// \name Actions
	//@{

	virtual bool												isSelectionDependent() const override;									///< Returns true when the editor's context menu actions depend on the current selection

	virtual void												getQuickAccessActions(SBVector<SBGAction*>& actionVector) override;		///< Returns the editor's quick access actions 
	virtual void												getContextMenuActions(SBVector<SBGAction*>& actionVector) override;		///< Returns the editor's context menu actions

	//@}

	/// \name Rendering
	//@{

	virtual void												display(SBNode::RenderingPass renderingPass) override;					///< To display elements related to the editor

	//@}

	/// \name GUI Events
	//@{

	virtual void												mousePressEvent(QMouseEvent* event) override;							///< Handles mouse press event
	virtual void												mouseReleaseEvent(QMouseEvent* event) override;							///< Handles mouse release event
	virtual void												mouseMoveEvent(QMouseEvent* event) override;							///< Handles mouse move event
	virtual void												mouseDoubleClickEvent(QMouseEvent* event) override;						///< Handles mouse double click event

	virtual void												wheelEvent(QWheelEvent* event) override;								///< Handles wheel event

	virtual void												keyPressEvent(QKeyEvent* event) override;								///< Handles key press event
	virtual void												keyReleaseEvent(QKeyEvent* event) override;								///< Handles key release event

	//@}

	/// \name SAMSON Events
	//@{

	virtual void												onBaseEvent(SBBaseEvent* baseEvent);									///< Handles base events
	virtual void												onDynamicalEvent(SBDynamicalEvent* dynamicalEvent);						///< Handles dynamical events
	virtual void												onDocumentEvent(SBDocumentEvent* documentEvent);						///< Handles document events
	virtual void												onStructuralEvent(SBStructuralEvent* documentEvent);					///< Handles structural events

	//@}

	/// \name GUI
	//@{

	SEAtomPusherEditorGUI*										getPropertyWidget() const;												///< Returns the property widget of the editor

	//@}

	void														pushAtoms();

	SBPosition3													spherePosition;
	SBQuantity::length											sphereRadius;
	bool														sphereIsActive{ false };

};


SB_REGISTER_TYPE(SEAtomPusherEditor, "SEAtomPusherEditor", "72F80EB5-E984-57D6-CFF5-7BFDCF0E139C");
SB_DECLARE_BASE_TYPE(SEAtomPusherEditor, SBGEditor);
