#pragma once

#include "SBDQuantityWrapper.hpp"
#include "SBDTypePhysicalVector3Wrapper.hpp"

#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDTypePhysicalVector6.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

/*! \file SBDTypePhysicalVector6Wrapper.hpp */

/// \brief This class is used as a wrapper between SAMSON SDK SBDTypePhysicalVector6 and Python.
///
/// \tparam Units - SBDQuantityWrapper<SBUnitSystem>

template <typename Units = SBDQuantityWrapperSI>
class SBDTypePhysicalVector6Wrapper {

public:

    /// \name Constructors
    //@{

    /// \brief Constructs the spatial vector [ 0 0 0 0 0 0 ]

	SBDTypePhysicalVector6Wrapper() {

        angular = SBDTypePhysicalVector3Wrapper<Units>();
        linear  = SBDTypePhysicalVector3Wrapper<Units>();

    }

    /// \brief Constructs the spatial vector [ \p a \p a \p a \p l \p l \p l ]

	explicit SBDTypePhysicalVector6Wrapper(const Units& a, const Units& l) {

        angular = SBDTypePhysicalVector3Wrapper<Units>(a);
        linear  = SBDTypePhysicalVector3Wrapper<Units>(l);

    }

    /// \brief Constructs the spatial vector [ \p ax \p ay \p az \p lx \p ly \p lz ]

	SBDTypePhysicalVector6Wrapper(const Units& ax, const Units& ay, const Units& az, const Units& lx, const Units& ly, const Units& lz) {

        angular = SBDTypePhysicalVector3Wrapper<Units>(ax, ay, az);
        linear  = SBDTypePhysicalVector3Wrapper<Units>(lx, ly, lz);

    }

    /// \brief Constructs the spatial vector [ \p a[0] \p a[1] \p a[2] \p l[0] \p l[1] \p l[2] ]

	SBDTypePhysicalVector6Wrapper(const std::vector<Units>& a, const std::vector<Units>& l) {

		if (a.size() != 3 || l.size() != 3) throw std::runtime_error("The size of the input vectors should be 3");

        angular = SBDTypePhysicalVector3Wrapper<Units>(a);
        linear  = SBDTypePhysicalVector3Wrapper<Units>(l);

    }

    /// \brief Constructs the spatial vector [ \p a \p l ]

	explicit SBDTypePhysicalVector6Wrapper(const SBDTypePhysicalVector3Wrapper<Units>& a, const SBDTypePhysicalVector3Wrapper<Units>& l) {

        angular = SBDTypePhysicalVector3Wrapper<Units>(a[0], a[1], a[2]);
        linear  = SBDTypePhysicalVector3Wrapper<Units>(l[0], l[1], l[2]);

    }

    /// \brief Constructs the spatial vector [ \p a \p a \p a \p l \p l \p l ]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalVector6Wrapper(double a, double l) {

        angular = SBDTypePhysicalVector3Wrapper<Units>(a);
        linear  = SBDTypePhysicalVector3Wrapper<Units>(l);

    }

    /// \brief Constructs the spatial vector [ \p ax \p ay \p az \p lx \p ly \p lz ]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalVector6Wrapper(double ax, double ay, double az, double lx, double ly, double lz) {

        angular = SBDTypePhysicalVector3Wrapper<Units>(ax, ay, az);
        linear  = SBDTypePhysicalVector3Wrapper<Units>(lx, ly, lz);

    }

    /// \brief Constructs the spatial vector [ \p a \p l ]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalVector6Wrapper(const std::vector<double>& a, const std::vector<double>& l) {

        angular = SBDTypePhysicalVector3Wrapper<Units>(a);
        linear  = SBDTypePhysicalVector3Wrapper<Units>(l);

    }

    /// \brief Constructs a spatial vector from SBPhysicalVector6 \p q

    template<typename QuantityA, typename QuantityL, typename System = SBUnitSystemSI>
	SBDTypePhysicalVector6Wrapper(const SBPhysicalVector6<QuantityA, QuantityL>& q) {

		angular = {SBDQuantityWrapper<System>(q.angular.v[0]),
				   SBDQuantityWrapper<System>(q.angular.v[1]),
				   SBDQuantityWrapper<System>(q.angular.v[2])};
		linear  = {SBDQuantityWrapper<System>(q.linear.v[0]),
				   SBDQuantityWrapper<System>(q.linear.v[1]),
				   SBDQuantityWrapper<System>(q.linear.v[2])};

    }

    //@}


    /// \name Accessors
    //@{

    /// \brief Returns a dimensionless spatial vector whose components are equal to those of this spatial vector

    std::vector<double>         getValue() const {

		std::vector<double> ret = {angular.v[0].getValue(), angular.v[1].getValue(), angular.v[2].getValue(),
								   linear.v[0].getValue(),  linear.v[1].getValue(),  linear.v[2].getValue()};
		return ret;

    }

    /*/// \brief Sets the components of this spatial vector equal to those of the vectors \p a and \p l

    void                        setValue(const std::vector<double>& a, const std::vector<double>& l) {

        if (a.size() != 3 || l.size() != 3) throw std::runtime_error("The size of the input vectors should be 3");

        angular.v[0].setValue(a[0]);
        angular.v[1].setValue(a[1]);
        angular.v[2].setValue(a[2]);
        linear.v[0].setValue(l[0]);
        linear.v[1].setValue(l[1]);
        linear.v[2].setValue(l[2]);

    }*/

    /// \brief Sets the components of this spatial vector equal to those of the vector \p u

    void                        setValue(const std::vector<double>& u) {

        if (u.size() != 6) throw std::runtime_error("The size of the input vector should be 6");

        angular.v[0].setValue(u[0]);
        angular.v[1].setValue(u[1]);
        angular.v[2].setValue(u[2]);
        linear.v[0].setValue(u[3]);
        linear.v[1].setValue(u[4]);
        linear.v[2].setValue(u[5]);

    }

    /// \brief Returns the arbitraty SBPhysicalVector6

    template<typename QuantityA, typename QuantityL, typename System = SBUnitSystemSI>
    SBPhysicalVector6<QuantityA, QuantityL> toSBPhysicalVector6 () const {

        return SBPhysicalVector6<QuantityA, QuantityL>(
                    getSBQuantity<QuantityA>(angular.v[0]), getSBQuantity<QuantityA>(angular.v[1]), getSBQuantity<QuantityA>(angular.v[2]),
                    getSBQuantity<QuantityL>(linear.v[0]),  getSBQuantity<QuantityL>(linear.v[1]),  getSBQuantity<QuantityL>(linear.v[2]));

    }

    /// \brief Returns the i-th component of the vector

    Units                       getComponent(const unsigned int i) const {

        if (i >= 6) throw std::runtime_error("Index is out of range");

        if (i < 3)  return angular[i];
        else        return linear[i-3];

    }

    //@}

    /// \name Operators
    //@{

    /// \brief Returns the dot product of this spatial vector with spatial vector \p u

	Units               operator|(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

        return (angular | u.angular) + (linear | u.linear);

    }

    /// \brief Returns the cross product of this spatial vector with spatial vector \p u

	SBDTypePhysicalVector6Wrapper<Units>               operator^(const SBDTypePhysicalVector6Wrapper<Units> force) const {

        Units R0(angular.v[1] * force.angular.v[2] - angular.v[2] * force.angular.v[1] + linear.v[1] * force.linear.v[2] - linear.v[2] * force.linear.v[1]);
        Units R1(angular.v[2] * force.angular.v[0] - angular.v[0] * force.angular.v[2] + linear.v[2] * force.linear.v[0] - linear.v[0] * force.linear.v[2]);
        Units R2(angular.v[0] * force.angular.v[1] - angular.v[1] * force.angular.v[0] + linear.v[0] * force.linear.v[1] - linear.v[1] * force.linear.v[0]);
        Units T3(angular.v[1] * force.linear.v[2] - angular.v[2] * force.linear.v[1]);
        Units T4(angular.v[2] * force.linear.v[0] - angular.v[0] * force.linear.v[2]);
        Units T5(angular.v[0] * force.linear.v[1] - angular.v[1] * force.linear.v[0]);

		return SBDTypePhysicalVector6Wrapper<Units>(R0, R1, R2, T3, T4, T5);

    }

    /// \brief Returns the sum of this spatial vector with spatial vector \p u

	SBDTypePhysicalVector6Wrapper<Units>               operator+(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

		return SBDTypePhysicalVector6Wrapper<Units>(
            angular.v[0] + u.angular.v[0], angular.v[1] + u.angular.v[1], angular.v[2] + u.angular.v[2],
            linear.v[0] + u.linear.v[0], linear.v[1] + u.linear.v[1], linear.v[2] + u.linear.v[2]
            );

    }

    /// \brief Returns the difference of this spatial vector with spatial vector \p u

	SBDTypePhysicalVector6Wrapper<Units>               operator-(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

		return SBDTypePhysicalVector6Wrapper<Units>(
            angular.v[0] - u.angular.v[0], angular.v[1] - u.angular.v[1], angular.v[2] - u.angular.v[2],
            linear.v[0] - u.linear.v[0], linear.v[1] - u.linear.v[1], linear.v[2] - u.linear.v[2]
            );

    }

    /// \brief Returns the product of this spatial vector with physical quantity \p d

	SBDTypePhysicalVector6Wrapper<Units>               operator*(const Units d) const {

		return SBDTypePhysicalVector6Wrapper<Units> (
                    d*angular.v[0], d*angular.v[1], d*angular.v[2],
                    d*linear.v[0], d*linear.v[1], d*linear.v[2]
                );

    }

    /// \brief Returns the product of this spatial vector with double \p d

	SBDTypePhysicalVector6Wrapper<Units>               operator*(const double d) const {

		return SBDTypePhysicalVector6Wrapper<Units> (
                    d*angular.v[0], d*angular.v[1], d*angular.v[2],
                    d*linear.v[0], d*linear.v[1], d*linear.v[2]
                );

    }

    /// \brief Multiplies this spatial vector with double \p d

	SBDTypePhysicalVector6Wrapper<Units>&				operator*=(const double d) {

        angular.v[0] *= d;
        angular.v[1] *= d;
        angular.v[2] *= d;
        linear.v[0] *= d;
        linear.v[1] *= d;
        linear.v[2] *= d;
        return *this;

    }

    /// \brief Multiplies this dimensionless spatial vector with physical quantity \p d

	SBDTypePhysicalVector6Wrapper<Units>&				operator*=(const Units& d) {

        angular.v[0] *= d;
        angular.v[1] *= d;
        angular.v[2] *= d;
        linear.v[0] *= d;
        linear.v[1] *= d;
        linear.v[2] *= d;
        return *this;

    }

    /// \brief Returns the component-wise product of this spatial vector with spatial vector \p u
    ///
    /// This operator returns the component-wise product of this spatial vector with spatial vector \p u, <em>i.e.</em>
    /// a spatial vector in which each component is the product of the corresponding components in this spatial vector and spatial vector \p u.

	SBDTypePhysicalVector6Wrapper<Units>               operator*(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

		return 	SBDTypePhysicalVector6Wrapper<Units> (
                    angular.v[0] * u.angular.v[0], angular.v[1] * u.angular.v[1], angular.v[2] * u.angular.v[2],
                    linear.v[0] * u.linear.v[0], linear.v[1] * u.linear.v[1], linear.v[2] * u.linear.v[2]
                );

    }

    /// \brief Returns the division of this spatial vector by physical quantity \p d

	SBDTypePhysicalVector6Wrapper<Units>               operator/(const Units d) const {

		return SBDTypePhysicalVector6Wrapper<Units> (
                    angular.v[0]/d, angular.v[1]/d, angular.v[2]/d,
                    linear.v[0]/d, linear.v[1]/d, linear.v[2]/d
                );

    }

    /// \brief Returns the division of this spatial vector by double \p d

	SBDTypePhysicalVector6Wrapper<Units>               operator/(const double d) const {

		return SBDTypePhysicalVector6Wrapper<Units> (
                    angular.v[0] / d, angular.v[1] / d, angular.v[2] / d,
                    linear.v[0] / d, linear.v[1] / d, linear.v[2] / d
                );

    }

    /// \brief Divides this spatial vector by physical quantity \p d

	SBDTypePhysicalVector6Wrapper<Units>&				operator/=(const Units d) {

        angular.v[0] /= d;
        angular.v[1] /= d;
        angular.v[2] /= d;
        linear.v[0] /= d;
        linear.v[1] /= d;
        linear.v[2] /= d;
        return *this;

    }

    /// \brief Divides this spatial vector by double \p d

	SBDTypePhysicalVector6Wrapper<Units>&				operator/=(const double d) {

        angular.v[0] /= d;
        angular.v[1] /= d;
        angular.v[2] /= d;
        linear.v[0] /= d;
        linear.v[1] /= d;
        linear.v[2] /= d;
        return *this;

    }

    /// \brief Returns the opposite of this spatial vector

	SBDTypePhysicalVector6Wrapper<Units>				operator-() const {

		return SBDTypePhysicalVector6Wrapper<Units>(-angular.v[0], -angular.v[1], -angular.v[2], -linear.v[0], -linear.v[1], -linear.v[2]);

    }

    /// \brief Adds spatial vector \p u to this spatial vector

	SBDTypePhysicalVector6Wrapper<Units>&				operator+=(const SBDTypePhysicalVector6Wrapper<Units>& u) {

        angular.v[0] += u.angular.v[0]; angular.v[1] += u.angular.v[1]; angular.v[2] += u.angular.v[2];
        linear.v[0] += u.linear.v[0]; linear.v[1] += u.linear.v[1]; linear.v[2] += u.linear.v[2];
        return *this;

    }

    /// \brief Subtracts spatial vector \p u from this spatial vector

	SBDTypePhysicalVector6Wrapper<Units>&				operator-=(const SBDTypePhysicalVector6Wrapper<Units>& u) {

        angular.v[0] -= u.angular.v[0]; angular.v[1] -= u.angular.v[1]; angular.v[2] -= u.angular.v[2];
        linear.v[0] -= u.linear.v[0]; linear.v[1] -= u.linear.v[1]; linear.v[2] -= u.linear.v[2];
        return *this;

    }

    /// \brief Returns true if this spatial vector is equal to spatial vector \p u (component-wise)

	bool	operator==(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

        return
            (angular.v[0] == u.angular.v[0]) && (angular.v[1] == u.angular.v[1]) && (angular.v[2] == u.angular.v[2]) &&
            (linear.v[0] == u.linear.v[0]) && (linear.v[1] == u.linear.v[1]) && (linear.v[2] == u.linear.v[2]);

    }

    /// \brief Returns true if this spatial vector is different from spatial vector \p u (component-wise)

	bool	operator!=(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

        return
            (angular.v[0] != u.angular.v[0]) || (angular.v[1] != u.angular.v[1]) || (angular.v[2] != u.angular.v[2]) ||
            (linear.v[0] != u.linear.v[0]) || (linear.v[1] != u.linear.v[1]) || (linear.v[2] != u.linear.v[2]);

    }

    /// \brief Returns true if this spatial vector is smaller than spatial vector \p u (lexicographic comparison)

	bool	operator<(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

        if (angular.v[0] >= u.angular.v[0]) return false;
        if (angular.v[1] >= u.angular.v[1]) return false;
        if (angular.v[2] >= u.angular.v[2]) return false;
        if (linear.v[0] >= u.linear.v[0]) return false;
        if (linear.v[1] >= u.linear.v[1]) return false;
        if (linear.v[2] >= u.linear.v[2]) return false;
        return true;

    }

    /// \brief Returns true if this spatial vector is larger than spatial vector \p u (lexicographic comparison)

	bool	operator>(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

        if (angular.v[0] <= u.angular.v[0]) return false;
        if (angular.v[1] <= u.angular.v[1]) return false;
        if (angular.v[2] <= u.angular.v[2]) return false;
        if (linear.v[0] <= u.linear.v[0]) return false;
        if (linear.v[1] <= u.linear.v[1]) return false;
        if (linear.v[2] <= u.linear.v[2]) return false;
        return true;

    }

    /// \brief Returns true if this spatial vector is smaller or equal than spatial vector \p u (lexicographic comparison)

	bool	operator<=(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

        if (angular.v[0] > u.angular.v[0]) return false;
        if (angular.v[1] > u.angular.v[1]) return false;
        if (angular.v[2] > u.angular.v[2]) return false;
        if (linear.v[0] > u.linear.v[0]) return false;
        if (linear.v[1] > u.linear.v[1]) return false;
        if (linear.v[2] > u.linear.v[2]) return false;
        return true;

    }

    /// \brief Returns true if this spatial vector is larger or equal than spatial vector \p u (lexicographic comparison)

	bool	operator>=(const SBDTypePhysicalVector6Wrapper<Units>& u) const {

        if (angular.v[0] < u.angular.v[0]) return false;
        if (angular.v[1] < u.angular.v[1]) return false;
        if (angular.v[2] < u.angular.v[2]) return false;
        if (linear.v[0] < u.linear.v[0]) return false;
        if (linear.v[1] < u.linear.v[1]) return false;
        if (linear.v[2] < u.linear.v[2]) return false;
        return true;

    }

    //@}

    /// \name Useful functions
    //@{
    /// \brief Sets all components to zero

    void														setZero() {

        angular.v[0].setValue(0.0);
        angular.v[1].setValue(0.0);
        angular.v[2].setValue(0.0);
		linear.v[0].setValue(0.0);
		linear.v[1].setValue(0.0);
		linear.v[2].setValue(0.0);

    }

    /// \brief Returns the cross product of this spatial vector with spatial vector \p force
    ///
    /// \param force The force
    /// \return The resulting cross product between this spatial vector and the \p force
    ///
    /// This function returns the cross product of this spatial vector with spatial vector \p u. As with the cross product operator, this function is only useful when this
    /// spatial vector is a motion and \p force is a force.

	SBDTypePhysicalVector6Wrapper<Units>    motionCrossForce(const SBDTypePhysicalVector6Wrapper<Units>& force) const {

		return SBDTypePhysicalVector6Wrapper<Units> (
            angular.v[1] * force.angular.v[2] - angular.v[2] * force.angular.v[1] + linear.v[1] * force.linear.v[2] - linear.v[2] * force.linear.v[1],
            angular.v[2] * force.angular.v[0] - angular.v[0] * force.angular.v[2] + linear.v[2] * force.linear.v[0] - linear.v[0] * force.linear.v[2],
            angular.v[0] * force.angular.v[1] - angular.v[1] * force.angular.v[0] + linear.v[0] * force.linear.v[1] - linear.v[1] * force.linear.v[0],
			angular.v[1] * force.linear.v[2]  - angular.v[2] * force.linear.v[1],
			angular.v[2] * force.linear.v[0]  - angular.v[0] * force.linear.v[2],
			angular.v[0] * force.linear.v[1]  - angular.v[1] * force.linear.v[0]);

    }

    //@}

    /// \name String representation
    //@{

    /// \brief Returns the string representation of the spatial vector (with a full unit name when fullName is true)

    std::string                                         toStdString(bool fullName = false) const {

        std::string ret = "(" + angular.v[0].toStdString(fullName) + ", " +
                                angular.v[1].toStdString(fullName) + ", " +
                                angular.v[2].toStdString(fullName) + ", " +
                                linear.v[0].toStdString(fullName)  + ", " +
                                linear.v[1].toStdString(fullName)  + ", " +
                                linear.v[2].toStdString(fullName)  + ")";

        return ret;

    }

    //@}

public:

    SBDTypePhysicalVector3Wrapper<Units>               angular;																///< The part of the spatial vector
	SBDTypePhysicalVector3Wrapper<Units>               linear;																///< The part of the spatial vector

};

/// \name Common types and shortnames
//@{

#define		SBPhysicalVector6Wrapper		SBDTypePhysicalVector6Wrapper

typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperSI>                   SBDTypePhysicalVector6WrapperSI;
typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperAU>                   SBDTypePhysicalVector6WrapperAU;
typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperDalton>               SBDTypePhysicalVector6WrapperDalton;
typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperElectronvolt>         SBDTypePhysicalVector6WrapperElectronvolt;
typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperKilocaloriePerMole>   SBDTypePhysicalVector6WrapperKilocaloriePerMole;

typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperSI>                   SBPhysicalVector6WrapperSI;
typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperAU>                   SBPhysicalVector6WrapperAU;
typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperDalton>               SBPhysicalVector6WrapperDalton;
typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperElectronvolt>         SBPhysicalVector6WrapperElectronvolt;
typedef     SBDTypePhysicalVector6Wrapper<SBDQuantityWrapperKilocaloriePerMole>   SBPhysicalVector6WrapperKilocaloriePerMole;

//@}

/// \name External functions
//@{

/// \brief Returns the getSBPhysicalVector6<QuantityA, QuantityL> from Unit \p u

template<typename QuantityA, typename QuantityL, typename T>
SBPhysicalVector6<QuantityA, QuantityL> getSBPhysicalVector6(const T& a) {

	return a.template toSBPhysicalVector6<QuantityA, QuantityL>();

}

//@}

/// \name External operators
//@{

/// \brief Returns the product of quantity \p d and spatial vector \p u

template<typename Units>
SBDTypePhysicalVector6Wrapper<Units>   operator*(const Units& d, const SBDTypePhysicalVector6Wrapper<Units>& u) {

	return SBDTypePhysicalVector6Wrapper<Units> (
                d*u.angular.v[0], d*u.angular.v[1], d*u.angular.v[2],
				d*u.linear.v[0],  d*u.linear.v[1],  d*u.linear.v[2]
            );

}

/// \brief Returns the product of double \p d and spatial vector \p u

template<typename Units>
SBDTypePhysicalVector6Wrapper<Units>   operator*(const double d, const SBDTypePhysicalVector6Wrapper<Units>& u) {

		return SBDTypePhysicalVector6Wrapper<Units> (
                    d*u.angular.v[0], d*u.angular.v[1], d*u.angular.v[2],
					d*u.linear.v[0],  d*u.linear.v[1],  d*u.linear.v[2]
                );

}

#endif
