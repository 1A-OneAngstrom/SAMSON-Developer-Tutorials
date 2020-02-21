#pragma once

#include "SBDQuantityWrapper.hpp"
#include "SBDTypePhysicalVector3Wrapper.hpp"

#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDTypePhysicalMatrix33.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

/*! \file SBDTypePhysicalMatrix33Wrapper.hpp */

/// \brief This class is used as a wrapper between SAMSON SDK SBDTypePhysicalMatrix33 and Python.
///
/// \tparam Units - SBDQuantityWrapper<SBUnitSystem>

template <typename Units = SBDQuantityWrapperSI>
class SBDTypePhysicalMatrix33Wrapper {

public:

    /// \name Constructors
    //@{

    /// \brief Constructs a physical matrix with all components set to zero

	SBDTypePhysicalMatrix33Wrapper() : m{{ Units(0.0), Units(0.0), Units(0.0) }, { Units(0.0), Units(0.0), Units(0.0) }, { Units(0.0), Units(0.0), Units(0.0) }} {}

    /// \brief Constructs the diagonal physical matrix with diagonal [ \p d.v[0] \p d.v[1] \p d.v[2] ]

	SBDTypePhysicalMatrix33Wrapper(const SBDTypePhysicalVector3Wrapper<Units>& d) {

        Units z = 0.0 * d.v[0];
        m = {{ d.v[0], z, z }, { z, d.v[1], z }, { z, z, d.v[2] }};

    }

    /// \brief Constructs the physical matrix with columns \p c0, \p c1 and \p c2

	SBDTypePhysicalMatrix33Wrapper(const SBDTypePhysicalVector3Wrapper<Units>& c0, const SBDTypePhysicalVector3Wrapper<Units>& c1, const SBDTypePhysicalVector3Wrapper<Units>& c2) {

        m = {{ c0.v[0], c1.v[0], c2.v[0] },
             { c0.v[1].getUnitScaledTo(c0.v[0]), c1.v[1].getUnitScaledTo(c0.v[0]), c2.v[1].getUnitScaledTo(c0.v[0]) },
             { c0.v[2].getUnitScaledTo(c0.v[0]), c1.v[2].getUnitScaledTo(c0.v[0]), c2.v[2].getUnitScaledTo(c0.v[0]) }};

    }

    /// \brief Constructs the physical matrix with all components set to \p v

	SBDTypePhysicalMatrix33Wrapper(const Units& v) {

        m = {{ v,v,v }, { v,v,v }, { v,v,v }};

    }

    /// \brief Constructs the physical matrix from the quantity array \p mat

	SBDTypePhysicalMatrix33Wrapper(const std::vector<std::vector<Units>>& mat) {

        if (mat.size() != 3) throw std::runtime_error("The size of the input matrix should be 3x3");
        for (auto u: mat)
			if (u.size() != 3) throw std::runtime_error("The size of the input matrix should be 3x3");

        m = {{ mat[0][0],                           mat[0][1].getUnitScaledTo(mat[0][0]),mat[0][2].getUnitScaledTo(mat[0][0]) },
             { mat[1][0].getUnitScaledTo(mat[0][0]),mat[1][1].getUnitScaledTo(mat[0][0]),mat[1][2].getUnitScaledTo(mat[0][0]) },
             { mat[2][0].getUnitScaledTo(mat[0][0]),mat[2][1].getUnitScaledTo(mat[0][0]),mat[2][2].getUnitScaledTo(mat[0][0]) }};

    }

    /// \brief Constructs the physical matrix from components \p m00,  \p m01, \p m02, \p m10,  \p m11, \p m12, \p m20,  \p m21 and \p m22

	SBDTypePhysicalMatrix33Wrapper(const Units& m00, const Units& m01, const Units& m02, const Units& m10, const Units& m11, const Units& m12, const Units& m20, const Units& m21, const Units& m22) {

        m = {{ m00,                     m01.getUnitScaledTo(m00),m02.getUnitScaledTo(m00) },
             { m10.getUnitScaledTo(m00),m11.getUnitScaledTo(m00),m12.getUnitScaledTo(m00) },
             { m20.getUnitScaledTo(m00),m21.getUnitScaledTo(m00),m22.getUnitScaledTo(m00) }};

    }

    /// \brief Constructs the dimensionless physical matrix with all components set to \p d

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalMatrix33Wrapper(double d) {

        m = {{ Units(d), Units(d), Units(d) }, { Units(d), Units(d), Units(d) }, { Units(d), Units(d), Units(d) }};

    }

    /// \brief Constructs the dimensionless physical matrix from double array \p mat

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalMatrix33Wrapper(const std::vector<std::vector<double>> mat) {

        if (mat.size() != 3) throw std::runtime_error("The size of the input matrix should be 3x3");
        for (auto u: mat)
			if (u.size() != 3) throw std::runtime_error("The size of the input matrix should be 3x3");

        m = {{ Units(mat[0][0]),Units(mat[0][1]),Units(mat[0][2]) },
             { Units(mat[1][0]),Units(mat[1][1]),Units(mat[1][2]) },
             { Units(mat[2][0]),Units(mat[2][1]),Units(mat[2][2]) }};

    }

    /// \brief Constructs the dimensionless physical matrix from components \p m00,  \p m01, \p m02, \p m10,  \p m11, \p m12, \p m20,  \p m21 and \p m22

	template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalMatrix33Wrapper(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22) {

        m = {{ Units(m00),Units(m01),Units(m02) }, { Units(m10),Units(m11),Units(m12) }, { Units(m20),Units(m21),Units(m22) }};

    }

    /// \brief Constructs a matrix from SBPhysicalMatrix33 \p q

    template<typename Quantity, typename System = SBUnitSystemSI>
	SBDTypePhysicalMatrix33Wrapper(const SBPhysicalMatrix33<Quantity>& q) {

		m = {{SBDQuantityWrapper<System>(q.m[0][0]),
			  SBDQuantityWrapper<System>(q.m[0][1]),
			  SBDQuantityWrapper<System>(q.m[0][2])},
			 {SBDQuantityWrapper<System>(q.m[1][0]),
			  SBDQuantityWrapper<System>(q.m[1][1]),
			  SBDQuantityWrapper<System>(q.m[1][2])},
			 {SBDQuantityWrapper<System>(q.m[2][0]),
			  SBDQuantityWrapper<System>(q.m[2][1]),
			  SBDQuantityWrapper<System>(q.m[2][2])}};

    }

    //@}


    /// \name Accessors
    //@{

    /// \brief Returns the first column of this physical matrix

	SBPhysicalVector3Wrapper<Units>								getE1() const {

		return SBPhysicalVector3Wrapper<Units>(m[0][0], m[1][0], m[2][0]);

    }

	/// \brief Sets the first column of this physical matrix

	void														setE1(const SBPhysicalVector3Wrapper<Units>& v) {

		m[0][0] = v.v[0];
		m[1][0] = v.v[1];
		m[2][0] = v.v[2];

	}

    /// \brief Returns the second column of this physical matrix

	SBPhysicalVector3Wrapper<Units>								getE2() const {

		return SBPhysicalVector3Wrapper<Units>(m[0][1], m[1][1], m[2][1]);

    }

	/// \brief Sets the second column of this physical matrix

	void														setE2(const SBPhysicalVector3Wrapper<Units>& v) {

		m[0][1] = v.v[0];
		m[1][1] = v.v[1];
		m[2][1] = v.v[2];

	}

    /// \brief Returns the third column of this physical matrix

	SBPhysicalVector3Wrapper<Units>								getE3() const {

		return SBPhysicalVector3Wrapper<Units>(m[0][2], m[1][2], m[2][2]);

    }

	/// \brief Sets the third column of this physical matrix

	void														setE3(const SBPhysicalVector3Wrapper<Units>& v) {

		m[0][2] = v.v[0];
		m[1][2] = v.v[1];
		m[2][2] = v.v[2];

	}

    /// \brief Returns the row \p r of this physical matrix

	SBPhysicalVector3Wrapper<Units>								getRow(const unsigned int r) const {

		if (r > 3) throw std::runtime_error("Index out of range");

		return SBPhysicalVector3Wrapper<Units>(m[r][0], m[r][1], m[r][1]);

    }

    /// \brief Returns the column \p c of this physical matrix

	SBPhysicalVector3Wrapper<Units>								getColumn(const unsigned int c) const {

		if (c > 3) throw std::runtime_error("Index out of range");

		return SBPhysicalVector3Wrapper<Units>(m[0][c], m[1][c], m[1][c]);

    }

    /// \brief Returns a dimensionless physical matrix whose components are equal to those of this physical matrix

	std::vector<std::vector<double>>							getValue() const {

        std::vector<std::vector<double>> ret = {{m[0][0].getValue(), m[0][1].getValue(), m[0][2].getValue()},
                                                {m[1][0].getValue(), m[1][1].getValue(), m[1][2].getValue()},
                                                {m[2][0].getValue(), m[2][1].getValue(), m[2][2].getValue()}};

        return ret;

    }

    /// \brief Sets the components of this physical matrix equal to those of the dimensionless physical matrix \p u

    void														setValue(const std::vector<std::vector<double>>& u) {

        if (u.size() != 3) throw std::runtime_error("The size of the input matrix should be 3x3");
		for (auto v: u)
			if (v.size() != 3) throw std::runtime_error("The size of the input matrix should be 3x3");

        m[0][0].setValue(u[0][0]); m[0][1].setValue(u[0][1]); m[0][2].setValue(u[0][2]);
        m[1][0].setValue(u[1][0]); m[1][1].setValue(u[1][1]); m[1][2].setValue(u[1][2]);
        m[2][0].setValue(u[2][0]); m[2][1].setValue(u[2][1]); m[2][2].setValue(u[2][2]);

    }

    /// \brief Returns the arbitraty SBPhysicalMatrix33

    template<typename Quantity, typename System = SBUnitSystemSI>
	SBPhysicalMatrix33<Quantity>								toSBPhysicalMatrix33 () const {

        return SBPhysicalMatrix33<Quantity>(
                    getSBQuantity<Quantity>(m[0][0]), getSBQuantity<Quantity>(m[0][1]), getSBQuantity<Quantity>(m[0][2]),
                    getSBQuantity<Quantity>(m[1][0]), getSBQuantity<Quantity>(m[1][1]), getSBQuantity<Quantity>(m[1][2]),
                    getSBQuantity<Quantity>(m[2][0]), getSBQuantity<Quantity>(m[2][1]), getSBQuantity<Quantity>(m[2][2]));

    }

    /// \brief Returns the i-th j-th component of the matrix

	Units														getComponent(const unsigned int i, const unsigned int j) const {

		if (i >= 3 || j >= 3)   throw std::runtime_error("Index is out of range");

        return m[i][j];

    }

	/// \brief Returns true if the matrix is dimensionless

	bool														isDimensionless() const {

		return m[0][0].isDimensionless();

	}

    //@}


    /// \name Operators
    //@{

    /// \brief Returns the sum of this physical matrix with physical matrix \p mat

	SBDTypePhysicalMatrix33Wrapper<Units>						operator+(const SBDTypePhysicalMatrix33Wrapper<Units>& mat) const {

		return SBDTypePhysicalMatrix33Wrapper<Units>(
                    m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1], m[0][2] + mat.m[0][2],
                    m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1], m[1][2] + mat.m[1][2],
                    m[2][0] + mat.m[2][0], m[2][1] + mat.m[2][1], m[2][2] + mat.m[2][2]);

    }

    /// \brief Returns the difference of this physical matrix with physical matrix \p mat

	SBDTypePhysicalMatrix33Wrapper<Units>						operator-(const SBDTypePhysicalMatrix33Wrapper<Units>& mat) const {

		return SBDTypePhysicalMatrix33Wrapper<Units>(
                    m[0][0] - mat.m[0][0], m[0][1] - mat.m[0][1], m[0][2] - mat.m[0][2],
                    m[1][0] - mat.m[1][0], m[1][1] - mat.m[1][1], m[1][2] - mat.m[1][2],
                    m[2][0] - mat.m[2][0], m[2][1] - mat.m[2][1], m[2][2] - mat.m[2][2]);

    }

    /// \brief Returns the product of this physical matrix with physical matrix \p mat

	SBDTypePhysicalMatrix33Wrapper<Units>						operator*(const SBDTypePhysicalMatrix33Wrapper<Units>& mat) const {

		return SBDTypePhysicalMatrix33Wrapper<Units>(
                    m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0],
                    m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1],
                    m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2],
                    m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0],
                    m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1],
                    m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2],
                    m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0],
                    m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1],
                    m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2]);

	}

	/// \brief Returns the product of this physical matrix with double \p d

	SBDTypePhysicalMatrix33Wrapper<Units>						operator*(const double d) const {

		return SBDTypePhysicalMatrix33Wrapper<Units>(
			m[0][0] * d, m[0][1] * d, m[0][2] * d,
			m[1][0] * d, m[1][1] * d, m[1][2] * d,
			m[2][0] * d, m[2][1] * d, m[2][2] * d
			);

	}

	/// \brief Returns the division of this physical matrix by double \p d

	SBDTypePhysicalMatrix33Wrapper<Units>						operator/(const double d) const {

		return SBDTypePhysicalMatrix33Wrapper<Units>(
			m[0][0] / d, m[0][1] / d, m[0][2] / d,
			m[1][0] / d, m[1][1] / d, m[1][2] / d,
			m[2][0] / d, m[2][1] / d, m[2][2] / d
			);

	}

    /* // makes multiplication by another matrix ambiguous
    /// \brief Multiplies this dimensionless physical matrix with physical quantity \p d

	SBDTypePhysicalMatrix33Wrapper<Units>						operator*(const Units& d) {

		return SBDTypePhysicalMatrix33Wrapper<Units>(
            m[0][0] * d, m[0][1] * d, m[0][2] * d,
            m[1][0] * d, m[1][1] * d, m[1][2] * d,
            m[2][0] * d, m[2][1] * d, m[2][2] * d
            );

    }*/

    /// \brief Adds physical matrix \p mat to this physical matrix

	SBDTypePhysicalMatrix33Wrapper<Units>&						operator+=(const SBDTypePhysicalMatrix33Wrapper<Units>& mat) {

        m[0][0] += mat.m[0][0]; m[0][1] += mat.m[0][1]; m[0][2] += mat.m[0][2];
        m[1][0] += mat.m[1][0]; m[1][1] += mat.m[1][1]; m[1][2] += mat.m[1][2];
        m[2][0] += mat.m[2][0]; m[2][1] += mat.m[2][1]; m[2][2] += mat.m[2][2];
        return *this;

    }

    /// \brief Subtracts physical matrix \p mat from this physical matrix

	SBDTypePhysicalMatrix33Wrapper<Units>&						operator-=(const SBDTypePhysicalMatrix33Wrapper<Units>& mat) {

        m[0][0] -= mat.m[0][0]; m[0][1] -= mat.m[0][1]; m[0][2] -= mat.m[0][2];
        m[1][0] -= mat.m[1][0]; m[1][1] -= mat.m[1][1]; m[1][2] -= mat.m[1][2];
        m[2][0] -= mat.m[2][0]; m[2][1] -= mat.m[2][1]; m[2][2] -= mat.m[2][2];
        return *this;

    }

    /// \brief Returns the opposite of this physical matrix

	SBDTypePhysicalMatrix33Wrapper<Units>						operator-() const {

		return SBDTypePhysicalMatrix33Wrapper<Units>(
            -m[0][0], -m[0][1], -m[0][2],
            -m[1][0], -m[1][1], -m[1][2],
            -m[2][0], -m[2][1], -m[2][2]
            );

    }

    /// \brief Multiplies this physical matrix with double \p d

	SBDTypePhysicalMatrix33Wrapper<Units>&						operator*=(const double d) {

        m[0][0] *= d; m[0][1] *= d; m[0][2] *= d;
        m[1][0] *= d; m[1][1] *= d; m[1][2] *= d;
        m[2][0] *= d; m[2][1] *= d; m[2][2] *= d;
        return *this;

	}

	/// \brief Multiplies this dimensionless physical matrix with physical quantity \p d

	SBDTypePhysicalMatrix33Wrapper<Units>&						operator*=(const Units& d) {

		if (!isDimensionless() || !d.isDimensionless()) throw std::runtime_error("Error, this function may only be used for dimensionless quantities");

		m[0][0] *= d; m[0][1] *= d; m[0][2] *= d;
		m[1][0] *= d; m[1][1] *= d; m[1][2] *= d;
		m[2][0] *= d; m[2][1] *= d; m[2][2] *= d;
		return *this;

	}

	/// \brief Divides this dimensionless physical matrix by physical quantity \p d

	SBDTypePhysicalMatrix33Wrapper<Units>&						operator/=(const Units& d) {

		if (!isDimensionless() || !d.isDimensionless()) throw std::runtime_error("Error, this function may only be used for dimensionless quantities");

		m[0][0] /= d; m[0][1] /= d; m[0][2] /= d;
		m[1][0] /= d; m[1][1] /= d; m[1][2] /= d;
		m[2][0] /= d; m[2][1] /= d; m[2][2] /= d;
		return *this;

	}

    /// \brief Returns the product of this physical matrix with physical vector \p v

	SBPhysicalVector3Wrapper<Units>								operator*(const SBPhysicalVector3Wrapper<Units>& v) const {

        Units res0 (m[0][0] * v.v[0] + m[0][1] * v.v[1] + m[0][2] * v.v[2] );
        Units res1 (m[1][0] * v.v[0] + m[1][1] * v.v[1] + m[1][2] * v.v[2] );
        Units res2 (m[2][0] * v.v[0] + m[2][1] * v.v[1] + m[2][2] * v.v[2] );

		return SBPhysicalVector3Wrapper<Units>(res0, res1, res2);

    }

    /// \brief Returns true if this physical matrix is equal to physical matrix \p mat (component-wise)

	bool														operator==(const SBDTypePhysicalMatrix33Wrapper<Units>& mat) const {

        return
            (m[0][0] == mat.m[0][0]) && (m[0][1] == mat.m[0][1]) && (m[0][2] == mat.m[0][2]) &&
            (m[1][0] == mat.m[1][0]) && (m[1][1] == mat.m[1][1]) && (m[1][2] == mat.m[1][2]) &&
            (m[2][0] == mat.m[2][0]) && (m[2][1] == mat.m[2][1]) && (m[2][2] == mat.m[2][2]);

    }

    /// \brief Returns true if this physical matrix is different from physical matrix \p mat (component-wise)

	bool														operator!=(const SBDTypePhysicalMatrix33Wrapper<Units>& mat) const {

        return
            (m[0][0] != mat.m[0][0]) || (m[0][1] != mat.m[0][1]) || (m[0][2] != mat.m[0][2]) ||
            (m[1][0] != mat.m[1][0]) || (m[1][1] != mat.m[1][1]) || (m[1][2] != mat.m[1][2]) ||
            (m[2][0] != mat.m[2][0]) || (m[2][1] != mat.m[2][1]) || (m[2][2] != mat.m[2][2]);

    }

    //@}


    /// \name Useful functions
    //@{

    /// \brief Returns the trace m[0][0] + m[1][1] + m[2][2] of this physical matrix

	Units														trace() const {

        return m[0][0] + m[1][1] + m[2][2];

    }

    /// \brief Sets this physical matrix to the identity matrix

	void														setIdentity() {

        m[0][0].setValue(1.0);
        m[0][1].setValue(0.0);
        m[0][2].setValue(0.0);
        m[1][0].setValue(0.0);
        m[1][1].setValue(1.0);
        m[1][2].setValue(0.0);
        m[2][0].setValue(0.0);
        m[2][1].setValue(0.0);
        m[2][2].setValue(1.0);

    }

    /// \brief Sets this physical matrix to zero

    void														setZero() {

        m[0][0].setValue(0.0);
        m[0][1].setValue(0.0);
        m[0][2].setValue(0.0);
        m[1][0].setValue(0.0);
        m[1][1].setValue(0.0);
        m[1][2].setValue(0.0);
        m[2][0].setValue(0.0);
        m[2][1].setValue(0.0);
        m[2][2].setValue(0.0);

    }

    /// \brief Returns the transpose of this physical matrix

	SBDTypePhysicalMatrix33Wrapper<Units>						transpose() const {

		return SBDTypePhysicalMatrix33Wrapper<Units>(
                    m[0][0], m[1][0], m[2][0],
                    m[0][1], m[1][1], m[2][1],
                    m[0][2], m[1][2], m[2][2]
                );

    }

    /// \brief Computes the quaternion [ \p w \p x \p y \p z ] corresponding to this physical matrix

	//template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	std::vector<SBDQuantityWrapperSI>							toQuaternion() const {

		if (!isDimensionless()) throw std::runtime_error("This function can be applied only to a dimensionless matrix");

        SBQuantity::dimensionless w, x, y, z;

        SBPhysicalMatrix33<SBQuantity::dimensionless> sm = this->template toSBPhysicalMatrix33<SBQuantity::dimensionless>();
        sm.toQuaternion(w,x,y,z);

		std::vector<SBDQuantityWrapperSI> ret = {w,x,y,z};

        return ret;

    }

    /// \brief Returns the dimensionless physical matrix corresponding to quaternion [ \p w \p x \p y \p z ]

	//template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	static SBDTypePhysicalMatrix33Wrapper<Units>				fromQuaternion(const Units& uw, const Units& ux, const Units& uy, const Units& uz) {

		if (!uw.isDimensionless()) throw std::runtime_error("This function can be used only with dimensionless units");
		if (!ux.isDimensionless()) throw std::runtime_error("This function can be used only with dimensionless units");
		if (!uy.isDimensionless()) throw std::runtime_error("This function can be used only with dimensionless units");
		if (!uz.isDimensionless()) throw std::runtime_error("This function can be used only with dimensionless units");

        SBQuantity::dimensionless w = uw.template toSBQuantity<SBQuantity::dimensionless>();
        SBQuantity::dimensionless x = ux.template toSBQuantity<SBQuantity::dimensionless>();
        SBQuantity::dimensionless y = uy.template toSBQuantity<SBQuantity::dimensionless>();
        SBQuantity::dimensionless z = uz.template toSBQuantity<SBQuantity::dimensionless>();

        SBDTypePhysicalMatrix33<SBQuantity::dimensionless> sm = SBDTypePhysicalMatrix33<SBQuantity::dimensionless>::fromQuaternion(w,x,y,z);

		return SBDTypePhysicalMatrix33Wrapper<Units>(sm);

    }

    /// \brief Computes the rotation vector corresponding to this dimensionless physical matrix

	//template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	SBDTypePhysicalVector3WrapperSI								toRotationVector() const {

		if (!isDimensionless()) throw std::runtime_error("This function can be applied only to a dimensionless matrix");

        SBPhysicalMatrix33<SBQuantity::dimensionless> sm = this->template toSBPhysicalMatrix33<SBQuantity::dimensionless>();

        SBVector3 rotationVector;

        sm.toRotationVector(rotationVector);

		return SBDTypePhysicalVector3WrapperSI(rotationVector);

    }

    /// \brief Orthonormalizes this dimensionless physical matrix

	//template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
    void														orthonormalize() {

		if (!isDimensionless()) throw std::runtime_error("This function can be applied only to a dimensionless matrix");

        SBPhysicalMatrix33<SBQuantity::dimensionless> sm = this->template toSBPhysicalMatrix33<SBQuantity::dimensionless>();

        sm.orthonormalize();

		SBDTypePhysicalMatrix33Wrapper<Units> om(sm);

        m[0][0] = om.m[0][0]; m[0][1] = om.m[0][1]; m[0][2] = om.m[0][2];
        m[1][0] = om.m[1][0]; m[1][1] = om.m[1][1]; m[1][2] = om.m[1][2];
        m[2][0] = om.m[2][0]; m[2][1] = om.m[2][1]; m[2][2] = om.m[2][2];

    }

    /// \brief Performs a quasi-static update of this dimensionless physical matrix using the rotation vector [ \p wx \p wy \p wz ]
    ///
    /// \param wx The first component of the rotation vector
    /// \param wy The second component of the rotation vector
    /// \param wz The third component of the rotation vector
    /// \param rotAngle The rotation angle
    /// \param rotAxis The rotation axis
    /// \param rotA The rotation axis
    /// \param rotB The rotation axis
    /// \param rotC The rotation axis
    ///
    /// This function performs a quasi-static update of this dimensionless physical matrix using the rotation vector [ \p wx \p wy \p wz ]. During the update,
    /// The rotation vector [ \p wx \p wy \p wz ] is converted to a rotation angle and rotation axis, respectively stored into \p rotAngle and \p rotAxis.
    /// If \f$\mathbf{M}\f$ denotes the original matrix, the final matrix is \f$\cos(w)\mathbf{A}+\sin(w)\mathbf{B}+\mathbf{C}\f$, where
    /// \f$\mathbf{A}\f$, \f$\mathbf{B}\f$ and \f$\mathbf{C}\f$ are physical matrices computed from \f$\mathbf{M}\f$ and the rotation axis \f$\mathbf{v}\f$,
    /// and \f$w\f$ is the rotation angle:
    /// - \f$\mathbf{A}=(\mathbf{I}-\mathbf{v}\mathbf{v}^T)\mathbf{M}\f$
    /// - \f$\mathbf{B}=\tilde{\mathbf{v}}\mathbf{M}\f$
    /// - \f$\mathbf{C}=\mathbf{v}\mathbf{v}^T\mathbf{M}\f$
    ///
    /// where \f$\tilde{\mathbf{v}}\f$ is the matrix such that \f$\tilde{\mathbf{v}}\mathbf{x}=\mathbf{v}\times\mathbf{x}\f$ for any \f$\mathbf{x}\f$.
    ///
    /// When the function returns, \f$\mathbf{A}\f$, \f$\mathbf{B}\f$ and \f$\mathbf{C}\f$ are stored into \p rotA, \p rotB and \p rotC, respectively.
    ///
    /// Note that this function may only be used with dimensionless physical matrices.

	//template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	void quasiStaticUpdate(const Units& wx, const Units& wy, const Units& wz,
                                 Units &rotAngle,
								 SBDTypePhysicalVector3Wrapper<Units> &rotAxis,
								 SBDTypePhysicalMatrix33Wrapper<Units> &rotA,
								 SBDTypePhysicalMatrix33Wrapper<Units> &rotB,
								 SBDTypePhysicalMatrix33Wrapper<Units> &rotC) {

		if (!isDimensionless()) throw std::runtime_error("This function can be applied only to a dimensionless matrix");

        SBQuantity::dimensionless swx = wx.template toSBQuantity<SBQuantity::dimensionless>();
        SBQuantity::dimensionless swy = wy.template toSBQuantity<SBQuantity::dimensionless>();
        SBQuantity::dimensionless swz = wz.template toSBQuantity<SBQuantity::dimensionless>();
        SBQuantity::dimensionless srotAngle;
        SBVector3 srotAxis;
        SBDTypePhysicalMatrix33<SBQuantity::dimensionless> srotA, srotB, srotC;

        SBPhysicalMatrix33<SBQuantity::dimensionless> sm = this->template toSBPhysicalMatrix33<SBQuantity::dimensionless>();

        sm.quasiStaticUpdate(swx, swy, swz, srotAngle, srotAxis, srotA, srotB, srotC);

		SBDTypePhysicalMatrix33Wrapper<Units> om(sm);

        m[0][0] = om.m[0][0]; m[0][1] = om.m[0][1]; m[0][2] = om.m[0][2];
        m[1][0] = om.m[1][0]; m[1][1] = om.m[1][1]; m[1][2] = om.m[1][2];
        m[2][0] = om.m[2][0]; m[2][1] = om.m[2][1]; m[2][2] = om.m[2][2];

        rotAngle = Units (srotAngle);
		rotAxis = SBDTypePhysicalVector3Wrapper<Units> (srotAxis);
		rotA = SBDTypePhysicalMatrix33Wrapper<Units> (srotA);
		rotB = SBDTypePhysicalMatrix33Wrapper<Units> (srotB);
		rotC = SBDTypePhysicalMatrix33Wrapper<Units> (srotC);

    }

    /// \brief Computes a ZYZ Euler decomposition of this physical matrix
    ///
    /// \param phi The first Z rotation angle
    /// \param theta The Y rotation angle
    /// \param psi The second Z rotation angle
    ///
    /// This function computes a ZYZ Euler decomposition of this physical matrix:
    ///
    /// \f$\mathbf{M}=\mathbf{R}(z,psi)\mathbf{R}(y,theta)\mathbf{R}(z,phi)\f$
    ///
    /// where \f$\mathbf{M}\f$ denotes this physical matrix, \f$\mathbf{R}(z,phi)\f$ denotes the first rotation around the Z axis, \f$\mathbf{R}(y,theta)\f$ denotes the rotation around
    /// the Y axis, and \f$\mathbf{R}(z,psi)\f$ denotes the second rotation around the Z axis.
    ///
    /// Note that this function may only be used with dimensionless physical matrices.

	//template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
	std::vector<Units>											computeEulerDecompositionZYZ() {

		if (!isDimensionless()) throw std::runtime_error("This function can be applied only to a dimensionless matrix");

        SBQuantity::dimensionless sphi   ;
        SBQuantity::dimensionless stheta ;
        SBQuantity::dimensionless spsi   ;

        SBPhysicalMatrix33<SBQuantity::dimensionless> sm = this->template toSBPhysicalMatrix33<SBQuantity::dimensionless>();

        sm.computeEulerDecompositionZYZ(sphi, stheta, spsi);

        Units phi(sphi);
        Units theta(stheta);
        Units psi(spsi);

        std::vector<Units> ret = {phi, theta, psi};

        return ret;

    }

    /// \brief Returns the dimensionless physical matrix corresponding to rotation axis \p axis and rotation angle \p angle (in radians)

	static SBDTypePhysicalMatrix33Wrapper<Units>				fromAxisAngle(const SBDTypePhysicalVector3WrapperSI& axis, const Units& angle) {

		SBVector3 saxis = getSBPhysicalVector3<SBQuantity::dimensionless>(axis);
        SBQuantity::dimensionless sangle = angle.template toSBQuantity<SBQuantity::dimensionless>();

        SBDTypePhysicalMatrix33<SBQuantity::dimensionless> sret = SBDTypePhysicalMatrix33<SBQuantity::dimensionless>::fromAxisAngle(saxis, sangle);

		return SBDTypePhysicalMatrix33Wrapper<Units>(sret);

    }

	/// \brief Returns the dimensionless physical matrix corresponding to rotation axis \p axis and a rotation angle equal to Pi

	static SBDTypePhysicalMatrix33Wrapper<Units>				fromAxisAnglePi(const SBDTypePhysicalVector3WrapperSI& axis) {

		SBVector3 saxis = getSBPhysicalVector3<SBQuantity::dimensionless>(axis);

        SBDTypePhysicalMatrix33<SBQuantity::dimensionless> sret = SBDTypePhysicalMatrix33<SBQuantity::dimensionless>::fromAxisAnglePi(saxis);

		return SBDTypePhysicalMatrix33Wrapper<Units>(sret);

    }

	/// \brief Returns the dimensionless physical matrix that transforms vector \p from into vector \p to. Precisely, left-multiplying vector \p from by the resulting matrix produces vector \p to.

	static SBDTypePhysicalMatrix33Wrapper<Units>				fromAlignment(const SBDTypePhysicalVector3WrapperSI& from, const SBDTypePhysicalVector3WrapperSI& to) {

		SBVector3 sfrom = getSBPhysicalVector3<SBQuantity::dimensionless>(from);
		SBVector3 sto   = getSBPhysicalVector3<SBQuantity::dimensionless>(to);

		SBDTypePhysicalMatrix33<SBQuantity::dimensionless> sret = SBDTypePhysicalMatrix33<SBQuantity::dimensionless>::fromAlignment(sfrom, sto);

		return SBDTypePhysicalMatrix33Wrapper<Units>(sret);

	}


    /// \brief Sets this physical matrix to an orthonormal matrix whose third column is \p axis

	void														revoluteJointZAxisMatrix(const SBDTypePhysicalVector3WrapperSI &axis) {

		SBVector3 saxis = getSBPhysicalVector3<SBQuantity::dimensionless>(axis);

        SBPhysicalMatrix33<SBQuantity::dimensionless> sm = this->template toSBPhysicalMatrix33<SBQuantity::dimensionless>();

        sm.revoluteJointZAxisMatrix(saxis);

		SBDTypePhysicalMatrix33Wrapper<Units> om(sm);

        m[0][0] = om.m[0][0]; m[0][1] = om.m[0][1]; m[0][2] = om.m[0][2];
        m[1][0] = om.m[1][0]; m[1][1] = om.m[1][1]; m[1][2] = om.m[1][2];
        m[2][0] = om.m[2][0]; m[2][1] = om.m[2][1]; m[2][2] = om.m[2][2];

    }

    /// \brief Computes the eigenvalues \p ev and the eigenvectors \p p of this physical matrix
    ///
    /// \param ev Stores the eigenvalues when this function returns
    /// \param p Stores the eigenvectors when this function returns
    ///
    /// This function computes the eigenvalues \p ev and the eigenvectors \p p of this physical matrix. Note that the eigenvalues have the same units as the physical matrix,
    /// while the eigenvectors are stored in a dimensionless matrix.
    ///
    /// \sa \ref pageUnits "SAMSON's unit system"

	void														diagonalize(SBDTypePhysicalVector3Wrapper<Units>& ev, SBDTypePhysicalMatrix33Wrapper<Units>& p) const {

        // NB : M=Pdiag(e)PINVERSE (and PINVERSE=PTRANSPOSE)
        // NB : From Numerical Recipes

        int nrot; // number of Jacobi rotations
        int i, j, ip, iq;

        Units uzero(0.0, m[0][0].getScale(), m[0][0].getExponent()); // a zero unit in Units of the matrix
        Units sm = uzero;
        Units tresh = uzero;
        Units g = uzero;
        Units h = uzero;
        Units c, s, t, tau, theta;

        std::vector<std::vector<Units>> v = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};

        std::vector<std::vector<Units>> a = {{uzero, uzero, uzero},{uzero, uzero, uzero},{uzero, uzero, uzero}};
        std::vector<Units> d = {uzero, uzero, uzero};
        std::vector<Units> b = {uzero, uzero, uzero};
        std::vector<Units> z = {uzero, uzero, uzero};

        // initialization

		for (i = 0; i < 3; i++) {

			for (j = 0; j < 3; j++) {

                a[i][j] = m[i][j];
                v[i][j] = 0.0;

            }

            v[i][i] = 1.0;

        }

		for (i = 0; i < 3; i++) {

            b[i] = a[i][i];
            d[i] = a[i][i];
            z[i] = uzero;

        }

        nrot = 0;

        for (i = 1; i <= 500; i++) {

            sm = fabs(a[0][1]) + fabs(a[0][2]) + fabs(a[1][2]);

            if (sm == uzero) {

				for (ip = 0; ip < 3; ip++) {

					for (iq = 0; iq < 3; iq++) p.m[ip][iq] = v[ip][iq];
                    ev.v[ip] = d[ip];

                }

                return;

            }

			if (i < 4) tresh = 0.2 * sm / 9.0;
            else tresh = uzero;

			for (ip = 0; ip < 2; ip++) {

				for (iq = ip + 1; iq < 3; iq++) {

					g = 100.0 * fabs(a[ip][iq]);

					if ((i > 4) && (fabs(d[ip] + g) == fabs(d[ip])) && (fabs(d[iq] + g) == fabs(d[iq]))) a[ip][iq] = uzero;
                    else if (fabs(a[ip][iq])>tresh) {

                        h = d[iq] - d[ip];

                        if ((fabs(h) + g) == (fabs(h))) t = a[ip][iq] / h;
                        else {

                            theta = 0.5*h / (a[ip][iq]);
                            t = 1.0 / (fabs(theta) + sqrt(1.0 + theta*theta));
                            if (theta<0.0) t = -t;

                        }

                        c = 1.0 / sqrt(1.0 + t*t);
                        s = t*c;
                        tau = s / (1.0 + c);
                        h = t*a[ip][iq];
                        z[ip] -= h;
                        z[iq] += h;
                        d[ip] -= h;
                        d[iq] += h;
                        a[ip][iq] = uzero;

                        for (j = 0; j <= (ip - 1); j++) {

                            g = a[j][ip];
                            h = a[j][iq];
                            a[j][ip] = g - s*(h + g*tau);
                            a[j][iq] = h + s*(g - h*tau);

                        }

                        for (j = (ip + 1); j <= (iq - 1); j++) {

                            g = a[ip][j];
                            h = a[j][iq];
                            a[ip][j] = g - s*(h + g*tau);
                            a[j][iq] = h + s*(g - h*tau);

                        }

                        for (j = (iq + 1); j<3; j++) {

                            g = a[ip][j];
                            h = a[iq][j];
                            a[ip][j] = g - s*(h + g*tau);
                            a[iq][j] = h + s*(g - h*tau);

                        }

                        for (j = 0; j<3; j++) {

							g = v[j][ip];
							h = v[j][iq];
							v[j][ip] = g - s * (h + g * tau);
							v[j][iq] = h + s * (g - h * tau);

                        }

                        nrot++;

                    }

                }

            }

            for (ip = 0; ip<3; ip++) {

                b[ip] += z[ip];
                d[ip] = b[ip];
                z[ip] = uzero;

            }

        }

        SB_TRACE("Error in diagonalization");

    }

    /// \brief Returns the determinant of this physical matrix

	Units														det() const {

        return (m[0][0] * m[1][1] * m[2][2] + m[1][0] * m[2][1] * m[0][2] + m[2][0] * m[0][1] * m[1][2]) - (m[2][0] * m[1][1] * m[0][2] + m[0][0] * m[2][1] * m[1][2] + m[1][0] * m[0][1] * m[2][2]);

    }

    /// \brief Returns the 2-norm of this physical matrix

	Units														norm() const {

		SBDTypePhysicalMatrix33Wrapper<Units> t = transpose();
		SBDTypePhysicalMatrix33Wrapper<Units> A = *this;
		SBDTypePhysicalMatrix33Wrapper<Units> AtA = t * A;
		SBDTypePhysicalVector3Wrapper<Units> eV(AtA.m[0][0]*0.0);

		SBDTypePhysicalMatrix33Wrapper<Units> P;
        AtA.diagonalize(eV, P);
        Units rho(AtA.m[0][0]*0.0);
        if (rho<fabs(eV.v[0])) rho = fabs(eV.v[0]);
        if (rho<fabs(eV.v[1])) rho = fabs(eV.v[1]);
        if (rho<fabs(eV.v[2])) rho = fabs(eV.v[2]);

        return sqrt(rho);

    }

    /// \brief Returns the cosine of the rotation angle of this rotation matrix
    ///
    /// This function assumes this physical matrix is a rotation matrix, and returns the cosine of the corresponding rotation angle

	Units														cosphi() const {

		SBDTypePhysicalMatrix33Wrapper<Units> A = *this;

		SBDTypePhysicalVector3Wrapper<Units> eV(m[0][0]*0.0);
		SBDTypePhysicalMatrix33Wrapper<Units> P;

        A.diagonalize(eV, P);

        Units rho(1.0, m[0][0].getScale(), m[0][0].getExponent());
        if (rho>fabs(eV.v[0])) rho = (eV.v[0]);
        if (rho>fabs(eV.v[1])) rho = (eV.v[1]);
        if (rho>fabs(eV.v[2])) rho = (eV.v[2]);

        return rho;

    }

    /// \brief Returns the inverse of this physical matrix
    ///
    /// This function assumes the physical matrix is invertible and returns its inverse.

	SBDTypePhysicalMatrix33Wrapper<Units>						inverse() const {

		SBDTypePhysicalMatrix33Wrapper<Units> mat = *this;

        Units d = det();

        mat = mat.transpose();

		return SBDTypePhysicalMatrix33Wrapper<Units> (
                (mat.m[1][1] * mat.m[2][2] - mat.m[2][1] * mat.m[1][2]) / d,
                -(mat.m[1][0] * mat.m[2][2] - mat.m[2][0] * mat.m[1][2]) / d,
                (mat.m[1][0] * mat.m[2][1] - mat.m[2][0] * mat.m[1][1]) / d,
                -(mat.m[0][1] * mat.m[2][2] - mat.m[2][1] * mat.m[0][2]) / d,
                (mat.m[0][0] * mat.m[2][2] - mat.m[2][0] * mat.m[0][2]) / d,
                -(mat.m[0][0] * mat.m[2][1] - mat.m[2][0] * mat.m[0][1]) / d,
                (mat.m[0][1] * mat.m[1][2] - mat.m[1][1] * mat.m[0][2]) / d,
                -(mat.m[0][0] * mat.m[1][2] - mat.m[1][0] * mat.m[0][2]) / d,
                (mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1]) / d
                );

    }

    /// \brief This function sets this physical matrix from ZYZ Euler angles \p phi, \p theta and \p psi.
    ///
    /// \param phi The first Z rotation angle
    /// \param theta The Y rotation angle
    /// \param psi The second Z rotation angle
    ///
    /// This function sets this physical matrix from ZYZ Euler angles:
    ///
    /// \f$\mathbf{M}=\mathbf{R}(z,psi)\mathbf{R}(y,theta)\mathbf{R}(z,phi)\f$
    ///
    /// where \f$\mathbf{M}\f$ denotes this physical matrix, \f$\mathbf{R}(z,phi)\f$ denotes the first rotation around the Z axis, \f$\mathbf{R}(y,theta)\f$ denotes the rotation around
    /// the Y axis, and \f$\mathbf{R}(z,psi)\f$ denotes the second rotation around the Z axis.
    ///
    /// Note that this function may only be used with dimensionless physical matrices.

	//template<typename t = Units, typename std::enable_if<std::is_same<t, SBDQuantityWrapperSI>::value, int>::type = 0>
    void														makeEulerRotationZYZ(const Units& phi, const Units& theta, const Units& psi) {

		if (!m[0][0].isDimensionless()) throw std::runtime_error("Error, this function can only be used for dimensionless quantities");

        m[0][0] = -sin(psi)*sin(phi) + cos(theta)*cos(phi)*cos(psi);
        m[0][1] = sin(psi)*cos(phi) + cos(theta)*sin(phi)*cos(psi);
        m[0][2] = -cos(psi)*sin(theta);
        m[1][0] = -cos(psi)*sin(phi) - cos(theta)*cos(phi)*sin(psi);
        m[1][1] = cos(psi)*cos(phi) - cos(theta)*sin(phi)*sin(psi);
        m[1][2] = sin(psi)*sin(theta);
        m[2][0] = sin(theta)*cos(phi);
        m[2][1] = sin(theta)*sin(phi);
        m[2][2] = cos(theta);

    }

    /// \brief Swaps columns \p i and \p j

    void														swapColumns(const unsigned int i, const unsigned int j) {

        if (i >= 3 || j >= 3) throw std::runtime_error("The indexes should be in range [0,2]");
        if (i == j) return;

        Units s = m[0][i]; m[0][i] = m[0][j]; m[0][j] = s;
        s = m[1][i]; m[1][i] = m[1][j]; m[1][j] = s;
        s = m[2][i]; m[2][i] = m[2][j]; m[2][j] = s;

    }

    /// \brief Swaps rows \p i and \p j

    void														swapRows(const unsigned int i, const unsigned int j) {

        if (i >= 3 || j >= 3) throw std::runtime_error("The indexes should be in range [0,2]");
        if (i == j) return;

        Units s = m[i][0]; m[i][0] = m[j][0]; m[j][0] = s;
        s = m[i][1]; m[i][1] = m[j][1]; m[j][1] = s;
        s = m[i][2]; m[i][2] = m[j][2]; m[j][2] = s;

    }

    //@}

    /// \name String representation
    //@{

    /// \brief Returns the string representation of the matrix (with a full unit name when fullName is true)

	std::string													toStdString(bool fullName = false) const {

        std::string ret =   "[" + m[0][0].toStdString(fullName) + "\t" + m[0][1].toStdString(fullName) + "\t" + m[0][2].toStdString(fullName) + "]" + "\n"
                            "[" + m[1][0].toStdString(fullName) + "\t" + m[1][1].toStdString(fullName) + "\t" + m[1][2].toStdString(fullName) + "]" + "\n"
							"[" + m[2][0].toStdString(fullName) + "\t" + m[2][1].toStdString(fullName) + "\t" + m[2][2].toStdString(fullName) + "]";

        return ret;

    }

    //@}

public:

	std::vector< std::vector<Units> >							m;																///< The components of the physical matrix

};

/// \name Shortnames
//@{

#define		SBPhysicalMatrix33Wrapper									SBDTypePhysicalMatrix33Wrapper

typedef     SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapperSI>		SBDTypePhysicalMatrix33WrapperSI;
typedef     SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapperSI>		SBPhysicalMatrix33WrapperSI;

//@}

/// \name External functions
//@{

/// \brief Returns the SBPhysicalMatrix33<Quantity> from Unit \p u

template<typename Quantity, typename T>
SBPhysicalMatrix33<Quantity>				getSBPhysicalMatrix33(const T& a) {

	return a.template toSBPhysicalMatrix33<Quantity>();

}

//@}

/// \name External operators
//@{

/// \brief Returns the product of double \p d and matrix \p u

template<typename Units>
SBDTypePhysicalMatrix33Wrapper<Units>		operator*(const double d, const SBDTypePhysicalMatrix33Wrapper<Units>& u) {

	return SBDTypePhysicalMatrix33Wrapper<Units>(
        u.m[0][0] * d, u.m[0][1] * d, u.m[0][2] * d,
        u.m[1][0] * d, u.m[1][1] * d, u.m[1][2] * d,
        u.m[2][0] * d, u.m[2][1] * d, u.m[2][2] * d
        );

}

//@}

#endif
