#include "CustomStructuralGroup.hpp"

bool CustomStructuralGroup::hasCustomComment() const {

	return (customComment.size() != 0);

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
