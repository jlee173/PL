#include<iostream>
#include "for_stmt.h"

For_stmt::For_stmt(Statement_block *my_init, Statement_block *my_increment, Statement_block *my_body, Expression *my_expr)
{
  init = my_init;
	increment = my_increment;
	body = my_body;
	m_expr = my_expr;
}

void For_stmt::execute()
{
	for((init->execute()); (m_expr->eval_int()); (increment->execute()))
	{
		body->execute();
	}
}
