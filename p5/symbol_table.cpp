#include "symbol_table.h"
#include <unordered_map>
#include <algorithm>

/* static */ Symbol_table *Symbol_table::m_instance = 0;

/* static */ Symbol_table * Symbol_table::instance()
{
  if (m_instance == 0)
    m_instance = new Symbol_table();
  return m_instance;
}

Symbol *Symbol_table::lookup(std::string name)
{
  std::unordered_map<std::string, Symbol*>::iterator iter;
  iter = m.find(name);
  if (iter == m.end())
    return NULL;
  else
    return iter->second;
}

void Symbol_table::insert(std::string m_id, Symbol* s)
{
  std::pair<std::string, Symbol*> my_pair (m_id, s);
  m.insert (my_pair);
  v.push_back(s);
}

bool my_sort (Symbol* i, Symbol* j) { return (i->get_id() < j->get_id()); }

void Symbol_table::print(std::ostream &os)
{
  std::sort (v.begin(), v.end(), my_sort);
  std::vector<Symbol*>::iterator iter;
  for (iter = v.begin(); iter != v.end(); iter++)
  {
    (*iter)->print();
  }
}   
