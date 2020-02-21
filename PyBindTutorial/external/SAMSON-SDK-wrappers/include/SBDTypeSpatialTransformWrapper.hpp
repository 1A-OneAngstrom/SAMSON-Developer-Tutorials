#pragma once

#include "SBDQuantityWrapper.hpp"
#include "SBDTypePhysicalVector3Wrapper.hpp"
#include "SBDTypePhysicalVector6Wrapper.hpp"
#include "SBDTypePhysicalMatrix33Wrapper.hpp"
#include "SBDTypePhysicalMatrix66Wrapper.hpp"

#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDTypeSpatialTransform.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

/*! \file SBDTypeSpatialTransformWrapper.hpp */

/// \brief This class is used as a wrapper between SAMSON SDK SBDTypeSpatialTranform and Python.

class SBDTypeSpatialTransformWrapper {

public:

    /// \name Constructors
    //@{

    /// \brief The default constructor initializes all components to zero

	SBDTypeSpatialTransformWrapper() {

		SBDQuantityWrapperSI qo(0.0, orientationScale, orientationExponent);
		SBDQuantityWrapperSI qp(0.0, positionScale, positionExponent);

		orientation = SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapperSI>(qo);
		position = SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>(qp);

	}

	/// \brief Constructs a transform from an \p orientation matrix and a \p position vector
	///
	/// \param orientation The orientation matrix of the spatial transform
	/// \param position The position vector of the spatial transform

	SBDTypeSpatialTransformWrapper(const SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapperSI>& o,
								   const SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>& p) {

		SBDQuantityWrapperSI qo(0.0, orientationScale, orientationExponent);
		SBDQuantityWrapperSI qp(0.0, positionScale, positionExponent);

		orientation = SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapperSI>(qo);
		position = SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>(qp);

		if (o.m[0][0].getExponent() != orientationExponent || p.v[0].getExponent() != positionExponent)
			throw std::runtime_error("Cannot construct a spatial transform: matrix33 should be of type dimensionless, vector3 should be of type position");

		orientation = o;
		position = p;

	}

	/// \brief Constructs a spatial transform from SBSpatialTransform \p st

	SBDTypeSpatialTransformWrapper(const SBSpatialTransform& st) {

		orientation = {{SBDQuantityWrapperSI(st.orientation->m[0][0]),
						SBDQuantityWrapperSI(st.orientation->m[0][1]),
						SBDQuantityWrapperSI(st.orientation->m[0][2])},
					   {SBDQuantityWrapperSI(st.orientation->m[1][0]),
						SBDQuantityWrapperSI(st.orientation->m[1][1]),
						SBDQuantityWrapperSI(st.orientation->m[1][2])},
					   {SBDQuantityWrapperSI(st.orientation->m[2][0]),
						SBDQuantityWrapperSI(st.orientation->m[2][1]),
						SBDQuantityWrapperSI(st.orientation->m[2][2])}};

		position = {SBDQuantityWrapperSI(st.position->v[0]),
					SBDQuantityWrapperSI(st.position->v[1]),
					SBDQuantityWrapperSI(st.position->v[2])};

	}

    //@}

	/// \name Accessors
	//@{

	/// \brief Returns the arbitraty SBSpatialTransform

	SBSpatialTransform										toSBSpatialTransform () const {

		return SBSpatialTransform(
					orientation.template toSBPhysicalMatrix33<SBQuantity::dimensionless>(),
					getSBPhysicalVector3<SBQuantity::position>(position)
					);

	}

	/// \brief Returns the first column of the orientation matrix

	SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>			getE1() const {

		return SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>(orientation.m[0][0], orientation.m[1][0], orientation.m[2][0]);

	}

	/// \brief Returns the second column of the orientation matrix

	SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>			getE2() const {

		return SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>(orientation.m[0][1], orientation.m[1][1], orientation.m[2][1]);

	}

	/// \brief Returns the third column of the orientation matrix

	SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>			getE3() const {

		return SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>(orientation.m[0][2], orientation.m[1][2], orientation.m[2][2]);

	}

	/// \brief Returns the position vector

	SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>			getE4() const {

		return SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>(position.v[0], position.v[1], position.v[2]);

	}

	/// \brief Sets the first column of the orientation matrix to \p vec

	void													setE1(const SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>& vec) {

		if (vec.v[0].getExponent() != orientationExponent)
			throw std::runtime_error("Cannot set the first column of the orientation matrix for transform: types mismatch - input vector should be dimensionless");

		orientation.m[0][0] = vec.v[0];
		orientation.m[1][0] = vec.v[1];
		orientation.m[2][0] = vec.v[2];

	}

	/// \brief Sets the second column of the orientation matrix to \p vec

	void													setE2(const SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>& vec) {

		if (vec.v[0].getExponent() != orientationExponent)
			throw std::runtime_error("Cannot set the second column of the orientation matrix for transform: types mismatch - input vector should be dimensionless");

		orientation.m[0][1] = vec.v[0];
		orientation.m[1][1] = vec.v[1];
		orientation.m[2][1] = vec.v[2];

	}

	/// \brief Sets the third column of the orientation matrix to \p vec

	void													setE3(const SBPhysicalVector3Wrapper<SBDQuantityWrapperSI>& vec) {

		if (vec.v[0].getExponent() != orientationExponent)
			throw std::runtime_error("Cannot set the third column of the orientation matrix for transform: types mismatch - input vector should be dimensionless");

		orientation.m[0][2] = vec.v[0];
		orientation.m[1][2] = vec.v[1];
		orientation.m[2][2] = vec.v[2];

	}

	/// \brief Sets the position vector to \p vec

	void													setE4(const SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI> &vec) {

		if (vec.v[0].getExponent() != positionExponent)
			throw std::runtime_error("Cannot set the position of the spatial transform: types mismatch - input vector should of type position3");

		position = vec;

	}

	/// \brief Returns the orientation of the spatial transform

	SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapperSI>	getOrientation() const {

		return orientation;

	}

	/// \brief Returns the position of the spatial transform

	SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>		getPosition() const {

		return position;

	}

	/// \brief Sets the orientation of the spatial transform to \p om

	void													setOrientation(const SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapperSI> &om) {

		if (om.m[0][0].getExponent() != orientationExponent)
			throw std::runtime_error("Cannot set the orientation of the spatial transform: types mismatch - input matrix should be dimensionless");

		orientation = om;

	}

	/// \brief Sets the position of the spatial transform to \p pos

	void													setPosition(const SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI> &pos) {

		if (pos.v[0].getExponent() != positionExponent)
			throw std::runtime_error("Cannot set the position of the spatial transform: types mismatch - input vector should be of type position3");

		position = pos;

	}

	//@}

	/// \name Operators
	//@{

	/// \brief Returns the result of the transformation of position \p p by this transform
	///
	/// \param p - position

	SBDTypePhysicalVector3WrapperSI							operator*(const SBDTypePhysicalVector3WrapperSI &p) const {

		if (p.v[0].getExponent() != positionExponent)
			throw std::runtime_error("Cannot multiply transform by this vector: types mismatch. The vector should be of position3 type");

		SBPosition3 psam = getSBPhysicalVector3<SBQuantity::position>(p);
		return SBDTypePhysicalVector3WrapperSI(toSBSpatialTransform() * psam);

	}

	/// \brief Returns the result of the transformation of spatial vector \p sv by this transform
	///
	/// \param sv - spatial vector (vector6 type: velocity6, acceleration6 or force6)

	SBDTypePhysicalVector6WrapperSI							operator*(const SBDTypePhysicalVector6WrapperSI &sv) const {

		if (sv.angular[0].getExponent() == QuantityScaleExponent<SBQuantity::inverseTime>::exponent &&
			sv.linear[0].getExponent()  == QuantityScaleExponent<SBQuantity::velocity>::exponent) {

			SBVelocity6 tmp = sv.template toSBPhysicalVector6<SBQuantity::inverseTime, SBQuantity::velocity>();
			//SBVelocity6 tmp = getSBPhysicalVector6<SBQuantity::inverseTime, SBQuantity::velocity>(sv);
			return SBDTypePhysicalVector6WrapperSI(toSBSpatialTransform() * tmp);

		}
		else if (sv.angular[0].getExponent() == QuantityScaleExponent<SBQuantity::inverseSquareTime>::exponent &&
				 sv.linear[0].getExponent()  == QuantityScaleExponent<SBQuantity::acceleration>::exponent) {

			SBAcceleration6 tmp = sv.template toSBPhysicalVector6<SBQuantity::inverseSquareTime, SBQuantity::acceleration>();
			return SBDTypePhysicalVector6WrapperSI(toSBSpatialTransform() * tmp);

		}
		else if (sv.angular[0].getExponent() == QuantityScaleExponent<SBQuantity::energy>::exponent &&
				 sv.linear[0].getExponent()  == QuantityScaleExponent<SBQuantity::force>::exponent) {

			SBForce6 tmp = sv.template toSBPhysicalVector6<SBQuantity::energy, SBQuantity::force>();
			return SBDTypePhysicalVector6WrapperSI(toSBSpatialTransform() * tmp);

		}
		else {

			throw std::runtime_error("Cannot multiply transform by this vector: types mismatch. The vector should be one of the following vector6 types: velocity6, acceleration6 or force6");

		}

	}

	/// \brief Returns the product of this transform with the transform \p st
	///
	/// \param st - spatial transform

	SBDTypeSpatialTransformWrapper							operator*(const SBDTypeSpatialTransformWrapper &st) const {

		return SBDTypeSpatialTransformWrapper(toSBSpatialTransform() * st.toSBSpatialTransform());

	}

	/// \brief Returns true if and only if this transform is equal to \p transform

	bool													operator==(const SBDTypeSpatialTransformWrapper& transform) const {

		return (orientation == transform.orientation && position == transform.position);

	}

	/// \brief Returns true if and only if this transform is equal to \p transform

	bool													operator!=(const SBDTypeSpatialTransformWrapper& transform) const {

		return (orientation != transform.orientation || position != transform.position);

	}

	//@}

    /// \name Useful functions
	//@{

	/// \brief Sets this transform to identity

	void													setIdentity() {

		orientation.setIdentity();
		position.setZero();

	}

	/// \brief Returns the inverse of this transform

	SBDTypeSpatialTransformWrapper							inverse() {

		return SBDTypeSpatialTransformWrapper(toSBSpatialTransform().inverse());

	}

	/// \brief Returns the product of \p leftMember and this transform
	///
	/// \param leftMember - spatial transform

	SBDTypeSpatialTransformWrapper							rightMultiply3D(const SBDTypeSpatialTransformWrapper &leftMember) const {

		SBDTypeSpatialTransform result;
		toSBSpatialTransform().rightMultiply3D(leftMember.toSBSpatialTransform(), result);
		return SBDTypeSpatialTransformWrapper(result);

	}

	/// \brief Returns the product of \p leftMember and the inverse of this transform
	///
	/// \param leftMember - spatial transform

	SBDTypeSpatialTransformWrapper							rightMultiplyInverse3D(const SBDTypeSpatialTransformWrapper &leftMember) const {

		SBDTypeSpatialTransform result;
		toSBSpatialTransform().rightMultiplyInverse3D(leftMember.toSBSpatialTransform(), result);
		return SBDTypeSpatialTransformWrapper(result);

	}

    //@}

	/// \name Transformations
	//@{

	/// \brief Returns the result of the transformation of the point \p p
	///
	/// \param p - position of the point (position3 type)

	SBDTypePhysicalVector3WrapperSI							transformPoint(const SBDTypePhysicalVector3WrapperSI &p) const {

		if (p.v[0].getExponent() != positionExponent)
			throw std::runtime_error("Cannot multiply transform by this vector: types mismatch. The vector should be of position3 type");

		SBPosition3 result;
		toSBSpatialTransform().transformPoint(getSBPhysicalVector3<SBQuantity::position>(p), result);
		return SBDTypePhysicalVector3WrapperSI(result);

	}

	/// \brief Returns the result of the transformation of the spatial velocity \p sv
	///
	/// \param sv - spatial velocity (velocity6 type)

	SBDTypePhysicalVector6WrapperSI							transformVelocity(const SBDTypePhysicalVector6WrapperSI &sv) const {

		if (sv.angular[0].getExponent() != QuantityScaleExponent<SBQuantity::inverseTime>::exponent ||
			sv.linear[0].getExponent()  != QuantityScaleExponent<SBQuantity::velocity>::exponent)
			throw std::runtime_error("Cannot multiply transform by this vector: types mismatch. The vector should be of velocity6 type");

		SBVelocity6 result;
		toSBSpatialTransform().transformVelocity(sv.template toSBPhysicalVector6<SBQuantity::inverseTime, SBQuantity::velocity>(), result);
		return SBDTypePhysicalVector6WrapperSI(result);

	}

	/// \brief Returns the result of the transformation of the spatial acceleration \p sa
	///
	/// \param sa - spatial acceleration (acceleration6 type)

	SBDTypePhysicalVector6WrapperSI							transformAcceleration(const SBDTypePhysicalVector6WrapperSI &sa) const {

		if (sa.angular[0].getExponent() != QuantityScaleExponent<SBQuantity::inverseSquareTime>::exponent ||
			sa.linear[0].getExponent()  != QuantityScaleExponent<SBQuantity::acceleration>::exponent)
			throw std::runtime_error("Cannot multiply transform by this vector: types mismatch. The vector should be of acceleration6 type");

		SBAcceleration6 result;
		toSBSpatialTransform().transformAcceleration(sa.template toSBPhysicalVector6<SBQuantity::inverseSquareTime, SBQuantity::acceleration>(), result);
		return SBDTypePhysicalVector6WrapperSI(result);

	}

	/// \brief Returns the result of the transformation of the spatial force \p sf
	///
	/// \param sf - spatial force (force6 type)

	SBDTypePhysicalVector6WrapperSI							transformForce(const SBDTypePhysicalVector6WrapperSI &sf) const {

		if (sf.angular[0].getExponent() != QuantityScaleExponent<SBQuantity::energy>::exponent ||
			sf.linear[0].getExponent()  != QuantityScaleExponent<SBQuantity::force>::exponent)
			throw std::runtime_error("Cannot multiply transform by this vector: types mismatch. The vector should be of force6 type");

		SBForce6 result;
		toSBSpatialTransform().transformForce(sf.template toSBPhysicalVector6<SBQuantity::energy, SBQuantity::force>(), result);
		return SBDTypePhysicalVector6WrapperSI(result);

	}

	/// \brief Returns the result of the transformation of the spatial velocity \p sv by applying the <em>inverse</em> of this transform
	///
	/// \param sv - spatial velocity (velocity6 type)

	SBDTypePhysicalVector6WrapperSI							inverseTransformVelocity(const SBDTypePhysicalVector6WrapperSI &sv) const {

		if (sv.angular[0].getExponent() != QuantityScaleExponent<SBQuantity::inverseTime>::exponent ||
			sv.linear[0].getExponent()  != QuantityScaleExponent<SBQuantity::velocity>::exponent)
			throw std::runtime_error("Cannot multiply transform by this vector: types mismatch. The vector should be of velocity6 type");

		SBVelocity6 result;
		toSBSpatialTransform().inverseTransformVelocity(sv.template toSBPhysicalVector6<SBQuantity::inverseTime, SBQuantity::velocity>(), result);
		return SBDTypePhysicalVector6WrapperSI(result);

	}

	/// \brief Returns the result of the transformation of the spatial acceleration \p sa by applying the <em>inverse</em> of this transform
	///
	/// \param sa - spatial acceleration (acceleration6 type)

	SBDTypePhysicalVector6WrapperSI							inverseTransformAcceleration(const SBDTypePhysicalVector6WrapperSI &sa) const {

		if (sa.angular[0].getExponent() != QuantityScaleExponent<SBQuantity::inverseSquareTime>::exponent ||
			sa.linear[0].getExponent()  != QuantityScaleExponent<SBQuantity::acceleration>::exponent)
			throw std::runtime_error("Cannot multiply transform by this vector: types mismatch. The vector should be of acceleration6 type");

		SBAcceleration6 result;
		toSBSpatialTransform().inverseTransformAcceleration(sa.template toSBPhysicalVector6<SBQuantity::inverseSquareTime, SBQuantity::acceleration>(), result);
		return SBDTypePhysicalVector6WrapperSI(result);

	}

	/// \brief Returns the result of the transformation of the inverse inertia \p phi
	///
	/// \param phi - inverse inertia (inverseInertia66 type)

	SBDTypePhysicalMatrix66WrapperSI						transformInverseInertia(const SBDTypePhysicalMatrix66WrapperSI &phi) const {

		if (phi.m00.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseMomentOfInertia>::exponent ||
			phi.m01.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseLengthInverseMass>::exponent ||
			phi.m10.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseLengthInverseMass>::exponent ||
			phi.m11.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseMass>::exponent)
			throw std::runtime_error("Cannot apply transform: types mismatch. The input should be of inverseInertia66 type");

		SBInverseInertia66 result;
		toSBSpatialTransform().transformInverseInertia(
					phi.template toSBPhysicalMatrix66<SBQuantity::inverseMomentOfInertia, SBQuantity::inverseLengthInverseMass, SBQuantity::inverseLengthInverseMass, SBQuantity::inverseMass>(),
					result);
		return SBDTypePhysicalMatrix66WrapperSI(result);

	}

	/// \brief Left-multiplies the inverse inertia \p phi by this spatial transform and returns the result
	///
	/// \param phi - inverse inertia (inverseInertia66 type)

	SBDTypePhysicalMatrix66WrapperSI						transformInverseInertiaLeft(const SBDTypePhysicalMatrix66WrapperSI &phi) const {

		if (phi.m00.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseMomentOfInertia>::exponent ||
			phi.m01.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseLengthInverseMass>::exponent ||
			phi.m10.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseLengthInverseMass>::exponent ||
			phi.m11.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseMass>::exponent)
			throw std::runtime_error("Cannot apply transform: types mismatch. The input should be of inverseInertia66 type");

		SBInverseInertia66 result;
		toSBSpatialTransform().transformInverseInertiaLeft(
					phi.template toSBPhysicalMatrix66<SBQuantity::inverseMomentOfInertia, SBQuantity::inverseLengthInverseMass, SBQuantity::inverseLengthInverseMass, SBQuantity::inverseMass>(),
					result);
		return SBDTypePhysicalMatrix66WrapperSI(result);

	}

	/// \brief Right-multiplies the inverse inertia \p phi by this spatial transform and returns the result
	///
	/// \param phi - inverse inertia (inverseInertia66 type)

	SBDTypePhysicalMatrix66WrapperSI						transformInverseInertiaRight(const SBDTypePhysicalMatrix66WrapperSI &phi) const {

		if (phi.m00.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseMomentOfInertia>::exponent ||
			phi.m01.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseLengthInverseMass>::exponent ||
			phi.m10.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseLengthInverseMass>::exponent ||
			phi.m11.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseMass>::exponent)
			throw std::runtime_error("Cannot apply transform: types mismatch. The input should be of inverseInertia66 type");

		SBInverseInertia66 result;
		toSBSpatialTransform().transformInverseInertiaRight(
					phi.template toSBPhysicalMatrix66<SBQuantity::inverseMomentOfInertia, SBQuantity::inverseLengthInverseMass, SBQuantity::inverseLengthInverseMass, SBQuantity::inverseMass>(),
					result);
		return SBDTypePhysicalMatrix66WrapperSI(result);

	}

	/// \brief Right-multiplies the transpose of the inverse inertia \p phi by this spatial transform and returns the result
	///
	/// \param phi - inverse inertia (inverseInertia66 type)

	SBDTypePhysicalMatrix66WrapperSI						transformInverseInertiaTransposeRight(const SBDTypePhysicalMatrix66WrapperSI &phi) const {

		if (phi.m00.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseMomentOfInertia>::exponent ||
			phi.m01.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseLengthInverseMass>::exponent ||
			phi.m10.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseLengthInverseMass>::exponent ||
			phi.m11.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::inverseMass>::exponent)
			throw std::runtime_error("Cannot apply transform: types mismatch. The input should be of inverseInertia66 type");

		SBInverseInertia66 result;
		toSBSpatialTransform().transformInverseInertiaTransposeRight(
					phi.template toSBPhysicalMatrix66<SBQuantity::inverseMomentOfInertia, SBQuantity::inverseLengthInverseMass, SBQuantity::inverseLengthInverseMass, SBQuantity::inverseMass>(),
					result);
		return SBDTypePhysicalMatrix66WrapperSI(result);

	}

	/// \brief Returns the result of the transformation of the inertia \p I
	///
	/// \param I - inertia (inertia66 type)

	SBDTypePhysicalMatrix66WrapperSI						transformInertia(const SBDTypePhysicalMatrix66WrapperSI &I) const {

		if (I.m00.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::momentOfInertia>::exponent ||
			I.m01.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::lengthMass>::exponent ||
			I.m10.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::lengthMass>::exponent ||
			I.m11.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::mass>::exponent)
			throw std::runtime_error("Cannot apply transform: types mismatch. The input should be of inertia66 type");

		SBInertia66 result;
		toSBSpatialTransform().transformInertia(
					I.template toSBPhysicalMatrix66<SBQuantity::momentOfInertia, SBQuantity::lengthMass, SBQuantity::lengthMass, SBQuantity::mass>(),
					result);
		return SBDTypePhysicalMatrix66WrapperSI(result);

	}

	/// \brief Left-multiplies the inertia \p I by this spatial transform and returns the result
	///
	/// \param I - inertia (inertia66 type)

	SBDTypePhysicalMatrix66WrapperSI						transformInertiaLeft(const SBDTypePhysicalMatrix66WrapperSI &I) const {

		if (I.m00.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::momentOfInertia>::exponent ||
			I.m01.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::lengthMass>::exponent ||
			I.m10.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::lengthMass>::exponent ||
			I.m11.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::mass>::exponent)
			throw std::runtime_error("Cannot apply transform: types mismatch. The input should be of inertia66 type");

		SBInertia66 result;
		toSBSpatialTransform().transformInertiaLeft(
					I.template toSBPhysicalMatrix66<SBQuantity::momentOfInertia, SBQuantity::lengthMass, SBQuantity::lengthMass, SBQuantity::mass>(),
					result);
		return SBDTypePhysicalMatrix66WrapperSI(result);

	}

	/// \brief Right-multiplies the inertia \p I by this spatial transform and returns the result
	///
	/// \param I - inertia (inertia66 type)

	SBDTypePhysicalMatrix66WrapperSI						transformInertiaRight(const SBDTypePhysicalMatrix66WrapperSI &I) const {

		if (I.m00.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::momentOfInertia>::exponent ||
			I.m01.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::lengthMass>::exponent ||
			I.m10.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::lengthMass>::exponent ||
			I.m11.m[0][0].getExponent() != QuantityScaleExponent<SBQuantity::mass>::exponent)
			throw std::runtime_error("Cannot apply transform: types mismatch. The input should be of inertia66 type");

		SBInertia66 result;
		toSBSpatialTransform().transformInertiaRight(
					I.template toSBPhysicalMatrix66<SBQuantity::momentOfInertia, SBQuantity::lengthMass, SBQuantity::lengthMass, SBQuantity::mass>(),
					result);
		return SBDTypePhysicalMatrix66WrapperSI(result);

	}

	//@}

    /// \name String representation
	//@{

	/// \brief Returns the string representation of the spatial transform (with a full unit name when fullName is true)

	std::string												toStdString(bool fullName = false) const {

		std::string ret =
				"orientation\n" + orientation.toStdString(fullName) +
				"\nposition\n" + position.toStdString(fullName);

		return ret;

	}

    //@}

	/// \name The zero and identity spatial transform
	//@{

	/// \brief Returns the zero spatial transform

	static SBDTypeSpatialTransformWrapper					getZero() {

		return SBDTypeSpatialTransformWrapper(SBSpatialTransform::zero);

	}

	/// \brief Returns the identity spatial transform

	static SBDTypeSpatialTransformWrapper					getIdentity() {

		return SBDTypeSpatialTransformWrapper(SBSpatialTransform::identity);

	}

	//@}

public:

	SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapperSI>	orientation;	///< The orientation of the spatial transform
	SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>		position;		///< The position of the spatial transform

private:

	/*
	 * SBSpatialTransform is only for SBMatrix33 (based on SBQuantity::dimensionless) and SBPosition (based on SBQuantity::position)
	 */
	std::vector<int> orientationExponent = QuantityScaleExponent<SBQuantity::dimensionless>::exponent;
	std::vector<int> orientationScale    = QuantityScaleExponent<SBQuantity::dimensionless>::scale;
	std::vector<int> positionExponent    = QuantityScaleExponent<SBQuantity::position>::exponent;
	std::vector<int> positionScale       = QuantityScaleExponent<SBQuantity::position>::scale;

};

/// \name Shortnames
//@{

typedef SBDTypeSpatialTransformWrapper						SBSpatialTransformWrapper;				///< The short name of SBDTypeSpatialTransformWrapper

//@}

/*
/// \name External operators
//@{

/// \brief Returns the product of double \p d and spatial matrix \p u

template<typename Units>
SBDTypeSpatialTransformWrapper<Units>						operator*(const double d, const SBDTypeSpatialTranformWrapperForPython<Units>& u) {

	return SBDTypeSpatialTransformWrapper<Units>(u.m00 * d, u.m01 * d, u.m10 * d, u.m11 * d);

}

//@}
*/
#endif
