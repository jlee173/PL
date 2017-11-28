#ifndef VARIABLE_H
#define VARIABLE_H


#include <iostream>
#include "gpl_type.h"
#include "animation_block.h"

class Expression;
class Symbol;

class Variable
{
  public:
    Variable(Symbol*); //bitchass constructor
    Variable(Symbol*, Expression*); //stupid array constructor
		Variable(Symbol*, std::string);
		Variable(Symbol*, Expression*, std::string);
    Gpl_type get_type();
    int get_int_val();
    double get_double_val();
    std::string get_string_val();
    int get_int_index(int);
    double get_double_index(int);
    std::string get_string_index(int);
		Animation_block* get_animation_block_val();
		void assign(Expression*, Assign_operator);


  private:
    Symbol *m_sym;
    Gpl_type m_type;
    Expression *m_expr = NULL;
		std::string m_field = "";
};
#endif
