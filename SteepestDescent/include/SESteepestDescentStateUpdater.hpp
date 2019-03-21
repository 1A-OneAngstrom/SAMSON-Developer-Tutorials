#pragma once 

#include "SBSStateUpdaterParticleSystem.hpp"

class SESteepestDescentStateUpdater : public SBSStateUpdaterParticleSystem {

	SB_CLASS

public:

	SESteepestDescentStateUpdater(SBMDynamicalModelParticleSystem* dynamicalModel, SBMInteractionModelParticleSystem* interactionModel);
	virtual ~SESteepestDescentStateUpdater();
	
	/// \name Simulation
	//@{

	virtual void												updateState();
	
	//@}

	/// \name Rendering
	//@{

	virtual void												display();																///< Displays the state updater
	virtual void												displayForShadow();														///< Displays the state updater for shadow purposes
	virtual void												displayForSelection();													///< Displays the state updater for selection purposes

	virtual void												expandBounds(SBIAPosition3& bounds) const;								///< Expands the bounds to make sure the state updater fits inside them

	virtual void												collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData);		///< To collect ambient occlusion data

	//@}

};


SB_REGISTER_TARGET_TYPE(SESteepestDescentStateUpdater, "SESteepestDescentStateUpdater", "BB707A94-2CFB-6600-3CF1-598E41EC54A5");
SB_DECLARE_BASE_TYPE(SESteepestDescentStateUpdater, SBSStateUpdaterParticleSystem);
