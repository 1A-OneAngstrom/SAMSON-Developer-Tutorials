#pragma once


#include "SBGDataGraphNodeProperties.hpp" 
#include "ui_SEPathGeneratorNodeProperties.h"
#include "SBPointer.hpp"
#include "SEPathGeneratorNode.hpp"


/// This class implements the property window of the node

// SAMSON Extension generator pro tip: add GUI functionality in this class. The non-GUI functionality should go in the SEPathGeneratorNode class

// SAMSON Extension generator pro tip: if you do not want to have a property window associated to your node, do not expose it in the descriptor. 
// Precisely, remove the line SB_ELEMENT_CLASS(SEPathGeneratorNodeProperties); from the file SEPathGeneratorDescriptor.cpp

class SB_EXPORT SEPathGeneratorNodeProperties : public SBGDataGraphNodeProperties {

	SB_CLASS
	Q_OBJECT

public:

	/// \name Constructors and destructors
	//@{

	SEPathGeneratorNodeProperties();																									///< Constructs a widget to show the properties of the node
	virtual ~SEPathGeneratorNodeProperties();																							///< Destructs the widget

	//@}

	/// \name Identity
	//@{

	virtual SBCContainerUUID									getUUID() const override;												///< Returns the widget UUID
	virtual QString												getName() const override;												///< Returns the widget name (used as a title for the embedding window)
	virtual QPixmap												getLogo() const override;												///< Returns the widget logo
	virtual int													getFormat() const override;												///< Returns the widget format
	virtual QString												getCitation() const override;											///< Returns the citation information

	//@}

	///\name Settings
	//@{

	virtual void												loadSettings(SBGSettings* settings) override;							///< Load GUI settings
	virtual void												saveSettings(SBGSettings* settings) override;							///< Save GUI settings

	//@}

	///\name Setup
	//@{

	virtual bool												setup() override;														///< Initializes the properties widget
	virtual bool												setup(SBNode* node) override;											///< Initializes the properties widget

	//@}

	class Observer : public SBCReferenceTarget {

		Observer(SEPathGeneratorNodeProperties* properties);
		virtual ~Observer();

		friend class SEPathGeneratorNodeProperties;

		void														onBaseEvent(SBBaseEvent* baseEvent);								///< Base event management

		SEPathGeneratorNodeProperties* properties;

	};

private:

	friend class SEPathGeneratorNode;
	Ui::SEPathGeneratorNodePropertiesClass						ui;
	SBPointer<SEPathGeneratorNode>								node;

	SBPointer<Observer>											observer;

};

SB_REGISTER_TYPE(SEPathGeneratorNodeProperties, "SEPathGeneratorNodeProperties", "7A7EC6B5-1C6E-39C5-31C3-218966C78ECD");
SB_DECLARE_BASE_TYPE(SEPathGeneratorNodeProperties, SBGDataGraphNodeProperties);
