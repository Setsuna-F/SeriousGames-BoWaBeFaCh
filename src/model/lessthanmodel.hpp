#ifndef LESSTHANMODEL_HPP
#define LESSTHANMODEL_HPP
#include "binarymodel.hpp"

/*
 *
 * Description :
 *
 *
*/

namespace satap {

	class LessThanModel : BinaryModel {

		public:
			LessThanModel();
			LessThanModel(BlockCompositeModel* firstOperand, BlockCompositeModel* secondOperand);
			LessThanModel(const BinaryModel & binaryModel);
			~LessThanModel();
			std::string execute();
	};
}

#endif	// LESSTHANMODEL_HPP
