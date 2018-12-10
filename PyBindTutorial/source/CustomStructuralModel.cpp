#include "CustomStructuralModel.hpp"

bool CustomStructuralModel::hasCustomComment() const {

	if (customComment.size() == 0)
		return false;
	else
		return true;

}

std::string const& CustomStructuralModel::getCustomComment() const {

	return customComment;

}

void CustomStructuralModel::setCustomComment(const std::string& str){

	customComment = str;

}

void CustomStructuralModel::clearCustomComment(){

	customComment.clear();

}
