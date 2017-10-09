#include "symbol.h"

Symbol::Symbol(int value, std::string name)
{
    m_value_ptr = (void*) new int(value);
    m_type = INT;
    m_id = name;
    m_size = -1;

}

Symbol::Symbol(double value, std::string name)
{
    m_value_ptr = (void*) new double(value);
    m_type = DOUBLE;
    m_id = name;
    m_size = -1;
}


Symbol::Symbol(std::string value, std::string name)
{
    m_value_ptr = (void*) new std::string(value); 
    m_type = STRING;
    m_id = name;
    m_size = -1;

}

/*Symbol::Symbol(Gpl_type data, std::string name)
{
  if( data == INT) 
  {
    m_value_ptr = (void*) new int(0);
    m_type = INT;
  }
  if( data == DOUBLE)
  {
    m_value_ptr = (void*) new double(0.0);
    m_type = DOUBLE;
  }
  if( data == STRING)
  {
    m_value_ptr = (void*) new std::string(""); 
    m_type = STRING;
  }
  m_id = name;
  m_size = -1;
}
*/

Symbol::Symbol(Gpl_type data, std::string name, int size)
{
  if( data == INT)
  {
    m_value_ptr = (void*) new int[size];
    for( int i = 0; i < size; i++)
    {
    *((int*)m_value_ptr+i) = 0;
    }
	m_type = INT_ARRAY;
  }
  if( data == DOUBLE)
  {
    m_value_ptr = (void*) new double[size];
    for( int i = 0; i < size; i++)
    {
    *((double*)m_value_ptr+i) = 0.0;
    }
    m_type = DOUBLE_ARRAY;
  }
  if( data == STRING)
  {
    m_value_ptr = (void*) new std::string[size];
    for( int i = 0; i < size; i++)
    {
    *((std::string*)m_value_ptr+i) = "";
    }
    m_type = STRING_ARRAY;
  }
  m_id = name;
  m_size = size;
}


void Symbol::print()
{
  if(m_type == INT)
  {
    std::cout << gpl_type_to_string(m_type) << " " << m_id << " = " << *((int*)m_value_ptr) << std::endl;
  }
if(m_type == DOUBLE)
  {
    std::cout << gpl_type_to_string(m_type) << " " << m_id << " = " << *((double*)m_value_ptr) << std::endl;
  }
if(m_type == STRING)
  {
    std::cout << gpl_type_to_string(m_type) << " " << m_id << " = \"" << *((std::string*)m_value_ptr) << "\"" << std::endl;
  }
if(m_type == INT_ARRAY)
  {
    for( int i = 0; i < m_size; i++)
    {
      std::cout << gpl_type_to_base_string(m_type) << " " << m_id << "[" << i << "]" << " = "  << *((int*)m_value_ptr+i) << std::endl;
    }
  }
if(m_type == DOUBLE_ARRAY)
  {
    for( int i = 0; i < m_size; i++)
    {
      std::cout << gpl_type_to_base_string(m_type) << " " << m_id << "[" << i << "]" << " = "  << *((double*)m_value_ptr+i) << std::endl;
    }
  } 
if(m_type == STRING_ARRAY)
  {
    for( int i = 0; i < m_size; i++)
    {
      std::cout << gpl_type_to_base_string(m_type) << " " << m_id << "[" << i << "]" << " = \""  << *((std::string*)m_value_ptr+i) << "\"" << std::endl;
    }
  }
}

std::string Symbol::get_id()
{ 
  return m_id;
}

Gpl_type Symbol::get_type()
{
  if(m_size > 0)
  {
    return (Gpl_type)(m_type-ARRAY);
  }
  else
    return m_type;
}

int Symbol::get_int()
{
  return *((int*)(m_value_ptr));
}

double Symbol::get_double()
{
  return *((double*)(m_value_ptr));
}

std::string Symbol::get_string()
{
  return *((std::string*)(m_value_ptr));
}

