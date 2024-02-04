#include <iostream>
#include "expr.h"
#include "unary.h"
#include "binary.h"

//example testcase to run
int main() {
{
   sym::Var v = "v";
   sym::Const c = -2;
   sym::Const cc = 0;
   sym::NegOp n = cc.eval();

   sym::Expr e = v*n +c;
   std::cout << e << std::endl;
   std::cout << *(e.diff(v)) << std::endl;
   std::cout << (e==c) << std::endl;
}

return 0 ;
}
