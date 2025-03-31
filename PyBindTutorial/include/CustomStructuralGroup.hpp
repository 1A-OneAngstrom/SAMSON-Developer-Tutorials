#pragma once

#include "SBStructuralGroup.hpp"

/// This class represents an example of a custom class based on SBStructuralGroup

class CustomStructuralGroup : public SBStructuralGroup {

public:

	/// \name Constructors and destructors
	//@{

	CustomStructuralGroup() : SBStructuralGroup() {}
	CustomStructuralGroup(const std::string &name) : SBStructuralGroup(name) {}

	//@}

	/// \name Custom functions
	//@{

	bool															hasCustomComment() const;
	std::string const&												getCustomComment() const;
	void															setCustomComment(const std::string& str);
	void															clearCustomComment();

	//@}

private:

	std::string														customComment;

};
