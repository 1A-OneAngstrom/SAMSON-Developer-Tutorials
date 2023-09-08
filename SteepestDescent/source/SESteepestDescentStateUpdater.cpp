#include "SESteepestDescentStateUpdater.hpp"

SESteepestDescentStateUpdater::SESteepestDescentStateUpdater(SBMDynamicalModelParticleSystem* d, SBMInteractionModelParticleSystem* i) : SBSStateUpdaterParticleSystem(d, i) {

	// SAMSON Extension generator pro tip: this constructor is called when initializing the state updater.

	setName("DevTutorial: Steepest Descent");

	setStepSize(SBQuantity::femtosecond(1.0));
	setNumberOfSteps(1);

}

SESteepestDescentStateUpdater::~SESteepestDescentStateUpdater() {

}

void SESteepestDescentStateUpdater::updateState() {

	SBPointerIndexer<SBAtom> const* particleIndexer = (*dynamicalModel)->getAtomIndexer();

	const unsigned int nParticles = particleIndexer->size(); // number of particles in the particle system
	const unsigned int nSteps = getNumberOfSteps(); // the number of iterations per interactive simulation step

	// A state updater that just displaces atoms in the x-direction
	/*
	for (unsigned int k = 0; k < nSteps; k++) {

		for (unsigned int i = 0; i < nParticles; i++) {

			// get the current position of particle i
			SBPosition3 currentPosition = (*dynamicalModel)->getPosition(i);

			SBPosition3 displacement = SBPosition3(SBQuantity::picometer(1.0),
												   SBQuantity::picometer(0.0),
												   SBQuantity::picometer(0.0));

			// change the current position
			SBPosition3 newPosition = currentPosition + displacement;

			// set the new position of particle i
			(*dynamicalModel)->setPosition(i, newPosition);

		}

	}
	*/

	// The basic implementation of the steepest descent minimization algorithm

	for (unsigned int k = 0; k < nSteps; k++) {

		// compute the new energy and forces based on the updated positions
		(*interactionModel)->updateInteractions();
		// tell the dynamical model that we have used the list of updated positions
		(*dynamicalModel)->flushPositionBuffer();

		for (unsigned int i = 0; i < nParticles; i++) {

			// get the current position of particle i
			SBPosition3 currentPosition = (*dynamicalModel)->getPosition(i);

			// get the force applied to particle i
			SBForce3 force = (*interactionModel)->getForce(i);

			// compute the displacement (take care of dimensions)
			SBPosition3 deltaPosition = 1.0 / SBQuantity::mass(1) * getStepSize() * getStepSize() * force;

			// change the current position
			SBPosition3 newPosition = currentPosition + deltaPosition;

			// set the new position of particle i
			(*dynamicalModel)->setPosition(i, newPosition);

		}

		// notify the interaction model that we have used the list of updated forces
		// (actually, we used all forces in this non-adaptive algorithm)
		(*interactionModel)->flushForceBuffer();

	}

	// update the structural model based on the new positions in the dynamical model
	(*dynamicalModel)->updateStructuralNodes();

}

void SESteepestDescentStateUpdater::display(RenderingPass renderingPass) {

	// SAMSON Extension generator pro tip: this function is called by SAMSON during the main rendering loop. 
	// Implement this function to display things in SAMSON, for example thanks to the utility functions provided by SAMSON (e.g. displaySpheres, displayTriangles, etc.)

}

void SESteepestDescentStateUpdater::expandBounds(SBIAPosition3& bounds) const {

	// SAMSON Extension generator pro tip: this function is called by SAMSON to determine the model's spatial bounds. 
	// When this function returns, the bounds interval vector should contain the state updater. 
	// This should be implemented if your state updater displays something in viewports. 

}

void SESteepestDescentStateUpdater::collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData) {

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

