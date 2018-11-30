#pragma once

#include "SBStructuralModel.hpp"

/// This class represents an example of a custom class based on SBStructuralModel

class CustomStructuralModel : public SBStructuralModel {

public:

	/// \name Constructors and destructors
	//@{

	CustomStructuralModel() : SBStructuralModel() {}

	//@}

	/// \name Custom functions
	//@{

	bool				hasCustomComment() const;
	std::string const&	getCustomComment() const;
	void				setCustomComment(const std::string& str);
	void				clearCustomComment();

	//@}

private:

	std::string			customComment;

};
