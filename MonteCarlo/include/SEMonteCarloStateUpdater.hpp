#pragma once 

#include "SBSStateUpdaterParticleSystem.hpp"
#include "SBRandom.hpp"
#include "SAMSON.hpp"

class SB_EXPORT SEMonteCarloStateUpdater : public SBSStateUpdaterParticleSystem {

	SB_CLASS

public:

	SEMonteCarloStateUpdater(SBMDynamicalModelParticleSystem* dynamicalModel, SBMInteractionModelParticleSystem* interactionModel);
	virtual ~SEMonteCarloStateUpdater();
	
	/// \name Simulation
	//@{

	virtual void												updateState() override;
	
	//@}

	/// \name Rendering
	//@{

	virtual void												display(SBNode::RenderingPass renderingPass) override;					///< Displays the state updater

	virtual void												expandBounds(SBIAPosition3& bounds) const override;						///< Expands the bounds to make sure the state updater fits inside them

	virtual void												collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) override;		///< To collect ambient occlusion data

	//@}

	/// \name Setters
	//@{

	void														setNumberOfMovingParticles(int n);
	void														setTemperature(SBQuantity::temperature T);

	//@}

private:

	// Monte Carlo variables
	unsigned int												numberOfRejects{ 0 };
	unsigned int												numberOfTrials{ 0 };
	SBRandom													randomNumberGenerator;

	// Metropolis variables
	unsigned int												numberOfMovingParticles{ 0 };
	SBQuantity::angstrom										maximumDisplacement;
	SBQuantity::temperature										temperature;

};


SB_REGISTER_TARGET_TYPE(SEMonteCarloStateUpdater, "SEMonteCarloStateUpdater", "EEF9BCFC-1A22-3C07-F981-540B47F2D91C");
SB_DECLARE_BASE_TYPE(SEMonteCarloStateUpdater, SBSStateUpdaterParticleSystem);
