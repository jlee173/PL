#ifndef EXIT_STMT
#define EXIT_STMT


#include <iostream>
#include "statement.h"


class Exit_stmt: public Statement
{
	public:
		Exit_stmt();
		void execute();

	private:

};
#endif
