#include<iostream>
#include "gpl_type.h"

class Symbol
{
  public:
    static Symbol *instance();

    Symbol(int, std::string);
    Symbol(double, std::string);
    Symbol(std::string, std::string);
    Symbol(Gpl_type, std::string, int);
    void print();
    std::string get_id();
    Gpl_type get_type();
    int get_int();
    double get_double();
    std::string get_string();

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
