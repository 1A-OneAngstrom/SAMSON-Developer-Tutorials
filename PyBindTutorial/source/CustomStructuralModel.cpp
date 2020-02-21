#include "CustomStructuralModel.hpp"

bool CustomStructuralModel::hasCustomComment() const {

	return (customComment.size() != 0);

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
