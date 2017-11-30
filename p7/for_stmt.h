#ifndef FOR_STMT
#define FOR_STMT

#include<iostream>
#include "statement.h"
#include "expression.h"
#include "statement_block.h"


class For_stmt: public Statement
{
	public:
		For_stmt(Statement_block*, Statement_block*, Statement_block*, Expression*);
		void execute();


	private:
		Statement_block *init;
		Statement_block *increment;
		Statement_block *body;
		Expression *m_expr;

};
#endif
