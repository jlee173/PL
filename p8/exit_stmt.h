#ifndef EXIT_STMT
#define EXIT_STMT


#include <iostream>
#include "statement.h"
#include "expression.h"

class Exit_stmt: public Statement
{
	public:
		Exit_stmt(Expression*, int);
		void execute();

	private:
		Expression *m_expr;
		int m_line;
};
#endif
