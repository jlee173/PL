// updated 2/14/16

#include "statement_block.h"
#include "gpl_assert.h"
using namespace std;


Statement_block::Statement_block()
{

}

// this function is called for all non-animation_block statement_blocks
// Implement it for p7
void Statement_block::execute()
{
  // This function should be defined before it is ever called
  // This assert will cause the program to abort if this function 
  // is called before it is implemented.

  // *** ==> Remove this assert when you implement this function
	for(unsigned int i = 0; i < block.size(); i++)
	{
		block[i]->execute();
	}
	
}

void Statement_block::insert(Statement* statement)
{
	block.push_back(statement);
}
