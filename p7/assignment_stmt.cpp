#include<iostream>
#include "assignment_stmt.h"

Assignment_stmt::Assignment_stmt(Variable *my_var, Expression *my_expr, Assign_operator my_assign)
{
	my_var = m_var;
	my_expr = m_expr;
	my_assign = m_assign;
}

void Assignment_stmt::execute()
{
	m_var->assign(m_expr, m_assign);
}
