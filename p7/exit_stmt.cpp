#include <iostream>
#include "exit_stmt.h"

Exit_stmt::Exit_stmt(Expression *my_expr, int my_line)
{
	m_expr = my_expr;
	m_line = my_line;
}

void Exit_stmt::execute()
{
	std::cout << "gpl[" << m_line << "]: exit(" << m_expr->eval_int() << ")" << std::endl;	
	exit(m_expr->eval_int());
}
