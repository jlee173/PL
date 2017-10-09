#include <iostream>
#include "gpl_type.h"
//#include "symbol.h"

class Expression;
class Symbol;

class Variable
{
  public:
    Variable(Symbol*); //bitchass constructor
    //Variable(Symbol*, Expression*); 
    Gpl_type get_type();
    int get_int_val();
    double get_double_val();
    std::string get_string_val();
  private:
    Symbol *m_sym;
    Gpl_type m_type;
    Expression *m_expr = NULL;

};
