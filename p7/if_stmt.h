#ifndef IF_STMT
#define IF_STMT

#include <iostream>
#include "statement.h"
#include "statement_block.h"
#include "expression.h"

class If_stmt: public Statement
{
	public:
		If_stmt(Expression*, Statement_block*, Statement_block *my_else = NULL);
		void execute();

	private:
		Expression *m_expr;
		Statement_block *m_if;
		Statement_block *m_else;
};
#endif
