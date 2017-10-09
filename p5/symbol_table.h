#include<iostream>
#include "gpl_type.h"
#include "symbol.h"
#include<vector>
#include<unordered_map>

class Symbol_table
{
  public:
    static Symbol_table *instance();
    void insert(std::string, Symbol*);
    void print(std::ostream &os);
    Symbol* lookup(std::string);

  private:
    static Symbol_table *m_instance;

    Symbol_table() {};
 
    std::unordered_map<std::string, Symbol*> m;    
    std::vector<Symbol*> v;

    // disable default copy constructor and default assignment
    // done as a precaution, they should never be called
    Symbol_table(const Symbol_table &);
    const Symbol_table &operator=(const Symbol_table &);

};
