#include <iostream>
#include "expr.h"
#include "unary.h"
#include "binary.h"

int main() {
{
   //simple test case to check
   /*
   sym::Var x = "x", y = "y";
   sym::Expr f = 2.0 * y + x;
   auto f_y = f.diff(y);
   sym::Const val = 2;
   auto sanity = (*f_y == val ? "pass" : "fail");
   std::cout << "check: " << sanity << std::endl;
   std::cout << *(f_y->eval()) << std::endl;
   */

   //another test case
    sym::Var y="y";
    sym::Const c=2.0;
    sym::MulOp op(c.eval(), y.eval());
    std::cout << op << std::endl;
}

return 0 ;
}
