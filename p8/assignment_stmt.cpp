#include<iostream>
#include "assignment_stmt.h"

Assignment_stmt::Assignment_stmt(Variable *my_var, Expression *my_expr, Assign_operator my_assign)
{
	m_var = my_var;
	m_expr = my_expr;
	m_assign = my_assign;
}

void Assignment_stmt::execute()
{
	m_var->assign(m_expr, m_assign);
}
