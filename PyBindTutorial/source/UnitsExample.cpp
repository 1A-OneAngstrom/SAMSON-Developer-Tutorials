#include "UnitsExample.hpp"

UnitsExample::UnitsExample() {

	// SBQuantity
	dimensionless = SBQuantity::dimensionless(1.0);
	length = SBQuantity::length(2.0);
	mass = SBQuantity::mass(3.0);
	auMass = SBQuantity::auMass(4.0);
	dalton = SBQuantity::dalton(5.0);
	energyEv = SBQuantity::electronvolt(6.0);
	kcalPerMol = SBQuantity::kcalPerMol(7.0);

}

SBQuantity::dimensionless const& UnitsExample::getDimensionless() { return dimensionless; }
void UnitsExample::setDimensionless(const SBDQuantity::dimensionless &v) { dimensionless = v; }

SBQuantity::length const& UnitsExample::getLength() { return length; }
void UnitsExample::setLength(const SBDQuantity::length &v) { length = v; }

SBQuantity::mass const& UnitsExample::getMass() { return mass; }
void UnitsExample::setMass(const SBDQuantity::mass &v) { mass = v; }

SBQuantity::auMass const& UnitsExample::getAuMass() { return auMass; }
void UnitsExample::setAuMass(const SBDQuantity::auMass &v) { auMass = v; }

SBQuantity::dalton const& UnitsExample::getDalton() { return dalton; }
void UnitsExample::setDalton(const SBDQuantity::dalton &v) { dalton = v; }

SBQuantity::electronvolt const& UnitsExample::getEnergyEv() { return energyEv; }
void UnitsExample::setEnergyEv(const SBDQuantity::electronvolt &v) { energyEv = v; }

SBQuantity::kcalPerMol const& UnitsExample::getEnergyKcalPerMol() { return kcalPerMol; }
void UnitsExample::setEnergyKcalPerMol(const SBDQuantity::kcalPerMol &v) { kcalPerMol = v; }

SBVector3 const& UnitsExample::getVector3() { return dimensionlessVec3; }
void UnitsExample::setVector3(const SBVector3& v) { dimensionlessVec3 = v; }

SBPosition3 const& UnitsExample::getPosition3() { return position3; }
void UnitsExample::setPosition3(const SBPosition3& v) { position3 = v; }

SBVelocity6 const& UnitsExample::getVelocity6() { return velocity6; }
void UnitsExample::setVelocity6(const SBVelocity6& v) { velocity6 = v; }

SBLengthInterval const& UnitsExample::getLengthInterval() { return lengthInterval; }
void UnitsExample::setLengthInterval(const SBLengthInterval& v) { lengthInterval = v; }

SBIAForce3 const& UnitsExample::getForceInterval3() { return forceInterval3; }
void UnitsExample::setForceInterval3(const SBIAForce3& v) { forceInterval3 = v; }

SBInverseMass33 const& UnitsExample::getInverseMass33() { return inverseMass33; }
void UnitsExample::setInverseMass33(const SBInverseMass33& v) { inverseMass33 = v; }

SBInertia66 const& UnitsExample::getInertia66() { return inertia66; }
void UnitsExample::setInertia66(const SBInertia66& v) { inertia66 = v; }

SBSpatialTransform const& UnitsExample::getSpatialTransform() { return spatialTransform; }
void UnitsExample::setSpatialTransform(const SBSpatialTransform& v) { spatialTransform = v; }
