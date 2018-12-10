#include "CustomStructuralGroup.hpp"

bool CustomStructuralGroup::hasCustomComment() const {

	if (customComment.size() == 0)
		return false;
	else
		return true;

}

std::string const& CustomStructuralGroup::getCustomComment() const {

	return customComment;

}

void CustomStructuralGroup::setCustomComment(const std::string& str){

	customComment = str;

}

void CustomStructuralGroup::clearCustomComment(){

	customComment.clear();

}
