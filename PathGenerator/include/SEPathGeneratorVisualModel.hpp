#pragma once 

#include "SBMVisualModel.hpp"

#include "SBBaseEvent.hpp"
#include "SBDocumentEvent.hpp"
#include "SBStructuralEvent.hpp"
#include "SEPathGeneratorNode.hpp"


/// This class implements a visual model

class SB_EXPORT SEPathGeneratorVisualModel : public SBMVisualModel {

	SB_CLASS

public:

	/// \name Constructors and destructors
	//@{

	SEPathGeneratorVisualModel();																										///< Builds a visual model
	SEPathGeneratorVisualModel(const SBNodeIndexer& nodeIndexer);																		///< Builds a visual model 
	virtual ~SEPathGeneratorVisualModel();																								///< Destructs the visual model

	//@}

	/// \name Serialization
	//@{

	virtual bool												isSerializable() const override;										///< Returns true when the class is serializable

	virtual void												serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0)) const override;		///< Serializes the node
	virtual void												unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0)) override;			///< Unserializes the node

	//@}

	/// \name Topology
	//@{

	virtual	void												onErase() override;														///< Erases the visual model

	//@}

	/// \name Rendering
	//@{

	virtual void												display(SBNode::RenderingPass renderingPass) override;					///< Displays the visual model

	virtual void												expandBounds(SBIAPosition3& bounds) const override;						///< Expands the bounds to make sure the visual model fits inside them

	virtual void												collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) override;		///< To collect ambient occlusion data

	//@}

	/// \name Events
	//@{

	virtual void												onBaseEvent(SBBaseEvent* baseEvent);									///< Handles base events
	virtual void												onDocumentEvent(SBDocumentEvent* documentEvent);						///< Handles document events
	virtual void												onStructuralEvent(SBStructuralEvent* documentEvent);					///< Handles structural events

	//@}

	void														addNode(SEPathGeneratorNode* pathNode);
	void														removeNode(SEPathGeneratorNode* pathNode);

private:

	SBPointerList<SEPathGeneratorNode>							pathNodeList;

};


SB_REGISTER_TARGET_TYPE(SEPathGeneratorVisualModel, "SEPathGeneratorVisualModel", "852B9A50-D0D8-CC1E-2BC7-FCDCA8746F9D");
SB_DECLARE_BASE_TYPE(SEPathGeneratorVisualModel, SBMVisualModel);
