#pragma once

#include "SBDTypeSpatialTransformWrapper.hpp"

#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDTypeSpatialDomain.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

/*! \file SBDTypeSpatialDomainWrapper.hpp */

/// \brief This class handles spatial domains, i.e. oriented boxes that are represented through a spatial transform and the vector containing the half sizes of the box.

class SBDTypeSpatialDomainWrapper {

public:

    /// \name Constructors
	//@{

	/// \brief Constructs an identity domain

	SBDTypeSpatialDomainWrapper() {

		transform = SBDTypeSpatialTransformWrapper(SBDTypeSpatialTransform::identity);
		halfSize = SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>(SBLength3::zero);

	}

	/// \brief Constructs a domain from a \p spatial transform and a \p half size

	SBDTypeSpatialDomainWrapper(const SBDTypeSpatialTransformWrapper& transform, const SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>& halfSize) {

		if (halfSize.v[0].getExponent() != positionExponent)
			throw std::runtime_error("Cannot construct a spatial domain: the halfSize vector should be of type position");

		this->transform = transform;
		this->halfSize = halfSize;

	}

	/// \brief Constructs a spatial domain from SBDTypeSpatialDomain \p sd

	SBDTypeSpatialDomainWrapper(const SBDTypeSpatialDomain& sd) {

		transform = SBDTypeSpatialTransformWrapper(*sd.transform);

		halfSize = {SBDQuantityWrapperSI(sd.halfSize->v[0]),
					SBDQuantityWrapperSI(sd.halfSize->v[1]),
					SBDQuantityWrapperSI(sd.halfSize->v[2])};

	}

	//@}

	/// \name Accessors
	//@{

	/// \brief Returns the arbitrary SBSpatialDomain

	SBSpatialDomain										toSBSpatialDomain () const {

		return SBSpatialDomain(
					transform.toSBSpatialTransform(),
					getSBPhysicalVector3<SBQuantity::position>(halfSize)
					);

	}

	/// \brief Returns the spatial transform

	SBDTypeSpatialTransformWrapper							getTransform() const {

		return transform;

	}

	/// \brief Returns the half extent vector

	SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>		getHalfSize() const {

		return halfSize;

	}

	/// \brief Sets the spatial transform to \p transform

	void													setTransform(const SBDTypeSpatialTransformWrapper& transform) {

		this->transform = transform;

	}

	/// \brief Sets the half extent vector to \p v

	void													getHalfSize(const SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>& v) {

		if (v.v[0].getExponent() != positionExponent)
			throw std::runtime_error("Cannot set the half extent vector: types mismatch - input vector should be of type position3");

		this->halfSize = v;

	}

	//@}

	/// \name Operators
	//@{

	/// \brief Returns true if and only if this domain is equal to \p domain

	bool													operator==(const SBDTypeSpatialDomainWrapper& domain) const {

		return (transform == domain.transform && halfSize == domain.halfSize);

	}

	/// \brief Returns true if and only if this domain is not equal to \p domain

	bool													operator!=(const SBDTypeSpatialDomainWrapper& domain) const {

		return (transform != domain.transform || halfSize != domain.halfSize);

	}

	//@}

	/// \name Useful functions
	//@{

	void												setEmpty() {

		transform.setIdentity();
		halfSize.setZero();

	}

	//@}

    /// \name String representation
	//@{

	/// \brief Returns the string representation of the spatial domain (with a full unit name when fullName is true)

	std::string												toStdString(bool fullName = false) const {

		std::string ret =
				"transform\n" + transform.toStdString(fullName) +
				"\nhalfSize\n" + halfSize.toStdString(fullName);

		return ret;

	}

	//@}

public:

	SBDTypeSpatialTransformWrapper							transform;							///< The spatial transform
	SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>		halfSize{ SBLength3::zero };		///< The half extent vector

private:

	std::vector<int>										positionExponent = QuantityScaleExponent<SBQuantity::position>::exponent;

};

/// \name Short names
//@{

typedef SBDTypeSpatialDomain								SBSpatialDomainWrapper;				///< The short name of SBDTypeSpatialDomain

//@}

#endif
