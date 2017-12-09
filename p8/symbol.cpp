#include "symbol.h"
#include "error.h"
#include <sstream>
using std::ostringstream;

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
  if( data == RECTANGLE)
  {
    m_value_ptr = (void*) new Rectangle[size];
    m_type = RECTANGLE_ARRAY;
  }
  if( data == CIRCLE)
  {
    m_value_ptr = (void*) new Circle[size];
    m_type = CIRCLE_ARRAY;
  }
  if( data == TRIANGLE)
  {
    m_value_ptr = (void*) new Triangle[size];
    m_type = TRIANGLE_ARRAY;
  }
  if( data == TEXTBOX)
  {
    m_value_ptr = (void*) new Textbox[size];
    m_type = TEXTBOX_ARRAY;
  }
  if( data == PIXMAP) {
    m_value_ptr = (void*) new Pixmap[size];
    m_type = PIXMAP_ARRAY;
  }
  m_id = name;
  m_size = size;
}

Symbol::Symbol(Gpl_type object_type, std::string name)
{
	if(object_type == CIRCLE)
	{
		m_type = CIRCLE;
		m_value_ptr = (void*) new Circle();
	}
  else if(object_type == RECTANGLE)
  {
    m_type = RECTANGLE;
		m_value_ptr = (void*) new Rectangle();
  }
  else if(object_type == TRIANGLE)
  {
    m_type = TRIANGLE;
		m_value_ptr = (void*) new Triangle();
  }
  else if(object_type == TEXTBOX)
  {
    m_type = TEXTBOX;
		m_value_ptr = (void*) new Textbox();
  }
  else if(object_type == PIXMAP)
  {
    m_type = PIXMAP;
		m_value_ptr = (void*) new Pixmap();
  }
	else if(object_type == ANIMATION_BLOCK)
	{
		m_type = ANIMATION_BLOCK;
		m_value_ptr = (void*) new Animation_block();
	}
	m_id = name;
	m_size = -1;
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
	if(m_type == CIRCLE || m_type == RECTANGLE || m_type == TRIANGLE || m_type == TEXTBOX || m_type == PIXMAP)
	{
		((Game_object*)(m_value_ptr))->print(m_id, std::cout);
		std::cout << std::endl;
	}
	if(m_type == ANIMATION_BLOCK)
		std::cout << gpl_type_to_base_string(m_type) << " " << m_id << std::endl;
	if(m_type == CIRCLE_ARRAY)
	{
	  for(int i = 0; i < m_size; i++)
		{
			((Circle*)m_value_ptr+i)->print(m_id+"["+std::to_string(i)+"]", std::cout);
			std::cout << std::endl;
		}
	}
	if(m_type == RECTANGLE_ARRAY)
	{
	  for(int i = 0; i < m_size; i++)
		{
			((Rectangle*)m_value_ptr+i)->print(m_id+"["+std::to_string(i)+"]", std::cout);
			std::cout << std::endl;
		}
	}
	if(m_type == TRIANGLE_ARRAY)
	{
	  for(int i = 0; i < m_size; i++)
		{
			((Triangle*)m_value_ptr+i)->print(m_id+"["+std::to_string(i)+"]", std::cout);
			std::cout << std::endl;
		}
	}
	if(m_type == TEXTBOX_ARRAY)
	{
	  for(int i = 0; i < m_size; i++)
		{
			((Textbox*)m_value_ptr+i)->print(m_id+"["+std::to_string(i)+"]", std::cout);
			std::cout << std::endl;
		}
	}
	if(m_type == PIXMAP_ARRAY)
	{
	  for(int i = 0; i < m_size; i++)
		{
			((Pixmap*)m_value_ptr+i)->print(m_id+"["+std::to_string(i)+"]", std::cout);
			std::cout << std::endl;
		}
	}

}

void Symbol::set(int dimension)
{
	dimension = *((int*)(m_value_ptr));
}

bool Symbol::is_array()
{
	if(m_size != -1)
		return true;
}

std::string Symbol::get_id()
{ 
  return m_id;
}

Gpl_type Symbol::get_base_type()
{
		if (m_type & ARRAY)
      return (Gpl_type)(m_type - ARRAY);
  	else return m_type;

}
Gpl_type Symbol::get_type(std::string name)
{
	Status status;
	Gpl_type my_type;
	if(!(m_type & GAME_OBJECT) || name == "")
	{	
  	return m_type;
	}
	else
	{
		status = ((Game_object*)m_value_ptr)->get_member_variable_type(name, my_type);
		assert(status == OK);
		return my_type;
	}
}

int Symbol::get_int(std::string field)
{
	Status status;
	int val;
	if(!(m_type & GAME_OBJECT) || field == "")
	{
  	return *((int*)(m_value_ptr));
	}
	else
	{
		status = ((Game_object*)m_value_ptr)->get_member_variable(field, val);
		assert(status == OK);
		return val;
	}
}

double Symbol::get_double(std::string field)
{
	Status status;
	double val;
	if(!(m_type & GAME_OBJECT) || field == "")
	{
  	return *((double*)(m_value_ptr));
	}
	else
	{
		status = ((Game_object*)m_value_ptr)->get_member_variable(field, val);
		assert(status == OK);
		return val;
	}
}

std::string Symbol::get_string(std::string field)
{
	Status status;
	std::string val;
	if(!(m_type & GAME_OBJECT) || field == "")
	{
  	return *((std::string*)(m_value_ptr));
	}
	else
	{
		status = ((Game_object*)m_value_ptr)->get_member_variable(field, val);
		assert(status == OK);
		return val;
	}
}

int Symbol::get_int(int index, std::string m_field)
{
	if(m_type != CIRCLE_ARRAY && m_type != RECTANGLE_ARRAY && m_type != TRIANGLE_ARRAY && m_type != TEXTBOX_ARRAY && m_type != PIXMAP_ARRAY)
	{
		return *((int*)m_value_ptr+index);
	}
		int val;
		Status status;
	switch(m_type)
	{
		case RECTANGLE_ARRAY: status = ((Rectangle*)m_value_ptr+index)->get_member_variable(m_field, val);
					break;
    case CIRCLE_ARRAY: status = ((Circle*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case TRIANGLE_ARRAY: status = ((Triangle*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case TEXTBOX_ARRAY: status = ((Textbox*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case PIXMAP_ARRAY: status = ((Pixmap*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
		default: 
					break;
	}
		assert(status == OK);
		return val;
}

double Symbol::get_double(int index, std::string m_field)
{
	if(m_type != CIRCLE_ARRAY && m_type != RECTANGLE_ARRAY && m_type != TRIANGLE_ARRAY && m_type != TEXTBOX_ARRAY && m_type != PIXMAP_ARRAY)
    return *((double*)m_value_ptr+index);
    double val;
    Status status;
  switch(m_type)
  {
    case RECTANGLE_ARRAY: status = ((Rectangle*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case CIRCLE_ARRAY: status = ((Circle*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case TRIANGLE_ARRAY: status = ((Triangle*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case TEXTBOX_ARRAY: status = ((Textbox*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case PIXMAP_ARRAY: status = ((Pixmap*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    default:
          break;
  }
    assert(status == OK);
    return val;

}

std::string Symbol::get_string(int index, std::string m_field)
{
	if(m_type != CIRCLE_ARRAY && m_type != RECTANGLE_ARRAY && m_type != TRIANGLE_ARRAY && m_type != TEXTBOX_ARRAY && m_type != PIXMAP_ARRAY)
    return *((std::string*)m_value_ptr+index);
    std::string val;
    Status status;
  switch(m_type)
  {
    case RECTANGLE_ARRAY: status = ((Rectangle*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case CIRCLE_ARRAY: status = ((Circle*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case TRIANGLE_ARRAY: status = ((Triangle*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case TEXTBOX_ARRAY: status = ((Textbox*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    case PIXMAP_ARRAY: status = ((Pixmap*)m_value_ptr+index)->get_member_variable(m_field, val);
          break;
    default:
          break;
  }
    assert(status == OK);
    return val;

}

int Symbol::get_size()
{
	return m_size;
}
	
Game_object* Symbol::get_game_object_value()
{
	return (Game_object*)(m_value_ptr);
}

bool Symbol::is_game_object()
{
	return (m_type == CIRCLE || m_type == RECTANGLE || m_type == TRIANGLE || m_type == TEXTBOX || m_type == PIXMAP);
}

void Symbol::set_symbol_to_game_obj(Game_object *argument)
{
	m_value_ptr = (void*)(argument);	
}

Animation_block* Symbol::get_animation_block_value()
{
	return (Animation_block*)(m_value_ptr);
}

Game_object* Symbol::get_game_object_array_value(int size)
{
  if(m_type == RECTANGLE_ARRAY)
  {
    Rectangle *object_ptr = (Rectangle*)m_value_ptr;
		return &(object_ptr[size]);
  }
  if(m_type == CIRCLE_ARRAY)
  {
    Circle *object_ptr = (Circle*)m_value_ptr;
		return &(object_ptr[size]);
  }
  if(m_type == TRIANGLE_ARRAY)
  {
    Triangle *object_ptr = (Triangle*)m_value_ptr;
		return &(object_ptr[size]);
  }
  if(m_type == TEXTBOX_ARRAY)
  {
    Textbox *object_ptr = (Textbox*)m_value_ptr;
		return &(object_ptr[size]);
  }
  if(m_type == PIXMAP_ARRAY)
  {
    Pixmap *object_ptr = (Pixmap*)m_value_ptr;
		return &(object_ptr[size]);
  }
	return NULL;
}
	
void Symbol::assign(Expression *my_expr, Assign_operator my_assign)
{
	if(m_type == INT)
	{
		if(my_assign == ASSIGN)
			*((int*)m_value_ptr) = (my_expr->eval_int());
		if(my_assign == PLUS_ASSIGN)
			*((int*)m_value_ptr) += my_expr->eval_int();
		if(my_assign == MINUS_ASSIGN)
		{
			*((int*)m_value_ptr) -= my_expr->eval_int();
		}
		if(my_assign == PLUS_PLUS)
			(*((int*)m_value_ptr))++;
		if(my_assign == MINUS_MINUS)
			(*((int*)m_value_ptr))--;
	}
	if(m_type == DOUBLE)
	{
		if(my_assign == ASSIGN)
			*((double*)m_value_ptr) = my_expr->eval_double();			
		if(my_assign == PLUS_ASSIGN)
			*((double*)m_value_ptr) += my_expr->eval_double();
		if(my_assign == MINUS_ASSIGN)
			*((double*)m_value_ptr) -= my_expr->eval_double();
	}
	if(m_type == STRING)
	{
		if(my_assign == ASSIGN)
			*((std::string*)m_value_ptr) = my_expr->eval_string();			
		if(my_assign == PLUS_ASSIGN)
			*((std::string*)m_value_ptr) += my_expr->eval_string();
	}
}

void Symbol::assign(std::string my_field, Expression *my_expr, Assign_operator my_assign)
{
	Status status;
	if(get_type(my_field) == INT)
	{
		int total;
		if(my_assign == ASSIGN)
		{
						
			status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, (my_expr->eval_int()));
			assert(status == OK);
		}
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Game_object*)m_value_ptr)->get_member_variable(my_field, total);
							total += my_expr->eval_int();
      				status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Game_object*)m_value_ptr)->get_member_variable(my_field, total);
							total -= my_expr->eval_int();
      				status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
		if(my_assign == PLUS_PLUS)
		{
			status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, (get_int(my_field)) + 1);
			assert(status == OK);
		}
		if(my_assign == MINUS_MINUS)
		{
			status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, (get_int(my_field)) - 1);
			assert(status == OK);
		}
	}	
	if(get_type(my_field) == DOUBLE)
	{
		double total;
		if(my_assign == ASSIGN)
		{
			status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, my_expr->eval_double());
			assert(status == OK);
		}
    if(my_assign == PLUS_ASSIGN)
    {
    	status = ((Game_object*)m_value_ptr)->get_member_variable(my_field, total);
			total += my_expr->eval_double();
      status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, total);
      assert(status == OK);
    }
    if(my_assign == MINUS_ASSIGN)
    {
    	status = ((Game_object*)m_value_ptr)->get_member_variable(my_field, total);
			total -= my_expr->eval_double();
      status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, total);
      assert(status == OK);
		}
	}	
	if(get_type(my_field) == STRING)
	{
		std:: string total;
		if(my_assign == ASSIGN)
		{
			status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, my_expr->eval_string());
			assert(status == OK);
		}
    if(my_assign == PLUS_ASSIGN)
    {
    	status = ((Game_object*)m_value_ptr)->get_member_variable(my_field, total);
			total += my_expr->eval_string();
      status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, total);
      assert(status == OK);
    }
	}	
	else if(get_type(my_field) == ANIMATION_BLOCK)
	{
    if(my_assign == ASSIGN)
    {
       status = ((Game_object*)m_value_ptr)->set_member_variable(my_field, (my_expr->eval_animation_block()));
       assert(status == OK);
       }
		}
}

void Symbol::assign(int index, Expression *my_expr, Assign_operator my_assign)
{
	if(m_type == INT_ARRAY)
	{
		if(my_assign == ASSIGN)
		{
			if(index > m_size || index < 0)
			{
				ostringstream str_stream;
				str_stream << index;
				Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, m_id, str_stream.str());
				*((int*)m_value_ptr+0) = my_expr->eval_int();
			}
			else
				*((int*)m_value_ptr+index) = my_expr->eval_int();
		}
		if(my_assign == PLUS_ASSIGN)
		{
			*((int*)m_value_ptr+index) += my_expr->eval_int();
		}
		if(my_assign == MINUS_ASSIGN)
		{
			*((int*)m_value_ptr+index) -= my_expr->eval_int();
		}
		if(my_assign == PLUS_PLUS)
		{
			*((int*)m_value_ptr+index) += 1;
		}
		if(my_assign == MINUS_MINUS)
		{
			*((int*)m_value_ptr+index) -= 1;
		}
	}
	else if(m_type == DOUBLE_ARRAY)
	{
		if(my_assign == ASSIGN)
		{
			*((double*)m_value_ptr+index) = my_expr->eval_double();
		}
		if(my_assign == PLUS_ASSIGN)
		{
			*((double*)m_value_ptr+index) += my_expr->eval_double();
		}
		if(my_assign == MINUS_ASSIGN)
		{
			*((double*)m_value_ptr+index) -= my_expr->eval_double();
		}
	}
	else if(m_type == STRING_ARRAY)
	{
		if(my_assign == ASSIGN)
		{
			*((std::string*)m_value_ptr+index) = my_expr->eval_string();
		}
		if(my_assign == PLUS_ASSIGN)
		{
			*((std::string*)m_value_ptr+index) += my_expr->eval_string();
		}
	}
}
	
void Symbol::assign(std::string my_field, int index, Expression *my_expr, Assign_operator my_assign)
{
	Status status;
  switch(m_type)
  {
    case RECTANGLE_ARRAY:
				  if(get_type(my_field) == INT)
					{
						int total;
			    	if(my_assign == ASSIGN)
    				{
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_int()));
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_int();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_int();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_PLUS)
    				{
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) + 1);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_MINUS)
    				{
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) - 1);
      				assert(status == OK);
    				}
  				}
          else if(get_type(my_field) == DOUBLE) 
          {
						double total;
            if(my_assign == ASSIGN)
            {
              status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_double()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_double();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_double();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
          }
					else if(get_type(my_field) == STRING)
          {
						std::string total;
            if(my_assign == ASSIGN)
            {
              status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_string()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_string();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
					}
					else if(get_type(my_field) == ANIMATION_BLOCK)
					{
            if(my_assign == ASSIGN)
            {
              status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_animation_block()));
              assert(status == OK);
            }
					}
          break;
    case CIRCLE_ARRAY:
 				  if(get_type(my_field) == INT)
					{
						int total;
			    	if(my_assign == ASSIGN)
    				{
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_int()));
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_int();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_int();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_PLUS)
    				{
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) + 1);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_MINUS)
    				{
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) - 1);
      				assert(status == OK);
    				}
  				}	
          else if(get_type(my_field) == DOUBLE) 
          {
						double total;
            if(my_assign == ASSIGN)
            {
              status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_double()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_double();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_double();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
          }
          else if(get_type(my_field) == STRING)
          {
						std:: string total;
            if(my_assign == ASSIGN)
            {
              status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_string()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_string();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
					}
					else if(get_type(my_field) == ANIMATION_BLOCK)
					{
            if(my_assign == ASSIGN)
            {
              status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_animation_block()));
              assert(status == OK);
            }
					}
          break;
    case TRIANGLE_ARRAY:
				  if(get_type(my_field) == INT)
					{
						int total;
			    	if(my_assign == ASSIGN)
    				{
      				status = ((Triangle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_int()));
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_int();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_int();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_PLUS)
    				{
      				status = ((Triangle*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) + 1);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_MINUS)
    				{
      				status = ((Triangle*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) - 1);
      				assert(status == OK);
    				}
  				}
					else if(get_type(my_field) == DOUBLE)
					{
						double total;
            if(my_assign == ASSIGN)
            {
              status = ((Triangle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_double()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_double();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_double();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
					}
          else if(get_type(my_field) == STRING)
          {
						std::string total;
            if(my_assign == ASSIGN)
            {
              status = ((Triangle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_string()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_string();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
					}
					else if(get_type(my_field) == ANIMATION_BLOCK)
					{
            if(my_assign == ASSIGN)
            {
              status = ((Triangle*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_animation_block()));
              assert(status == OK);
            }
					}
          break;
    case TEXTBOX_ARRAY:
				  if(get_type(my_field) == INT)
					{
						int total;
			    	if(my_assign == ASSIGN)
    				{
      				status = ((Textbox*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_int()));
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_int();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_int();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_PLUS)
    				{
      				status = ((Textbox*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) + 1);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_MINUS)
    				{
      				status = ((Textbox*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) - 1);
      				assert(status == OK);
    				}
  				}	
          else if(get_type(my_field) == DOUBLE) 
          {
						double total;
            if(my_assign == ASSIGN)
            {
              status = ((Textbox*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_double()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_double();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_double();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
          }
          else if(get_type(my_field) == STRING)
          {
						std::string total;
            if(my_assign == ASSIGN)
            {
              status = ((Textbox*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_string()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_string();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
					}
					else if(get_type(my_field) == ANIMATION_BLOCK)
					{
            if(my_assign == ASSIGN)
            {
              status = ((Textbox*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_animation_block()));
              assert(status == OK);
            }
					}
          break;
    case PIXMAP_ARRAY:
				  if(get_type(my_field) == INT)
					{
						int total;
			    	if(my_assign == ASSIGN)
    				{
      				status = ((Pixmap*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_int()));
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_int();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_int();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == PLUS_PLUS)
    				{
      				status = ((Pixmap*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) + 1);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_MINUS)
    				{
      				status = ((Pixmap*)m_value_ptr+index)->set_member_variable(my_field, (get_int(my_field)) - 1);
      				assert(status == OK);
    				}
  				}	
          else if(get_type(my_field) == DOUBLE) 
          {
						double total;
            if(my_assign == ASSIGN)
            {
              status = ((Pixmap*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_double()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_double();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
    				if(my_assign == MINUS_ASSIGN)
    				{
    				  status = ((Circle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total -= my_expr->eval_double();
      				status = ((Circle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
          }
          else if(get_type(my_field) == STRING)
          {
						std::string total;
            if(my_assign == ASSIGN)
            {
              status = ((Pixmap*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_string()));
              assert(status == OK);
            }
    				if(my_assign == PLUS_ASSIGN)
    				{
    				  status = ((Rectangle*)m_value_ptr+index)->get_member_variable(my_field, total);
							total += my_expr->eval_string();
      				status = ((Rectangle*)m_value_ptr+index)->set_member_variable(my_field, total);
      				assert(status == OK);
    				}
					}
					else if(get_type(my_field) == ANIMATION_BLOCK)
					{
            if(my_assign == ASSIGN)
            {
              status = ((Pixmap*)m_value_ptr+index)->set_member_variable(my_field, (my_expr->eval_animation_block()));
              assert(status == OK);
            }
					}
          break;
    default:
          break;
  }
}

 
