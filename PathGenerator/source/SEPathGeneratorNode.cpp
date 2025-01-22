#include "SEPathGeneratorNode.hpp"
#include "SAMSON.hpp"


SEPathGeneratorNode::SEPathGeneratorNode(const SBPosition3& position) {

	// SAMSON Extension generator pro tip: this default constructor is called when unserializing the node, so it should perform all default initializations.

	this->position = position;

}

SEPathGeneratorNode::~SEPathGeneratorNode() {

	// SAMSON Extension generator pro tip: disconnect from signals you might have connected to.

}

 bool SEPathGeneratorNode::isSerializable() const {

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Modify the line below to "return true;" if you want this node to be serializable (hence copyable, savable, etc.)

	return false;
	
}

void SEPathGeneratorNode::serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) const {

	SBDDataGraphNode::serialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);

	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to serialize your node.

}

void SEPathGeneratorNode::unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber, const SBVersionNumber& classVersionNumber) {

	SBDDataGraphNode::unserialize(serializer, nodeIndexer, sdkVersionNumber, classVersionNumber);
	
	// SAMSON Extension generator pro tip: serialization is used in SAMSON to e.g. save documents, copy nodes, etc. 
	// Please refer to the SDK documentation for more information.
	// Complete this function to unserialize your node.

}

bool SEPathGeneratorNode::addChild(SBDDataGraphNode* node, SBDDataGraphNode* nextNode) {
	
	// SAMSON Extension generator pro tip: modify this function if your node can have descendants.
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

	return false;
	
}

bool SEPathGeneratorNode::removeChild(SBDDataGraphNode* node) {
	
	// SAMSON Extension generator pro tip: modify this function if your node can have descendants.
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

	return false;
	
}


SEPathGeneratorNode* SEPathGeneratorNode::clone() { return static_cast<SEPathGeneratorNode*>(SBNode::clone()); }

void SEPathGeneratorNode::onErase() {

	// SAMSON Extension generator pro tip: modify this function when you need to perform special tasks when your node is erased (e.g. disconnect from nodes you are connected to).
	// Important: this function must be undoable (i.e. only call undoable functions or add an undo command to the undo stack)

}

SBNode::Type SEPathGeneratorNode::getType() const { 

	// SAMSON Extension generator pro tip: modify this function to return the node type closest to your node's type.

	return SBNode::Undefined; 
	
}

void SEPathGeneratorNode::getNodes(SBNodeIndexer& nodeIndexer, SBNode::Type nodeType, bool selectedNodesOnly, const SBNodePredicate& visitPredicate, bool includeDependencies) const {

	// SAMSON Extension generator pro tip: modify this function if your node has descendants, in order to recursively call this function on these descendants.
	// If includeDependencies is true, you must add to the indexer all nodes that depend on this node without descending from it (for example, a bond would add the atoms it connects).

	if (visitPredicate(this) && (getType() == nodeType) && (!selectedNodesOnly || isSelected())) nodeIndexer.push_back(const_cast<SEPathGeneratorNode*>(this));

}

void SEPathGeneratorNode::getNodes(SBNodeIndexer& nodeIndexer, const SBNodePredicate& selectionPredicate, const SBNodePredicate& visitPredicate, bool includeDependencies) const {

	// SAMSON Extension generator pro tip: modify this function if your node has descendants, in order to recursively call this function on these descendants.
	// If includeDependencies is true, you must add to the indexer all nodes that depend on this node without descending from it (for example, a bond would add the atoms it connects).

	if (visitPredicate(this) && selectionPredicate(this)) nodeIndexer.push_back(const_cast<SEPathGeneratorNode*>(this));

}

bool SEPathGeneratorNode::hasNodes(SBNode::Type nodeType, bool selectedNodesOnly, const SBNodePredicate& visitPredicate, bool includeDependencies) const {

	// SAMSON Extension generator pro tip: modify this function if your node has descendants, in order to recursively call this function on these descendants.
	// If includeDependencies is true, you must check all nodes that depend on this node without descending from it (for example, a bond would add the atoms it connects).

	if (visitPredicate(this) && (getType() == nodeType) && (!selectedNodesOnly || isSelected())) return true;
	
	return false;

}

bool SEPathGeneratorNode::hasNodes(const SBNodePredicate& selectionPredicate, const SBNodePredicate& visitPredicate, bool includeDependencies) const {

	// SAMSON Extension generator pro tip: modify this function if your node has descendants, in order to recursively call this function on these descendants.
	// If includeDependencies is true, you must check all nodes that depend on this node without descending from it (for example, a bond would add the atoms it connects).

	if (visitPredicate(this) && selectionPredicate(this)) return true;
	
	return false;

}

void SEPathGeneratorNode::forEachNodeDepthFirst(void(*action)(SBDDataGraphNode* node)) {

	// SAMSON Extension generator pro tip: modify this function if your node has descendants, in order to recursively call this function on these descendants.

	action(this);

}

void SEPathGeneratorNode::forEachNodeDepthFirst(SBCClass* object, void (SBCClass::*action)(SBDDataGraphNode* node)) {
	
	// SAMSON Extension generator pro tip: modify this function if your node has descendants, in order to recursively call this function on these descendants.

	(*object.*action)(this);

}

SBPosition3 SEPathGeneratorNode::getPosition() const {

	return position;

}

void SEPathGeneratorNode::setPosition(const SBPosition3& position) {

	this->position = position;

}
