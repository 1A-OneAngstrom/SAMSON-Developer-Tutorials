#pragma once

#include "SBDQuantityWrapper.hpp"
#include "SBDTypePhysicalIntervalWrapper.hpp"
#include "SBDTypePhysicalVector3Wrapper.hpp"

#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDTypePhysicalIAVector3.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

#define SB_SIGN_BIT(A) ( (A)<0 ? true : false )

/*! \file SBDTypePhysicalIAVector3Wrapper.hpp */

/// \brief This class is used as a wrapper between SAMSON SDK SBDTypePhysicalIAVector3 and Python.
///
/// \tparam Units - SBDQuantityWrapper<SBUnitSystem>

template <typename Units = SBDQuantityWrapperSI>
class SBDTypePhysicalIAVector3Wrapper {

public:

    /// The overlap type

    enum OverlapType {

		IncludeNone												= 0,
		IncludeAll												= 1,
		Subdivide												= 2

    };

    /// \name Constructors
    //@{

    /// \brief Constructs a physical interval vector with all components set to [0,0]

	SBDTypePhysicalIAVector3Wrapper() : i {SBDTypePhysicalIntervalWrapper<Units>(), SBDTypePhysicalIntervalWrapper<Units>(), SBDTypePhysicalIntervalWrapper<Units>()} { }

    /// \brief Constructs a physical interval vector with all components set to [\p x, \p x]

	explicit SBDTypePhysicalIAVector3Wrapper(const Units& x) : i {SBDTypePhysicalIntervalWrapper<Units>(x), SBDTypePhysicalIntervalWrapper<Units>(x), SBDTypePhysicalIntervalWrapper<Units>(x)} { }

    /// \brief Constructs the physical interval vector [ [\p x, \p x] [\p y, \p y] [\p z, \p z] ]

	SBDTypePhysicalIAVector3Wrapper(const Units& x, const Units& y, const Units& z) : i {SBDTypePhysicalIntervalWrapper<Units>(x), SBDTypePhysicalIntervalWrapper<Units>(y.getUnitScaledTo(x)), SBDTypePhysicalIntervalWrapper<Units>(z.getUnitScaledTo(x))} { }

    /// \brief Constructs the physical interval vector [ [\p v[0][0], \p v[0][1]] [\p v[1][0], \p v[1][1]] [\p v[2][0], \p v[2][1]] ]

	SBDTypePhysicalIAVector3Wrapper(const std::vector<std::vector<Units>>& v) {

		if (v.size() != 3) throw std::runtime_error("The size of the input vector should be 3x2");

        for (auto u: v) {

			if (u.size() != 2) throw std::runtime_error("The size of the input vector should be 3x2");

			i.push_back(SBDTypePhysicalIntervalWrapper<Units> ( u[0], u[1].getUnitScaledTo(v[0][0]) )); // scale units to the first one - checks that all units are of the same type

        }

    }

    /// \brief Constructs the physical interval vector [ [\p xl, \p xu] [\p yl, \p yu] [\p zl, \p zu] ]

	SBDTypePhysicalIAVector3Wrapper(const Units&  xl, const Units&  xu, const Units&  yl, const Units&  yu, const Units&  zl, const Units&  zu) {

        // scale units to the first one - checks that all units are of the same type
		i = { SBDTypePhysicalIntervalWrapper<Units> ( xl,                     xu ),
			  SBDTypePhysicalIntervalWrapper<Units> ( yl.getUnitScaledTo(xl), yu ),
			  SBDTypePhysicalIntervalWrapper<Units> ( zl.getUnitScaledTo(xl), zu ) };

    }

    /// \brief Constructs the physical interval vector [ \p x \p x \p x ]

	SBDTypePhysicalIAVector3Wrapper(const SBDTypePhysicalIntervalWrapper<Units>& x) : i {x,x,x} { }

    /// \brief Constructs the physical interval vector [ \p v[0] \p v[1] \p v[2] ]

	SBDTypePhysicalIAVector3Wrapper(const std::vector<SBDTypePhysicalIntervalWrapper<Units>>& v) {

		if (v.size() != 3) throw std::runtime_error("The size of the input vector should be 3");

        i = { v[0],
			  SBDTypePhysicalIntervalWrapper<Units> (v[1].i[0].getUnitScaledTo(v[0].i[0]), v[1].i[1]),
			  SBDTypePhysicalIntervalWrapper<Units> (v[2].i[0].getUnitScaledTo(v[0].i[0]), v[2].i[1])};

    }

    /// \brief Constructs the physical interval vector [ \p x \p y \p z ]

	SBDTypePhysicalIAVector3Wrapper(const SBDTypePhysicalIntervalWrapper<Units>& x, const SBDTypePhysicalIntervalWrapper<Units>& y, const SBDTypePhysicalIntervalWrapper<Units>& z) {

        i = { x,
			  SBDTypePhysicalIntervalWrapper<Units> (y.i[0].getUnitScaledTo(x.i[0]), y.i[1]),
			  SBDTypePhysicalIntervalWrapper<Units> (z.i[0].getUnitScaledTo(x.i[0]), z.i[1])};

    }

    /// \brief Constructs the physical interval vector [ [\p u.v[0], \p u.v[0]] [\p u.v[1], \p u.v[1]] [\p u.v[2], \p u.v[2]] ]

	SBDTypePhysicalIAVector3Wrapper(SBDTypePhysicalVector3Wrapper<Units> const& u) {

		i = { SBDTypePhysicalIntervalWrapper<Units>(u.v[0]),
			  SBDTypePhysicalIntervalWrapper<Units>(u.v[1]),
			  SBDTypePhysicalIntervalWrapper<Units>(u.v[2]) };

    }

    /// \brief Constructs a dimensionless physical interval vector with all components set to [\p x, \p x]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	explicit SBDTypePhysicalIAVector3Wrapper(const double& x) {

		i = { SBDTypePhysicalIntervalWrapper<Units>( Units(x) ),
			  SBDTypePhysicalIntervalWrapper<Units>( Units(x) ),
			  SBDTypePhysicalIntervalWrapper<Units>( Units(x) ) };

    }

    /// \brief Constructs the dimensionless physical interval vector [ [\p x, \p x] [\p y, \p y] [\p z, \p z] ]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalIAVector3Wrapper(const double& x, const double& y, const double& z) {

		i = { SBDTypePhysicalIntervalWrapper<Units>( Units(x) ),
			  SBDTypePhysicalIntervalWrapper<Units>( Units(y) ),
			  SBDTypePhysicalIntervalWrapper<Units>( Units(z) ) };

    }

    /// \brief Constructs the dimensionless physical interval vector [ [\p v[0][0], \p v[0][1]] [\p v[1][0], \p v[1][1]] [\p v[2][0], \p v[2][1]] ]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalIAVector3Wrapper(const std::vector<std::vector<double>>& v) {

		if (v.size() != 3) throw std::runtime_error("The size of the input vector should be 3x2");

        for (auto u: v) {

			if (u.size() != 2) throw std::runtime_error("The size of the input vector should be 3x2");

			i.push_back(SBDTypePhysicalIntervalWrapper<Units> ( Units(u[0]), Units(u[1]) ));

        }

    }

    /// \brief Constructs the physical interval vector [ [\p xl, \p xu] [\p yl, \p yu] [\p zl, \p zu] ]

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalIAVector3Wrapper(const double& xl, const double& xu, const double& yl, const double& yu, const double& zl, const double& zu) {

		i = { SBDTypePhysicalIntervalWrapper<Units> ( Units(xl), Units(xu) ),
			  SBDTypePhysicalIntervalWrapper<Units> ( Units(yl), Units(yu) ),
			  SBDTypePhysicalIntervalWrapper<Units> ( Units(zl), Units(zu) ) };

    }

    /// \brief Constructs an physical interval vector from SBDTypePhysicalIAVector3 \p q

    template<typename Quantity, typename System = SBUnitSystemSI>
	SBDTypePhysicalIAVector3Wrapper(const SBDTypePhysicalIAVector3<Quantity>& q) {

		i = { SBDTypePhysicalIntervalWrapper<Units> ( q.i[0] ),
			  SBDTypePhysicalIntervalWrapper<Units> ( q.i[1] ),
			  SBDTypePhysicalIntervalWrapper<Units> ( q.i[2] ) };

    }

    //@}

    /// \name Accessors
    //@{

    /// \brief Returns a dimensionless physical interval vector whose bounds are equal to those of this physical interval vector

    std::vector<std::vector<double>>                                    getValue() const {

		std::vector<std::vector<double>> ret = {i[0].getValue(), i[1].getValue(), i[2].getValue()};
		return ret;

    }

    /// \brief Sets the bounds of this physical interval vector equal to those of the dimensionless physical interval vector \p v

    void                                                                setValue(const std::vector<std::vector<double>>& v) {

		if (v.size() != 3) throw std::runtime_error("The size of the input array should be 3x2");

        for (int j = 0; j < v.size(); j++) {

			if (v[j].size() != 2) throw std::runtime_error("The size of the input array should be 3x2");

            i[j].setValue(v[j]);

        }

    }

    /// \brief Returns the arbitraty SBPhysicalIAVector3

    template<typename Quantity, typename System = SBUnitSystemSI>
    SBPhysicalIAVector3<Quantity> toSBPhysicalIAVector3 () const {

        return SBPhysicalIAVector3<Quantity>(   getSBQuantity<Quantity>(i[0][0]), getSBQuantity<Quantity>(i[0][1]),
                                                getSBQuantity<Quantity>(i[1][0]), getSBQuantity<Quantity>(i[1][1]),
                                                getSBQuantity<Quantity>(i[2][0]), getSBQuantity<Quantity>(i[2][1]) );

    }

    /// \brief Returns the i-th component of the vector

	SBDTypePhysicalIntervalWrapper<Units>                      getComponent(const unsigned int& j) const {

		if (j >= i.size()) throw std::runtime_error("Index is out of range");

        return i[j];

    }

    /// \brief Returns the k-th component of the i-th interval

    Units                                                               getComponent(const unsigned int& j, const unsigned int& k) const {

		if (j >= i.size() || k >= 2) throw std::runtime_error("Index is out of range");

        return i[j][k];

    }

    //@}


    /// \name Operators
    //@{

    /// \brief Returns the dot product of this physical interval vector with physical interval vector \p u

	SBPhysicalIntervalWrapper<Units>                   operator|(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

        return i[0]*u.i[0]+i[1]*u.i[1]+i[2]*u.i[2];

    }

    /// \brief Returns the cross product of this physical interval vector with physical interval vector \p u

	SBDTypePhysicalIAVector3Wrapper<Units>             operator^(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(i[1]*u.i[2]-i[2]*u.i[1],i[2]*u.i[0]-i[0]*u.i[2],i[0]*u.i[1]-i[1]*u.i[0]);

    }

    /// \brief Returns the sum of this physical interval vector with physical interval vector \p u

	SBDTypePhysicalIAVector3Wrapper<Units>             operator+(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(i[0]+u.i[0],i[1]+u.i[1],i[2]+u.i[2]);

    }

    /// \brief Returns the difference of this physical interval vector with physical interval vector \p u

	SBDTypePhysicalIAVector3Wrapper<Units>             operator-(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(i[0]-u.i[0],i[1]-u.i[1],i[2]-u.i[2]);

    }

    /// \brief Returns the product of this physical interval vector with physical quantity \p d

	SBDTypePhysicalIAVector3Wrapper<Units>             operator*(Units d) const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(d*i[0],d*i[1],d*i[2]);

    }

    /// \brief Multiplies this physical interval vector with physical quantity \p d

	SBDTypePhysicalIAVector3Wrapper<Units>&            operator*=(Units d) {

		i[0] *= d;
		i[1] *= d;
		i[2] *= d;
        return *this;

    }

    /// \brief Returns the product of this physical interval vector with double \p d

	SBDTypePhysicalIAVector3Wrapper<Units>             operator*(const double d) const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(i[0]*d,i[1]*d,i[2]*d);

    }

    /// \brief Multiplies this physical interval vector with double \p d

	SBDTypePhysicalIAVector3Wrapper<Units>&            operator*=(const double d) {

		i[0] *= d;
		i[1] *= d;
		i[2] *= d;
        return *this;

    }

    /// \brief Returns the component-wise product of this physical interval vector with physical interval vector \p u
    ///
    /// This operator returns the component-wise product of this physical interval vector with physical interval vector \p u, <em>i.e.</em>
    /// a physical interval vector in which each component is the product of the corresponding components in this physical interval vector and physical interval vector \p u.

	SBDTypePhysicalIAVector3Wrapper<Units>             operator*(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(i[0]*u.i[0],i[1]*u.i[1],i[2]*u.i[2]);

    }

    /// \brief Returns the division of this physical interval vector by physical quantity \p d

	SBDTypePhysicalIAVector3Wrapper<Units>             operator/(const Units d) const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(i[0]/d,i[1]/d,i[2]/d);

    }

    /// \brief Divides this physical interval vector by physical quantity \p d

	SBDTypePhysicalIAVector3Wrapper<Units>&            operator/=(const Units d) {

		i[0] /= d;
		i[1] /= d;
		i[2] /= d;
        return *this;

    }

    /// \brief Returns the division of this physical interval vector by double \p d

	SBDTypePhysicalIAVector3Wrapper<Units>             operator/(const double d) const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(i[0]/d,i[1]/d,i[2]/d);

    }

    /// \brief Divides this physical interval vector by double \p d

	SBDTypePhysicalIAVector3Wrapper<Units>&            operator/=(const double d) {

		i[0] /= d;
		i[1] /= d;
		i[2] /= d;
        return *this;

    }

    /// \brief Returns the opposite of this physical interval vector

	SBDTypePhysicalIAVector3Wrapper<Units>             operator-() const {

		return SBDTypePhysicalIAVector3Wrapper<Units>(-i[0],-i[1],-i[2]);

    }

    /// \brief Adds physical interval vector \p u to this physical interval vector

	SBDTypePhysicalIAVector3Wrapper<Units>&            operator+=(const SBDTypePhysicalIAVector3Wrapper<Units>& u) {

		i[0] += u.i[0];
		i[1] += u.i[1];
		i[2] += u.i[2];
        return *this;

    }

    /// \brief Subtracts physical interval vector \p u from this physical interval vector

	SBDTypePhysicalIAVector3Wrapper<Units>&            operator-=(const SBDTypePhysicalIAVector3Wrapper<Units>& u) {

		i[0] -= u.i[0];
		i[1] -= u.i[1];
		i[2] -= u.i[2];
        return *this;

    }

    /// \brief Returns true if this physical interval vector is equal to physical interval vector \p u (component-wise)

	bool                                                        operator==(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		return (i[0] == u.i[0]) && (i[1] == u.i[1]) && (i[2] == u.i[2]);

    }

    /// \brief Returns true if this physical interval vector is different from physical interval vector \p u (component-wise)

	bool                                                        operator!=(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		return (i[0] != u.i[0]) || (i[1] != u.i[1]) || (i[2] != u.i[2]);

    }

    /// \brief Returns a reference to component \p index

	SBDTypePhysicalIntervalWrapper<Units>&             operator[](const int index) { return i[index]; }

    /// \brief Returns a reference to component \p index (const version)

	const SBDTypePhysicalIntervalWrapper<Units>&       operator[](const int index) const { return i[index]; }

    //@}


    /// \name Useful functions
    //@{

    /// \brief Sets all components to [0,0]

    void														setZero() {

        i[0].setZero();
        i[1].setZero();
        i[2].setZero();

    }

    /// \brief Returns the center [ 0.5*(i[0].i[0]+i[0].i[1]) 0.5*(i[1].i[0]+i[1].i[1]) 0.5*(i[2].i[0]+i[2].i[1]) ] of the physical interval vector

	SBDTypePhysicalVector3Wrapper<Units>                       center() const {

		return SBDTypePhysicalVector3Wrapper<Units>(i[0].center(),i[1].center(),i[2].center());

    }

    /// \brief Returns the diameter [ 0.5*(i[0].i[1]-i[0].i[0]) 0.5*(i[1].i[1]-i[1].i[0]) 0.5*(i[2].i[1]-i[2].i[0]) ] of the physical interval vector

	SBDTypePhysicalVector3Wrapper<Units>                       diameter() const {

		return SBDTypePhysicalVector3Wrapper<Units>(i[0].diameter(),i[1].diameter(),i[2].diameter());

    }

    /// \brief Returns the volume (i[0].i[1]-i[0].i[0])*(i[1].i[1]-i[1].i[0])*(i[2].i[1]-i[2].i[0]) of the physical interval vector

    Units                                                               volume() const {

		return i[0].diameter() * i[1].diameter() * i[2].diameter();

    }

    /// \brief Returns the area 2.0*((i[0].i[1]-i[0].i[0])*(i[0].i[1]-i[0].i[0])+(i[1].i[1]-i[1].i[0])*(i[1].i[1]-i[1].i[0])+(i[2].i[1]-i[2].i[0])*(i[2].i[1]-i[2].i[0])) of the physical interval vector

    Units                                                               area() const {

		return 2.0*((i[0].i[1]-i[0].i[0])*(i[0].i[1]-i[0].i[0]) + (i[1].i[1]-i[1].i[0])*(i[1].i[1]-i[1].i[0]) + (i[2].i[1]-i[2].i[0])*(i[2].i[1]-i[2].i[0]));

    }

    /// \brief Returns the sum i[0].diameter()+i[1].diameter()+i[2].diameter() of the components diameters of the physical interval vector

    Units                                                               lengthsSum() const {

		return i[0].diameter() + i[1].diameter() + i[2].diameter();

    }

    /// \brief Returns the lower bound [ i[0].i[0] i[1].i[0] i[2].i[0] ] of the physical interval vector

	SBDTypePhysicalVector3Wrapper<Units>                       lowerBound() const {

		return SBDTypePhysicalVector3Wrapper<Units>(i[0].i[0], i[1].i[0], i[2].i[0]);

    }

    /// \brief Returns the upper bound [ i[0].i[1] i[1].i[1] i[2].i[1] ] of the physical interval vector

	SBDTypePhysicalVector3Wrapper<Units>                       upperBound() const {

		return SBDTypePhysicalVector3Wrapper<Units>(i[0].i[1], i[1].i[1], i[2].i[1]);

    }

    /// \brief Sets the upper bounds of the intervals equal to the lower bounds

    void                                                                collapseToUpperBound() {

        i[0].i[1] = i[0].i[0];
        i[1].i[1] = i[1].i[0];
        i[2].i[1] = i[2].i[0];

    }

    /// \brief Sets the lower bounds of the intervals equal to the upper bounds

    void                                                                collapseToLowerBound() {

        i[0].i[0] = i[0].i[1];
        i[1].i[0] = i[1].i[1];
        i[2].i[0] = i[2].i[1];

    }

    /// \brief Returns true when this physical interval vector overlaps physical interval vector \p u

	bool														overlaps(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		if (u.i[0].i[1] < i[0].i[0]) return false;
		if (u.i[0].i[0] > i[0].i[1]) return false;
		if (u.i[1].i[1] < i[1].i[0]) return false;
		if (u.i[1].i[0] > i[1].i[1]) return false;
		if (u.i[2].i[1] < i[2].i[0]) return false;
		if (u.i[2].i[0] > i[2].i[1]) return false;

        return true;

    }

    /// \brief Returns true when the Manhattan distance between this physical interval vector and physical interval vector \p u is smaller than \p cutoffDistance

	bool 														overlaps(const SBDTypePhysicalIAVector3Wrapper<Units>& u, const Units& cutoffDistance) const {

		if (u.i[0].i[1] + cutoffDistance < i[0].i[0]) return false;
		if (u.i[0].i[0] > i[0].i[1] + cutoffDistance) return false;
		if (u.i[1].i[1] + cutoffDistance < i[1].i[0]) return false;
		if (u.i[1].i[0] > i[1].i[1] + cutoffDistance) return false;
		if (u.i[2].i[1] + cutoffDistance < i[2].i[0]) return false;
		if (u.i[2].i[0] > i[2].i[1] + cutoffDistance) return false;

        return true;

    }
/*
    /// \brief Returns true when this physical interval vector overlaps physical interval vector \p u transformed by \p t

	bool 														overlaps(const SBDTypePhysicalIAVector3Wrapper<Units>& u, const SBDTypeSymmetryTransform& t) const {

        if (t.orthorhombic) {

            int sign=2*t.upper[0]-1;

            if (u.i[t.index[0]].i[t.upper[0]]*sign + t.position->v[0]<i[0].i[0]) return false;
            if (u.i[t.index[0]].i[t.lower[0]]*sign + t.position->v[0]>i[0].i[1]) return false;

            sign=2*t.upper[1]-1;
            if (u.i[t.index[1]].i[t.upper[1]]*sign + t.position->v[1]<i[1].i[0]) return false;
            if (u.i[t.index[1]].i[t.lower[1]]*sign + t.position->v[1]>i[1].i[1]) return false;

            sign=2*t.upper[2]-1;
            if (u.i[t.index[2]].i[t.upper[2]]*sign + t.position->v[2]<i[2].i[0]) return false;
            if (u.i[t.index[2]].i[t.lower[2]]*sign + t.position->v[2]>i[2].i[1]) return false;

            return true;

        }
        else {

			SBDTypePhysicalIAVector3Wrapper<Units> transformedu=((*t.orientation)*u)+(SBDTypePhysicalIAVector3Wrapper<Units>)(*t.position);
            return overlaps(transformedu);

        }

    }
*/
    /// \brief Returns the OverlapType between this physical interval vector and physical interval vector \p u

	OverlapType 												overlapsAdvanced(const SBDTypePhysicalIAVector3Wrapper<Units>& u, const Units& cutoff, const Units& cutoff2) const {

        bool signA, signB;
        Units max2(0.0);
        Units min2(0.0);
        Units a, b;

        if ((a = u.i[0].i[1] - i[0].i[0]) < -cutoff)
            return IncludeNone;
        if ((b = u.i[0].i[0] - i[0].i[1]) > cutoff)
            return IncludeNone;

        if ((signA = SB_SIGN_BIT(a.getValue()))^(signB = SB_SIGN_BIT(b.getValue())))  { // intersection, sign(a0)=true, sign(b0)=false
            max2 += a.getValue()>fabs(b.getValue()) ? a*a: b*b;
        }
        else if (!signA) {
            max2 += a*a; min2 += b*b;
        }
        else {
            max2 += b*b; min2 += a*a;
        }

        if ((a = u.i[1].i[1] - i[1].i[0]) < -cutoff)
            return IncludeNone;
        if ((b = u.i[1].i[0] - i[1].i[1]) > cutoff)
            return IncludeNone;


        if ((signA = SB_SIGN_BIT(a.getValue()))^(signB = SB_SIGN_BIT(b.getValue())))  { // intersection, sign(a0)=true, sign(b0)=false
            max2 += a.getValue()>fabs(b.getValue()) ? a*a: b*b;
        }
        else if (!signA) {
            max2 += a*a; min2 += b*b;
        }
        else {
            max2 += b*b; min2 += a*a;
        }

        if ((a = u.i[2].i[1] - i[2].i[0]) < -cutoff)
            return IncludeNone;
        if ((b = u.i[2].i[0] - i[2].i[1]) > cutoff)
            return IncludeNone;


        if ((signA = SB_SIGN_BIT(a.getValue()))^(signB = SB_SIGN_BIT(b.getValue())))  { // intersection, sign(a0)=true, sign(b0)=false
            max2 += a.getValue()>fabs(b.getValue()) ? a*a: b*b;
        }
        else if (!signA) {
            max2 += a*a; min2 += b*b;
        }
        else {
            max2 += b*b; min2 += a*a;
        }

        if (max2 < cutoff2) return IncludeAll;					// include all pairs
        else if (min2 > cutoff2) return IncludeNone;			// none is included
        else return Subdivide;									// subdivide

    }
/*
    /// \brief Returns the OverlapType between this physical interval vector and physical interval vector \p u transformed by \p t

	OverlapType 												overlapsAdvanced(const SBDTypePhysicalIAVector3Wrapper<Units>& u, const Units& cutoff, const Units& cutoff2, const SBDTypeSymmetryTransform& t) const {

        int signA, signB;
        Units max2(0.0);
        Units min2(0.0);
        Units a0, b0;
        Units a1, b1;
        Units a2, b2;

        if (t.orthorhombic) {

            int sign=2*t.upper[0] - 1;

            if ((a0 = u.i[t.index[0]].i[t.upper[0]]*sign + t.position->v[0] - i[0].i[0])
                < -cutoff)
                return IncludeNone;
            if ((b0 = u.i[t.index[0]].i[t.lower[0]]*sign + t.position->v[0] - i[0].i[1])
                > cutoff)
                return IncludeNone;

            sign=2*t.upper[1] - 1;
            if ((a1 = u.i[t.index[1]].i[t.upper[1]]*sign + t.position->v[1] - i[1].i[0])
                < -cutoff)
                return IncludeNone;
            if ((b1 = u.i[t.index[1]].i[t.lower[1]]*sign + t.position->v[1] - i[1].i[1])
                > cutoff)
                return IncludeNone;

            sign=2*t.upper[2] - 1;
            if ((a2 = u.i[t.index[2]].i[t.upper[2]]*sign + t.position->v[2] - i[2].i[0])
                < -cutoff)
                return IncludeNone;
            if ((b2 = u.i[t.index[2]].i[t.lower[2]]*sign + t.position->v[2] - i[2].i[1])
                > cutoff)
                return IncludeNone;


            if ((signA = SB_SIGN_BIT(a0.getValue()))^(signB = SB_SIGN_BIT(b0.getValue())))  { // intersection, sign(a0)=true, sign(b0)=false
                max2 += a0.getValue()>fabs(b0.getValue()) ? a0*a0: b0*b0;
            }
            else if (!signA) {
                max2 += a0*a0; min2 += b0*b0;
            }
            else {
                max2 += b0*b0; min2 += a0*a0;
            }

            if ((signA = SB_SIGN_BIT(a1.getValue()))^(signB = SB_SIGN_BIT(b1.getValue())))  { // intersection, sign(a0)=true, sign(b0)=false
                max2 += a1.getValue()>fabs(b1.getValue()) ? a1*a1: b1*b1;
            }
            else if (!signA) {
                max2 += a1*a1; min2 += b1*b1;
            }
            else {
                max2 += b1*b1; min2 += a1*a1;
            }

            if ((signA = SB_SIGN_BIT(a2.getValue()))^(signB = SB_SIGN_BIT(b2.getValue())))  { // intersection, sign(a0)=true, sign(b0)=false
                max2 += a2.getValue()>fabs(b2.getValue()) ? a2*a2: b2*b2;
            }
            else if (!signA) {
                max2 += a2*a2; min2 += b2*b2;
            }
            else {
                max2 += b2*b2; min2 += a2*a2;
            }

            if (max2 < cutoff2) // include all pairs
                return IncludeAll;
            else if (min2 > cutoff2) // none is included
                return IncludeNone;
            else	// subdivide
                return Subdivide;

        }
        else {

			SBDTypePhysicalIAVector3Wrapper<Units> transformedAABB=((*t.orientation)*u)+SBDTypePhysicalIAVector3Wrapper<Units>(*t.position);
            return overlapsAdvanced(transformedAABB, cutoff, cutoff2);

        }

    }
*/
    /// \brief Returns true when this physical interval vector contains the physical vector \p u

	bool														contains(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

		if (i[0].i[0] > u.v[0]) return false;
		if (i[0].i[1] < u.v[0]) return false;
		if (i[1].i[0] > u.v[1]) return false;
		if (i[1].i[1] < u.v[1]) return false;
		if (i[2].i[0] > u.v[2]) return false;
		if (i[2].i[1] < u.v[2]) return false;

        return true;

    }

    /// \brief Returns true when this physical interval vector contains in physical interval vector \p u

	bool														contains(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		if (u.i[0].i[0] < i[0].i[0]) return false;
		if (u.i[0].i[1] > i[0].i[1]) return false;
		if (u.i[1].i[0] < i[1].i[0]) return false;
		if (u.i[1].i[1] > i[1].i[1]) return false;
		if (u.i[2].i[0] < i[2].i[0]) return false;
		if (u.i[2].i[1] > i[2].i[1]) return false;

        return true;

    }

    /// \brief Returns true when this physical interval vector is contained in physical interval vector \p u

	bool														isContainedIn(const SBDTypePhysicalIAVector3Wrapper<Units>& u) const {

		if (i[0].i[0] < u.i[0].i[0]) return false;
		if (i[0].i[1] > u.i[0].i[1]) return false;
		if (i[1].i[0] < u.i[1].i[0]) return false;
		if (i[1].i[1] > u.i[1].i[1]) return false;
		if (i[2].i[0] < u.i[2].i[0]) return false;
		if (i[2].i[1] > u.i[2].i[1]) return false;

        return true;

    }

    /// \brief Returns the squared euclidean distance between this physical interval vector and physical vector \p u

	Units                                                       distance2ToPoint(const SBDTypePhysicalVector3Wrapper<Units>& u) const {

        Units x,y,z;

        if (u.v[0]<=i[0].i[0]) x=i[0].i[0];
        else if (u.v[0]>=i[0].i[1]) x=i[0].i[1];
        else x=u.v[0];

        if (u.v[1]<=i[1].i[0]) y=i[1].i[0];
        else if (u.v[1]>=i[1].i[1]) y=i[1].i[1];
        else y=u.v[1];

        if (u.v[2]<=i[2].i[0]) z=i[2].i[0];
        else if (u.v[2]>=i[2].i[1]) z=i[2].i[1];
        else z=u.v[2];

        return (x-u.v[0])*(x-u.v[0])+(y-u.v[1])*(y-u.v[1])+(z-u.v[2])*(z-u.v[2]);

    }

    /// \brief Splits this physical interval vector along the longest axis into physical interval vectors

	std::vector<SBDTypePhysicalIAVector3Wrapper<Units>>            split() const {

        // split along the longest axis

		std::vector<SBDTypePhysicalIAVector3Wrapper<Units>> u1u2;
		SBDTypePhysicalIAVector3Wrapper<Units> u1, u2;

        int axis=0;
        Units maxLength=i[0].diameter();
        Units m;

        if (i[1].diameter()>maxLength) { axis=1;maxLength=i[1].diameter(); }
        if (i[2].diameter()>maxLength) { axis=2;maxLength=i[2].diameter(); }

        switch (axis) {

        case 0:

            m=i[0].center();
            u1.i[0].i[0]=i[0].i[0];u1.i[0].i[1]=m;
            u2.i[0].i[1]=i[0].i[1];u2.i[0].i[0]=m;
            u1.i[1]=i[1];u2.i[1]=i[1];
            u1.i[2]=i[2];u2.i[2]=i[2];
            break;

        case 1:

            m=i[1].center();
            u1.i[1].i[0]=i[1].i[0];u1.i[1].i[1]=m;
            u2.i[1].i[1]=i[1].i[1];u2.i[1].i[0]=m;
            u1.i[0]=i[0];u2.i[0]=i[0];
            u1.i[2]=i[2];u2.i[2]=i[2];
            break;

        case 2:

            m=i[2].center();
            u1.i[2].i[0]=i[2].i[0];u1.i[2].i[1]=m;
            u2.i[2].i[1]=i[2].i[1];u2.i[2].i[0]=m;
            u1.i[0]=i[0];u2.i[0]=i[0];
            u1.i[1]=i[1];u2.i[1]=i[1];
            break;

        }

        u1u2.push_back(u1);
        u1u2.push_back(u2);
        return u1u2;

    }

    /// \brief Expands all components of this physical interval vector by offset \p r

    void														expand(Units r) {

        i[0].expand(r);
        i[1].expand(r);
        i[2].expand(r);

    }

    /// \brief Srinks all components of this physical interval vector by offset \p r

    void														shrink(Units r) {

        i[0].shrink(r);
        i[1].shrink(r);
        i[2].shrink(r);

    }

    /// \brief Sets this physical interval vector to [ [\p u.v[0], \p u.v[0]] [\p u.v[1], \p u.v[1]] [\p u.v[2], \p u.v[2]] ]

	void														reset(const SBDTypePhysicalVector3Wrapper<Units>& u) {

        i[0].i[0] = i[0].i[1] = u.v[0];
        i[1].i[0] = i[1].i[1] = u.v[1];
        i[2].i[0] = i[2].i[1] = u.v[2];

    }

    /// \brief Enlarges this physical interval vector to contain the physical vector \p u

	void														bound(const SBDTypePhysicalVector3Wrapper<Units>& u) {

        i[0].bound(u.v[0]);
        i[1].bound(u.v[1]);
        i[2].bound(u.v[2]);

    }

    /// \brief Enlarges this physical interval vector to contain the physical interval vector \p u

	void														bound(const SBDTypePhysicalIAVector3Wrapper<Units>& u) {

        i[0].bound(u.i[0]);
        i[1].bound(u.i[1]);
        i[2].bound(u.i[2]);

    }

    /// \brief Sets the components of this physical interval vector to exactly bound both physical interval vectors \p a and \p b

	void														fit(const SBDTypePhysicalIAVector3Wrapper<Units>& a, const SBDTypePhysicalIAVector3Wrapper<Units>& b) {

        if (a.i[0].i[0]<b.i[0].i[0]) i[0].i[0]=a.i[0].i[0];
        else i[0].i[0]=b.i[0].i[0];

        if (a.i[1].i[0]<b.i[1].i[0]) i[1].i[0]=a.i[1].i[0];
        else i[1].i[0]=b.i[1].i[0];

        if (a.i[2].i[0]<b.i[2].i[0]) i[2].i[0]=a.i[2].i[0];
        else i[2].i[0]=b.i[2].i[0];

        if (a.i[0].i[1]>b.i[0].i[1]) i[0].i[1]=a.i[0].i[1];
        else i[0].i[1]=b.i[0].i[1];

        if (a.i[1].i[1]>b.i[1].i[1]) i[1].i[1]=a.i[1].i[1];
        else i[1].i[1]=b.i[1].i[1];

        if (a.i[2].i[1]>b.i[2].i[1]) i[2].i[1]=a.i[2].i[1];
        else i[2].i[1]=b.i[2].i[1];

    }

    //@}


    /// \name String representation
    //@{

    /// \brief Returns the string representation of the physical interval vector (with a full unit name when fullName is true)

    std::string                                         toStdString(bool fullName = false) const {

        std::string ret = "(" + i[0].toStdString(fullName) + ", " +
                                i[1].toStdString(fullName) + ", " +
                                i[2].toStdString(fullName) + ")";
        return ret;

    }

    //@}


	std::vector<SBDTypePhysicalIntervalWrapper<Units>>                                          i;                  ///< The components of the physical interval vector

};

/// \name Common types and shortnames
//@{

#define		SBPhysicalIAVector3Wrapper		SBDTypePhysicalIAVector3Wrapper

typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperSI>                   SBDTypePhysicalIAVector3WrapperSI;
typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperAU>                   SBDTypePhysicalIAVector3WrapperAU;
typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperDalton>               SBDTypePhysicalIAVector3WrapperDalton;
typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperElectronvolt>         SBDTypePhysicalIAVector3WrapperElectronvolt;
typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperKilocaloriePerMole>   SBDTypePhysicalIAVector3WrapperKilocaloriePerMole;

typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperSI>                   SBPhysicalIAVector3WrapperSI;
typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperAU>                   SBPhysicalIAVector3WrapperAU;
typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperDalton>               SBPhysicalIAVector3WrapperDalton;
typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperElectronvolt>         SBPhysicalIAVector3WrapperElectronvolt;
typedef     SBDTypePhysicalIAVector3Wrapper<SBDQuantityWrapperKilocaloriePerMole>   SBPhysicalIAVector3WrapperKilocaloriePerMole;

//@}

/// \name External functions
//@{

/// \brief Returns the SBPhysicalIAVector3<Quantity> from Unit \p u

template<typename Quantity, typename T>
SBPhysicalIAVector3<Quantity>	getSBPhysicalIAVector3(const T& a) {

	return a.template toSBPhysicalIAVector3<Quantity>();

}

//@}

/// \name External operators
//@{

/// \brief Returns the product of physical quantity \p d with physical interval vector \p u

template<typename Units>
SBDTypePhysicalIAVector3Wrapper<Units>     operator*(const Units d, const SBDTypePhysicalIAVector3Wrapper<Units>& u) {

	return SBDTypePhysicalIAVector3Wrapper<Units>(d*u.i[0],d*u.i[1],d*u.i[2]);

}

/// \brief Returns the product of double \p d with physical interval vector \p u

template <typename Units>
SBDTypePhysicalIAVector3Wrapper<Units>     operator*(const double d, const SBDTypePhysicalIAVector3Wrapper<Units>& u) {

	return SBDTypePhysicalIAVector3Wrapper<Units>(d*u.i[0],d*u.i[1],d*u.i[2]);

}
/*
/// \brief Returns the product of dimensionless 3x3 matrix \p m with physical interval vector \p u

template <typename Units>
SBDTypePhysicalIAVector3Wrapper<Units>     operator*(const SBMatrix33WrapperForPython& m, const SBDTypePhysicalIAVector3Wrapper<Units>& u) {

	return SBDTypePhysicalIAVector3Wrapper<Units>(
        m.m[0][0]*u.i[0]+m.m[0][1]*u.i[1]+m.m[0][2]*u.i[2],
        m.m[1][0]*u.i[0]+m.m[1][1]*u.i[1]+m.m[1][2]*u.i[2],
        m.m[2][0]*u.i[0]+m.m[2][1]*u.i[1]+m.m[2][2]*u.i[2]
    );

}
*/
/// \brief Inserts the physical interval vector \p u in the output stream \p s

template <typename Units>
std::ostream&                                       operator<<(std::ostream& s, const SBDTypePhysicalIAVector3Wrapper<Units>& u) {

    s << "(" << u.i[0] << ", " << u.i[1] << ", " << u.i[2] << ")";
    return s;

}

//@}

#endif
