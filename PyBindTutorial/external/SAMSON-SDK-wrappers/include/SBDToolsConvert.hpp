#pragma once

#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/stl.h"
#include "pybind11/numpy.h"
namespace py = pybind11;

#include "SBDQuantityWrapper.hpp"
#include "SBDTypePhysicalVector3Wrapper.hpp"

#ifdef UNITSFORPYTHON

#include <SBVector.hpp>

#include <string>
#include <iostream>
#include <vector>

namespace SBDToolsConvert {

/**
 * \brief Converts SBVector<SBQuantity::...>* to std::vector<SBDQuantityWrapperSI>
 */
template <typename T>
std::vector<SBDQuantityWrapperSI> to1DPyArray(SBVector<T>* arr) {

	if (arr == nullptr) throw py::value_error("The vector is null");

	std::vector<SBDQuantityWrapperSI> pyArr;
	pyArr.resize(arr->size());

	for (unsigned int t = 0; t < arr->size(); t++) pyArr[t] = SBDQuantityWrapperSI( (*arr)[t] );

	return pyArr;

}

/**
 * \brief Converts SBVector<SBPhysicalVector3<SBQuantity::...>>* to std::vector<SBDTypePhysicalVector3WrapperSI>
 */
template <typename T>
std::vector<SBDTypePhysicalVector3WrapperSI> to1DPyArray(SBVector<SBPhysicalVector3<T>>* arr) {

	if (arr == nullptr) throw py::value_error("The vector is null");

	std::vector<SBDTypePhysicalVector3WrapperSI> pyArr;
	pyArr.resize(arr->size());

	for (unsigned int t = 0; t < arr->size(); t++) pyArr[t] = SBDTypePhysicalVector3WrapperSI( (*arr)[t] );

	return pyArr;

}

/**
 * \brief Converts std::vector<SBDQuantityWrapperSI> to SBVector<SBQuantity::...>*
 */
template <typename T>
SBVector<T>* from1DPyArray (std::vector<SBDQuantityWrapperSI>& pyArr) {

	auto size1stDimension = pyArr.size();

	SBVector<T>* arr = new SBVector<T>(size1stDimension);

	for (auto t = 0; t < size1stDimension; t++) arr->push_back(getSBQuantity<T>(pyArr[t]));

	return arr;

}

/**
 * \brief Converts std::vector<SBDTypePhysicalVector3WrapperSI> to SBVector<SBPhysicalVector3<SBQuantity::...>>*
 */
template <typename T>
SBVector<SBPhysicalVector3<T>>* from1DPyArray (std::vector<SBDTypePhysicalVector3WrapperSI>& pyArr) {

	auto size1stDimension = pyArr.size();

	SBVector<SBPhysicalVector3<T>>* arr = new SBVector<SBPhysicalVector3<T>>(size1stDimension);

	for (auto t = 0; t < size1stDimension; t++) arr->push_back(getSBPhysicalVector3<T>(pyArr[t]));

	return arr;

}

/**
 * \brief Converts SBVector<SBVector<SBQuantity::...>*>* to std::vector<std::vector<SBDQuantityWrapperSI>>
 */
template <typename T>
std::vector< std::vector<SBDQuantityWrapperSI> > to2DPyArray(SBVector<SBVector<T>*>* arr) {

	if (arr == nullptr) throw py::value_error("The vector is null");

	std::vector< std::vector<SBDQuantityWrapperSI> > pyArr;

	std::size_t size1stDimension = arr->size();
	std::size_t size2ndDimension = 0;

	if (size1stDimension) size2ndDimension = (*arr)[0]->size();
	else return pyArr;

	for (std::size_t t = 1; t < size1stDimension; t++)
		if ((*arr)[t]->size() != size2ndDimension) throw py::value_error("The vector has the wrong size");

	pyArr.resize(arr->size(), std::vector<SBDQuantityWrapperSI>(size2ndDimension));

	for (std::size_t t = 0; t < size1stDimension; t++)
		for(std::size_t i = 0; i < size2ndDimension; i++)
			pyArr[t][i] = SBDQuantityWrapperSI( (*(*arr)[t])[i] );

	return pyArr;

}

/**
 * \brief Converts SBVector<SBVector<SBPhysicalVector3<SBQuantity::...>>*>* to std::vector<std::vector<SBDTypePhysicalVector3WrapperSI>>
 */
template <typename T>
std::vector< std::vector<SBDTypePhysicalVector3WrapperSI> > to2DPyArray(SBVector<SBVector<SBPhysicalVector3<T>>*>* arr) {

	if (arr == nullptr) throw py::value_error("The vector is null");

	std::vector< std::vector<SBDTypePhysicalVector3WrapperSI> > pyArr;

	unsigned int size1stDimension = arr->size();
	if (size1stDimension == 0) return pyArr;

	unsigned int size2ndDimension = (*arr)[0]->size();

	for (unsigned int t = 1; t < size1stDimension; t++)
		if ((*arr)[t]->size() != size2ndDimension) throw py::value_error("The vector has the wrong size");

	pyArr.resize(arr->size(), std::vector<SBDTypePhysicalVector3WrapperSI>(size2ndDimension));

	for (unsigned int t = 0; t < size1stDimension; t++)
		for(unsigned int i = 0; i < size2ndDimension; i++)
			pyArr[t][i] = SBDTypePhysicalVector3WrapperSI( (*(*arr)[t])[i] );

	return pyArr;

}

/**
 * \brief Converts std::vector<std::vector<SBDQuantityWrapperSI>> to SBVector<SBVector<SBQuantity::...>*>*
 */
template <typename T>
SBVector<SBVector<T>*>* from2DPyArray (std::vector< std::vector<SBDQuantityWrapperSI> >& pyArr) {

	std::size_t size1stDimension = pyArr.size();
	std::size_t size2ndDimension = 0;

	SBVector<SBVector<T>*>* arr = new SBVector<SBVector<T>*>(size1stDimension);

	for (std::size_t t = 0; t < size1stDimension; t++) {

		size2ndDimension = pyArr[t].size();

		SBVector<T>* currentArrT = new SBVector<T>(size2ndDimension);

		for(std::size_t i = 0; i < size2ndDimension; i++)
			currentArrT->push_back(getSBQuantity<T>(pyArr[t][i]));

		arr->push_back(currentArrT);

	}

	return arr;

}

/**
 * \brief Converts std::vector<std::vector<SBDTypePhysicalVector3WrapperSI>> to SBVector<SBVector<SBPhysicalVector3<SBQuantity::...>>*>*
 */
template <typename T>
SBVector<SBVector<SBPhysicalVector3<T>>*>* from2DPyArray (std::vector< std::vector<SBDTypePhysicalVector3WrapperSI> >& pyArr) {

	auto size1stDimension = pyArr.size();

	SBVector<SBVector<SBPhysicalVector3<T>>*>* arr = new SBVector<SBVector<SBPhysicalVector3<T>>*>(size1stDimension);

	for (auto t = 0; t < size1stDimension; t++) {

		auto size2ndDimension = pyArr[t].size();

		SBVector<SBPhysicalVector3<T>>* currentArrT = new SBVector<SBPhysicalVector3<T>>(size2ndDimension);

		for(auto i = 0; i < size2ndDimension; i++)
			currentArrT->push_back(getSBPhysicalVector3<T>(pyArr[t][i]));

		arr->push_back(currentArrT);

	}

	return arr;

}

} // namespace

#endif
