#pragma once

#include "SBQuantity.hpp"
#include "SBDTypePhysicalInterval.hpp"
#include "SBDTypePhysicalIAVector3.hpp"
#include "SBVector3.hpp"
#include "SBVector6.hpp"
#include "SBMatrix33.hpp"
#include "SBMatrix66.hpp"
#include "SBSpatialTransform.hpp"

/// This class represents an example of a class which has functions that return/receive SAMSON Units and Types

class UnitsExample {

public:

	/// \name Constructors and destructors
	//@{

	UnitsExample();
	~UnitsExample() {}

	//@}


	/// \name Examples for getter and setter functions with SBQuantity and SBType*
	//@{

	SBQuantity::dimensionless const&								getDimensionless();
	void															setDimensionless(const SBQuantity::dimensionless& v);

	SBQuantity::length const&										getLength();
	void															setLength(const SBQuantity::length& v);

	SBQuantity::mass const&											getMass();
	void															setMass(const SBQuantity::mass& v);

	SBQuantity::auMass const&										getAuMass();
	void															setAuMass(const SBQuantity::auMass& v);

	SBQuantity::dalton const&										getDalton();
	void															setDalton(const SBQuantity::dalton& v);

	SBQuantity::electronvolt const&									getEnergyEv();
	void															setEnergyEv(const SBQuantity::electronvolt& v);

	SBQuantity::kilocaloriePerMole const&							getEnergyKcalPerMol();
	void															setEnergyKcalPerMol(const SBQuantity::kilocaloriePerMole& v);

	SBVector3 const&												getVector3();
	void															setVector3(const SBVector3& v);

	SBPosition3 const&												getPosition3();
	void															setPosition3(const SBPosition3& v);

	SBVelocity6 const&												getVelocity6();
	void															setVelocity6(const SBVelocity6& v);

	SBLengthInterval const&											getLengthInterval();
	void															setLengthInterval(const SBLengthInterval& v);

	SBIAForce3 const&												getForceInterval3();
	void															setForceInterval3(const SBIAForce3& v);

	SBInverseMass33 const&											getInverseMass33();
	void															setInverseMass33(const SBInverseMass33& v);

	SBInertia66 const&												getInertia66();
	void															setInertia66(const SBInertia66& v);

	SBSpatialTransform const&										getSpatialTransform();
	void															setSpatialTransform(const SBSpatialTransform& v);


	//@}

private:

	/* Example objects for SBQuantity
	 * SBQuantity provides you with several different unit systems:
	 * SI, Dalton, AU, Electronvolt, KilocaloriePerMole
	*/
	// SI units
	SBQuantity::dimensionless										dimensionless;
	SBQuantity::length												length;
	SBQuantity::mass												mass;
	// AU units
	SBQuantity::auMass												auMass;
	// Dalton units
	SBQuantity::dalton												dalton;
	// electronvolt units
	SBQuantity::electronvolt										energyEv;
	// kilocaloriePerMole units
	SBQuantity::kilocaloriePerMole									kcalPerMol;

	/* Example objects for SBVector3 */
	SBVector3														dimensionlessVec3;
	SBPosition3														position3;

	/* Example objects for SBVector6 */
	SBVelocity6														velocity6;

	/* Example objects for SBPhysicalInterval */
	SBLengthInterval												lengthInterval;

	/* Example objects for SBDTypePhysicalIAVector3 */
	SBIAForce3														forceInterval3;

	/* Example objects for SBPhysicalMatrix33 */
	SBInverseMass33													inverseMass33;

	/* Example objects for SBPhysicalMatrix66 */
	SBInertia66														inertia66;

	/* Example objects for SBSpatialTransform */
	SBSpatialTransform												spatialTransform;

};
