#include <iostream>
#include "gpl_type.h"
//#include "symbol.h"

class Expression;
class Symbol;

class Variable
{
  public:
    Variable(Symbol*); //bitchass constructor
    Variable(Symbol*, Expression*); //stupid array constructor
    Gpl_type get_type();
    int get_int_val();
    double get_double_val();
    std::string get_string_val();
    int get_int_index(int);
    double get_double_index(int);
    std::string get_string_index(int);

  private:
    Symbol *m_sym;
    Gpl_type m_type;
    Expression *m_expr = NULL;

};
