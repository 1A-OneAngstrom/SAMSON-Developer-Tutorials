#pragma once

#include "SBDQuantityWrapper.hpp"
#include "SBDTypePhysicalVector3Wrapper.hpp"
#include "SBDTypePhysicalVector6Wrapper.hpp"
#include "SBDTypePhysicalMatrix33Wrapper.hpp"

#ifdef UNITSFORPYTHON

#include <string>
#include <iostream>
#include <vector>

#include "SBDTypePhysicalMatrix66.hpp"
#include "SBDQuantityType.hpp"
#include "SBDQuantityUnitType.hpp"
#include "SBDQuantityUnitSystem.hpp"

/*! \file SBDTypePhysicalMatrix66Wrapper.hpp */

/// \brief This class is used as a wrapper between SAMSON SDK SBDTypePhysicalMatrix66 and Python.
///
/// \tparam Units - SBDQuantityWrapper<SBUnitSystem>

template <typename Units = SBDQuantityWrapperSI>
class SBDTypePhysicalMatrix66Wrapper {

public:

    /// \name Constructors
    //@{

    /// \brief The default constructor initializes all components to zero

	SBDTypePhysicalMatrix66Wrapper() :

        m00(SBDTypePhysicalMatrix33Wrapper<Units>()),
        m01(SBDTypePhysicalMatrix33Wrapper<Units>()),
        m10(SBDTypePhysicalMatrix33Wrapper<Units>()),
        m11(SBDTypePhysicalMatrix33Wrapper<Units>())

    {}

    /// \brief Constructs a spatial matrix from four 3x3 matrices
    ///
    /// \param mat00 The top left 3x3 block
    /// \param mat01 The top right 3x3 block
    /// \param mat10 The bottom left 3x3 block
    /// \param mat11 The bottom right 3x3 block
    ///
    /// This constructor initializes a spatial matrix from four 3x3 matrices

	SBDTypePhysicalMatrix66Wrapper(const SBDTypePhysicalMatrix33Wrapper<Units>& mat00, const SBDTypePhysicalMatrix33Wrapper<Units>& mat01,
								   const SBDTypePhysicalMatrix33Wrapper<Units>& mat10, const SBDTypePhysicalMatrix33Wrapper<Units>& mat11) :

        m00(mat00),
        m01(mat01),
        m10(mat10),
        m11(mat11)

    {}

	/// \brief Constructs a spatial matrix from SBDTypePhysicalMatrix66 \p q

    template<typename Quantity00, typename Quantity01,
             typename Quantity10, typename Quantity11,
             typename System = SBUnitSystemSI>
	SBDTypePhysicalMatrix66Wrapper(const SBDTypePhysicalMatrix66<Quantity00, Quantity01, Quantity10, Quantity11>& u) {

		m00 = SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapper<System>>(u.m00);
		m01 = SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapper<System>>(u.m01);
		m10 = SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapper<System>>(u.m10);
		m11 = SBDTypePhysicalMatrix33Wrapper<SBDQuantityWrapper<System>>(u.m11);

	}

    //@}

    /// \name Accessors
    //@{

    /// \brief Returns the first column of the spatial matrix

	SBDTypePhysicalVector6Wrapper<Units>							getE1() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
            m00.m[0][0],
            m00.m[1][0],
            m00.m[2][0],
            m10.m[0][0],
            m10.m[1][0],
            m10.m[2][0]
            );

    }

    /// \brief Returns the second column of the spatial matrix

	SBDTypePhysicalVector6Wrapper<Units>							getE2() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
            m00.m[0][1],
            m00.m[1][1],
            m00.m[2][1],
            m10.m[0][1],
            m10.m[1][1],
            m10.m[2][1]
            );

    }

    /// \brief Returns the third column of the spatial matrix

	SBDTypePhysicalVector6Wrapper<Units>							getE3() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
            m00.m[0][2],
            m00.m[1][2],
            m00.m[2][2],
            m10.m[0][2],
            m10.m[1][2],
            m10.m[2][2]
            );

    }

    /// \brief Returns the fourth column of the spatial matrix

	SBDTypePhysicalVector6Wrapper<Units>							getE4() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
            m01.m[0][0],
            m01.m[1][0],
            m01.m[2][0],
            m11.m[0][0],
            m11.m[1][0],
            m11.m[2][0]
            );

    }

    /// \brief Returns the fifth column of the spatial matrix

	SBDTypePhysicalVector6Wrapper<Units>							getE5() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
            m01.m[0][1],
            m01.m[1][1],
            m01.m[2][1],
            m11.m[0][1],
            m11.m[1][1],
            m11.m[2][1]
            );

    }

    /// \brief Returns the sixth column of the spatial matrix

	SBDTypePhysicalVector6Wrapper<Units>							getE6() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
            m01.m[0][2],
            m01.m[1][2],
            m01.m[2][2],
            m11.m[0][2],
            m11.m[1][2],
            m11.m[2][2]
            );

    }

    /// \brief Returns the first row of this spatial physical matrix

	SBDTypePhysicalVector6Wrapper<Units>							getRow1() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
                    m00.m[0][0],
                    m00.m[0][1],
                    m00.m[0][2],
                    m01.m[0][0],
                    m01.m[0][1],
                    m01.m[0][2]
                    );

    }

    /// \brief Returns the second row of this spatial physical matrix

	SBDTypePhysicalVector6Wrapper<Units>							getRow2() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
                    m00.m[1][0],
                    m00.m[1][1],
                    m00.m[1][2],
                    m01.m[1][0],
                    m01.m[1][1],
                    m01.m[1][2]
                    );

    }

    /// \brief Returns the third row of this spatial physical matrix

	SBDTypePhysicalVector6Wrapper<Units>							getRow3() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
                    m00.m[2][0],
                    m00.m[2][1],
                    m00.m[2][2],
                    m01.m[2][0],
                    m01.m[2][1],
                    m01.m[2][2]
                    );

    }

    /// \brief Returns the fourth row of this spatial physical matrix

	SBDTypePhysicalVector6Wrapper<Units>							getRow4() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
                    m10.m[0][0],
                    m10.m[0][1],
                    m10.m[0][2],
                    m11.m[0][0],
                    m11.m[0][1],
                    m11.m[0][2]
                    );

    }

    /// \brief Returns the fifth row of this spatial physical matrix

	SBDTypePhysicalVector6Wrapper<Units>							getRow5() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
                    m10.m[1][0],
                    m10.m[1][1],
                    m10.m[1][2],
                    m11.m[1][0],
                    m11.m[1][1],
                    m11.m[1][2]
                    );

    }

    /// \brief Returns the sixth row of this spatial physical matrix

	SBDTypePhysicalVector6Wrapper<Units>							getRow6() const {

		return SBDTypePhysicalVector6Wrapper<Units>(
                    m10.m[2][0],
                    m10.m[2][1],
                    m10.m[2][2],
                    m11.m[2][0],
                    m11.m[2][1],
                    m11.m[2][2]
                    );

    }

    /// \brief Returns the row \p r of this spatial physical matrix

	SBPhysicalVector6Wrapper<Units>									getRow(const unsigned int r) const {

		if (r >= 6) throw std::runtime_error("Index out of range");

        if (r == 0) return getRow1();
        if (r == 1) return getRow2();
        if (r == 2) return getRow3();
        if (r == 3) return getRow4();
        if (r == 4) return getRow5();
		return getRow6();

    }

    /// \brief Returns the column \p c of this spatial physical matrix

	SBPhysicalVector6Wrapper<Units>									getColumn(const unsigned int c) const {

		if (c >= 6) throw std::runtime_error("Index out of range");

        if (c == 0) return getE1();
        if (c == 1) return getE2();
        if (c == 2) return getE3();
        if (c == 3) return getE4();
        if (c == 4) return getE5();
		return getE6();

    }

    /// \brief Returns a dimensionless physical matrix whose components are equal to those of this physical matrix

	std::vector<std::vector<double>>								getValue() const {

        std::vector<std::vector<double>> ret = {{m00.m[0][0].getValue(), m00.m[0][1].getValue(), m00.m[0][2].getValue(), m01.m[0][0].getValue(), m01.m[0][1].getValue(), m01.m[0][2].getValue()},
                                                {m00.m[1][0].getValue(), m00.m[1][1].getValue(), m00.m[1][2].getValue(), m01.m[1][0].getValue(), m01.m[1][1].getValue(), m01.m[1][2].getValue()},
                                                {m00.m[2][0].getValue(), m00.m[2][1].getValue(), m00.m[2][2].getValue(), m01.m[2][0].getValue(), m01.m[2][1].getValue(), m01.m[2][2].getValue()},
                                                {m10.m[0][0].getValue(), m10.m[0][1].getValue(), m10.m[0][2].getValue(), m11.m[0][0].getValue(), m11.m[0][1].getValue(), m11.m[0][2].getValue()},
                                                {m10.m[1][0].getValue(), m10.m[1][1].getValue(), m10.m[1][2].getValue(), m11.m[1][0].getValue(), m11.m[1][1].getValue(), m11.m[1][2].getValue()},
                                                {m10.m[2][0].getValue(), m10.m[2][1].getValue(), m10.m[2][2].getValue(), m11.m[2][0].getValue(), m11.m[2][1].getValue(), m11.m[2][2].getValue()}};

        return ret;

    }

    /// \brief Sets the components of this physical matrix equal to those of the dimensionless physical matrix \p u

	void															setValue(const std::vector<std::vector<double>>& u) {

        if (u.size() != 6) throw std::runtime_error("The size of the input matrix should be 6x6");
        for (auto v: u)
			if (v.size() != 6) throw std::runtime_error("The size of the input matrix should be 6x6");

        m00.m[0][0].setValue(u[0][0]); m00.m[0][1].setValue(u[0][1]); m00.m[0][2].setValue(u[0][2]); m01.m[0][0].setValue(u[0][3]); m01.m[0][1].setValue(u[0][4]); m01.m[0][2].setValue(u[0][5]);
        m00.m[1][0].setValue(u[1][0]); m00.m[1][1].setValue(u[1][1]); m00.m[1][2].setValue(u[1][2]); m01.m[1][0].setValue(u[1][3]); m01.m[1][1].setValue(u[1][4]); m01.m[1][2].setValue(u[1][5]);
        m00.m[2][0].setValue(u[2][0]); m00.m[2][1].setValue(u[2][1]); m00.m[2][2].setValue(u[2][2]); m01.m[2][0].setValue(u[2][3]); m01.m[2][1].setValue(u[2][4]); m01.m[2][2].setValue(u[2][5]);
        m10.m[0][0].setValue(u[3][0]); m10.m[0][1].setValue(u[3][1]); m10.m[0][2].setValue(u[3][2]); m11.m[0][0].setValue(u[3][3]); m11.m[0][1].setValue(u[3][4]); m11.m[0][2].setValue(u[3][5]);
        m10.m[1][0].setValue(u[4][0]); m10.m[1][1].setValue(u[4][1]); m10.m[1][2].setValue(u[4][2]); m11.m[1][0].setValue(u[4][3]); m11.m[1][1].setValue(u[4][4]); m11.m[1][2].setValue(u[4][5]);
        m10.m[2][0].setValue(u[5][0]); m10.m[2][1].setValue(u[5][1]); m10.m[2][2].setValue(u[5][2]); m11.m[2][0].setValue(u[5][3]); m11.m[2][1].setValue(u[5][4]); m11.m[2][2].setValue(u[5][5]);

    }

    /// \brief Returns the arbitraty SBPhysicalMatrix66

    template<typename Quantity00, typename Quantity01,
             typename Quantity10, typename Quantity11,
             typename System = SBUnitSystemSI>
	SBPhysicalMatrix66<Quantity00, Quantity01, Quantity10, Quantity11>	toSBPhysicalMatrix66 () const {

        return SBPhysicalMatrix66<Quantity00, Quantity01, Quantity10, Quantity11>(
                    m00.template toSBPhysicalMatrix33<Quantity00>(), m01.template toSBPhysicalMatrix33<Quantity01>(),
                    m10.template toSBPhysicalMatrix33<Quantity10>(), m11.template toSBPhysicalMatrix33<Quantity11>());

    }

	/// \brief Returns true if the spatial matrix is dimensionless

	bool																isDimensionless() const {

		return m00.isDimensionless() && m01.isDimensionless() && m10.isDimensionless() && m11.isDimensionless();

	}

    //@}

    /// \name Operators
    //@{

    /// \brief Returns the sum of the spatial matrix with the \p mat spatial matrix
    ///
    /// \param mat A spatial matrix
    ///
    /// This function returns the sum of the spatial matrix with the \p mat spatial matrix. Both spatial matrices must
    /// have identical units.

	SBDTypePhysicalMatrix66Wrapper<Units>								operator+(const SBDTypePhysicalMatrix66Wrapper<Units>& mat) const {

		return SBDTypePhysicalMatrix66Wrapper<Units>(m00 + mat.m00, m01 + mat.m01, m10 + mat.m10, m11 + mat.m11);

    }

    /// \brief Adds the \p mat spatial matrix to this spatial matrix
    ///
    /// \param mat A spatial matrix
    ///
    /// This function adds the \p mat spatial matrix to this spatial matrix. Both spatial matrices must
    /// have identical units.

	SBDTypePhysicalMatrix66Wrapper<Units>&								operator+=(const SBDTypePhysicalMatrix66Wrapper<Units>& mat) {

        m00 += mat.m00;
        m01 += mat.m01;
        m10 += mat.m10;
        m11 += mat.m11;
        return *this;

    }

    /// \brief Returns the subtraction of the spatial matrix from the \p mat spatial matrix
    ///
    /// \param mat A spatial matrix
    ///
    /// This function returns the subtraction of the spatial matrix from the \p mat spatial matrix. Both spatial matrices must
    /// have identical units.

	SBDTypePhysicalMatrix66Wrapper<Units>								operator-(const SBDTypePhysicalMatrix66Wrapper<Units>& mat) const {

		return SBDTypePhysicalMatrix66Wrapper<Units>(m00 - mat.m00, m01 - mat.m01, m10 - mat.m10, m11 - mat.m11);

    }

    /// \brief Subtracts the \p mat spatial matrix from this spatial matrix
    ///
    /// \param mat A spatial matrix
    ///
    /// This function subtracts the \p mat spatial matrix from this spatial matrix. Both spatial matrices must
    /// have identical units.

	SBDTypePhysicalMatrix66Wrapper<Units>&								operator-=(const SBDTypePhysicalMatrix66Wrapper<Units>& mat) {

        m00 -= mat.m00;
        m01 -= mat.m01;
        m10 -= mat.m10;
        m11 -= mat.m11;
        return *this;

    }

	/// \brief Returns the opposite of the spatial matrix

	SBDTypePhysicalMatrix66Wrapper<Units>								operator-() const {

		return SBDTypePhysicalMatrix66Wrapper<Units>(-m00, -m01, -m10, -m11);

    }

	/// \brief Returns the product of this spatial matrix with the double \p d
	///
	/// \param d A double

	SBDTypePhysicalMatrix66Wrapper<Units>								operator*(const double d) const {

		return SBDTypePhysicalMatrix66Wrapper<Units>(m00 * d, m01 * d, m10 * d, m11 * d);

	}

	/// \brief Multiplies this spatial matrix with the double \p d
	///
	/// \param d A double

	SBDTypePhysicalMatrix66Wrapper<Units>&								operator*=(const double d) {

		m00 *= d;
		m01 *= d;
		m10 *= d;
		m11 *= d;
		return *this;

	}

    /// \brief Returns the product of this spatial matrix with the spatial vector \p v
    ///
    /// \param v A spatial vector
    ///
    /// This function returns the product of this spatial matrix with the spatial vector \p v.
    /// \ref pageUnits "SAMSON's unit system" checks that the units in the spatial matrix and the spatial vector are compatible.

	SBDTypePhysicalVector6Wrapper<Units>								operator*(const SBDTypePhysicalVector6Wrapper<Units>& v) const {

		return SBDTypePhysicalVector6Wrapper<Units>(
				m00 * v.angular + m01 * v.linear,
				m10 * v.angular + m11 * v.linear
                );

	}

	/// \brief Multiplies this spatial matrix with physical quantity \p d

	SBDTypePhysicalMatrix66Wrapper<Units>&								operator*=(const Units& d) {

		if (!isDimensionless() || !d.isDimensionless()) throw std::runtime_error("Error, this function may only be used for dimensionless quantities");

		m00 *= d;
		m01 *= d;
		m10 *= d;
		m11 *= d;
		return *this;

	}

	/// \brief Divides this spatial matrix by physical quantity \p d

	SBDTypePhysicalMatrix66Wrapper<Units>&								operator/=(const Units& d) {

		if (!isDimensionless() || !d.isDimensionless()) throw std::runtime_error("Error, this function may only be used for dimensionless quantities");

		m00 /= d;
		m01 /= d;
		m10 /= d;
		m11 /= d;
		return *this;

	}

    //@}

    /// \name Useful functions
    //@{

    /// \brief Sets the matrix to zero

	void																setZero() {

        m00.setZero();
        m01.setZero();
        m10.setZero();
        m11.setZero();

    }

    /// \brief Makes the matrix symmetric
    ///
    /// Makes the matrix symmetric by replacing it with the half-sum of itself and its transpose: \f$\mathbf{M}:=\frac{\mathbf{M}+\mathbf{M}^T}{2}\f$

	void																symmetrize() {

        m00.m[0][1] = 0.5*(m00.m[0][1] + m00.m[1][0]); m00.m[0][2] = 0.5*(m00.m[0][2] + m00.m[2][0]); m01.m[0][0] = 0.5*(m01.m[0][0] + m10.m[0][0]); m01.m[0][1] = 0.5*(m01.m[0][1] + m10.m[1][0]); m01.m[0][2] = 0.5*(m01.m[0][2] + m10.m[2][0]);
        m00.m[1][2] = 0.5*(m00.m[1][2] + m00.m[2][1]); m01.m[1][0] = 0.5*(m01.m[1][0] + m10.m[0][1]); m01.m[1][1] = 0.5*(m01.m[1][1] + m10.m[1][1]); m01.m[1][2] = 0.5*(m01.m[1][2] + m10.m[2][1]);
        m01.m[2][0] = 0.5*(m01.m[2][0] + m10.m[0][2]); m01.m[2][1] = 0.5*(m01.m[2][1] + m10.m[1][2]); m01.m[2][2] = 0.5*(m01.m[2][2] + m10.m[2][2]);
        m11.m[0][1] = 0.5*(m11.m[0][1] + m11.m[1][0]); m11.m[0][2] = 0.5*(m11.m[0][2] + m11.m[2][0]);
        m11.m[1][2] = 0.5*(m11.m[1][2] + m11.m[2][1]);

        m00.m[1][0] = m00.m[0][1];
        m00.m[2][0] = m00.m[0][2]; m00.m[2][1] = m00.m[1][2];
        m10.m[0][0] = m01.m[0][0]; m10.m[0][1] = m01.m[1][0]; m10.m[0][2] = m01.m[2][0];
        m10.m[1][0] = m01.m[0][1]; m10.m[1][1] = m01.m[1][1]; m10.m[1][2] = m01.m[2][1]; m11.m[1][0] = m11.m[0][1];
        m10.m[2][0] = m01.m[0][2]; m10.m[2][1] = m01.m[1][2]; m10.m[2][2] = m01.m[2][2]; m11.m[2][0] = m11.m[0][2]; m11.m[2][1] = m11.m[1][2];

    }

    /// \brief Sets the matrix to identity

	void																setIdentity() {

        m00.setIdentity();
        m11.setIdentity();

        m01.setZero();
        m10.setZero();

    }

    /// \brief Returns the transpose

	SBDTypePhysicalMatrix66Wrapper<Units>								transpose() const {

		return SBDTypePhysicalMatrix66Wrapper<Units>(m00.transpose(), m10.transpose(), m01.transpose(), m11.transpose());

    }

    /// \brief Returns twice the symmetric part of the matrix

	SBDTypePhysicalMatrix66Wrapper<Units>								doubleSymmetricPart() const {

		return SBDTypePhysicalMatrix66Wrapper<Units>(m00 + m00.transpose(), m01 + m10.transpose(), m10 + m01.transpose(), m11 + m11.transpose());

    }

    //@}

    /// \name String representation
    //@{

    /// \brief Returns the string representation of the spatial matrix (with a full unit name when fullName is true)

	std::string															toStdString(bool fullName = false) const {

        std::string ret = "";
        ret += "m00\n" + m00.toStdString(fullName);
        ret += "m01\n" + m01.toStdString(fullName);
        ret += "m10\n" + m10.toStdString(fullName);
        ret += "m11\n" + m11.toStdString(fullName);

        return ret;

    }

    //@}

public:


	SBDTypePhysicalMatrix33Wrapper<Units>								m00;																	///< The top left 3x3 matrix
	SBDTypePhysicalMatrix33Wrapper<Units>								m01;																	///< The top right 3x3 matrix
	SBDTypePhysicalMatrix33Wrapper<Units>								m10;																	///< The bottom left 3x3 matrix
	SBDTypePhysicalMatrix33Wrapper<Units>								m11;																	///< The bottom right 3x3 matrix

};

/// \name Common types and shortnames
//@{

#define		SBPhysicalMatrix66Wrapper									SBDTypePhysicalMatrix66Wrapper

typedef     SBDTypePhysicalMatrix66Wrapper<SBDQuantityWrapperSI>		SBDTypePhysicalMatrix66WrapperSI;
typedef     SBDTypePhysicalMatrix66Wrapper<SBDQuantityWrapperSI>		SBPhysicalMatrix66WrapperSI;

//@}

/// \name External functions
//@{

/// \brief Returns the SBPhysicalMatrix66<Quantity00, Quantity01, Quantity10, Quantity11> from Unit \p u

template<typename Quantity00, typename Quantity01,
		 typename Quantity10, typename Quantity11,
		 typename T>
SBPhysicalMatrix66<Quantity00, Quantity01, Quantity10, Quantity11>		getSBPhysicalMatrix66(const T& a) {

	return a.template toSBPhysicalMatrix66<Quantity00, Quantity01, Quantity10, Quantity11>();

}

//@}

/// \name External operators
//@{

/// \brief Returns the product of double \p d and spatial matrix \p u

template<typename Units>
SBDTypePhysicalMatrix66Wrapper<Units>									operator*(const double d, const SBDTypePhysicalMatrix66Wrapper<Units>& u) {

	return SBDTypePhysicalMatrix66Wrapper<Units>(u.m00 * d, u.m01 * d, u.m10 * d, u.m11 * d);

}

//@}

#endif
