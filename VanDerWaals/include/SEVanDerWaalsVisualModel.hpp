#pragma once 

#include "SBMVisualModel.hpp"

#include "SBBaseEvent.hpp"
#include "SBDocumentEvent.hpp"
#include "SBStructuralEvent.hpp"
#include "SBAtom.hpp"


/// This class implements a visual model

class SEVanDerWaalsVisualModel : public SBMVisualModel {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEVanDerWaalsVisualModel();																													///< Builds a visual model					
	SEVanDerWaalsVisualModel(const SBNodeIndexer& nodeIndexer);																					///< Builds a visual model 
	virtual ~SEVanDerWaalsVisualModel();																											///< Destructs the visual model

	//@}

	/// \name Serialization
	//@{

	virtual bool												isSerializable() const;													///< Returns true when the class is serializable

	virtual void												serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0)) const;		///< Serializes the node
	virtual void												unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0));			///< Unserializes the node

	//@}

	/// \name Topology
	//@{

	virtual	void												eraseImplementation();													///< Erases the visual model

	//@}

	/// \name Rendering
	//@{

	virtual void												display(RenderingPass renderingPass);									///< Displays the node

	virtual void												expandBounds(SBIAPosition3& bounds) const;								///< Expands the bounds to make sure the visual model fits inside them

	virtual void												collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData);		///< To collect ambient occlusion data

	//@}

	/// \name Events
	//@{

	virtual void												onBaseEvent(SBBaseEvent* baseEvent);									///< Handles base events
	virtual void												onDocumentEvent(SBDocumentEvent* documentEvent);						///< Handles document events
	virtual void												onStructuralEvent(SBStructuralEvent* documentEvent);					///< Handles structural events

	//@}

	/// \name Radius factor
	//@{

	const float&												getRadiusFactor() const;
	void														setRadiusFactor(const float& r);
	bool														hasRadiusFactorRange() const;
	const float&												getMinimumRadiusFactor() const;
	const float&												getMaximumRadiusFactor() const;
	const float&												getRadiusFactorSingleStep() const;
	std::string													getRadiusFactorSuffix() const;

	//@}

	/// \name Opacity
	//@{

	void														setOpacity(unsigned int opacity);
	unsigned int												getOpacity() const;
	bool														hasOpacityRange() const;
	unsigned int												getMinimumOpacity() const;
	unsigned int												getMaximumOpacity() const;
	unsigned int												getOpacitySingleStep() const;
	std::string													getOpacitySuffix() const;

	//@}

private:

	SBPointerIndexer<SBAtom>									atomIndexer;

	float														radiusFactor;															///< The radius factor
	float														minimumRadiusFactor;
	float														maximumRadiusFactor;
	float														radiusFactorSingleStep;

	float														opacity;																///< Opacity

	/// \name Display data
	//@{

	void														updateDisplayData();													///< Updates polyhedra display data

	unsigned int												numberOfAtoms;

	float*														positionData;
	float*														radiusData;
	float*														colorData;
	unsigned int*												flagData;
	unsigned int*												nodeIndexData;

	//@}

};


SB_REGISTER_TARGET_TYPE(SEVanDerWaalsVisualModel, "SEVanDerWaalsVisualModel", "9EDCF553-97F9-07EB-9192-0157BF80D666");
SB_DECLARE_BASE_TYPE(SEVanDerWaalsVisualModel, SBMVisualModel);
