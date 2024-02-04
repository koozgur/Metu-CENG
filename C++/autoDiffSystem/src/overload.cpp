#include "nullary.h"
#include "unary.h"
#include "binary.h"

namespace sym {
	//__expr_t dediği bir interface, derived edenler bu fonksiyonları implement edicek
	__expr_t& operator-(const __expr_t &op) {
		if(op.is_nullary()){
			return *(new NegOp(op.eval()));
		}
		return *(new NegOp(&op));
	}
	__expr_t& exp(const __expr_t &op) {
		if(op.is_nullary())
			return *(new ExpOp(op.eval())); 
		return *(new ExpOp(&op));
	}

	__expr_t& operator+(const __expr_t &lhs, const __expr_t &rhs) {
		if(lhs.is_nullary()){
			if(rhs.is_nullary())
				return *(new AddOp(lhs.eval(),rhs.eval()));
			return *(new AddOp(lhs.eval(),&rhs));
		}
		else{
			if(rhs.is_nullary())
				return *(new AddOp(&lhs,rhs.eval()));
			return *(new AddOp(&lhs,&rhs));
		}
	}
	__expr_t& operator+(double lhs, const __expr_t &rhs) {
		if(rhs.is_nullary()){
			return *(new AddOp(new Const(lhs), rhs.eval()));
		}
		return *(new AddOp(new Const(lhs),&rhs));
	 }
	__expr_t& operator+(const __expr_t &lhs, double rhs) {
		if(lhs.is_nullary()){
			return *(new AddOp(lhs.eval(),new Const(rhs)));
		}
		return *(new AddOp(&lhs,new Const(rhs))); 
	 }


	__expr_t& operator*(const __expr_t &lhs, const __expr_t &rhs) {
		if(lhs.is_nullary()){
			if(rhs.is_nullary())
				return *(new MulOp(lhs.eval(),rhs.eval()));
			std::cout << "EEE!\n";
			return *(new MulOp(lhs.eval(),&rhs));
		}
		else{
			if(rhs.is_nullary())
				return *(new MulOp(&lhs,rhs.eval()));
			return *(new MulOp(&lhs,&rhs));
		}
	}
	__expr_t& operator*(double lhs, const __expr_t &rhs) {
		if(rhs.is_nullary()){
			return *(new MulOp(new Const(lhs), rhs.eval()));
		}
		return *(new MulOp(new Const(lhs),&rhs));
	}
	__expr_t& operator*(const __expr_t &lhs, double rhs) {
		if(lhs.is_nullary()){
			return *(new MulOp(lhs.eval(),new Const(rhs)));
		}
		return *(new MulOp(&lhs,new Const(rhs))); 
	}
}
