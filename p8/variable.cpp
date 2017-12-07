#include <iostream>
#include "variable.h"
#include "expression.h"
#include "symbol.h"
#include "error.h"

Variable::Variable(Symbol *my_sym)
{
  // m_type = (Gpl_type)(my_sym->get_type() - ARRAY);
	m_type = my_sym->get_base_type();
  m_sym = my_sym;
}

Variable::Variable(Symbol *my_sym, Expression *my_expr)
{
  // m_type = (Gpl_type)(my_sym->get_type() - ARRAY);
	m_type = my_sym->get_base_type();
	m_sym = my_sym;
 	m_expr = my_expr;
}

Variable::Variable(Symbol *my_sym, std::string my_field)
{
	Game_object *my_game_obj;
	m_sym = my_sym;
	my_game_obj = my_sym->get_game_object_value();
  Status status =	my_game_obj->get_member_variable_type(my_field, m_type);
	if(status == OK)
 	{
		m_field = my_field;
	}
}

Variable::Variable(Symbol *my_sym, Expression *my_expr, std::string my_field)
{
  Game_object *my_game_obj;
  m_sym = my_sym;
  my_game_obj = my_sym->get_game_object_value();
  Status status = my_game_obj->get_member_variable_type(my_field, m_type);
	m_expr = my_expr;
  if(status == OK)
  {
    m_field = my_field;
  }
}	

Gpl_type Variable::get_type()
{
		return m_type;
	/*
	if(m_field == "")
	{
  	Gpl_type tmp = m_sym->get_type();
		if (tmp & ARRAY)
      return (Gpl_type)(tmp - ARRAY);
  	else return m_sym->get_type();
	}
	else
	{
		return m_type;
	}
	*/
}

int Variable::get_int_val()
{

	/*
  if (m_field == "" && m_expr == NULL)
  {
	  return m_sym->get_int();
  }

	if (m_filed == "" && m_expr != NULL)
	{
	  return m_sym->get_int(m_expr->eval_int());
  }
  
  // we know tha m_field is NOT empty
	*/
	if (m_expr != NULL)
	  return m_sym->get_int(m_expr->eval_int(),m_field);


  Game_object *game_obj;
  int my_val;
  if(m_sym->get_size() == -1) {
    if(m_field == "")
    { 
      return m_sym->get_int();
    }
    else
    {
      game_obj = m_sym->get_game_object_value();
      Status status = game_obj->get_member_variable(m_field, my_val);
			assert(status == OK);
      return my_val;
    }
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
	return m_sym->get_int(m_expr->eval_int(), m_field);
}

double Variable::get_double_val()
{
	if (m_expr != NULL)
	return m_sym->get_double(m_expr->eval_int(),m_field);

	Game_object *game_obj;
	double my_val;
	if(m_sym->get_size() == -1)
	{
		if(m_field == "")
		{
			return m_sym->get_double(); 
		}
		else
		{
			game_obj = m_sym->get_game_object_value();
			game_obj->get_member_variable(m_field, my_val);			
			return my_val;
		}
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
	return m_sym->get_double(m_expr->eval_int(), m_field);
}


std::string Variable::get_string_val()
{
	if (m_expr != NULL)
	return m_sym->get_string(m_expr->eval_int(),m_field);

  Game_object *game_obj;
  std::string my_val;
  if(m_sym->get_size() == -1)
  {
    if(m_field == "")
    { 
      return m_sym->get_string();
    }
    else
    {
      game_obj = m_sym->get_game_object_value();
      game_obj->get_member_variable(m_field, my_val);
      return my_val;
		}
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
	return m_sym->get_string(m_expr->eval_int(), m_field);
}


int Variable::get_int_index(int index)
{

  return m_sym->get_int(index, m_field);
}

double Variable::get_double_index(int index)
{
  return m_sym->get_double(index, m_field);
}

std::string Variable::get_string_index(int index)
{
  return m_sym->get_string(index, m_field);
}

Animation_block* Variable::get_animation_block_val()
{
	return m_sym->get_animation_block_value();
}

Game_object* Variable::get_game_object_value()
{
	return m_sym->get_game_object_value();
}

std::string Variable::get_id()
{
	if(m_field == "")
		return m_sym->get_id();
	else
		return (m_sym->get_id() + "." + m_field);
}

void Variable::assign(Expression* my_expr, Assign_operator my_assign)
{
	if(m_expr == NULL && m_field == "")
	{
		m_sym->assign(my_expr, my_assign);
	}
	else if(m_expr == NULL && m_field != "")
	{
		m_sym->assign(m_field, my_expr, my_assign);
	}
	else if(m_expr != NULL && m_field == "")
	{
		m_sym->assign(m_expr->eval_int(), my_expr, my_assign);
	}
	else if(m_expr != NULL && m_field != "")
	{
		m_sym->assign(m_field, m_expr->eval_int(), my_expr, my_assign);
	}
}


/*
// eval expression if there is one, return index
// if index is out of bounds, issue error, return 0 (0 is always in bounds)
int Variable::eval_index_with_error_checking() 
{
  assert(m_expression); // should only be called if this is an array

	int index = m_expression->eval_int();

	// an annoying special case
	// if the index is -1 it confuses symbol that uses -1 for
	//   not an array
	if (m_symbol->index_within_range(index))
	{
		return index;
	}
	else
	{
		ostringstream index_stream;
		index_stream << index;
		Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, m_symbol->get_name(),index_stream.str());

		return 0; // 0 is always within range
	}
}
*/
