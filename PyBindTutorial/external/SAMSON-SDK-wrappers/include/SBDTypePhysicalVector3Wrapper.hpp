#pragma once

#include "SBDQuantityWrapper.hpp"

#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDTypePhysicalVector3.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

/*! \file SBDTypePhysicalVector3Wrapper.hpp */

/// \brief This class is used as a wrapper between SAMSON SDK SBDTypePhysicalVector3 and Python.
///
/// \tparam Units - SBDQuantityWrapper<SBUnitSystem>

template <typename Units = SBDQuantityWrapperSI>
class SBDTypePhysicalVector3Wrapper {

public:

    /// \name Constructors
    //@{

    /// \brief Constructs the physical vector [ 0 0 0 ]

	SBDTypePhysicalVector3Wrapper() : v{ Units(0.0), Units(0.0), Units(0.0) } {}

    /// \brief Constructs the physical vector [ \p x \p x \p x ]

	explicit SBDTypePhysicalVector3Wrapper(const Units& x) : v{ x, x, x } {}

    /// \brief Constructs the physical vector [ \p x \p y \p z ]

	SBDTypePhysicalVector3Wrapper(const Units& x, const Units& y, const Units& z) {

        v = { x, y.getUnitScaledTo(x), z.getUnitScaledTo(x) };

    }

    /// \brief Constructs the physical vector [ \p v[0] \p v[1] \p v[2] ]

	SBDTypePhysicalVector3Wrapper(const std::vector<Units>& u) {

		if (u.size() != 3) throw std::runtime_error("The size of the input vector should be 3");

        v = { u[0], u[1].getUnitScaledTo(u[0]), u[2].getUnitScaledTo(u[0]) };

    }

    /// \brief Constructs a dimensionless physical vector with all components set to \p x

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	explicit SBDTypePhysicalVector3Wrapper(double x) : v{ Units(x), Units(x), Units(x) } {}

    /// \brief Constructs the dimensionless physical vector [ \p x \p y \p z ]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalVector3Wrapper(double x, double y, double z) : v{ Units(x), Units(y), Units(z) } {}

    /// \brief Constructs the dimensionless physical vector [ \p v[0] \p v[1] \p v[2] ]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalVector3Wrapper(const std::vector<double>& u) {

		if (u.size() != 3) throw std::runtime_error("The size of the input vector should be 3");

        v = { Units(u[0]), Units(u[1]), Units(u[2]) };

    }

    /// \brief Constructs a physical vector from SBPhysicalVector3 \p q

    template<typename Quantity, typename System = SBUnitSystemSI>
	SBDTypePhysicalVector3Wrapper(const SBPhysicalVector3<Quantity>& q) {

		v = {SBDQuantityWrapper<System>(q[0]),
			 SBDQuantityWrapper<System>(q[1]),
			 SBDQuantityWrapper<System>(q[2])};

    }

    //@}

    /// \name Accessors
    //@{

    /// \brief Returns a dimensionless vector whose components are equal to those of this physical vector

    std::vector<double>         getValue() const {

		std::vector<double> ret = {v[0].getValue(), v[1].getValue(), v[2].getValue()};
		return ret;

    }

    /// \brief Sets the components of this physical vector equal to those of the vector \p u

    void                        setValue(const std::vector<double>& u) {

        if (u.size() != 3) throw std::runtime_error("The size of the input vector should be 3");

        v[0].setValue(u[0]);
        v[1].setValue(u[1]);
		v[2].setValue(u[2]);

    }

    /// \brief Returns the arbitraty SBPhysicalVector3

    template<typename Quantity, typename System = SBUnitSystemSI>
	SBPhysicalVector3<Quantity> toSBPhysicalVector3 () const {

        return SBPhysicalVector3<Quantity>( getSBQuantity<Quantity>(v[0]), getSBQuantity<Quantity>(v[1]), getSBQuantity<Quantity>(v[2]) );

    }

    /// \brief Returns the i-th component of the vector

    Units                       getComponent(const unsigned int i) const {

		if (i >= v.size()) throw std::runtime_error("Index is out of range");

        return v[i];

    }

    //@}

    /// \name Operators
    //@{

    /// \brief Returns the dot product of this physical vector with physical vector \p u

    Units                                                   operator|(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        return v[0] * u.v[0] + v[1] * u.v[1] + v[2] * u.v[2];

    }

    /// \brief Returns the cross product of this physical vector with physical vector \p u

    SBDTypePhysicalVector3Wrapper<Units>           operator^(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        return SBDTypePhysicalVector3Wrapper<Units>(v[1] * u.v[2] - v[2] * u.v[1], v[2] * u.v[0] - v[0] * u.v[2], v[0] * u.v[1] - v[1] * u.v[0]);

    }

    /// \brief Returns the sum of this physical vector with physical vector \p u

    SBDTypePhysicalVector3Wrapper<Units>           operator+(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        return SBDTypePhysicalVector3Wrapper<Units>(v[0] + u.v[0], v[1] + u.v[1], v[2] + u.v[2]);

    }

    /// \brief Returns the difference of this physical vector with physical vector \p u

    SBDTypePhysicalVector3Wrapper<Units>           operator-(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        return SBDTypePhysicalVector3Wrapper<Units>(v[0] - u.v[0], v[1] - u.v[1], v[2] - u.v[2]);

    }

    /// \brief Returns the product of this physical vector with physical quantity \p u

    SBDTypePhysicalVector3Wrapper<Units>           operator*(const Units& u) const {

        return SBDTypePhysicalVector3Wrapper<Units>(u*v[0], u*v[1], u*v[2]);

    }

    /// \brief Returns the product of this physical vector with double \p d

    SBDTypePhysicalVector3Wrapper<Units>           operator*(const double d) const {

        return SBDTypePhysicalVector3Wrapper<Units>(v[0] * d, v[1] * d, v[2] * d);

    }

    /// \brief Multiplies this physical vector with double \p d

    SBDTypePhysicalVector3Wrapper<Units>&          operator*=(const double d) {

        v[0] *= d;
        v[1] *= d;
        v[2] *= d;
        return *this;

    }

    /// \brief Multiplies this physical vector with physical quantity \p u

    SBDTypePhysicalVector3Wrapper<Units>&          operator*=(const Units& u) {

        v[0] *= u;
        v[1] *= u;
        v[2] *= u;
        return *this;

    }

    /// \brief Returns the component-wise product of this physical vector with physical vector \p u
    ///
    /// This operator returns the component-wise product of this physical vector with physical vector \p u, <em>i.e.</em>
    /// a physical vector in which each component is the product of the corresponding components in this physical vector and physical vector \p u.

    SBDTypePhysicalVector3Wrapper<Units>           operator*(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        return SBDTypePhysicalVector3Wrapper<Units>(v[0] * u.v[0], v[1] * u.v[1], v[2] * u.v[2]);

    }

    /// \brief Returns the division of this physical vector by physical quantity \p u

    SBDTypePhysicalVector3Wrapper<Units>           operator/(const Units& u) const {

        return SBDTypePhysicalVector3Wrapper<Units>(v[0] / u, v[1] / u, v[2] / u);

    }

    /// \brief Divides this physical vector by physical quantity \p u

    SBDTypePhysicalVector3Wrapper<Units>&          operator/=(const Units& u) {

        v[0] /= u;
        v[1] /= u;
        v[2] /= u;
        return *this;

    }

    /// \brief Returns the division of this physical vector by double \p d

    SBDTypePhysicalVector3Wrapper<Units>           operator/(const double d) const {

        return SBDTypePhysicalVector3Wrapper<Units>(v[0] / d, v[1] / d, v[2] / d);

    }

    /// \brief Divides this physical vector by double \p d

    SBDTypePhysicalVector3Wrapper<Units>&          operator/=(const double d) {

        v[0] /= d;
        v[1] /= d;
        v[2] /= d;
        return *this;

    }

    /// \brief Returns the opposite of this physical vector

    SBDTypePhysicalVector3Wrapper<Units>           operator-() const {

        return SBDTypePhysicalVector3Wrapper<Units>(-v[0], -v[1], -v[2]);

    }

    /// \brief Adds physical vector \p u to this physical vector

    SBDTypePhysicalVector3Wrapper<Units>&          operator+=(const SBDTypePhysicalVector3Wrapper<Units>& u) {

        v[0] += u.v[0]; v[1] += u.v[1]; v[2] += u.v[2];
        return *this;

    }

    /// \brief Subtracts physical vector \p u from this physical vector

    SBDTypePhysicalVector3Wrapper<Units>&          operator-=(const SBDTypePhysicalVector3Wrapper<Units>& u) {

        v[0] -= u.v[0]; v[1] -= u.v[1]; v[2] -= u.v[2];
        return *this;

    }

    /// \brief Returns true if this physical vector is equal to physical vector \p u (component-wise)

    bool                                                    operator==(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        return (v[0] == u.v[0]) && (v[1] == u.v[1]) && (v[2] == u.v[2]);

    }

    /// \brief Returns true if this physical vector is different from physical vector \p u (component-wise)

    bool                                                    operator!=(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        return (v[0] != u.v[0]) || (v[1] != u.v[1]) || (v[2] != u.v[2]);

    }

    /// \brief Returns true if this physical vector is smaller than physical vector \p u (lexicographic comparison)

    bool                                                    operator<(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        if (v[0] >= u.v[0]) return false;
        if (v[1] >= u.v[1]) return false;
        if (v[2] >= u.v[2]) return false;
        return true;

    }

    /// \brief Returns true if this physical vector is larger than physical vector \p u (lexicographic comparison)

    bool                                                    operator>(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        if (v[0] <= u.v[0]) return false;
        if (v[1] <= u.v[1]) return false;
        if (v[2] <= u.v[2]) return false;
        return true;

    }

    /// \brief Returns true if this physical vector is smaller or equal than physical vector \p u (lexicographic comparison)

    bool                                                    operator<=(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        if (v[0] > u.v[0]) return false;
        if (v[1] > u.v[1]) return false;
        if (v[2] > u.v[2]) return false;
        return true;

    }

    /// \brief Returns true if this physical vector is larger or equal than physical vector \p u (lexicographic comparison)

    bool                                                    operator>=(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        if (v[0] < u.v[0]) return false;
        if (v[1] < u.v[1]) return false;
        if (v[2] < u.v[2]) return false;
        return true;

    }

    /// \brief Returns a reference to component \p index

    Units&                                                  operator[](const int index) { return v[index]; }

    /// \brief Returns a reference to component \p index (const version)

    const Units&                                            operator[](const int index) const { return v[index]; }


    //@}

    /// \name Useful functions
    //@{

    /// \brief Sets all components to zero

    void														setZero() {

        v[0].setValue(0.0);
        v[1].setValue(0.0);
        v[2].setValue(0.0);

    }

    /// \brief Returns the norm of this physical vector

    Units                                                       norm() const {

        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    }

    /// \brief Returns the squared norm of this physical vector

    Units                                                       norm2()	const {

        return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    }

    /// \brief Returns the dimensionless normalized version of this physical vector

    SBDTypePhysicalVector3Wrapper<Units>               normalizedVersion()	const {

        double norm = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]).getValue();
        if (norm == 0) return SBDTypePhysicalVector3Wrapper<Units>(0.0, 0.0, 0.0);
        return SBDTypePhysicalVector3Wrapper<Units>(v[0].getValue() / norm, v[1].getValue() / norm, v[2].getValue() / norm);

    }

    /// \brief Returns the normalized version of this physical vector, but with preserved units

    SBDTypePhysicalVector3Wrapper<Units>               normalizedVersionWithUnits() const {

        double norm = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]).getValue();
        if (norm == 0) return SBDTypePhysicalVector3Wrapper<Units>(Units(0.0, v[0].getScale(), v[0].getExponent()),
                                                                            Units(0.0, v[1].getScale(), v[1].getExponent()),
                                                                            Units(0.0, v[2].getScale(), v[2].getExponent()));
        return SBDTypePhysicalVector3Wrapper<Units>(v[0] / norm, v[1] / norm, v[2] / norm);

    }

    /// \brief Normalizes this physical vector while preserving units

    void														normalizeWithUnits() {

        double norm = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]).getValue();

        if (norm) {

            v[0] /= norm;
            v[1] /= norm;
            v[2] /= norm;

        }

    }

    /*/// \brief Normalizes this dimensionless physical vector

    void														normalize() {

        if (v[0].getExponent() != v[0].getZerosVector() && v[1].getExponent() != v[1].getZerosVector() && v[2].getExponent() != v[2].getZerosVector())
            throw std::runtime_error("Error, this function may only be called for dimensionless quantities");

        double norm = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]).getValue();

        if (norm) {

            v[0] /= norm;
            v[1] /= norm;
            v[2] /= norm;

        }

    }*/

    /// \brief Swaps components \p i and \pj of this physical vector

    void														swap(unsigned int i, unsigned j) {

        Units s = v[i];
        v[i] = v[j];
        v[j] = s;

    }

    //@}

    /// \name String representation
    //@{

    /// \brief Returns the string representation of the physical vector (with a full unit name when fullName is true)

    std::string                                         toStdString(bool fullName = false) const {

        std::string ret = "(" + v[0].toStdString(fullName) + ", " +
                                v[1].toStdString(fullName) + ", " +
                                v[2].toStdString(fullName) + ")";

        return ret;

    }

    //@}

public:

	std::vector<Units>													v;                  ///< The components of the physical vector

};

/// \name Common types and shortnames
//@{

#define		SBPhysicalVector3Wrapper		SBDTypePhysicalVector3Wrapper

typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>                   SBDTypePhysicalVector3WrapperSI;
typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperAU>                   SBDTypePhysicalVector3WrapperAU;
typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperDalton>               SBDTypePhysicalVector3WrapperDalton;
typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperElectronvolt>         SBDTypePhysicalVector3WrapperElectronvolt;
typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperKilocaloriePerMole>   SBDTypePhysicalVector3WrapperKilocaloriePerMole;

typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperSI>                   SBPhysicalVector3WrapperSI;
typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperAU>                   SBPhysicalVector3WrapperAU;
typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperDalton>               SBPhysicalVector3WrapperDalton;
typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperElectronvolt>         SBPhysicalVector3WrapperElectronvolt;
typedef     SBDTypePhysicalVector3Wrapper<SBDQuantityWrapperKilocaloriePerMole>   SBPhysicalVector3WrapperKilocaloriePerMole;

//@}

/// \name External functions
//@{

/// \brief Returns the getSBPhysicalVector3<Quantity> from Unit \p u

template<typename Quantity, typename T>
SBPhysicalVector3<Quantity>	getSBPhysicalVector3(const T& a) {

	return a.template toSBPhysicalVector3<Quantity>();

}

//@}

/// \name External operators
//@{

/// \brief Returns the product of physical quantity \p d and physical vector \p u

template<typename Units>
SBDTypePhysicalVector3Wrapper<Units>       operator*(const Units d, const SBDTypePhysicalVector3Wrapper<Units>& u) {

    return SBDTypePhysicalVector3Wrapper<Units>(d*u.v[0], d*u.v[1], d*u.v[2]);

}

/// \brief Returns the product of double \p d and physical vector \p u

template<typename Units>
SBDTypePhysicalVector3Wrapper<Units>       operator*(const double d, const SBDTypePhysicalVector3Wrapper<Units>& u) {

        return SBDTypePhysicalVector3Wrapper<Units>(d*u.v[0], d*u.v[1], d*u.v[2]);

}

/// \brief Inserts the physical vector \p u in the output stream \p s

template <typename Units>
std::ostream&                                       operator<<(std::ostream &s, const  SBDTypePhysicalVector3Wrapper<Units>& u) {

    s << "(" << u[0] << ", " << u[1] << ", " << u[2] << ")";
    return s;

}

//@}

#endif
