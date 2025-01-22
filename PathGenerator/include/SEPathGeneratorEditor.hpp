#pragma once 

#include "SBGEditor.hpp"
#include "SEPathGeneratorEditorGUI.hpp"
#include "SEPathGeneratorVisualModel.hpp"

#include "SBBaseEvent.hpp"
#include "SBDocumentEvent.hpp"
#include "SBDynamicalEvent.hpp"
#include "SBStructuralEvent.hpp"
#include "SBAction.hpp"

/// This class implements an editor

class SB_EXPORT SEPathGeneratorEditor : public SBGEditor {

	SB_CLASS
	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEPathGeneratorEditor();																											///< Builds an editor
	virtual ~SEPathGeneratorEditor();																									///< Destructs the editor

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const override;												///< Returns the widget UUID
	virtual QString												getName() const override;												///< Returns the class name
	virtual QString												getDescription() const override;										///< Returns the menu item text
	virtual QPixmap												getLogo() const override;												///< Returns the pixmap logo
	virtual int													getFormat() const override;												///< Returns the format
	virtual QKeySequence										getShortcut() const override;											///< Returns the shortcut
	virtual QString												getToolTip() const override;											///< Returns the tool tip

	//@}

	///\name Settings
	//@{

	virtual void												loadSettings(SBGSettings* settings) override;							///< Loads \p settings
	virtual void												saveSettings(SBGSettings* settings) override;							///< Saves \p settings

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

	virtual void												display(SBNode::RenderingPass renderingPass) override;					///< Displays the editor

	//@}

	/// \name GUI Events
	//@{

	virtual void												mousePressEvent(QMouseEvent* event);									///< Handles mouse press event
	virtual void												mouseReleaseEvent(QMouseEvent* event);									///< Handles mouse release event
	virtual void												mouseMoveEvent(QMouseEvent* event);										///< Handles mouse move event
	virtual void												mouseDoubleClickEvent(QMouseEvent* event);								///< Handles mouse double click event

	virtual void												wheelEvent(QWheelEvent* event);											///< Handles wheel event

	virtual void												keyPressEvent(QKeyEvent* event);										///< Handles key press event
	virtual void												keyReleaseEvent(QKeyEvent* event);										///< Handles key release event

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

	SEPathGeneratorEditorGUI*									getPropertyWidget() const;												///< Returns the property widget of the editor

	//@}

private:

	SBPointer<SEPathGeneratorVisualModel>						path;
	SBPointer<SEPathGeneratorNode>								selectedPathNode;

};


SB_REGISTER_TYPE(SEPathGeneratorEditor, "SEPathGeneratorEditor", "9EEECB5E-9F40-0842-5A5F-5B0D6D508F6A");
SB_DECLARE_BASE_TYPE(SEPathGeneratorEditor, SBGEditor);
