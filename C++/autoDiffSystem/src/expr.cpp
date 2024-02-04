#include "expr.h"

namespace sym 
{
	Expr::Expr(const Const& c) {expr_ = c.eval(); }
	Expr::Expr(const Var& v) {expr_ = v.eval(); }
	Expr::Expr(const __expr_t* e) {expr_ = e; }
	Expr::Expr(const __expr_t& e) {expr_ = &e; }
	Expr::Expr(const Expr& e) {expr_ = e.expr_;}
		
	Expr::~Expr() {
		if(expr_ != nullptr) {
			delete expr_;
			expr_ = nullptr;
		}
		
	 }

	__expr_t* Expr::eval(const var_map_t& var_map) const {
		return new Expr(expr_->eval());
	 }
	__expr_t* Expr::diff(const std::string& v) const {
		auto a = expr_->diff(v);
		return a;
	 }
	std::ostream& Expr::operator<< (std::ostream &out) const {
		auto b = expr_->eval(); 
		out << *b;
		delete b;
		return out;
	}
	bool Expr::operator==(const Expr& other) const {
		if(*(other.expr_) == *(this->expr_)) return true;
		else return false;
	 }
	bool Expr::operator==(const __expr_t& other) const {
		if(other == *(this->expr_)) return true;
		else return false;
	 }
}                                                                   	
