#ifndef ASSIGNMENT_STMT
#define ASSIGNMENT_STMT


#include <iostream>
#include "statement.h"
#include "gpl_type.h"
#include "variable.h"
#include "expression.h"


class Assignment_stmt: public Statement
{
	public:
		Assignment_stmt(Variable*, Expression*, Assign_operator);
		void execute();


	private:
		Variable *m_var;
		Expression *m_expr;
		Assign_operator m_assign; 				
};
#endif
