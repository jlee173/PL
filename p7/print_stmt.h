#ifndef PRINT_STMT
#define PRINT_STMT

#include <iostream>
#include "statement.h"
#include "expression.h"

class Print_stmt: public Statement
{
	public:
		Print_stmt(Expression*);
		void execute();
	
	private:
		Expression* m_expr;
};
#endif
