#include<iostream>
#include "if_stmt.h"

If_stmt::If_stmt(Expression *my_expr, Statement_block *my_if, Statement_block *my_else)
{
	m_expr = my_expr;
	m_if = my_if;
	m_else = my_else;
}

void If_stmt::execute()
{
	if(m_expr->eval_int())
	{
		m_if->execute();
	}
	else if(m_else != NULL)
	{
		m_else->execute();
	}	
}
