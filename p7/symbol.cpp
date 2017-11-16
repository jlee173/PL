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

std::string Symbol::get_id()
{ 
  return m_id;
}

Gpl_type Symbol::get_type()
{
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

Animation_block* Symbol::get_animation_block_value()
{
	return (Animation_block*)(m_value_ptr);
}

Game_object* Symbol::get_game_object_array_value(int size)
{
  if(m_type == RECTANGLE)
  {
    Rectangle *object_ptr = (Rectangle*)m_value_ptr;
		return &(object_ptr[size]);
  }
  if(m_type == CIRCLE)
  {
    Circle *object_ptr = (Circle*)m_value_ptr;
		return &(object_ptr[size]);
  }
  if(m_type == TRIANGLE)
  {
    Triangle *object_ptr = (Triangle*)m_value_ptr;
		return &(object_ptr[size]);
  }
  if(m_type == TEXTBOX)
  {
    Textbox *object_ptr = (Textbox*)m_value_ptr;
		return &(object_ptr[size]);
  }
  if(m_type == PIXMAP)
  {
    Pixmap *object_ptr = (Pixmap*)m_value_ptr;
		return &(object_ptr[size]);
  }
	return NULL;
}
	
	
