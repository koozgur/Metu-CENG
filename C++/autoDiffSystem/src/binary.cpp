#include "binary.h"
#include "nullary.h"
#include <math.h>

namespace sym 
{
	bool AddOp::is_add() const { return true;}

	__expr_t* AddOp::eval(const var_map_t& vars) const {
		auto l_eval = lhs_->eval();
		auto r_eval = rhs_->eval();
		const Const* lhs_check = dynamic_cast<const Const*>(l_eval);
		const Const* rhs_check = dynamic_cast<const Const*>(r_eval);
		
		if( (lhs_check != nullptr) && (lhs_check->get_value()==0.0))
			return rhs_->eval(vars);
		else if( (rhs_check != nullptr) && (rhs_check->get_value()==0.0))
			return lhs_-> eval(vars);
		else if( (lhs_check != nullptr) && (lhs_check!=nullptr))
		 	return new Const(lhs_check->get_value()+rhs_check->get_value());
		else{
			return new AddOp(lhs_,rhs_);
		}
		
	 }

	__expr_t* AddOp::diff(const std::string& v) const {
		auto a = new AddOp((lhs_->diff(v))->eval(),(rhs_->diff(v))->eval());
		auto b = a->eval();
		return b;
	 }

	std::ostream& AddOp::operator<< (std::ostream &out) const {
		/* modifiyeler var*/
		const Const* a = dynamic_cast<const Const*>(lhs_);
		const Const* b = dynamic_cast<const Const*>(rhs_);

		if((a!= nullptr) && (a->get_value()==0)){
			out << *rhs_;
			return out;
		}
		else if((b!=nullptr) && (b->get_value()==0)){
			out << *lhs_;
			return out;
		}

		if(lhs_->is_nullary()) out << *lhs_;
		else out << "(" << *lhs_ << ")"; 

		out << " + ";

		if(rhs_->is_nullary()) out << *rhs_;
		else out << "(" << *rhs_ << ")";
		return out;
	 }

	bool AddOp::operator==(const __expr_t& other_) const {
		const AddOp* a = dynamic_cast<const AddOp*>(&other_);
		if(a == nullptr) return false;
		if( (*(a->lhs_) == *lhs_) && ( *(a->rhs_)== *rhs_) ) return true;
		else if ( (*lhs_ == *(a->rhs_)) && (*rhs_ == *(a->lhs_))) return true;
		else return false;
	 }
}

namespace sym 
{
	bool MulOp::is_mul() const {return true; }

	__expr_t* MulOp::eval(const var_map_t& vars) const {
		auto l_eval = lhs_->eval();
		auto r_eval = rhs_->eval();
		const Const* a = dynamic_cast<const Const*>(l_eval);
		const Const* b = dynamic_cast<const Const*>(r_eval);

		if(*l_eval == Const(0.0))	return new Const(0.0);
		else if(*r_eval == Const(0.0)) return new Const(0.0);
		else if(*l_eval == Const(1.0)) return r_eval;
		else if(*r_eval == Const(1.0)) return l_eval;
		else if((a != nullptr) && (b != nullptr)) return new Const(a->get_value() * b->get_value());
		else return new MulOp(l_eval,r_eval);
		
	 }

	__expr_t* MulOp::diff(const std::string& v) const {
		auto l_dif = (lhs_->diff(v));
		auto r_dif = (rhs_->diff(v));
		auto c = new AddOp((new MulOp(l_dif,rhs_))->eval(), (new MulOp(lhs_,r_dif))->eval());
		return c->eval();
	 }

	std::ostream& MulOp::operator<< (std::ostream &out) const {
		const Const* a = dynamic_cast<const Const*>(lhs_);
		const Const* b = dynamic_cast<const Const*>(rhs_);
		if((a!= nullptr) && (a->get_value()==0)){
			out << 0;
			return out;
		}
		else if((b!=nullptr) && (b->get_value()==0)){
			out << 0;
			return out;
		}

		if((a!= nullptr) && (a->get_value()==1)){
			out << *rhs_;
			return out;
		}
		else if((b!=nullptr) && (b->get_value()==1)){
			out << *lhs_;
			return out;
		}

		if(lhs_->is_nullary()) out << *lhs_;
		else out << "(" << *lhs_ << ")"; 
		out << " * ";
		if(rhs_->is_nullary()) out << *rhs_;
		else out << "(" << *rhs_ << ")";
		return out;
	}

	bool MulOp::operator==(const __expr_t& other_) const {
		const MulOp* a = dynamic_cast<const MulOp*>(&other_);
		if(a == nullptr) return false;
		if( (*(a->lhs_) == *lhs_) && ( *(a->rhs_)== *rhs_) ) return true;
		else if ( (*lhs_ == *(a->rhs_)) && (*rhs_ == *(a->lhs_))) return true;
		else return false;
	 }
	 
}
