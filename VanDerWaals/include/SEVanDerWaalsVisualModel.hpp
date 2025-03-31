#pragma once 

#include "SBMVisualModel.hpp"

#include "SBBaseEvent.hpp"
#include "SBDocumentEvent.hpp"
#include "SBStructuralEvent.hpp"
#include "SBAtom.hpp"

#include "SBGRenderOpenGLFunctions.hpp"


/// This class implements a visual model

class SB_EXPORT SEVanDerWaalsVisualModel : public SBMVisualModel {

	SB_CLASS

public:

	/// \name Constructors and destructors
	//@{

	SEVanDerWaalsVisualModel();																											///< Builds a visual model					
	SEVanDerWaalsVisualModel(const SBNodeIndexer& nodeIndexer);																			///< Builds a visual model 
	virtual ~SEVanDerWaalsVisualModel();																								///< Destructs the visual model

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

	virtual void												display(RenderingPass renderingPass) override;							///< Displays the node

	virtual void												expandBounds(SBIAPosition3& bounds) const override;						///< Expands the bounds to make sure the visual model fits inside them

	virtual void												collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) override;		///< To collect ambient occlusion data

	//@}

	/// \name Events
	//@{

	virtual void												onBaseEvent(SBBaseEvent* event);									///< Handles base events
	virtual void												onDocumentEvent(SBDocumentEvent* event);						///< Handles document events
	virtual void												onStructuralEvent(SBStructuralEvent* event);					///< Handles structural events

	//@}

	/// \name Radius factor
	//@{

	float														getRadiusFactor() const;
	void														setRadiusFactor(float value);
	bool														hasRadiusFactorRange() const;
	float														getMinimumRadiusFactor() const;
	float														getMaximumRadiusFactor() const;
	float														getDefaultRadiusFactor() const;
	float														getRadiusFactorSingleStep() const;
	std::string													getRadiusFactorSuffix() const;

	//@}

private:

	friend class removeAtomCommand;

	SBPointerIndexer<SBAtom>									atomIndexer;

	float														radiusFactor{ 1.0f };													///< The radius factor

	/// \name Display data
	//@{

	bool														updateRequired{ true };
	void														updateDisplayData();													///< Updates display data

	unsigned int												numberOfAtoms{ 0 };

	float*														positionData{ nullptr };
	float*														radiusData{ nullptr };
	float*														colorData{ nullptr };
	unsigned int*												flagData{ nullptr };
	unsigned int*												nodeIndexData{ nullptr };

	//@}
	
	static SB_OPENGL_FUNCTIONS*									gl;

};


SB_REGISTER_TARGET_TYPE(SEVanDerWaalsVisualModel, "SEVanDerWaalsVisualModel", "9EDCF553-97F9-07EB-9192-0157BF80D666");
SB_DECLARE_BASE_TYPE(SEVanDerWaalsVisualModel, SBMVisualModel);
