// updated 2/14/2016

#include "event_manager.h"
#include "gpl_assert.h"
using namespace std;

/* static */ Event_manager *Event_manager::m_instance = 0;

/* static */ Event_manager * Event_manager::instance()
{
  if (!m_instance)
    m_instance = new Event_manager();
  return m_instance;
}

Event_manager::Event_manager()
{
}

Event_manager::~Event_manager()
{
}


void Event_manager::execute_handlers(Window::Keystroke keystroke)
{
	for(unsigned int i = 0; i < block[keystroke].size(); i++)
	{
		block[keystroke][i]->execute();
	}
}

void Event_manager::insert(Statement_block *m_stmt, Window::Keystroke keystroke)
{
	block[keystroke].push_back(m_stmt);
}
