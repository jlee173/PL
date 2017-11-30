#include "expression.h"
#include "variable.h"
#include <cmath> 
#include "error.h"


Expression::Expression(int value)
{
  m_const = new Constant(value);
  m_type = INT;
}

Expression::Expression(double value)
{
  m_const = new Constant(value);
  m_type = DOUBLE;
}

Expression::Expression(std::string *value)
{
  m_const = new Constant(value);
  m_type = STRING;
}

Expression::Expression(Variable* var)
{
	m_type = var->get_type();
	m_variable = var;
	/*if(var->get_type() == INT)
		m_type = INT;
	if(var->get_type() == DOUBLE)
		m_type = DOUBLE;
	if(var->get_type() == STRING)
		m_type = STRING;
	if(var->get_type() == INT_ARRAY)
		m_type = INT;
	if(var->get_type() == DOUBLE_ARRAY)
		m_type = DOUBLE;
	if(var->get_type() == STRING_ARRAY)
		m_type = STRING;
	if(var->get_type() == ANIMATION_BLOCK)
		m_type = ANIMATION_BLOCK;
  m_variable = var;
	*/
}

Expression::Expression(Expression* lhs, Operator_type type, Expression* rhs)
{
  m_lhs = lhs;
  m_rhs = rhs;
  m_oper = type;
  if(m_oper == LESS_THAN || m_oper == GREATER_THAN || m_oper == LESS_EQUAL || m_oper == GREATER_EQUAL || m_oper == EQUAL || m_oper == NOT_EQUAL || m_oper == OR || m_oper == AND || m_oper == MOD)
  {
    m_type = INT;
  }
  else if((m_lhs->get_type() == STRING || m_rhs->get_type() == STRING) && m_oper == PLUS)
  {
    m_type = STRING;
  }
  else if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
  {
    m_type = DOUBLE;
  }
  else
  {
    m_type = INT;
  }
}

Expression::Expression(Expression* lhs, Operator_type type)
{
  m_lhs = lhs;
  m_oper = type;
  if(m_oper == NOT || m_oper == RANDOM || m_oper == FLOOR)
  {
    m_type = INT;
  }
  else if(m_oper == SIN || m_oper == COS || m_oper == TAN || m_oper == ASIN|| m_oper == ACOS || m_oper == ATAN || m_oper == SQRT)
  {
    m_type = DOUBLE;
  }
  else if(m_lhs->get_type() == DOUBLE)
  {
    m_type = DOUBLE;
  }
  else if(m_lhs->get_type() == INT)
  {
    m_type = INT;
  }
}

int Expression::eval_int()
{
  if (m_lhs == NULL && m_rhs == NULL)
  {
    if(m_variable != NULL)
    {
      return m_variable->get_int_val();
    }
    else if(m_const != NULL)
    {
      return m_const->get_int_value();
    }
  }
  else if(m_lhs != NULL && m_rhs != NULL)
  {
    if(m_oper == PLUS)
    { 
      if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        return m_lhs->eval_int() + m_rhs->eval_int();
      }
    }
    else if(m_oper == MINUS)
    {
      if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int value = m_lhs->eval_int();
        int value2 = m_rhs->eval_int();
        return (value-value2);
      }
    }
    else if(m_oper == MULTIPLY)
    {
      if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int value = m_lhs->eval_int();
        int value2 = m_rhs->eval_int();
        return (value*value2);
      }
    }
    else if(m_oper == DIVIDE)
    {
      if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int value = m_lhs->eval_int();
        int value2 = m_rhs->eval_int();
        return (value/value2);
      }
    }
    else if(m_oper == MOD)
    { 
        int value = m_lhs->eval_int();
        int value2 = m_rhs->eval_int();
        return (value%value2);
    }
    else if(m_oper == LESS_THAN)
    {
      if(m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
      {
        std::string left = m_lhs->eval_string();
        std::string right = m_rhs->eval_string();
        if(left < right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
      {
        double left = m_lhs->eval_double();
        double right = m_rhs->eval_double();
        if(left < right)
          return 1;
        else //if(left > right)
	  return 0;
      }
      else if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int left = m_lhs->eval_int();
        int right = m_rhs->eval_int();
        if(left < right)
          return 1;
        else //if(left > right)
          return 0;
      }
    }
    else if(m_oper == GREATER_THAN)
    {
      if(m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
      {
        std::string left = m_lhs->eval_string();
        std::string right = m_rhs->eval_string();
        if(left > right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
      {
        double left = m_lhs->eval_double();
        double right = m_rhs->eval_double();
        if(left > right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int left = m_lhs->eval_int();
        int right = m_rhs->eval_int();
        if(left > right)
          return 1;
        else //if(left > right)
          return 0;
      }
    }
    else if(m_oper == LESS_EQUAL)
    {
      if(m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
      {
        std::string left = m_lhs->eval_string();
        std::string right = m_rhs->eval_string();
        if(left <= right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
      {
        double left = m_lhs->eval_double();
        double right = m_rhs->eval_double();
        if(left <= right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int left = m_lhs->eval_int();
        int right = m_rhs->eval_int();
        if(left <= right)
          return 1;
        else //if(left > right)
          return 0;
      }
    }
    else if(m_oper == GREATER_EQUAL)
    {
      if(m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
      {
        std::string left = m_lhs->eval_string();
        std::string right = m_rhs->eval_string();
        if(left >= right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
      {
        double left = m_lhs->eval_double();
        double right = m_rhs->eval_double();
        if(left >= right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int left = m_lhs->eval_int();
        int right = m_rhs->eval_int();
        if(left >= right)
          return 1;
        else //if(left > right)
          return 0;
      }
    }
    else if(m_oper == EQUAL)
    {
      if(m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
      {
        std::string left = m_lhs->eval_string();
        std::string right = m_rhs->eval_string();
        if(left == right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
      {
        double left = m_lhs->eval_double();
        double right = m_rhs->eval_double();
        if(left == right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int left = m_lhs->eval_int();
        int right = m_rhs->eval_int();
        if(left == right)
          return 1;
        else //if(left > right)
          return 0;
      }
    }
    else if(m_oper == NOT_EQUAL)
    {
      if(m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
      { 
        std::string left = m_lhs->eval_string();
        std::string right = m_rhs->eval_string();
        if(left != right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
      { 
        double left = m_lhs->eval_double();
        double right = m_rhs->eval_double();
        if(left != right)
          return 1;
        else //if(left > right)
          return 0;
      }
      else if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int left = m_lhs->eval_int();
        int right = m_rhs->eval_int();
        if(left != right)
          return 1;
        else //if(left > right)
          return 0;
      }
    }
    else if(m_oper == AND)
    {
      if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
      {
        double left = m_lhs->eval_double();
        double right = m_rhs->eval_double();
        if(left && right)
          return 1;
        else 
   	  		return 0;
      }
       else if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int left = m_lhs->eval_int();
        int right = m_rhs->eval_int();
        if(left && right)
          return 1;
        else //if(left > right)
          return 0;
      } 
    }
    else if(m_oper == OR)
    {
      if(m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE)
      {
        double left = m_lhs->eval_double();
        double right = m_rhs->eval_double();
        if(left || right)
          return 1;
        else
          return 0;
      }
       else if(m_lhs->get_type() == INT || m_rhs->get_type() == INT)
      {
        int left = m_lhs->eval_int();
        int right = m_rhs->eval_int();
        if(left || right)
          return 1;
        else //if(left > right)
          return 0;
      }
    }
		
  }
  else if(m_lhs != NULL && m_rhs == NULL)
  {
    if(m_oper == UNARY_MINUS)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return -(val);
      }
    }
    if(m_oper == NOT)
    {
      double val = m_lhs->eval_double();
      return (val == 0);
    }
    if(m_oper == ABS)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return (std::abs(val));
      }
    }
    if(m_oper == FLOOR)
    {
      if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return floor(val);
      }
      else if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return (floor(val));
      }
    }
    if(m_oper == RANDOM)
    {
      if(m_lhs->get_type() == DOUBLE)
      {
        /*if(m_lhs->eval_double() < 1)
        {
          std::ostringstream num;
          num << m_lhs->eval_double();
          Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, num.str());
				}*/
        double val = m_lhs->eval_double();
        int floor_d = floor(val);
        return rand() % floor_d + 0;
      }
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return rand() % val + 0;
      }
    }
		/*if(m_oper == SQRT)
		{
			if(m_lhs->get_type() == INT)
			{
				int val = m_lhs->eval_int();
				return sqrt(val);
			}
		}*/
  }
return 0;
}

double Expression::eval_double()
{
  if(m_type == INT)
  {
    return (double) eval_int();
  }
  if(m_lhs == NULL && m_rhs == NULL)
  {
    if(m_variable != NULL)//double variable
    {
        return m_variable->get_double_val();
    }
    else if(m_const != NULL)//double constant
    {
     	return m_const->get_double_value();
    }
  }
  else if(m_lhs != NULL && m_rhs != NULL)
  {
    if(m_oper == PLUS)
    {
      if(m_lhs->get_type() == INT && m_rhs->get_type() == DOUBLE)
      {
        int value = m_lhs->eval_int();
        double value2 = m_rhs->eval_double();
        return (value+value2);
      }
      if(m_lhs->get_type() == DOUBLE && m_rhs->get_type() == INT)
      {
        double value = m_lhs->eval_double();
        int value2 = m_rhs->eval_int();
        return (value+value2);
      }
      if(m_lhs->get_type() == INT && m_rhs->get_type() == INT)
      {
        int value = m_lhs->eval_int();
        int value2 = m_rhs->eval_int();
        return (value+value2);
      }
      if(m_lhs->get_type() == DOUBLE && m_rhs->get_type() == DOUBLE)
      { 
        double value = m_lhs->eval_double();
        double value2 = m_rhs->eval_double();
        return (value+value2);
      }
    }
    if(m_oper == MINUS)
    {
      if(m_lhs->get_type() == INT && m_rhs->get_type() == DOUBLE)
      {
        int value = m_lhs->eval_int();
        double value2 = m_rhs->eval_double();
        return (value-value2);
      }
      else if(m_lhs->get_type() == DOUBLE && m_rhs->get_type() == INT)
      {
        double value = m_lhs->eval_double();
        int value2 = m_rhs->eval_int();
        return (value-value2);
      }
      else
      {
        double value = m_lhs->eval_double();
        double value2 = m_rhs->eval_double();
        return (value-value2);
      }
    }
    if(m_oper == MULTIPLY)
    {
      if(m_lhs->get_type() == INT && m_rhs->get_type() == DOUBLE)
      {
    		int value = m_lhs->eval_int();
        double value2 = m_rhs->eval_double();
        return (value*value2);
      }
      if(m_lhs->get_type() == DOUBLE && m_rhs->get_type() == INT)
      {
				double value = m_lhs->eval_double();
				int value2 = m_rhs->eval_int();
				return (value*value2);
      }
      if(m_lhs->get_type() == DOUBLE && m_rhs->get_type() == DOUBLE)
      {
				double value = m_lhs->eval_double();
				double value2 = m_rhs->eval_double();
        return (value*value2);
      }
    }
    if(m_oper == DIVIDE)
    {
      if(m_lhs->get_type() == INT && m_rhs->get_type() == DOUBLE)
      {
        int value = m_lhs->eval_int();
        double value2 = m_rhs->eval_double();
        return (value/value2);
      }
      else if(m_lhs->get_type() == DOUBLE && m_rhs->get_type() == INT)
      {
        double value = m_lhs->eval_double();
        int value2 = m_rhs->eval_int();
        return (value/value2);
      }
      else
      { 
				double value = m_lhs->eval_double();
				double value2 = m_rhs->eval_double();
        return (value/value2);
      }
    }
  }
  if(m_lhs != NULL && m_rhs == NULL)
  {
    if(m_oper == UNARY_MINUS)
    {
      if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return (val*(-1));
      }
    }
		/*if(m_oper == NOT)
		{
			if(m_lhs->get_type() == DOUBLE)
			{
				double val = m_lhs->eval_double();
				return (!val);
			}
		}*/
    if(m_oper == FLOOR)
    {
			if(m_lhs->get_type() == DOUBLE)
  		{
				double val = m_lhs->eval_double();
 				return floor(val);
 			}
		}
    if(m_oper == SIN)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return sin((val)*(M_PI/180));
      }
      else if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return sin((val)*(M_PI/180));
      }
    }
    if(m_oper == COS)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return cos((val)*(M_PI/180));
      }
      else if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return cos((val)*(M_PI/180));
      }
    }
    if(m_oper == TAN)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return tan((val)*(M_PI/180));
      }
      else if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return tan((val)*(M_PI/180));
      }
    }
    if(m_oper == ASIN)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return (asin(val)*(180/M_PI));
      }
      else if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return (asin(val)*(180/M_PI));
      }
    }
    if(m_oper == ACOS)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return (acos(val)*(180/M_PI));
      }
      else if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return (acos(val)*(180/M_PI));
      }
    }
    if(m_oper == ATAN)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return (atan(val)*(180/M_PI));
      }
      else if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return (atan(val)*(180/M_PI));
      }
    }
    if(m_oper == SQRT)
    {
      if(m_lhs->get_type() == INT)
      {
        int val = m_lhs->eval_int();
        return (sqrt(val));
      }
      else if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return (sqrt(val));
      }
    }
    if(m_oper == ABS)
    {
			/*if(m_lhs->get_type() == INT)
      {
				int val = m_lhs->eval_int();
				return (abs(val));
			}*/
      if(m_lhs->get_type() == DOUBLE)
      {
        double val = m_lhs->eval_double();
        return (std::abs(val));
      }
    }
 		/*if(m_oper == RANDOM)
    {
 			if(m_lhs->get_type() == DOUBLE)
			{
        double val = m_lhs->eval_double();
        int floor_d = floor(val);
				if(floor_d < 1)
					Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM
        return rand() % floor_d + 0;
			}
		}*/
  }
return 0;
}  

std::string Expression::eval_string()
{
  std::ostringstream num;
  if(m_type == INT)
  {
    num << eval_int();
    return num.str();
  }
  if(m_type == DOUBLE)
  {
    num << eval_double();
    return num.str();
  }
  if(m_lhs == NULL && m_rhs == NULL)
  {
  	if(m_type == INT)
  	{
    	num << eval_int();
    	return num.str();
  	}
  	if(m_type == DOUBLE)
  	{	
    	num << eval_double();
    	return num.str();
  	}

    if(m_variable != NULL)//string variable
    {
				if(m_type == INT || m_type == INT_ARRAY)
				{
					num << m_variable->get_int_val();
					return num.str();
				}
				else if(m_type == DOUBLE || m_type == DOUBLE_ARRAY)
				{
					num << m_variable->get_double_val();
					return num.str();
				}
				
         return m_variable->get_string_val();
    }
    else if(m_const != NULL)//string constant
    {
             return m_const->get_string_value();
    }
  }
  else if(m_lhs != NULL && m_rhs != NULL)
  {
    if(m_oper == PLUS)
    {
        std::string total = m_lhs->eval_string() + m_rhs->eval_string();
        return total;
    }
  }
return "";
} 


Gpl_type Expression::get_type()
{
  return m_type;
}

Animation_block* Expression::eval_animation_block()
{
	return m_variable->get_animation_block_val();	
} 
