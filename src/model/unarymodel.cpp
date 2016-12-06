#include "unarymodel.hpp"

/*
 *
 * Description :
 *
 *
*/

using namespace satap;

UnaryModel::UnaryModel() {
	//
}

UnaryModel::UnaryModel(BlockCompositeModel* operand) {
	this->_operand = operand;
}

UnaryModel::UnaryModel(const UnaryModel & unaryModel) {
	this->_operand = unaryModel._operand;
}

UnaryModel::~UnaryModel() {
	//
}

BlockCompositeModel* UnaryModel::getOperand() {
	return this->_operand;
}

void UnaryModel::setOperand(BlockCompositeModel* operand) {
	this->_operand = operand;
}

