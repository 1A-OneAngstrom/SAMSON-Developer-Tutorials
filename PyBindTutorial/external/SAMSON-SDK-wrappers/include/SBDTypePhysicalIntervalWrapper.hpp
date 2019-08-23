#pragma once

#include "SBDQuantityWrapper.hpp"

#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDTypePhysicalInterval.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

/*! \file SBDTypePhysicalIntervalWrapper.hpp */

/// \brief This class is used as a wrapper between SAMSON SDK SBDTypePhysicalInterval and Python.
///
/// \tparam Units - SBDQuantityWrapper<SBUnitSystem>

template <typename Units = SBDQuantityWrapperSI>
class SBDTypePhysicalIntervalWrapper {

public:

    /// \name Constructors
    //@{

    /// \brief The default constructor initializes all components to zero

	SBDTypePhysicalIntervalWrapper() : i {Units(0.0), Units(0.0)}   {}

    /// \brief Constructs a physical interval [\p x, \p x]

	explicit SBDTypePhysicalIntervalWrapper(const Units& x) : i {x, x}  {}

    /// \brief Constructs a physical interval [\p x, \p y]

	SBDTypePhysicalIntervalWrapper(const Units& x, const Units& y) : i {x, y.getUnitScaledTo(x)} {}

    /// \brief Constructs a physical interval [\p u[0], \p u[1]]

	SBDTypePhysicalIntervalWrapper(const std::vector<Units>& u) {

		if (u.size() != 2) throw std::runtime_error("The size of the input vector should be 2");

		i = {u[0], u[1].getUnitScaledTo(u[0])};

    }

    /// \brief Constructs an interval vector from SBDTypePhysicalInterval \p q

    template<typename Quantity, typename System = SBUnitSystemSI>
	SBDTypePhysicalIntervalWrapper(const SBDTypePhysicalInterval<Quantity>& q) {

		i = {SBDQuantityWrapper<System>(q.i[0]),
			 SBDQuantityWrapper<System>(q.i[1])};

	}

    //@}

    /// \name Accessors
    //@{

    /// \brief Returns a dimensionless physical interval whose bounds are equal to those of this physical interval

	std::vector<double>											getValue() const {

		std::vector<double> ret = {i[0].getValue(), i[1].getValue()};
		return ret;

    }

    /// \brief Sets the bounds of this physical interval equal to those of the dimensionless physical interval \p u

	void														setValue(const std::vector<double>& u) {

		if (u.size() != 2) throw std::runtime_error("The size of the input array should be 2");

        i[0].setValue(u[0]);
        i[1].setValue(u[1]);

    }

    /// \brief Returns the arbitraty SBPhysicalInterval

    template<typename Quantity, typename System = SBUnitSystemSI>
	SBPhysicalInterval<Quantity>								toSBPhysicalInterval () const {

        return SBPhysicalInterval<Quantity>( getSBQuantity<Quantity>(i[0]), getSBQuantity<Quantity>(i[1]) );

    }

    /// \brief Returns the i-th component of the vector

	Units														getComponent(const unsigned int j) const {

		if (j >= 2) throw std::runtime_error("Index is out of range");

        return i[j];

    }

	/// \brief Returns true if the interval is dimensionless

	bool														isDimensionless() const {

		return i[0].isDimensionless();

	}

    //@}

    /// \name Operators
    //@{

    /// \brief Returns the sum of this physical interval and the physical interval \p u.

	SBDTypePhysicalIntervalWrapper<Units>						operator+(const SBDTypePhysicalIntervalWrapper<Units>& u) const {

		return SBDTypePhysicalIntervalWrapper<Units>(i[0]+u.i[0],i[1]+u.i[1]);

    }

    /// \brief Returns the difference between this physical interval and the physical interval \p u.

	SBDTypePhysicalIntervalWrapper<Units>						operator-(const SBDTypePhysicalIntervalWrapper<Units>& u) const {

		return SBDTypePhysicalIntervalWrapper<Units>(i[0]-u.i[1],i[1]-u.i[0]);

    }

	/// \brief Returns the result of the product of this physical interval by the double \p d

	SBDTypePhysicalIntervalWrapper<Units>						operator*(const double d) const {

		if (d >= 0) return SBDTypePhysicalIntervalWrapper<Units>(i[0] * d, i[1] * d);
		return SBDTypePhysicalIntervalWrapper<Units>(i[1] * d, i[0] * d);

	}

	/// \brief Multiplies this physical interval with double \p d

	SBDTypePhysicalIntervalWrapper<Units>&						operator*=(const double d) {

		if (d >= 0) {

			i[0] *= d;
			i[1] *= d;

		}
		else {

			Units t(i[0]);
			i[0] = i[1] * d;
			i[1] = t * d;

		}

		return *this;

	}

	/// \brief Returns the product of this physical interval by the quantity \p d.
    ///
    /// This function returns the product of this physical interval by the quantity \p d. Note that the
    /// unit of the returned physical interval is the product of the physical interval's unit and the quantity's unit.

	SBDTypePhysicalIntervalWrapper<Units>						operator*(const Units& d) const {

		if (d.getValue() >= 0) return SBDTypePhysicalIntervalWrapper<Units>(d * i[0], d * i[1]);
		return SBDTypePhysicalIntervalWrapper<Units>(d * i[1], d * i[0]);

    }

	/// \brief Multiplies this physical interval with physical quantity \p d

	SBDTypePhysicalIntervalWrapper<Units>&						operator*=(const Units& d) {

		if (!isDimensionless() || !d.isDimensionless()) throw std::runtime_error("Error, this function can only be used for dimensionless quantities");

		if (d.getValue() >= 0) {

			i[0] *= d;
			i[1] *= d;

		}
		else {

			Units t(i[0]);
			i[0] = i[1] * d;
			i[1] = t * d;

		}

        return *this;

	}

	/// \brief Returns the product of this physical interval with the physical interval \p in

	SBDTypePhysicalIntervalWrapper<Units>						operator*(const SBDTypePhysicalIntervalWrapper<Units>& in) const {

		if (in.i[0].getValue() >= 0.0) {

			if (i[0].getValue() >= 0.0) return SBDTypePhysicalIntervalWrapper<Units>(i[0]*in.i[0], i[1]*in.i[1]);
			if (i[1].getValue() <= 0.0) return SBDTypePhysicalIntervalWrapper<Units>(i[0]*in.i[1], i[1]*in.i[0]);
			return SBDTypePhysicalIntervalWrapper<Units>(i[0]*in.i[1], i[1]*in.i[1]);

		}

		if (in.i[1].getValue() <= 0.0) {

			if (i[0].getValue() >= 0.0) return SBDTypePhysicalIntervalWrapper<Units>(i[1]*in.i[0], i[0]*in.i[1]);
			if (i[1].getValue() <= 0.0) return SBDTypePhysicalIntervalWrapper<Units>(i[1]*in.i[1], i[0]*in.i[0]);
			return SBDTypePhysicalIntervalWrapper<Units>(i[1]*in.i[0], i[0]*in.i[0]);

		}

		if (i[0].getValue() >= 0.0) return SBDTypePhysicalIntervalWrapper<Units>(i[1]*in.i[0], i[1]*in.i[1]);
		if (i[1].getValue() <= 0.0) return SBDTypePhysicalIntervalWrapper<Units>(i[0]*in.i[1], i[0]*in.i[0]);

		Units v00 = i[0] * in.i[0];
		Units v11 = i[1] * in.i[1];

		if (v00.getValue() <= v11.getValue()) {

			Units v01 = i[0] * in.i[1];
			Units v10 = i[1] * in.i[0];
			if (v01.getValue() < v10.getValue()) return SBDTypePhysicalIntervalWrapper<Units>(v01, v11);
			return SBDTypePhysicalIntervalWrapper<Units>(v10, v11);

		}

		Units v01 = i[0] * in.i[1];
		Units v10 = i[1] * in.i[0];

		if (v01.getValue() < v10.getValue()) return SBDTypePhysicalIntervalWrapper<Units>(v01, v00);
		return SBDTypePhysicalIntervalWrapper<Units>(v10, v00);

	}

	/// \brief Multiplies this physical interval with the physical interval \p in

	SBDTypePhysicalIntervalWrapper<Units>&						operator*=(const SBDTypePhysicalIntervalWrapper<Units>& in) {

		if (!isDimensionless() || !in.isDimensionless()) throw std::runtime_error("Error, this function can only be used for dimensionless quantities");

		(*this) = (*this) * (in);
		return *this;

	}

    /// \brief Returns the result of the division of this physical interval by the double \p d

	SBDTypePhysicalIntervalWrapper<Units>						operator/(const double d) const {

		if (d > 0) return SBDTypePhysicalIntervalWrapper<Units>(i[0] / d, i[1] / d);
		return SBDTypePhysicalIntervalWrapper<Units>(i[1] / d, i[0] / d);

    }

    /// \brief Divides this physical interval by double \p d

	SBDTypePhysicalIntervalWrapper<Units>&						operator/=(const double d) {

		if (d > 0) {

			i[0] /= d;
			i[1] /= d;

		}
		else {

			Units t(i[0]);
			i[0] = i[1] * d;
			i[1] = t * d;

		}

        return *this;

	}

    /// \brief Returns the division of this physical interval by physical quantity \p u

	SBDTypePhysicalIntervalWrapper<Units>						operator/(const Units& u) const {

		if (u.getValue() >= 0) return SBDTypePhysicalIntervalWrapper<Units>(i[0] / u, i[1] / u);
		return SBDTypePhysicalIntervalWrapper<Units>(i[1] / u, i[0] / u);


	}

    /// \brief Divides this physical interval by physical quantity \p u

	SBDTypePhysicalIntervalWrapper<Units>&						operator/=(const Units& u) {

		if (!isDimensionless() || !u.isDimensionless()) throw std::runtime_error("Error, this function can only be used for dimensionless quantities");

		if (u.getValue() >= 0) {

			i[0] /= u;
			i[1] /= u;

		}
		else {

			Units t(i[0]);
			i[0] = i[1] / u;
			i[1] = t / u;

		}

        return *this;

	}

	/// \brief Returns the result of the division of this physical interval by the physical interval \p in

	SBDTypePhysicalIntervalWrapper<Units>						operator/(const SBDTypePhysicalIntervalWrapper<Units>& in) const {

		return (*this) * SBDTypePhysicalIntervalWrapper<Units>(1.0 / in.i[1], 1.0 / in.i[0]);

	}

	/// \brief Divides this physical interval by the physical interval \p in

	SBDTypePhysicalIntervalWrapper<Units>&						operator/=(const SBDTypePhysicalIntervalWrapper<Units>& in) {

		if (!isDimensionless() || !in.isDimensionless()) throw std::runtime_error("Error, this function can only be used for dimensionless quantities");

		(*this) = (*this) / (in);
		return *this;

	}

    /// \brief Returns the opposite of this physical interval

	SBDTypePhysicalIntervalWrapper<Units>						operator-() const {

		return SBDTypePhysicalIntervalWrapper<Units>(-i[1], -i[0]);

    }

    /// \brief Adds the physical interval \p u to this physical interval

	SBDTypePhysicalIntervalWrapper<Units>&						operator+=(const SBDTypePhysicalIntervalWrapper<Units>& u) {

		i[0] += u.i[0];
		i[1] += u.i[1];
        return *this;

    }

    /// \brief Subtracts the physical interval \p u from this physical interval

	SBDTypePhysicalIntervalWrapper<Units>&						operator-=(const SBDTypePhysicalIntervalWrapper<Units>& u) {

		i[0] -= u.i[1];
		i[1] -= u.i[0];
        return *this;

    }

    /// \brief Intersects this physical interval with the physical interval \p u
    ///
    /// \param u A physical interval
    /// \returns True when the intersection with \p u is empty
    ///
    /// This operator returns true when the intersection between this physical interval and the physical interval \p u is empty. When it is not,
    /// this interval is replaced by the intersection.

	bool														operator^(const SBDTypePhysicalIntervalWrapper<Units>& u) {

		if (i[1] < u.i[0]) return true;
		if (i[0] > u.i[1]) return true;
		if (i[1] > u.i[1]) i[1] = u.i[1];
		if (i[0] < u.i[0]) i[0] = u.i[0];
        return false;

	}

    /// \brief Returns true when this physical interval is equal to physical interval \p u

	bool														operator==(const SBDTypePhysicalIntervalWrapper<Units>& u) const {

		return (i[0] == u.i[0]) && (i[1] == u.i[1]);

    }

    /// \brief Returns true when this physical interval is different from physical interval \p u

	bool														operator!=(const SBDTypePhysicalIntervalWrapper<Units>& u) const {

		return (i[0] != u.i[0]) || (i[1] != u.i[1]);

    }

    /// \brief Returns a reference to component \p index of this physical interval

	Units&														operator[](const int index) { return i[index]; }

    /// \brief Returns a reference to component \p index of this physical interval (const version)

	const Units&												operator[](const int index) const { return i[index]; }

    //@}

    /// \name Useful functions
    //@{

    /// \brief Determines whether the intersection between this physical interval and the physical interval [\p l, \p r] is empty,

	bool														isEmpty(const Units& l, const Units& r) {

		if (i[1] < l) return true;
		if (i[0] > r) return true;
        return false;

    }

    /// \brief Returns the lower bound of the absolute value of this physical interval

	Units														getAbsLower() const {

		if (i[0].getValue() >= 0.0) return i[0];
		if (i[1].getValue() >= 0.0) return Units(0.0, i[1].getScale(), i[1].getExponent());
        return -i[1];

    }

    /// \brief Returns the upper bound of the absolute value of this physical interval

	Units														getAbsUpper() const {

		if (i[0].getValue() + i[1].getValue() >= 0.0) return i[1];
        return -i[0];

    }

    /// \brief Returns true when this physical interval contains \p v

	bool														contains(const Units& v) {

		if (v < i[0]) return false;
		if (v > i[1]) return false;
        return true;

    }

    /// \brief Enlarges this physical interval to contain \p v

	void														bound(const Units& v) {

		if (v < i[0]) i[0] = v;
		if (v > i[1]) i[1] = v;

    }

    /// \brief Enlarges this physical interval to contain the physical interval \p j

	void														bound(const SBDTypePhysicalIntervalWrapper<Units>& j) {

		if (j.i[0] < i[0]) i[0] = j.i[0];
		if (j.i[1] > i[1]) i[1] = j.i[1];

    }

    /// \brief Expands this physical interval by offset \p r
    ///
    /// \param r The offset size
    ///
    /// This function expands this physical interval by offset \p r: [\p a, \p b] becomes [\p a-r, \p b+r].

	void														expand(const Units& r) {

		i[0] -= r;
		i[1] += r;

    }

    /// \brief Shrinks this physical interval by offset \p r
    ///
    /// \param r The offset size
    ///
    /// This function shrinks this physical interval by offset \p r: [\p a, \p b] becomes [\p a+r, \p b-r]. When the offset \p r is larger than the half-size of the physical interval,
    /// the interval becomes [\p m, \p m], where \p m is the center of the interval.

    void														shrink(const Units& r) {

		Units c = center();

		i[0] += r;
		if (i[0] > c)
			i[0] = i[1] = c;
        else
			i[1] -= r;

    }

    /// \brief Returns the center 0.5*(i[0]+i[1]) of the physical interval

    Units                                                       center() const {

		return 0.5 * (i[0] + i[1]);

    }

    /// \brief Returns the diameter i[1]-i[0] of the physical interval

    Units                                                       diameter() const {

		return i[1] - i[0];

    }

    /// \brief Sets the physical interval to [0,0]

    void														setZero() { i[0].setValue(0.0); i[1].setValue(0.0); }

    //@}

    /// \name String representation
    //@{

    /// \brief Returns the string representation of the physical interval (with a full unit name when fullName is true)

	std::string													toStdString(bool fullName = false) const {

        std::string ret = "[" + i[0].toStdString(fullName) + ", " +
                                i[1].toStdString(fullName) + "]";

        return ret;

    }

	//@}

public:

	std::vector<Units>											i;                  ///< The components of the interval

};

/// \name Common types and shortnames
//@{

#define		SBPhysicalIntervalWrapper							SBDTypePhysicalIntervalWrapper

typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperSI>                   SBDTypePhysicalIntervalWrapperSI;
typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperAU>                   SBDTypePhysicalIntervalWrapperAU;
typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperDalton>               SBDTypePhysicalIntervalWrapperDalton;
typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperElectronvolt>         SBDTypePhysicalIntervalWrapperElectronvolt;
typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperKilocaloriePerMole>   SBDTypePhysicalIntervalWrapperKilocaloriePerMole;

typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperSI>                   SBPhysicalIntervalWrapperSI;
typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperAU>                   SBPhysicalIntervalWrapperAU;
typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperDalton>               SBPhysicalIntervalWrapperDalton;
typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperElectronvolt>         SBPhysicalIntervalWrapperElectronvolt;
typedef     SBDTypePhysicalIntervalWrapper<SBDQuantityWrapperKilocaloriePerMole>   SBPhysicalIntervalWrapperKilocaloriePerMole;

//@}

/// \name External functions
//@{

/// \brief Returns the SBPhysicalInterval<Quantity> from Unit \p u

template<typename Quantity, typename T>
SBPhysicalInterval<Quantity>				getSBPhysicalInterval(const T& a) {

	return a.template toSBPhysicalInterval<Quantity>();

}

//@}

/// \name External operators
//@{

/// \brief Returns the product of double \p d and physical interval \p u

template<typename Units>
SBDTypePhysicalIntervalWrapper<Units>       operator*(const double d, const SBDTypePhysicalIntervalWrapper<Units>& u) {

	if (d >= 0) return SBDTypePhysicalIntervalWrapper<Units>(d * u.i[0], d * u.i[1]);
	return SBDTypePhysicalIntervalWrapper<Units>(d * u.i[1], d * u.i[0]);

}

/// \brief Returns the product of physical quantity \p d and physical interval \p u

template<typename Units>
SBDTypePhysicalIntervalWrapper<Units>       operator*(const Units d, const SBDTypePhysicalIntervalWrapper<Units>& u) {

	if (d.getValue() >= 0) return SBDTypePhysicalIntervalWrapper<Units>(d * u.i[0], d * u.i[1]);
	return SBDTypePhysicalIntervalWrapper<Units>(d * u.i[1], d * u.i[0]);

}

/// \brief Inserts the physical interval \p u in the output stream \p s

template <typename Units>
std::ostream&								operator<<(std::ostream &s, const SBDTypePhysicalIntervalWrapper<Units>& u) {

    s << "[" << u.i[0] << ", " << u.i[1] << "]";
    return s;

}

//@}

#endif // UNITSFORPYTHON
