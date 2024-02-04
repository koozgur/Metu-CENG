#include "type.h"
#include "nullary.h"

namespace sym
{
	double Const::get_value() const { return value_; }
	Const::operator double() const { return value_; }

	 bool Const::is_con() const {return true;}   

	__expr_t *Const::eval(const var_map_t &var_map) const
	{
		 // memory leak'e dikkat edilmeli
		return new sym::Const(value_);
	}

	__expr_t *Const::diff(const std::string &v) const { return new sym::Const(0); }

	std::ostream &Const::operator<<(std::ostream &out) const
	{
		out << value_;
		return out;
	}

	bool Const::operator==(const __expr_t &other) const
	{
		const Const* a = dynamic_cast<const Const*>(&other);
		if(a == nullptr) return false;
		return a->value_ == this->value_ ? true : false; 
	}
}

namespace sym
{
	std::string Var::get_variable() const {return var_;}
	Var::operator std::string() const {return var_;} //? hani pointerdı??

	bool Var::is_var() const {return true;}

	__expr_t *Var::eval(const var_map_t &vars) const {
		if (vars.count(var_) == 1){
			return new sym::Const(vars.find(var_)->second);
		}
		else{
			return new sym::Var(var_);
		}
	}

	__expr_t *Var::diff(const std::string &v) const {
		return (v==var_) ? new sym::Const(1) : new sym::Const(0);
	}

	std::ostream &Var::operator<<(std::ostream &out) const {
		out << var_;
		return out;
	}

	bool Var::operator==(const __expr_t &other) const {
		const Var* a = dynamic_cast<const Var*>(&other);
		if(a==nullptr) return false;
		return a->var_ == this->var_ ? true : false; 
	}
}
