#include<iostream>
#include "print_stmt.h"

Print_stmt::Print_stmt(Expression *my_expr)
{
	m_expr = my_expr;
}

void Print_stmt::execute()
{
	std::cout << m_expr->eval_string() << std::endl;
}
