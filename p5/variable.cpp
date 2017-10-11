#include <iostream>
#include "variable.h"
#include "expression.h"
#include "symbol.h"
#include "error.h"

Variable::Variable(Symbol *my_sym)
{
  m_type = (Gpl_type)(my_sym->get_type() - ARRAY);
  m_sym = my_sym;
}

Variable::Variable(Symbol *my_sym, Expression *my_expr)
{
  m_type = (Gpl_type)(my_sym->get_type() - ARRAY);
	m_sym = my_sym;
 	m_expr = my_expr;
}

Gpl_type Variable::get_type()
{
  return m_sym->get_type();
}

int Variable::get_int_val()
{
	if(m_sym->get_size() < 1)
	{
  	return m_sym->get_int(); 
	}
	if(m_expr == NULL)
	{
		Error::error(Error::VARIABLE_IS_AN_ARRAY, m_sym->get_id());
		return 0;
	}
	if(m_expr->eval_int() < 0)
	{
		Error::error(Error::INVALID_ARRAY_SIZE, m_sym->get_id(), std::to_string(m_expr->eval_int()));
		return 0;
	}
	if(m_expr->eval_int() >= m_sym->get_size())
	{
		Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, m_sym->get_id(), std::to_string(m_expr->eval_int()));
		return 0;
	}
	return m_sym->get_int(m_expr->eval_int());
}

double Variable::get_double_val()
{
	if(m_sym->get_size() == -1)
  	return m_sym->get_double(); 

	if(m_expr == NULL)
	{
		Error::error(Error::VARIABLE_IS_AN_ARRAY, m_sym->get_id());
		return 0;
	}
	if(m_expr->eval_int() < 0)
	{
		Error::error(Error::INVALID_ARRAY_SIZE, m_sym->get_id(), std::to_string(m_expr->eval_int()));
		return 0;
	}
	if(m_expr->eval_int() >= m_sym->get_size())
	{
		Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, m_sym->get_id(), std::to_string(m_expr->eval_int()));
		return 0;
	}
	return m_sym->get_double(m_expr->eval_int());
}


std::string Variable::get_string_val()
{
	if(m_sym->get_size() == -1)
  	return m_sym->get_string(); 

	if(m_expr == NULL)
	{
		Error::error(Error::VARIABLE_IS_AN_ARRAY, m_sym->get_id());
		return 0;
	}
	if(m_expr->eval_int() < 0)
	{
		Error::error(Error::INVALID_ARRAY_SIZE, m_sym->get_id(), std::to_string(m_expr->eval_int()));
		return 0;
	}
	if(m_expr->eval_int() >= m_sym->get_size())
	{
		Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, m_sym->get_id(), std::to_string(m_expr->eval_int()));
		return 0;
	}
	return m_sym->get_string(m_expr->eval_int());
}


int Variable::get_int_index(int index)
{
  return m_sym->get_int(index);
}

double Variable::get_double_index(int index)
{
  return m_sym->get_double(index);
}

std::string Variable::get_string_index(int index)
{
  return m_sym->get_string(index);
}

