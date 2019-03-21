#pragma once 

#include "SBSStateUpdaterParticleSystem.hpp"
#include "SBRandom.hpp"
#include "SAMSON.hpp"

class SEMonteCarloStateUpdater : public SBSStateUpdaterParticleSystem {

	SB_CLASS

public:

	SEMonteCarloStateUpdater(SBMDynamicalModelParticleSystem* dynamicalModel, SBMInteractionModelParticleSystem* interactionModel);
	virtual ~SEMonteCarloStateUpdater();
	
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

	/// \name Setters
	//@{

	void														setNumberOfMovingParticles(int n);
	void														setTemperature(SBQuantity::temperature T);

	//@}


private:

	// Monte Carlo variables
	unsigned int												numberOfRejects;
	unsigned int												numberOfTrials;
	SBRandom													randomNumberGenerator;

	// Metropolis variables
	unsigned int												numberOfMovingParticles;
	SBQuantity::angstrom										maximumDisplacement;
	SBQuantity::temperature										temperature;

};


SB_REGISTER_TARGET_TYPE(SEMonteCarloStateUpdater, "SEMonteCarloStateUpdater", "EEF9BCFC-1A22-3C07-F981-540B47F2D91C");
SB_DECLARE_BASE_TYPE(SEMonteCarloStateUpdater, SBSStateUpdaterParticleSystem);
