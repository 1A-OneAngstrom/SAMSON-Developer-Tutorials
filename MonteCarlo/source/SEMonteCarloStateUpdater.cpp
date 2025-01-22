#include "SEMonteCarloStateUpdater.hpp"

SEMonteCarloStateUpdater::SEMonteCarloStateUpdater(SBMDynamicalModelParticleSystem* d, SBMInteractionModelParticleSystem* i) : SBSStateUpdaterParticleSystem(d, i) {

	// SAMSON Extension generator pro tip: this constructor is called when initializing the state updater.

	setName("DevTutorial: Monte Carlo");

	setStepSize(SBQuantity::femtosecond(1.0));
	setNumberOfSteps(1);

	numberOfRejects = numberOfTrials = 0;
	randomNumberGenerator.seed(SAMSON::getTime());

	numberOfMovingParticles = 5;
	maximumDisplacement = SBQuantity::angstrom(0.1);
	temperature = SBQuantity::kelvin(50);

}

SEMonteCarloStateUpdater::~SEMonteCarloStateUpdater() {

}

void SEMonteCarloStateUpdater::updateState() {

	SBPointerIndexer<SBAtom> const* particleIndexer = (*dynamicalModel)->getAtomIndexer();
	const unsigned int nParticles = particleIndexer->size(); // number of particles in the particle system

	// check the maximum number of particles
	numberOfMovingParticles = (numberOfMovingParticles > nParticles) ? nParticles : numberOfMovingParticles;

	// compute the current energy

	(*interactionModel)->updateInteractions();
	SBQuantity::energy currentEnergy = (*interactionModel)->getEnergy();
	// notify the interaction model that we have used the list of updated forces since we do not need it
	(*interactionModel)->flushForceBuffer();

	// randomly generate the list of moving particles

	std::vector<unsigned int> movingParticleIndexer;
	while (movingParticleIndexer.size() != numberOfMovingParticles) {

		// generate an index of a particle and add it in the indexer of moving particles
		unsigned int idx = static_cast<unsigned int>(randomNumberGenerator.randUnsignedLong() % nParticles);
		movingParticleIndexer.push_back(idx);

	}

	// move particles incrementally

	std::vector<SBPosition3> currentPositionVector;
	for (unsigned int i = 0; i < numberOfMovingParticles; i++) {

		unsigned int currentMovingParticleIndex = movingParticleIndexer[i];
		// store the current position
		SBPosition3 currentPosition = (*dynamicalModel)->getPosition(currentMovingParticleIndex);
		currentPositionVector.push_back(currentPosition);

		// create the random displacement normalized by the maximumDisplacement
		SBPosition3 displacement((randomNumberGenerator.randDouble1() - 0.5) * maximumDisplacement,
			(randomNumberGenerator.randDouble1() - 0.5) * maximumDisplacement,
			(randomNumberGenerator.randDouble1() - 0.5) * maximumDisplacement);

		SBPosition3 newPosition = currentPosition + displacement;

		// set the new position of particle i
		(*dynamicalModel)->setPosition(currentMovingParticleIndex, newPosition);

	}

	// compute the new energy

	(*interactionModel)->updateInteractions();
	SBQuantity::energy newEnergy = (*interactionModel)->getEnergy();

	// accept or reject

	if (newEnergy > currentEnergy) {

		double p = randomNumberGenerator.randDouble1();
		double b = exp(((currentEnergy - newEnergy) /
			((*SBConstant::boltzmannConstant) * temperature)).getValue());

		// check the probability
		if (p > b) {

			// reject the move
			for (unsigned int i = 0; i < numberOfMovingParticles; i++) {

				unsigned int currentMovingParticleIndex = movingParticleIndexer[i];
				(*dynamicalModel)->setPosition(currentMovingParticleIndex, currentPositionVector[i]);

			}

			numberOfRejects++;

		}

	}
	numberOfTrials++;

	// update the structural model based on the new positions in the dynamical model
	(*dynamicalModel)->updateStructuralNodes();

	// check for the rejects ratio after a certain number of trials
	// and modify the maximum displacement

	if (numberOfTrials == 100) {

		// check the rejects ratio
		if (static_cast<double>(numberOfRejects) / static_cast<double>(numberOfTrials) > 0.5) {

			// rejects constitute to more than a half of trials

			// decrease the maximum displacement
			maximumDisplacement *= 0.95;
			// but not less than 0.01 Å
			maximumDisplacement = (maximumDisplacement > SBQuantity::angstrom(0.01)) ? SBQuantity::angstrom(0.01) : maximumDisplacement;

		}
		else {

			// rejects constitute to less (or equal) than a half of trials

			// increase the maximum displacement by 5%
			maximumDisplacement *= 1.05;

		}

		// reset the number of trials and rejects
		numberOfRejects = 0;
		numberOfTrials = 0;

	}

}

void SEMonteCarloStateUpdater::display(SBNode::RenderingPass renderingPass) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SEMonteCarloStateUpdater::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Extension generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the state updater. 
	// This should be implemented if your state updater displays something in viewports. 

}

void SEMonteCarloStateUpdater::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON to determine your model's influence on ambient occlusion (in case your state updater displays something in viewports).
	// Implement this function if you want your state updater to occlude other objects in ambient occlusion calculations.
	//
	// The ambientOcclusionData represents a nCellsX x nCellsY x nCellsZ grid of occlusion densities over the spatial region (boxOrigin, boxSize).
	// If your model represents geometry at position (x, y, z), then the occlusion density in corresponding grid nodes should be increased.
	//
	// Assuming x, y and z are given in length units (SBQuantity::length, SBQuantity::angstrom, etc.), the grid coordinates are:
	// SBQuantity::dimensionless xGrid = nCellsX * (x - boxOrigin.v[0]) / boxSize.v[0];
	// SBQuantity::dimensionless yGrid = nCellsY * (x - boxOrigin.v[1]) / boxSize.v[1];
	// SBQuantity::dimensionless zGrid = nCellsZ * (x - boxOrigin.v[2]) / boxSize.v[2];
	//
	// The corresponding density can be found at ambientOcclusionData[((int)zGrid.getValue() + 0)*nCellsY*nCellsX + ((int)yGrid.getValue() + 0)*nCellsX + ((int)xGrid.getValue() + 0)] (beware of grid bounds).
	// For higher-quality results, the influence of a point can be spread over neighboring grid nodes.

}

void SEMonteCarloStateUpdater::setNumberOfMovingParticles(int n) {

	numberOfMovingParticles = (n < 1 ? numberOfMovingParticles : n);

}
void SEMonteCarloStateUpdater::setTemperature(SBQuantity::temperature T) {

	temperature = (T < SBQuantity::temperature(0.0) ? temperature : T);

}
