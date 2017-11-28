#include<iostream>
#include "print_stmt.h"

Print_stmt::Print_stmt(Expression *my_expr, int line)
{
	m_expr = my_expr;
	m_line = line;
}

void Print_stmt::execute()
{
	std::cout << "print[" << m_line << "]: " << m_expr->eval_string() << std::endl;
}
