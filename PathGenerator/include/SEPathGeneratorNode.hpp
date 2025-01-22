#pragma once 

#include "SBDDataGraphNode.hpp"
#include "SBVector3.hpp"

/// This class implements a node

class SB_EXPORT SEPathGeneratorNode : public SBDDataGraphNode {

	SB_CLASS

public:

	/// \name Constructors and destructors
	//@{

	SEPathGeneratorNode(const SBPosition3& position);																					///< Builds a node
	virtual ~SEPathGeneratorNode();																										///< Destructs the node

	//@}

	/// \name Serialization
	//@{

	virtual bool												isSerializable() const override;										///< Returns true when the node is serializable

	virtual void												serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0)) const override;		///< Serializes the node
	virtual void												unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0)) override;			///< Unserializes the node

	//@}

	/// \name Topology
	//@{

	virtual bool												addChild(SBDDataGraphNode* node, SBDDataGraphNode* nextNode = 0) override;		///< Adds a child to the node
	virtual bool												removeChild(SBDDataGraphNode* node) override;							///< Removes a child from the node

	virtual SEPathGeneratorNode*								clone() override;														///< Returns a copy of the node and its descendants

	//@}

	/// \name Identity
	//@{

	virtual Type												getType() const override;												///< Returns the type of the data graph node

	//@}

	/// \name Selection functions
	//@{

	virtual void												getNodes(SBNodeIndexer& nodeIndexer, SBDDataGraphNode::Type nodeType, bool selectedNodesOnly = false, const SBNodePredicate& visitPredicate = SBDDataGraphNode::All(), bool includeDependencies = false) const;			///< Collects nodes into \p nodeIndexer, based on a \p nodeType, a selection status and a \p visitPredicate, with or without dependencies
	virtual void												getNodes(SBNodeIndexer& nodeIndexer, const SBNodePredicate& selectionPredicate = SBDDataGraphNode::All(), const SBNodePredicate& visitPredicate = SBDDataGraphNode::All(), bool includeDependencies = false) const;		///< Collects nodes into \p nodeIndexer, based on a \p selectionPredicate and a \p visitPredicate, with or without dependencies

	virtual bool												hasNodes(SBDDataGraphNode::Type nodeType, bool selectedNodesOnly = false, const SBNodePredicate& visitPredicate = SBDDataGraphNode::All(), bool includeDependencies = false) const;										///< Returns whether the node has nodes based on a \p nodeType, a selection status and a \p visitPredicate, with or without dependencies
	virtual bool												hasNodes(const SBNodePredicate& selectionPredicate = SBDDataGraphNode::All(), const SBNodePredicate& visitPredicate = SBDDataGraphNode::All(), bool includeDependencies = false) const;									///< Returns whether the node has nodes based on a \p selectionPredicate and a \p visitPredicate, with or without dependencies

	//@}

	/// \name Visitor functions
	//@{

	virtual void												forEachNodeDepthFirst(void(*action)(SBDDataGraphNode* node)) override;									///< Performs an action on each node
	virtual void												forEachNodeDepthFirst(SBCClass* object, void (SBCClass::*action)(SBDDataGraphNode* node)) override;		///< Performs an action on each node

	//@}

	/// \name Position
	//@{

	SBPosition3													getPosition() const;
	void														setPosition(const SBPosition3& position);

	//@}

private:

	/// \name Topology implementation
	//@{

	virtual void												onErase() override;														///< Implementation of the erase function for this node

	//@}

	SBPosition3													position;

};


SB_REGISTER_TARGET_TYPE(SEPathGeneratorNode, "SEPathGeneratorNode", "A0DF39E6-F0C7-4729-B982-F875D7E9079E");
SB_DECLARE_BASE_TYPE(SEPathGeneratorNode, SBDDataGraphNode);
