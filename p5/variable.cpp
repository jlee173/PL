#include <iostream>
#include "variable.h"
#include "expression.h"
#include "symbol.h"

Variable::Variable(Symbol *my_sym)
{
  m_type = my_sym->get_type();
  m_sym = my_sym;
}

Gpl_type Variable::get_type()
{
  return m_type;
}

int Variable::get_int_val()
{
  return m_sym->get_int(); 
}

double Variable::get_double_val()
{
  return m_sym->get_double();
}

std::string Variable::get_string_val()
{
  return m_sym->get_string();
}

