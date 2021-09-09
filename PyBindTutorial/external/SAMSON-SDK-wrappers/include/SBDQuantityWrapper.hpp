#pragma once

#define UNITSFORPYTHON
#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDQuantity.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

#define DO_NOT_EXPOSE_GETTER_SETTER_FUNCTIONS_AS_ATTRIBUTES_FOR_SAMSON_CLASSES_WHICH_USE_PYUNITS

/*
 * Support class which provides exponent and scale for SBQuantity::*
 */
template <typename Quantity>
class QuantityScaleExponent{

public:

    typedef typename Quantity::UnitType                 UnitType;
	typedef typename Quantity::UnitType::SystemType     SystemType;

    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemSI>::value, int>::type = 0>
    static std::vector<int>     getScale() {
            return {    UnitType::scale1,
                        UnitType::scale2,
                        UnitType::scale3,
                        UnitType::scale4,
                        UnitType::scale5,
                        UnitType::scale6,
                        UnitType::scale7};
    }
    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemAU>::value, int>::type = 0>
    static std::vector<int>     getScale() {
            return {    UnitType::scale1,
                        UnitType::scale2,
                        UnitType::scale3,
                        UnitType::scale4};
    }
    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemDalton>::value, int>::type = 0>
    static std::vector<int>     getScale() {
            return {    UnitType::scale1};
    }
    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemElectronvolt>::value, int>::type = 0>
    static std::vector<int>     getScale() {
            return {    UnitType::scale1};
    }
    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemKilocaloriePerMole>::value, int>::type = 0>
    static std::vector<int>     getScale() {
            return {    UnitType::scale1};
    }

    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemSI>::value, int>::type = 0>
    static std::vector<int>     getExponent() {
            return {    UnitType::exponent1,
                        UnitType::exponent2,
                        UnitType::exponent3,
                        UnitType::exponent4,
                        UnitType::exponent5,
                        UnitType::exponent6,
                        UnitType::exponent7};
    }
    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemAU>::value, int>::type = 0>
    static std::vector<int>     getExponent() {
            return {    UnitType::exponent1,
                        UnitType::exponent2,
                        UnitType::exponent3,
                        UnitType::exponent4};
    }
    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemDalton>::value, int>::type = 0>
    static std::vector<int>     getExponent() {
            return {    UnitType::exponent1};
    }
    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemElectronvolt>::value, int>::type = 0>
    static std::vector<int>     getExponent() {
            return {    UnitType::exponent1};
    }
    template<typename t = SystemType, typename std::enable_if<std::is_same<t, SBUnitSystemKilocaloriePerMole>::value, int>::type = 0>
    static std::vector<int>     getExponent() {
            return {    UnitType::exponent1};
    }

	static const std::vector<int>       scale;
	static const std::vector<int>       exponent;

};

template <typename Quantity>
const std::vector<int> QuantityScaleExponent<Quantity>::scale    = QuantityScaleExponent<Quantity>::getScale();

template <typename Quantity>
const std::vector<int> QuantityScaleExponent<Quantity>::exponent = QuantityScaleExponent<Quantity>::getExponent();


/*! \file SBDQuantityWrapper.hpp */

/// \brief This class defines physical units for use as a wrapper between SAMSON SDK Quantities and Python.
///
/// \tparam System The SBUnitSystem

template <typename System = SBUnitSystemSI>
class SBDQuantityWrapper {

public:

    /// \name Constructors
    //@{

    /// \brief Constructs a physical quantity with default value

	SBDQuantityWrapper() : value(0.0), scale(System::size, 0), exponent(System::size, 0) {}

    /// \brief Constructs a physical quantity with value \p v

	SBDQuantityWrapper(const double& v) : value(v), scale(System::size, 0), exponent(System::size, 0) {}

    /// \brief Constructs a physical quantity with value \p v, scale vector \p s and exponent vector \p e

	SBDQuantityWrapper(const double& v, const std::vector<int>&s, const std::vector<int>&e) :  value(v), scale(s), exponent(e) {}

    /// \brief Copy constructor: Constructs a physical quantity from quantity \p q

	SBDQuantityWrapper(const SBDQuantityWrapper<System>& q) : value(q.getValue()), scale(q.getScale()), exponent(q.getExponent()) {}

    /// \brief Constructs a physical quantity from arbitrary SBQuantity::Quantity \p q

    template<typename Quantity>
	SBDQuantityWrapper(const Quantity& q) {

        value    = q.getValue();
		scale    = QuantityScaleExponent<Quantity>::scale;
		exponent = QuantityScaleExponent<Quantity>::exponent;

	}

    //@}

    /// \name Destructors
    //@{

	~SBDQuantityWrapper() {}

    //@}

	/// \name Functions for comparing and scaling SBDQuantityWrapper
	//@{

    /// \brief Compares \p exponent to \p UnitTypeExponent

	bool							compareExponent(const std::vector<int>& unitTypeExponent) const {

		return unitTypeExponent == exponent;

    }

    /// \brief Compares \p exponent to \p exponent for Unit \p q

	bool							compareExponent(const SBDQuantityWrapper<System>& q) const {

		return q.exponent == exponent;

    }

	/// \brief Returns true if the physical quantity is dimensionless

	bool							isDimensionless() const {

		return (exponent == zeros);

	}

    /// \brief Returns scaling factor to \p UnitTypeScale without checking for \p exponent

	double							getScalingFactorToOtherUnit(const std::vector<int> &other_scale) const {

		if (scale == other_scale) return 1.0;

        double scaling_factor = 1.0;

		for (int i = 0; i < System::size; ++i)
			if (exponent[i] != 0)
				scaling_factor *= pow( 10.0, static_cast<double>( (scale[i] - other_scale[i]) * exponent[i]) );

        return scaling_factor;

    }

    /// \brief Returns value scaled to \p UnitTypeScale without checking for \p exponent

	double							getScaledValue(const std::vector<int>& UnitTypeScale) const { return value * getScalingFactorToOtherUnit(UnitTypeScale); }

    /// \brief Returns value scaled to \p UnitTypeScale with checking for \p exponent

	double							scaleToUnitType(const std::vector<int>& UnitTypeScale, const std::vector<int>& UnitTypeExponent) const {

		if (! compareExponent(UnitTypeExponent)) throw std::runtime_error("Units are not of the same type");

        return getScaledValue(UnitTypeScale);

    }

    /// \brief Returns Unit scaled to Unit \p u

	SBDQuantityWrapper<System>		getUnitScaledTo(const SBDQuantityWrapper<System>& u) const {

		if (! compareExponent(u.getExponent())) throw std::runtime_error("Units are not of the same type");

		//if (scale == u.getScale()) return SBDQuantityWrapper<System>(value, scale, exponent);

		return SBDQuantityWrapper<System>(value * getScalingFactorToOtherUnit(u.getScale()), u.getScale(), exponent);

    }

    //@}

    /// \name Getter and setter functions
    //@{

    /// \brief Returns the value

	double const&					getValue () const { return value; }

    /// \brief Sets the value, scale and exponent to be the same as for Unit \p u

	void							setToUnit (const SBDQuantityWrapper<System>& u) {

        value    = u.getValue();
        scale    = u.getScale();
        exponent = u.getExponent();

    }

    /*
     * There is a problem with changing value of the associated SBQuantity:
     * to change the value of the associated SBQuantity we need to store a pointer to this SBQuantity,
     * but we cannot detect if this SBQuantity was deleted or not, which leads to possible memory issues.
     * Therefore, for now, we do not store a connection to the associated SBQuantity.
    */

    /// \brief Sets the value to \p v

	void							setValue (const double &v) { value = v; }

    /// \brief Sets the value to zero

    void							setZero() { value = 0.0; }

    /// \brief Returns the scale

	const std::vector<int>&			getScale () const { return scale; }

    /// \brief Returns the exponent

	const std::vector<int>&			getExponent () const { return exponent; }

    /// \brief Returns the zeros vector with size as exponent and scale for comparison reasons

	const std::vector<int>&			getZerosVector () const { return zeros; }

    /// \brief Returns the reference scale for the current unit system

	static std::vector<int>			getRefScale() {

        if (std::is_same<System, SBUnitSystemSI>::value)
            return {    SBQuantity::length::UnitType::scale1,
                        SBQuantity::mass::UnitType::scale2,
                        SBQuantity::time::UnitType::scale3,
                        SBQuantity::intensity::UnitType::scale4,
                        SBQuantity::temperature::UnitType::scale5,
                        SBQuantity::amountOfSubstance::UnitType::scale6,
                        SBQuantity::luminousIntensity::UnitType::scale7};
        else if (std::is_same<System, SBUnitSystemAU>::value)
            return {    SBQuantity::auMass::UnitType::scale1,
                        SBQuantity::auCharge::UnitType::scale2,
                        SBQuantity::auAction::UnitType::scale3,
                        SBQuantity::auCoulombConstant::UnitType::scale4};
        else if (std::is_same<System, SBUnitSystemDalton>::value)
            return {    SBQuantity::dalton::UnitType::scale1};
        else if (std::is_same<System, SBUnitSystemElectronvolt>::value)
            return {    SBQuantity::electronvolt::UnitType::scale1};
        else if (std::is_same<System, SBUnitSystemKilocaloriePerMole>::value)
            return {    SBQuantity::kilocaloriePerMole::UnitType::scale1};
        else return {};

    }

    /// \brief Returns the size of the Unit system

	int								getUnitSystemSize () const { return System::size; }

    /// \brief Returns the SBQuantity::Quantity

    template<typename Quantity>
	Quantity						toSBQuantity() const {

		return Quantity( scaleToUnitType(QuantityScaleExponent<Quantity>::scale, QuantityScaleExponent<Quantity>::exponent) );

    }

    /// \brief Returns the value of SBQuantity::Quantity

    template<typename Quantity, typename t = System,
             typename std::enable_if<std::is_same<t, SBUnitSystemSI>::value, int>::type = 0>
	double							toSBQuantityValue() const {

		if (QuantityScaleExponent<Quantity>::exponent.size() < 7) throw std::runtime_error("The unit system has a wrong size");

		if (    static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[0]) ^ static_cast<bool>(exponent[0]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[1]) ^ static_cast<bool>(exponent[1]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[2]) ^ static_cast<bool>(exponent[2]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[3]) ^ static_cast<bool>(exponent[3]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[4]) ^ static_cast<bool>(exponent[4]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[5]) ^ static_cast<bool>(exponent[5]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[6]) ^ static_cast<bool>(exponent[6]) )
			throw std::runtime_error("This attribute cannot be applied to this unit");

		return getScaledValue(QuantityScaleExponent<Quantity>::scale);

    }

    template<typename Quantity, typename t = System,
             typename std::enable_if<std::is_same<t, SBUnitSystemAU>::value, int>::type = 0>
	double							toSBQuantityValue() const {

		if (QuantityScaleExponent<Quantity>::exponent.size() < 4) throw std::runtime_error("The unit system has a wrong size");

		if (    static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[0]) ^ static_cast<bool>(exponent[0]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[1]) ^ static_cast<bool>(exponent[1]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[2]) ^ static_cast<bool>(exponent[2]) ||
				static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[3]) ^ static_cast<bool>(exponent[3]) )
			throw std::runtime_error("This attribute cannot be applied to this unit");

		return getScaledValue(QuantityScaleExponent<Quantity>::scale);

    }

    template<typename Quantity, typename t = System,
             typename std::enable_if<std::is_same<t, SBUnitSystemDalton>::value, int>::type = 0>
	double							toSBQuantityValue() const {

		if (QuantityScaleExponent<Quantity>::exponent.size() < 1) throw std::runtime_error("The unit system has a wrong size");

		if ( static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[0]) ^ static_cast<bool>(exponent[0]) )
			throw std::runtime_error("This attribute cannot be applied to this unit");

		return getScaledValue(QuantityScaleExponent<Quantity>::scale);

    }

    template<typename Quantity, typename t = System,
             typename std::enable_if<std::is_same<t, SBUnitSystemElectronvolt>::value, int>::type = 0>
    double                          toSBQuantityValue() const {

		if (QuantityScaleExponent<Quantity>::exponent.size() < 1) throw std::runtime_error("The unit system has a wrong size");

		if ( static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[0]) ^ static_cast<bool>(exponent[0]) )
			throw std::runtime_error("This attribute cannot be applied to this unit");

		return getScaledValue(QuantityScaleExponent<Quantity>::scale);

    }

    template<typename Quantity, typename t = System,
             typename std::enable_if<std::is_same<t, SBUnitSystemKilocaloriePerMole>::value, int>::type = 0>
    double                          toSBQuantityValue() const {

		if (QuantityScaleExponent<Quantity>::exponent.size() < 1) throw std::runtime_error("The unit system has a wrong size");

		if ( static_cast<bool>(QuantityScaleExponent<Quantity>::exponent[0]) ^ static_cast<bool>(exponent[0]) )
			throw std::runtime_error("This attribute cannot be applied to this unit");

		return getScaledValue(QuantityScaleExponent<Quantity>::scale);

    }

    //@}

    /// \name Operators
    //@{

    /// \brief Copy the physical quantity \p q

	SBDQuantityWrapper<System>&		operator=(const SBDQuantityWrapper<System>& q) {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot copy different units");

        value = q.getScaledValue(scale);
        return *this;

	}

    /// \brief Assign the double \p d to the physical quantity (for dimensionless physical quantities only)

	SBDQuantityWrapper<System>&		operator=(const double d) {

		if (!isDimensionless()) throw std::runtime_error("Assigning a double to a quantity is only allowed for dimensionless quantities.");

        value = d;
        return *this;

    }

    /// \brief Returns the opposite of the physical quantity

	SBDQuantityWrapper<System>		operator-() const { return SBDQuantityWrapper(-value, scale, exponent); }

    /// \brief Returns the sum of this physical quantity with physical quantity \p q

	SBDQuantityWrapper<System>		operator+(const SBDQuantityWrapper<System>& q) const {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot add different units");

		return SBDQuantityWrapper<System>(value + (q.getScale() == scale ? q.getValue() : q.getScaledValue(scale)), scale, exponent);

    }

    /// \brief Returns the sum of this physical quantity with double \p d (for dimensionless physical quantities only)

	SBDQuantityWrapper<System>		operator+(const double d) const {

		if (!isDimensionless()) throw std::runtime_error("Adding a double to a quantity is only allowed for dimensionless quantities.");

		return SBDQuantityWrapper<System>(value + d);

    }

    /// \brief Adds physical quantity \p q to this physical quantity

	SBDQuantityWrapper<System>&		operator+=(const SBDQuantityWrapper<System>& q) {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot add different units");

        value += q.getScaledValue(scale);
        return *this;

    }

    /// \brief Add double \p d to this physical quantity (for dimensionless physical quantities only)

	SBDQuantityWrapper<System>&		operator+=(const double d) {

		if (!isDimensionless()) throw std::runtime_error("Assigning a double to a quantity is only allowed for dimensionless quantities.");

        value += d;
        return *this;

    }

    /// \brief Returns the difference between this physical quantity and physical quantity \p q

	SBDQuantityWrapper<System>		operator-(const SBDQuantityWrapper<System>& q) const {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot subtract different units");

		return SBDQuantityWrapper<System>(value - (q.getScaledValue(scale)), scale, exponent);

    }

    /// \brief Returns the difference between this physical quantity and double \p d (for dimensionless physical quantities only)

	SBDQuantityWrapper<System>		operator-(const double d) const {

		if (!isDimensionless()) throw std::runtime_error("Subtracting a double to a quantity is only allowed for dimensionless quantities.");

		return SBDQuantityWrapper<System>(value - d);

    }

    /// \brief Subtracts physical quantity \p q from this physical quantity

	SBDQuantityWrapper<System>&		operator-=(const SBDQuantityWrapper<System>& q) {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot subtract different units");

        value -= q.getScaledValue(scale);
        return *this;

    }

    /// \brief Subtracts double \p d from this physical quantity (for dimensionless physical quantities only)

	SBDQuantityWrapper<System>&		operator-=(const double d) {

		if (!isDimensionless()) throw std::runtime_error("Subtracting a double to a quantity is only allowed for dimensionless quantities.");

        value -= d;
        return *this;

    }

    /// \brief Returns the product of this physical quantity with double \p d

	SBDQuantityWrapper<System>		operator*(const double d) const { return SBDQuantityWrapper<System>(d * value, scale, exponent); }

    /// \brief Multiplies this physical quantity with double \p d

	SBDQuantityWrapper<System>&		operator*=(const double d) { value *= d; return *this; }

    /// \brief Returns the product of this physical quantity with physical quantity \p q

	SBDQuantityWrapper<System>		operator* (const SBDQuantityWrapper<System>& q) const {

		SBDQuantityWrapper<System> result;

        for (int i = 0; i < System::size; ++i)
            result.scale[i] = (exponent[i] != 0 ? scale[i] : q.getScale()[i]);

        result.value = getScaledValue(result.scale) * q.getScaledValue(result.scale);

        for (int i = 0; i < System::size; ++i)
            result.exponent[i] = exponent[i] + q.getExponent()[i];

        return result;
    }

    /// \brief Multiplies this physical quantity with physical quantity \p q

	SBDQuantityWrapper<System>&		operator*=(const SBDQuantityWrapper<System>& q) {

		std::vector<int> result_scale(System::size, 0);

        for (int i = 0; i < System::size; ++i)
            result_scale[i] = (exponent[i] != 0 ? scale[i] : q.getScale()[i]);

        value = getScaledValue(result_scale) * q.getScaledValue(result_scale);

        scale = result_scale;
        for (int i = 0; i < System::size; ++i)
            exponent[i] = exponent[i] + q.getExponent()[i];

        return *this;

    }

    /// \brief Returns the division of this physical quantity by double \p d

	SBDQuantityWrapper<System>		operator/(const double d) const { return SBDQuantityWrapper<System>(value / d, scale, exponent); }

    /// \brief Divides this physical quantity by double \p d

	SBDQuantityWrapper<System>&		operator/=(const double d) { value /= d; return *this; }

    /// \brief Returns the division of this physical quantity by physical quantity \p q

	SBDQuantityWrapper<System>		operator/ (const SBDQuantityWrapper<System>& q) const {

		SBDQuantityWrapper<System> result;

        for (int i = 0; i < System::size; ++i)
            result.scale[i] = (exponent[i] != 0 ? scale[i] : q.getScale()[i]);

        result.value = getScaledValue(result.scale) / q.getScaledValue(result.scale);

        for (int i = 0; i < System::size; ++i)
            result.exponent[i] = exponent[i] - q.getExponent()[i];

        return result;

    }

    /// \brief Divides this physical quantity by physical quantity \p q (for dimensionless physical quantities only)

	SBDQuantityWrapper<System>&		operator/=(const SBDQuantityWrapper<System>& q) {

		std::vector<int> result_scale(System::size, 0);

        for (int i = 0; i < System::size; ++i)
            result_scale[i] = (exponent[i] != 0 ? scale[i] : q.getScale()[i]);

        value = getScaledValue(result_scale) / q.getScaledValue(result_scale);

        scale = result_scale;
        for (int i = 0; i < System::size; ++i)
            exponent[i] = exponent[i] - q.getExponent()[i];

        return *this;

    }

    /// \brief Returns true if this physical quantity is equal to physical quantity \p q

	bool							operator==(const SBDQuantityWrapper<System>& q) const {

		if (q.getExponent() != exponent) return false;

        return value == q.getScaledValue(scale);

    }

    /// \brief Returns true if this physical quantity is different from physical quantity \p q

	bool							operator!=(const SBDQuantityWrapper<System>& q) const {

		if (q.getExponent() != exponent) return true;

        return value != q.getScaledValue(scale);

    }

    /// \brief Returns true if this physical quantity is smaller than physical quantity \p q

	bool							operator<(const SBDQuantityWrapper<System>& q) const {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot compare different units");

        return value < q.getScaledValue(scale);

    }

    /// \brief Returns true if this physical quantity is larger than physical quantity \p q

	bool							operator>(const SBDQuantityWrapper<System>& q) const {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot compare different units");

        return value > q.getScaledValue(scale);

    }

    /// \brief Returns true if this physical quantity is smaller than or equal to physical quantity \p q

	bool							operator<=(const SBDQuantityWrapper<System>& q) const {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot compare different units");

        return value <= q.getScaledValue(scale);

    }

    /// \brief Returns true if this physical quantity is larger or equal to than physical quantity \p q

	bool							operator>=(const SBDQuantityWrapper<System>& q) const {

		if (q.getExponent() != exponent) throw std::runtime_error("Cannot compare different units");

        return value >= q.getScaledValue(scale);

    }


    /// \brief Returns true if this physical quantity is equal to double \p d (for dimensionless physical quantities only)

	bool							operator==(const double d) const {

		if (!isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

        return value == d;

    }

    /// \brief Returns true if this physical quantity is different from double \p d (for dimensionless physical quantities only)

	bool							operator!=(const double d) const {

		if (!isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

        return value != d;

    }

    /// \brief Returns true if this physical quantity is smaller than double \p d (for dimensionless physical quantities only)

	bool							operator<(const double d) const {

		if (!isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

        return value < d;

    }

    /// \brief Returns true if this physical quantity is larger than double \p d (for dimensionless physical quantities only)

	bool							operator>(const double d) const {

		if (!isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

        return value > d;

    }

    /// \brief Returns true if this physical quantity is smaller than or equal to double \p d (for dimensionless physical quantities only)

	bool							operator<=(const double d) const {

		if (!isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

        return value <= d;

    }

    /// \brief Returns true if this physical quantity is larger than or equal to double \p d (for dimensionless physical quantities only)

	bool							operator>=(const double d) const {

		if (!isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

        return value >= d;

    }

    //@}

    /// \name Useful functions
    //@{

	/// \brief Returns a linear interpolation between two physical quantities \p q0 and \p q1 for a parameter \p alpha in the closed unit interval [0, 1].

	static SBDQuantityWrapper<System>							fromLinearInterpolation(const SBDQuantityWrapper<System>& q0, const SBDQuantityWrapper<System>& q1, double alpha) {

		if (q0.getExponent() != q1.getExponent()) throw std::runtime_error("Cannot produce a linear interpolation from quantities of different units.");

		if (alpha < 0.0) return q0;
		if (alpha > 1.0) return q1;

		return (1.0 - alpha) * q0 + alpha * q1;

	}

    /*template <class Quantity>
    std::string getNameOrSymbol(bool fullName = false) {

        return fullName ? Quantity::UnitType::getName() : Quantity::UnitType::getSymbol();

    }*/

    /// \brief Returns string representation of the unit

	/*template<typename t = System, typename std::enable_if<!std::is_same<t, SBUnitSystemAU>::value, int>::type = 0>*/
	std::string						toStdString (const bool fullName = false) const {

		if      (std::is_same<System, SBUnitSystemSI>::value)
            return toStdString_SI(fullName);
        else if (std::is_same<System, SBUnitSystemAU>::value)
            return toStdString_AU(fullName);
        else if (std::is_same<System, SBUnitSystemDalton>::value)
            return toStdString_Dalton(fullName);
        else if (std::is_same<System, SBUnitSystemElectronvolt>::value)
            return toStdString_Electronvolt(fullName);
        else if (std::is_same<System, SBUnitSystemKilocaloriePerMole>::value)
            return toStdString_KilocaloriePerMole(fullName);
        else
            throw std::runtime_error("Unit system is not defined");

    }

	/*template<typename t = System, typename std::enable_if<std::is_same<t, SBUnitSystemAU>::value, int>::type = 0>*/
	std::string						toStdString_AU(const bool fullName = false) const {

        if (System::size != 4) throw std::runtime_error("Changed size of AU unit system");

        std::string ret = "";
        std::vector<int> scaleForStr = ref_scale;

        // mass
        if (exponent[0] != 0) {

            ret += fullName ? SBQuantity::electronMass::UnitType::getName() : SBQuantity::electronMass::UnitType::getSymbol();
            scaleForStr[0] = SBQuantity::electronMass::UnitType::scale1;

            // add power if necessary
            if (exponent[0] != 1) ret += "^" + std::to_string(exponent[0]);

        }

        // charge
        if (exponent[1] != 0) {

            if (ret != "") ret += ".";
            ret += fullName ? SBQuantity::electronCharge::UnitType::getName() : SBQuantity::electronCharge::UnitType::getSymbol();
            scaleForStr[1] = SBQuantity::electronCharge::UnitType::scale2;

            // add power if necessary
            if (exponent[1] != 1) ret += "^" + std::to_string(exponent[1]);

        }

        // action
        if (exponent[2] != 0) {

            if (ret != "") ret += ".";
            ret += fullName ? SBQuantity::auAction::UnitType::getName() : SBQuantity::auAction::UnitType::getSymbol();
            scaleForStr[2] = SBQuantity::auAction::UnitType::scale3;

            // add power if necessary
            if (exponent[2] != 1) ret += "^" + std::to_string(exponent[2]);

        }

        // action
        if (exponent[3] != 0) {

            if (ret != "") ret += ".";
            ret += fullName ? SBQuantity::auCoulombConstant::UnitType::getName() : SBQuantity::auCoulombConstant::UnitType::getSymbol();
            scaleForStr[3] = SBQuantity::auCoulombConstant::UnitType::scale4;

            // add power if necessary
            if (exponent[3] != 1) ret += "^" + std::to_string(exponent[3]);

        }


        double v = value * getScalingFactorToOtherUnit(scaleForStr);

        ret = std::to_string(v) + " " + ret;

        return ret;

    }

	std::string						toStdString_Dalton(const bool fullName = false) const {

        if (System::size != 1) throw std::runtime_error("Changed size of Dalton unit system");

        std::string ret = "";
        std::vector<int> scaleForStr = ref_scale;

        if (exponent[0] != 0) {

            scaleForStr[0] = scale[0];
			if      (scale[0] == SBQuantity::gigadalton::UnitType::scale1) {ret += fullName ? SBQuantity::gigadalton::UnitType::getName() : SBQuantity::gigadalton::UnitType::getSymbol() ; }
            else if (scale[0] == SBQuantity::megadalton::UnitType::scale1) {ret += fullName ? SBQuantity::megadalton::UnitType::getName() : SBQuantity::megadalton::UnitType::getSymbol() ; }
            else if (scale[0] == SBQuantity::kilodalton::UnitType::scale1) {ret += fullName ? SBQuantity::kilodalton::UnitType::getName() : SBQuantity::kilodalton::UnitType::getSymbol() ; }
			else if (scale[0] == SBQuantity::dalton::UnitType::scale1    ) {ret += fullName ? SBQuantity::dalton::UnitType::getName()     : SBQuantity::dalton::UnitType::getSymbol() ; }
            else {
                     ret += fullName ? SBQuantity::dalton::UnitType::getName() : SBQuantity::dalton::UnitType::getSymbol();
                     scaleForStr[0] = SBQuantity::dalton::UnitType::scale1;
                 }

            // add power if necessary
            if (exponent[0] != 1) ret += "^" + std::to_string(exponent[0]);

        }

        double v = value * getScalingFactorToOtherUnit(scaleForStr);

        ret = std::to_string(v) + " " + ret;

        return ret;

    }

	std::string						toStdString_Electronvolt(const bool fullName = false) const {

        if (System::size != 1) throw std::runtime_error("Changed size of Electronvolt unit system");

        std::string ret = "";
        std::vector<int> scaleForStr = ref_scale;

		if (exponent[0] != 0) {

            ret += fullName ? SBQuantity::electronvolt::UnitType::getName() : SBQuantity::electronvolt::UnitType::getSymbol();
            scaleForStr[0] = SBQuantity::electronvolt::UnitType::scale1;

            // add power if necessary
            if (exponent[0] != 1) ret += "^" + std::to_string(exponent[0]);

        }

        double v = value * getScalingFactorToOtherUnit(scaleForStr);

        ret = std::to_string(v) + " " + ret;

        return ret;

    }

	std::string						toStdString_KilocaloriePerMole(const bool fullName = false) const {

        if (System::size != 1) throw std::runtime_error("Changed size of KilocaloriePerMole unit system");

        //std::stringstream sstream;
        std::string ret = "";
        std::vector<int> scaleForStr = ref_scale;

        if (exponent[0] != 0) {

            ret += fullName ? SBQuantity::kilocaloriePerMole::UnitType::getName() : SBQuantity::kilocaloriePerMole::UnitType::getSymbol();
            scaleForStr[0] = SBQuantity::kilocaloriePerMole::UnitType::scale1;

            // add power if necessary
            if (exponent[0] != 1) ret += "^" + std::to_string(exponent[0]);

        }

        double v = value * getScalingFactorToOtherUnit(scaleForStr);

        ret = std::to_string(v) + " " + ret;

        return ret;

    }

	std::string						toStdString_SI(const bool fullName = false) const {

        if (System::size != 7) throw std::runtime_error("Changed size of SI unit system");

        std::string ret = "";
		std::vector<int> scaleForStr = ref_scale;

        // dimensionless
		if (isDimensionless()) {

            ret = std::to_string(value) + " (dimensionless)";
            return ret;

        }

        // length
		if (exponent[0] != 0) {

            scaleForStr[0] = scale[0];
			if      (scale[0] == SBQuantity::kilometer::UnitType::scale1 ) {ret += fullName ? SBQuantity::kilometer::UnitType::getName()  : SBQuantity::kilometer::UnitType::getSymbol() ; }
            else if (scale[0] == SBQuantity::hectometer::UnitType::scale1) {ret += fullName ? SBQuantity::hectometer::UnitType::getName() : SBQuantity::hectometer::UnitType::getSymbol(); }
            else if (scale[0] == SBQuantity::decameter::UnitType::scale1 ) {ret += fullName ? SBQuantity::decameter::UnitType::getName()  : SBQuantity::decameter::UnitType::getSymbol() ; }
            else if (scale[0] == SBQuantity::meter::UnitType::scale1     ) {ret += fullName ? SBQuantity::meter::UnitType::getName()      : SBQuantity::meter::UnitType::getSymbol()     ; }
            else if (scale[0] == SBQuantity::decimeter::UnitType::scale1 ) {ret += fullName ? SBQuantity::decimeter::UnitType::getName()  : SBQuantity::decimeter::UnitType::getSymbol() ; }
            else if (scale[0] == SBQuantity::centimeter::UnitType::scale1) {ret += fullName ? SBQuantity::centimeter::UnitType::getName() : SBQuantity::centimeter::UnitType::getSymbol(); }
            else if (scale[0] == SBQuantity::millimeter::UnitType::scale1) {ret += fullName ? SBQuantity::millimeter::UnitType::getName() : SBQuantity::millimeter::UnitType::getSymbol(); }
            else if (scale[0] == SBQuantity::micrometer::UnitType::scale1) {ret += fullName ? SBQuantity::micrometer::UnitType::getName() : SBQuantity::micrometer::UnitType::getSymbol(); }
            else if (scale[0] == SBQuantity::nanometer::UnitType::scale1 ) {ret += fullName ? SBQuantity::nanometer::UnitType::getName()  : SBQuantity::nanometer::UnitType::getSymbol() ; }
			else if (scale[0] == SBQuantity::angstrom::UnitType::scale1  ) {ret += fullName ? SBQuantity::angstrom::UnitType::getName()   : std::string("Å")/*SBQuantity::angstrom::UnitType::getSymbol()*/  ; }
            else if (scale[0] == SBQuantity::picometer::UnitType::scale1 ) {ret += fullName ? SBQuantity::picometer::UnitType::getName()  : SBQuantity::picometer::UnitType::getSymbol() ; }
            else if (scale[0] == SBQuantity::femtometer::UnitType::scale1) {ret += fullName ? SBQuantity::femtometer::UnitType::getName() : SBQuantity::femtometer::UnitType::getSymbol(); }
            else if (scale[0] == SBQuantity::attometer::UnitType::scale1 ) {ret += fullName ? SBQuantity::attometer::UnitType::getName()  : SBQuantity::attometer::UnitType::getSymbol() ; }
            else if (scale[0] == SBQuantity::zeptometer::UnitType::scale1) {ret += fullName ? SBQuantity::zeptometer::UnitType::getName() : SBQuantity::zeptometer::UnitType::getSymbol(); }
            else if (scale[0] == SBQuantity::yoctometer::UnitType::scale1) {ret += fullName ? SBQuantity::yoctometer::UnitType::getName() : SBQuantity::yoctometer::UnitType::getSymbol(); }
            else {
                     ret += fullName ? SBQuantity::picometer::UnitType::getName() : SBQuantity::picometer::UnitType::getSymbol();
                     scaleForStr[0] = SBQuantity::picometer::UnitType::scale1;
                 }

            // add power if necessary
            if (exponent[0] != 1) ret += "^" + std::to_string(exponent[0]);

        }
        // mass
		if (exponent[1] != 0) {

            if (ret != "") ret += ".";
            scaleForStr[1] = scale[1];
			if      (scale[1] == SBQuantity::kilogram::UnitType::scale2 ) {ret += fullName ? SBQuantity::kilogram::UnitType::getName()  : SBQuantity::kilogram::UnitType::getSymbol() ; }
            else if (scale[1] == SBQuantity::hectogram::UnitType::scale2) {ret += fullName ? SBQuantity::hectogram::UnitType::getName() : SBQuantity::hectogram::UnitType::getSymbol(); }
            else if (scale[1] == SBQuantity::decagram::UnitType::scale2 ) {ret += fullName ? SBQuantity::decagram::UnitType::getName()  : SBQuantity::decagram::UnitType::getSymbol() ; }
            else if (scale[1] == SBQuantity::gram::UnitType::scale2     ) {ret += fullName ? SBQuantity::gram::UnitType::getName()      : SBQuantity::gram::UnitType::getSymbol()     ; }
            else if (scale[1] == SBQuantity::decigram::UnitType::scale2 ) {ret += fullName ? SBQuantity::decigram::UnitType::getName()  : SBQuantity::decigram::UnitType::getSymbol() ; }
            else if (scale[1] == SBQuantity::centigram::UnitType::scale2) {ret += fullName ? SBQuantity::centigram::UnitType::getName() : SBQuantity::centigram::UnitType::getSymbol(); }
            else if (scale[1] == SBQuantity::milligram::UnitType::scale2) {ret += fullName ? SBQuantity::milligram::UnitType::getName() : SBQuantity::milligram::UnitType::getSymbol(); }
            else if (scale[1] == SBQuantity::microgram::UnitType::scale2) {ret += fullName ? SBQuantity::microgram::UnitType::getName() : SBQuantity::microgram::UnitType::getSymbol(); }
            else if (scale[1] == SBQuantity::nanogram::UnitType::scale2 ) {ret += fullName ? SBQuantity::nanogram::UnitType::getName()  : SBQuantity::nanogram::UnitType::getSymbol() ; }
            else if (scale[1] == SBQuantity::picogram::UnitType::scale2 ) {ret += fullName ? SBQuantity::picogram::UnitType::getName()  : SBQuantity::picogram::UnitType::getSymbol() ; }
            else if (scale[1] == SBQuantity::femtogram::UnitType::scale2) {ret += fullName ? SBQuantity::femtogram::UnitType::getName() : SBQuantity::femtogram::UnitType::getSymbol(); }
            else if (scale[1] == SBQuantity::attogram::UnitType::scale2 ) {ret += fullName ? SBQuantity::attogram::UnitType::getName()  : SBQuantity::attogram::UnitType::getSymbol() ; }
            else if (scale[1] == SBQuantity::zeptogram::UnitType::scale2) {ret += fullName ? SBQuantity::zeptogram::UnitType::getName() : SBQuantity::zeptogram::UnitType::getSymbol(); }
            else if (scale[1] == SBQuantity::yoctogram::UnitType::scale2) {ret += fullName ? SBQuantity::yoctogram::UnitType::getName() : SBQuantity::yoctogram::UnitType::getSymbol(); }
            else {
                     ret += fullName ? SBQuantity::yoctogram::UnitType::getName() : SBQuantity::yoctogram::UnitType::getSymbol();
                     scaleForStr[1] = SBQuantity::yoctogram::UnitType::scale2;
                 }

            // add power if necessary
            if (exponent[1] != 1) ret += "^" + std::to_string(exponent[1]);

        }
        // time
		if (exponent[2] != 0) {

            if (ret != "") ret += ".";
            scaleForStr[2] = scale[2];
			if      (scale[2] == SBQuantity::second::UnitType::scale3     ) {ret += fullName ? SBQuantity::second::UnitType::getName()      : SBQuantity::second::UnitType::getSymbol()     ; }
            else if (scale[2] == SBQuantity::decisecond::UnitType::scale3 ) {ret += fullName ? SBQuantity::decisecond::UnitType::getName()  : SBQuantity::decisecond::UnitType::getSymbol() ; }
            else if (scale[2] == SBQuantity::centisecond::UnitType::scale3) {ret += fullName ? SBQuantity::centisecond::UnitType::getName() : SBQuantity::centisecond::UnitType::getSymbol(); }
            else if (scale[2] == SBQuantity::millisecond::UnitType::scale3) {ret += fullName ? SBQuantity::millisecond::UnitType::getName() : SBQuantity::millisecond::UnitType::getSymbol(); }
            else if (scale[2] == SBQuantity::microsecond::UnitType::scale3) {ret += fullName ? SBQuantity::microsecond::UnitType::getName() : SBQuantity::microsecond::UnitType::getSymbol(); }
            else if (scale[2] == SBQuantity::nanosecond::UnitType::scale3 ) {ret += fullName ? SBQuantity::nanosecond::UnitType::getName()  : SBQuantity::nanosecond::UnitType::getSymbol() ; }
            else if (scale[2] == SBQuantity::picosecond::UnitType::scale3 ) {ret += fullName ? SBQuantity::picosecond::UnitType::getName()  : SBQuantity::picosecond::UnitType::getSymbol() ; }
            else if (scale[2] == SBQuantity::femtosecond::UnitType::scale3) {ret += fullName ? SBQuantity::femtosecond::UnitType::getName() : SBQuantity::femtosecond::UnitType::getSymbol(); }
            else if (scale[2] == SBQuantity::attosecond::UnitType::scale3 ) {ret += fullName ? SBQuantity::attosecond::UnitType::getName()  : SBQuantity::attosecond::UnitType::getSymbol() ; }
            else if (scale[2] == SBQuantity::zeptosecond::UnitType::scale3) {ret += fullName ? SBQuantity::zeptosecond::UnitType::getName() : SBQuantity::zeptosecond::UnitType::getSymbol(); }
            else if (scale[2] == SBQuantity::yoctosecond::UnitType::scale3) {ret += fullName ? SBQuantity::yoctosecond::UnitType::getName() : SBQuantity::yoctosecond::UnitType::getSymbol(); }
            else {
                     ret += fullName ? SBQuantity::femtosecond::UnitType::getName() : SBQuantity::femtosecond::UnitType::getSymbol();
                     scaleForStr[2] = SBQuantity::femtosecond::UnitType::scale3;
                 }

            // add power if necessary
            if (exponent[2] != 1) ret += "^" + std::to_string(exponent[2]);

        }
        // intensity
		if (exponent[3] != 0) {

            if (ret != "") ret += ".";
            scaleForStr[3] = scale[3];
			if      (scale[3] == SBQuantity::kiloampere::UnitType::scale4 ) {ret += fullName ? SBQuantity::kiloampere::UnitType::getName()  : SBQuantity::kiloampere::UnitType::getSymbol() ; }
            else if (scale[3] == SBQuantity::hectoampere::UnitType::scale4) {ret += fullName ? SBQuantity::hectoampere::UnitType::getName() : SBQuantity::hectoampere::UnitType::getSymbol(); }
            else if (scale[3] == SBQuantity::decaampere::UnitType::scale4 ) {ret += fullName ? SBQuantity::decaampere::UnitType::getName()  : SBQuantity::decaampere::UnitType::getSymbol() ; }
            else if (scale[3] == SBQuantity::ampere::UnitType::scale4     ) {ret += fullName ? SBQuantity::ampere::UnitType::getName()      : SBQuantity::ampere::UnitType::getSymbol()     ; }
            else if (scale[3] == SBQuantity::deciampere::UnitType::scale4 ) {ret += fullName ? SBQuantity::deciampere::UnitType::getName()  : SBQuantity::deciampere::UnitType::getSymbol() ; }
            else if (scale[3] == SBQuantity::centiampere::UnitType::scale4) {ret += fullName ? SBQuantity::centiampere::UnitType::getName() : SBQuantity::centiampere::UnitType::getSymbol(); }
            else if (scale[3] == SBQuantity::milliampere::UnitType::scale4) {ret += fullName ? SBQuantity::milliampere::UnitType::getName() : SBQuantity::milliampere::UnitType::getSymbol(); }
            else if (scale[3] == SBQuantity::microampere::UnitType::scale4) {ret += fullName ? SBQuantity::microampere::UnitType::getName() : SBQuantity::microampere::UnitType::getSymbol(); }
            else if (scale[3] == SBQuantity::nanoampere::UnitType::scale4 ) {ret += fullName ? SBQuantity::nanoampere::UnitType::getName()  : SBQuantity::nanoampere::UnitType::getSymbol() ; }
            else if (scale[3] == SBQuantity::picoampere::UnitType::scale4 ) {ret += fullName ? SBQuantity::picoampere::UnitType::getName()  : SBQuantity::picoampere::UnitType::getSymbol() ; }
            else if (scale[3] == SBQuantity::femtoampere::UnitType::scale4) {ret += fullName ? SBQuantity::femtoampere::UnitType::getName() : SBQuantity::femtoampere::UnitType::getSymbol(); }
            else if (scale[3] == SBQuantity::attoampere::UnitType::scale4 ) {ret += fullName ? SBQuantity::attoampere::UnitType::getName()  : SBQuantity::attoampere::UnitType::getSymbol() ; }
            else if (scale[3] == SBQuantity::zeptoampere::UnitType::scale4) {ret += fullName ? SBQuantity::zeptoampere::UnitType::getName() : SBQuantity::zeptoampere::UnitType::getSymbol(); }
            else if (scale[3] == SBQuantity::yoctoampere::UnitType::scale4) {ret += fullName ? SBQuantity::yoctoampere::UnitType::getName() : SBQuantity::yoctoampere::UnitType::getSymbol(); }
            else {
                     ret += fullName ? SBQuantity::nanoampere::UnitType::getName() : SBQuantity::nanoampere::UnitType::getSymbol();
                     scaleForStr[3] = SBQuantity::nanoampere::UnitType::scale4;
                 }

            // add power if necessary
            if (exponent[3] != 1) ret += "^" + std::to_string(exponent[3]);

        }
        // temperature
		if (exponent[4] != 0) {

            if (ret != "") ret += ".";
            scaleForStr[4] = scale[4];
			if      (scale[4] == SBQuantity::kilokelvin::UnitType::scale5 ) {ret += fullName ? SBQuantity::kilokelvin::UnitType::getName()  : SBQuantity::kilokelvin::UnitType::getSymbol() ; }
            else if (scale[4] == SBQuantity::hectokelvin::UnitType::scale5) {ret += fullName ? SBQuantity::hectokelvin::UnitType::getName() : SBQuantity::hectokelvin::UnitType::getSymbol(); }
            else if (scale[4] == SBQuantity::decakelvin::UnitType::scale5 ) {ret += fullName ? SBQuantity::decakelvin::UnitType::getName()  : SBQuantity::decakelvin::UnitType::getSymbol() ; }
            else if (scale[4] == SBQuantity::kelvin::UnitType::scale5     ) {ret += fullName ? SBQuantity::kelvin::UnitType::getName()      : SBQuantity::kelvin::UnitType::getSymbol()     ; }
            else if (scale[4] == SBQuantity::decikelvin::UnitType::scale5 ) {ret += fullName ? SBQuantity::decikelvin::UnitType::getName()  : SBQuantity::decikelvin::UnitType::getSymbol() ; }
            else if (scale[4] == SBQuantity::centikelvin::UnitType::scale5) {ret += fullName ? SBQuantity::centikelvin::UnitType::getName() : SBQuantity::centikelvin::UnitType::getSymbol(); }
            else if (scale[4] == SBQuantity::millikelvin::UnitType::scale5) {ret += fullName ? SBQuantity::millikelvin::UnitType::getName() : SBQuantity::millikelvin::UnitType::getSymbol(); }
            else if (scale[4] == SBQuantity::microkelvin::UnitType::scale5) {ret += fullName ? SBQuantity::microkelvin::UnitType::getName() : SBQuantity::microkelvin::UnitType::getSymbol(); }
            else if (scale[4] == SBQuantity::nanokelvin::UnitType::scale5 ) {ret += fullName ? SBQuantity::nanokelvin::UnitType::getName()  : SBQuantity::nanokelvin::UnitType::getSymbol() ; }
            else if (scale[4] == SBQuantity::picokelvin::UnitType::scale5 ) {ret += fullName ? SBQuantity::picokelvin::UnitType::getName()  : SBQuantity::picokelvin::UnitType::getSymbol() ; }
            else if (scale[4] == SBQuantity::femtokelvin::UnitType::scale5) {ret += fullName ? SBQuantity::femtokelvin::UnitType::getName() : SBQuantity::femtokelvin::UnitType::getSymbol(); }
            else if (scale[4] == SBQuantity::attokelvin::UnitType::scale5 ) {ret += fullName ? SBQuantity::attokelvin::UnitType::getName()  : SBQuantity::attokelvin::UnitType::getSymbol() ; }
            else if (scale[4] == SBQuantity::zeptokelvin::UnitType::scale5) {ret += fullName ? SBQuantity::zeptokelvin::UnitType::getName() : SBQuantity::zeptokelvin::UnitType::getSymbol(); }
            else if (scale[4] == SBQuantity::yoctokelvin::UnitType::scale5) {ret += fullName ? SBQuantity::yoctokelvin::UnitType::getName() : SBQuantity::yoctokelvin::UnitType::getSymbol(); }
            else {
                     ret += fullName ? SBQuantity::kelvin::UnitType::getName() : SBQuantity::kelvin::UnitType::getSymbol() ;
                     scaleForStr[4] = SBQuantity::kelvin::UnitType::scale5;
                 }

            // add power if necessary
            if (exponent[4] != 1) ret += "^" + std::to_string(exponent[4]);

        }
        // amount of substance
		if (exponent[5] != 0) {

            if (ret != "") ret += ".";
            scaleForStr[5] = scale[5];
			if      (scale[5] == SBQuantity::kilomole::UnitType::scale6 ) {ret += fullName ? SBQuantity::kilomole::UnitType::getName()  : SBQuantity::kilomole::UnitType::getSymbol() ; }
            else if (scale[5] == SBQuantity::hectomole::UnitType::scale6) {ret += fullName ? SBQuantity::hectomole::UnitType::getName() : SBQuantity::hectomole::UnitType::getSymbol(); }
            else if (scale[5] == SBQuantity::decamole::UnitType::scale6 ) {ret += fullName ? SBQuantity::decamole::UnitType::getName()  : SBQuantity::decamole::UnitType::getSymbol() ; }
            else if (scale[5] == SBQuantity::mole::UnitType::scale6     ) {ret += fullName ? SBQuantity::mole::UnitType::getName()      : SBQuantity::mole::UnitType::getSymbol()     ; }
            else if (scale[5] == SBQuantity::decimole::UnitType::scale6 ) {ret += fullName ? SBQuantity::decimole::UnitType::getName()  : SBQuantity::decimole::UnitType::getSymbol() ; }
            else if (scale[5] == SBQuantity::centimole::UnitType::scale6) {ret += fullName ? SBQuantity::centimole::UnitType::getName() : SBQuantity::centimole::UnitType::getSymbol(); }
            else if (scale[5] == SBQuantity::millimole::UnitType::scale6) {ret += fullName ? SBQuantity::millimole::UnitType::getName() : SBQuantity::millimole::UnitType::getSymbol(); }
            else if (scale[5] == SBQuantity::micromole::UnitType::scale6) {ret += fullName ? SBQuantity::micromole::UnitType::getName() : SBQuantity::micromole::UnitType::getSymbol(); }
            else if (scale[5] == SBQuantity::nanomole::UnitType::scale6 ) {ret += fullName ? SBQuantity::nanomole::UnitType::getName()  : SBQuantity::nanomole::UnitType::getSymbol() ; }
            else if (scale[5] == SBQuantity::picomole::UnitType::scale6 ) {ret += fullName ? SBQuantity::picomole::UnitType::getName()  : SBQuantity::picomole::UnitType::getSymbol() ; }
            else if (scale[5] == SBQuantity::femtomole::UnitType::scale6) {ret += fullName ? SBQuantity::femtomole::UnitType::getName() : SBQuantity::femtomole::UnitType::getSymbol(); }
            else if (scale[5] == SBQuantity::attomole::UnitType::scale6 ) {ret += fullName ? SBQuantity::attomole::UnitType::getName()  : SBQuantity::attomole::UnitType::getSymbol() ; }
            else if (scale[5] == SBQuantity::zeptomole::UnitType::scale6) {ret += fullName ? SBQuantity::zeptomole::UnitType::getName() : SBQuantity::zeptomole::UnitType::getSymbol(); }
            else if (scale[5] == SBQuantity::yoctomole::UnitType::scale6) {ret += fullName ? SBQuantity::yoctomole::UnitType::getName() : SBQuantity::yoctomole::UnitType::getSymbol(); }
            else {
                     ret += fullName ? SBQuantity::mole::UnitType::getName() : SBQuantity::mole::UnitType::getSymbol();
                     scaleForStr[5] = SBQuantity::mole::UnitType::scale6;
                 }

            // add power if necessary
            if (exponent[5] != 1) ret += "^" + std::to_string(exponent[5]);

        }
        // luminous intensity
		if (exponent[6] != 0) {

            if (ret != "") ret += ".";
            scaleForStr[6] = scale[6];
			if      (scale[6] == SBQuantity::kilocandela::UnitType::scale7 ) {ret += fullName ? SBQuantity::kilocandela::UnitType::getName()  : SBQuantity::kilocandela::UnitType::getSymbol() ; }
            else if (scale[6] == SBQuantity::hectocandela::UnitType::scale7) {ret += fullName ? SBQuantity::hectocandela::UnitType::getName() : SBQuantity::hectocandela::UnitType::getSymbol(); }
            else if (scale[6] == SBQuantity::decacandela::UnitType::scale7 ) {ret += fullName ? SBQuantity::decacandela::UnitType::getName()  : SBQuantity::decacandela::UnitType::getSymbol() ; }
            else if (scale[6] == SBQuantity::candela::UnitType::scale7     ) {ret += fullName ? SBQuantity::candela::UnitType::getName()      : SBQuantity::candela::UnitType::getSymbol()     ; }
            else if (scale[6] == SBQuantity::decicandela::UnitType::scale7 ) {ret += fullName ? SBQuantity::decicandela::UnitType::getName()  : SBQuantity::decicandela::UnitType::getSymbol() ; }
            else if (scale[6] == SBQuantity::centicandela::UnitType::scale7) {ret += fullName ? SBQuantity::centicandela::UnitType::getName() : SBQuantity::centicandela::UnitType::getSymbol(); }
            else if (scale[6] == SBQuantity::millicandela::UnitType::scale7) {ret += fullName ? SBQuantity::millicandela::UnitType::getName() : SBQuantity::millicandela::UnitType::getSymbol(); }
            else if (scale[6] == SBQuantity::microcandela::UnitType::scale7) {ret += fullName ? SBQuantity::microcandela::UnitType::getName() : SBQuantity::microcandela::UnitType::getSymbol(); }
            else if (scale[6] == SBQuantity::nanocandela::UnitType::scale7 ) {ret += fullName ? SBQuantity::nanocandela::UnitType::getName()  : SBQuantity::nanocandela::UnitType::getSymbol() ; }
            else if (scale[6] == SBQuantity::picocandela::UnitType::scale7 ) {ret += fullName ? SBQuantity::picocandela::UnitType::getName()  : SBQuantity::picocandela::UnitType::getSymbol() ; }
            else if (scale[6] == SBQuantity::femtocandela::UnitType::scale7) {ret += fullName ? SBQuantity::femtocandela::UnitType::getName() : SBQuantity::femtocandela::UnitType::getSymbol(); }
            else if (scale[6] == SBQuantity::attocandela::UnitType::scale7 ) {ret += fullName ? SBQuantity::attocandela::UnitType::getName()  : SBQuantity::attocandela::UnitType::getSymbol() ; }
            else if (scale[6] == SBQuantity::zeptocandela::UnitType::scale7) {ret += fullName ? SBQuantity::zeptocandela::UnitType::getName() : SBQuantity::zeptocandela::UnitType::getSymbol(); }
            else if (scale[6] == SBQuantity::yoctocandela::UnitType::scale7) {ret += fullName ? SBQuantity::yoctocandela::UnitType::getName() : SBQuantity::yoctocandela::UnitType::getSymbol(); }
            else {
                     ret += fullName ? SBQuantity::candela::UnitType::getName() : SBQuantity::candela::UnitType::getSymbol();
                     scaleForStr[6] = SBQuantity::candela::UnitType::scale7;
                 }

            // add power if necessary
            if (exponent[6] != 1) ret += "^" + std::to_string(exponent[6]);

        }

        double v = value * getScalingFactorToOtherUnit(scaleForStr);

        ret = std::to_string(v) + " " + ret;

		return ret;

    }

	std::string						toDebugStdString () const {

        std::string ret = std::to_string(value) + " ";
        for (int i = 0; i < System::size; ++i)
            ret += std::to_string(scale[i]) + ":" + std::to_string(exponent[i]) + " ";

        return ret;

    }

    //@}

private:

	double							value;          ///> value
	std::vector<int>				scale;          ///> scale
	std::vector<int>				exponent;       ///> exponent

	static const std::vector<int>	ref_scale;      ///> reference scale: base units for the current UnitSystem

	static const std::vector<int>	zeros;          ///> array for comparisons

};

template <typename System>
const std::vector<int>				SBDQuantityWrapper<System>::ref_scale = SBDQuantityWrapper<System>::getRefScale();

template <typename System>
const std::vector<int>				SBDQuantityWrapper<System>::zeros(System::size, 0);

/// \name Common types and shortnames
//@{

#define		SBQuantityWrapper		SBDQuantityWrapper

typedef     SBDQuantityWrapper<SBUnitSystemSI>                           SBDQuantityWrapperSI;
typedef     SBDQuantityWrapper<SBUnitSystemAU>                           SBDQuantityWrapperAU;
typedef     SBDQuantityWrapper<SBUnitSystemDalton>                       SBDQuantityWrapperDalton;
typedef     SBDQuantityWrapper<SBUnitSystemElectronvolt>                 SBDQuantityWrapperElectronvolt;
typedef     SBDQuantityWrapper<SBUnitSystemKilocaloriePerMole>           SBDQuantityWrapperKilocaloriePerMole;

typedef     SBDQuantityWrapperSI                                         SBQuantityWrapperSI;
typedef     SBDQuantityWrapperAU                                         SBQuantityWrapperAU;
typedef     SBDQuantityWrapperDalton                                     SBQuantityWrapperDalton;
typedef     SBDQuantityWrapperElectronvolt                               SBQuantityWrapperElectronvolt;
typedef     SBDQuantityWrapperKilocaloriePerMole                         SBQuantityWrapperKilocaloriePerMole;

//@}

/// \name External functions
//@{

/// \brief Returns the SBQuantity::Quantity from Unit \p u

template<typename Quantity, typename Units>
Quantity							getSBQuantity(const Units& a) {

	return a.template toSBQuantity<Quantity>();

}

/// \brief Returns the value of SBQuantity::Quantity for Unit \p u

template<typename Quantity, typename Units>
double								getSBQuantityValue (const Units &a) {

	return a.template toSBQuantityValue<Quantity>();

}

/// \brief Converts UnitsA to UnitsB: UnitsA -> SBQuantityA -> SBQuantityB -> UnitsB

template<typename UnitSystemA, typename UnitSystemB, typename QuantityA, typename QuantityB>
SBDQuantityWrapper<UnitSystemB>		convertUnitAToUnitB(const SBDQuantityWrapper<UnitSystemA>& q) {

	return SBDQuantityWrapper<UnitSystemB>( QuantityB( getSBQuantity<QuantityA, SBDQuantityWrapper<UnitSystemA>>(q) ) );

}

//@}

/// \name External operators
//@{

/// \brief Returns the product of double \p d with physical quantity \p q
template <typename System>
SBDQuantityWrapper<System>			operator*(const double d, const SBDQuantityWrapper<System>& q) {

	return SBDQuantityWrapper<System>(d * q.getValue(), q.getScale(), q.getExponent());

}

/// \brief Returns the sum of double \p d with physical quantity \p q (for dimensionless physical quantities only)
template <typename System>
SBDQuantityWrapper<System>			operator+(const double d, const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Adding a quantity to a double is only allowed for dimensionless quantities.");

	return SBDQuantityWrapper<System>(d + q.getValue(), q.getScale(), q.getExponent());

}

/// \brief Returns the difference between double \p d with physical quantity \p q (for dimensionless physical quantities only)
template <typename System>
SBDQuantityWrapper<System>			operator-(const double d, const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Subtracting a quantity from a double is only allowed for dimensionless quantities.");

	return SBDQuantityWrapper<System>(d - q.getValue(), q.getScale(), q.getExponent());

}

/// \brief Returns true when double \p d and physical quantity \p q are equal (for dimensionless physical quantities only)
template <typename System>
bool								operator==(const double d, const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

    return d == q.getValue();

}

/// \brief Returns true when double \p d and physical quantity \p q are different (for dimensionless physical quantities only)
template <typename System>
bool								operator!=(const double d, const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

    return d != q.getValue();

}

/// \brief Returns true when double \p d is smaller than physical quantity \p q (for dimensionless physical quantities only)
template <typename System>
bool								operator<(const double d, const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

    return d < q.getValue();

}

/// \brief Returns true when double \p d is larger than physical quantity \p q (for dimensionless physical quantities only)
template <typename System>
bool								operator>(const double d, const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

    return d > q.getValue();

}

/// \brief Returns true when double \p d is smaller than or equal to physical quantity \p q (for dimensionless physical quantities only)
template <typename System>
bool								operator<=(const double d, const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

    return d <= q.getValue();

}

/// \brief Returns true when double \p d is larger than or equal to physical quantity \p q (for dimensionless physical quantities only)
template <typename System>
bool								operator>=(const double d, const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Comparing a quantity with a double is only allowed for dimensionless quantities.");

    return d >= q.getValue();

}

/// \brief Returns the division of double \p d by physical quantity \p q
template <typename System>
SBDQuantityWrapper<System>			operator/(const double d, const SBDQuantityWrapper<System>& q) {

    std::vector<int> exponent = q.getExponent();
    for(size_t i = 0; i < exponent.size(); ++i)
        exponent[i] = -exponent[i];

	return SBDQuantityWrapper<System>(d / q.getValue(), q.getScale(), exponent);

}

/// \brief Inserts the physical quantity \p q in the output stream \p s

template <typename System>
std::ostream&						operator<<(std::ostream &s, const SBDQuantityWrapper<System>& q) {

    s << q.toStdString();
    return s;

}

//@}

/// \name Mathematical functions
//@{

/// \brief Returns the absolute value of physical quantity \p q

template <typename System>
SBDQuantityWrapper<System>			fabs(const SBDQuantityWrapper<System>& q) {

	return SBDQuantityWrapper<System>(fabs(q.getValue()), q.getScale(), q.getExponent());

}

/// \brief Returns the floor value of physical quantity \p q

template <typename System>
SBDQuantityWrapper<System>			floor(const SBDQuantityWrapper<System>& q) {

	return SBDQuantityWrapper<System>(floor(q.getValue()), q.getScale(), q.getExponent());

}

/// \brief Returns the ceil value of physical quantity \p q

template <typename System>
SBDQuantityWrapper<System>			ceil(const SBDQuantityWrapper<System>& q) {

	return SBDQuantityWrapper<System>(ceil(q.getValue()), q.getScale(), q.getExponent());

}

/// \brief Returns the round value of physical quantity \p q

template <typename System>
SBDQuantityWrapper<System>			round(const SBDQuantityWrapper<System>& q) {

	return SBDQuantityWrapper<System>(round(q.getValue()), q.getScale(), q.getExponent());

}

/// \brief Returns the trunc value of physical quantity \p q

template <typename System>
SBDQuantityWrapper<System>			trunc(const SBDQuantityWrapper<System>& q) {

	return SBDQuantityWrapper<System>(trunc(q.getValue()), q.getScale(), q.getExponent());

}

/// \brief Returns the \p p th power of physical quantity \p q

template <typename System>
SBDQuantityWrapper<System>			pow(const SBDQuantityWrapper<System>& q, int p) {

	if (p == 0) throw std::runtime_error("Error, the exponent cannot be zero");

    std::vector<int> e = q.getExponent();
	for (auto& ei: e) ei *= p;

	return SBDQuantityWrapper<System>(pow(q.getValue(), static_cast<double>(p)), q.getScale(), e);

}

/// \brief Returns the square root of physical quantity \p q

template <typename System>
SBDQuantityWrapper<System>			sqrt(const SBDQuantityWrapper<System>& q) {

    std::vector<int> e = q.getExponent();
    for (auto& ei: e)
		if (ei % 2 != 0) throw std::runtime_error("Error, cannot take the square root of a quantity with non-even unit exponents");

	for (auto& ei: e) ei /= 2;

	return SBDQuantityWrapper<System>(sqrt(q.getValue()), q.getScale(), e);

}

/// \brief Returns the \p p th root of physical quantity \p q

template <typename System>
SBDQuantityWrapper<System>			root(const SBDQuantityWrapper<System>& q, int p) {

	if (p == 0) throw std::runtime_error("Error, the root exponent cannot be zero");

    std::vector<int> e = q.getExponent();
    for (auto& ei: e)
		if (ei % p != 0) throw std::runtime_error("Error, cannot take the root of a quantity for which the unit exponents are not multiples of the root exponent");

	for (auto& ei: e) ei /= p;

	return SBDQuantityWrapper<System>(pow(q.getValue(), 1.0 / static_cast<double>(p)), q.getScale(), e);

}

/// \brief Returns the exponential of physical quantity \p q (for dimensionless physical quantities only)

//template<typename t = System, typename std::enable_if<std::is_same<t, SBUnitSystemSI>::value, int>::type = 0>
template <typename System>
SBDQuantityWrapper<System>			exp(const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Error, cannot apply the exponential function to non-dimensionless quantities");

	return SBDQuantityWrapper<System>(exp(q.getValue()));

}

/// \brief Returns the logarithm of physical quantity \p q (for dimensionless physical quantities only)

template <typename System>
SBDQuantityWrapper<System>			log(const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Error, cannot apply the log function to non-dimensionless quantities");

	return SBDQuantityWrapper<SBUnitSystemSI>(log(q.getValue()));

}

/// \brief Returns the sin of physical quantity \p q (for dimensionless physical quantities only)

template <typename System>
SBDQuantityWrapper<System>			sin(const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Error, cannot apply the sin function to non-dimensionless quantities");

	return SBDQuantityWrapper<SBUnitSystemSI>(sin(q.getValue()));

}

/// \brief Returns the asin of physical quantity \p q (for dimensionless physical quantities only)

template <typename System>
SBDQuantityWrapper<System>			asin(const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Error, cannot apply the asin function to non-dimensionless quantities");

	return SBDQuantityWrapper<SBUnitSystemSI>(asin(q.getValue()));

}

/// \brief Returns the cos of physical quantity \p q (for dimensionless physical quantities only)

template <typename System>
SBDQuantityWrapper<System>			cos(const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Error, cannot apply the cos function to non-dimensionless quantities");

	return SBDQuantityWrapper<SBUnitSystemSI>(cos(q.getValue()));

}

/// \brief Returns the acos of physical quantity \p q (for dimensionless physical quantities only)

template <typename System>
SBDQuantityWrapper<System>			acos(const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Error, cannot apply the acos function to non-dimensionless quantities");

	return SBDQuantityWrapper<SBUnitSystemSI>(acos(q.getValue()));

}

/// \brief Returns the tan of physical quantity \p q (for dimensionless physical quantities only)

template <typename System>
SBDQuantityWrapper<System>			tan(const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Error, cannot apply the tan function to non-dimensionless quantities");

	return SBDQuantityWrapper<SBUnitSystemSI>(tan(q.getValue()));

}

/// \brief Returns the atan of physical quantity \p q (for dimensionless physical quantities only)

template <typename System>
SBDQuantityWrapper<System>			atan(const SBDQuantityWrapper<System>& q) {

	if (!q.isDimensionless()) throw std::runtime_error("Error, cannot apply the atan function to non-dimensionless quantities");

	return SBDQuantityWrapper<SBUnitSystemSI>(atan(q.getValue()));

}

//@}

#endif
