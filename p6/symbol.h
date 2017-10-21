#include<iostream>
#include "gpl_type.h"
#include "game_object.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "textbox.h"
#include "pixmap.h"

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
    int get_int(int);
    double get_double(int);
    std::string get_string(int);
		int get_size();
		bool is_game_object();
		Game_object* get_game_object_value();

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
