#include "core.h"


namespace sym {
	bool __expr_t::is_unary() const {return false; }
	bool __expr_t::is_binary() const {return false; }
	bool __expr_t::is_nullary() const {return false; }
}
