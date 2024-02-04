#include "type.h"

namespace sym 
{
	
	__nullary_op_t::~__nullary_op_t() {  }

	bool __nullary_op_t::is_nullary() const {return true; }

	bool __nullary_op_t::is_con() const {return false; }
	bool __nullary_op_t::is_var() const {return false; }

}

namespace sym 
{
	__unary_op_t::~__unary_op_t() {
		if(operand != nullptr){
			delete operand; 
			operand = nullptr;
		}
	}

	bool __unary_op_t::is_unary() const {return true; }

	bool __unary_op_t::is_neg() const {return false; }
	bool __unary_op_t::is_exp() const {return false; }

}

namespace sym 
{
	__binary_op_t::~__binary_op_t() {
		if(lhs_ != nullptr) {
			delete lhs_;
			lhs_ = nullptr;
		}
		if(rhs_ != nullptr){
			delete rhs_;
			rhs_ = nullptr;
		} 
	}

	bool __binary_op_t::is_binary() const {return true; }

	bool __binary_op_t::is_add() const {return false; }
	bool __binary_op_t::is_mul() const { return false;}

}
