#ifndef SYMBOL_H
#define SYMBOL_H

#include<iostream>
#include "gpl_type.h"
#include "game_object.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "textbox.h"
#include "pixmap.h"
#include "animation_block.h"
#include "assert.h"
#include "expression.h"

class Symbol
{
  public:
    static Symbol *instance();

    Symbol(int, std::string);// Int
    Symbol(double, std::string);//Double
    Symbol(std::string, std::string);//String
    Symbol(Gpl_type, std::string, int);//Arrays
		Symbol(Gpl_type, std::string);//Game Objects
    void print();
    std::string get_id();
    Gpl_type get_type();
    int get_int();
    double get_double();
    std::string get_string();
    int get_int(int, std::string);
    double get_double(int, std::string);
    std::string get_string(int, std::string);
		int get_size();
		bool is_game_object();
		Game_object* get_game_object_value();
		Animation_block* get_animation_block_value();
		Game_object* get_game_object_array_value(int);
		void set(int);
		void assign(Expression*, Assign_operator);
		void assign(int, Expression*, Assign_operator);
		void assign(std::string, Expression*, Assign_operator);
		void assign(std::string, int, Expression*, Assign_operator);

  private:
    static Symbol *m_instance;

    Symbol() {};

    Gpl_type m_type;
    void* m_value_ptr;
    std::string m_id;
    int m_size;

    // disable default copy constructor and default assignment
    // done as a precaution, they should never be called
    Symbol(const Symbol &);
    const Symbol &operator=(const Symbol &);

};
#endif
