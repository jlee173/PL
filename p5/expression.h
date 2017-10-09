#include <iostream>
#include <sstream>
#include "constant.h"
#include "gpl_type.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Variable;


class Expression
{
  public:
	Expression(int);
	Expression(double);
	Expression(std::string*);
	Expression(Variable*);
	Expression(Expression*, Operator_type, Expression*);
	Expression(Expression*, Operator_type);
	int eval_int();
	double eval_double();
	std::string eval_string();
	Gpl_type get_type();
	
  private:
	Expression *m_lhs = NULL;
	Expression *m_rhs = NULL;
	Gpl_type m_type = NO_TYPE;
	Variable* m_variable = NULL;
	Constant* m_const = NULL;
	Operator_type m_oper = NO_OP;
};	
