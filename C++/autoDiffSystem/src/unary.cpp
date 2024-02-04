#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
	bool NegOp::is_neg() const {return true; }

	__expr_t* NegOp::eval(const var_map_t& vars) const {
		const Const* a = dynamic_cast<const Const*>(operand);
		if(a!= nullptr && a->is_con()){
			return new sym::Const(-(a->get_value()));
		}
		else{
			return new sym::NegOp(operand->eval());
		}
	 }

	__expr_t* NegOp::diff(const std::string& v) const {
		return new sym::NegOp(operand->diff(std::string(v)));
	 }

	std::ostream& NegOp::operator<< (std::ostream &out) const {
		if(this->operand->is_nullary()){
			out << "-" << *(this->operand);
		}
		else{
			out << "-" << "(" << *(this->operand) << ")";
		}
		return out;
	 }

	bool NegOp::operator==(const __expr_t& other_) const { 
		const NegOp* a = dynamic_cast<const NegOp*>(&other_);
		if(a==nullptr) return false;
		return a->operand == this->operand ? true : false;
	}
}

namespace sym 
{
	bool ExpOp::is_exp() const {return true; }

	__expr_t* ExpOp::eval(const var_map_t& vars) const {
		const Const* a = dynamic_cast<const Const*>(operand);
		if(a == nullptr){
			return new ExpOp(operand->eval());
		}
		else{
			return new Const(std::exp(a->get_value()));
		}
	 }

	__expr_t* ExpOp::diff(const std::string& v) const {
		auto a = operand->diff(v);
		return new MulOp(a, new ExpOp(operand->eval()));
	 }

	std::ostream& ExpOp::operator<< (std::ostream &out) const {
		out << "e^";
		if(operand->is_nullary()) out << *operand;
		else out << "(" << *operand << ")"; 
		return out;
	 }

	bool ExpOp::operator==(const __expr_t& other_) const {
		const ExpOp* a = dynamic_cast<const ExpOp*>(&other_);
		if(a==nullptr) return false;
		return a->operand == this->operand ? true : false;
	 }
}
