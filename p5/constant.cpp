#include "constant.h"
#include <sstream>

int Constant::get_int_value() 
{
  return m_union_value.union_int;
}

double Constant::get_double_value() 
{
  return m_union_value.union_double;
}

std::string Constant::get_string_value() 
{
  return *m_union_value.union_string;
}
