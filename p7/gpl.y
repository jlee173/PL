%{  // bison syntax to indicate the start of the header
    // the header is copied directly into y.tab.c (the generated parser)

extern int yylex();               // this lexer function returns next token
extern int yyerror(const char *); // used to print errors
extern int line_count;            // current line in the input; from record.l

#include "error.h"      // class for printing errors (used by gpl)
#include "parser.h"
#include <iostream>
#include <string>
#include "gpl_type.h"
#include "symbol_table.h"
#include <stack>
#include "window.h"
#include "statement_block.h"
#include "statement.h"
#include "print_stmt.h"
#include "event_manager.h"
#include "exit_stmt.h"
#include "assignment_stmt.h"
#include "if_stmt.h"
#include "for_stmt.h"


using namespace std;

Game_object* cur_object_under_construction;
Animation_block* animation_block_just_created;
std::string cur_object_under_construction_name;
std::string animation_block_just_created_name;
bool error_object;
std::stack<Statement_block*> m_stack;

// bison syntax to indicate the end of the header
%}

%union {
 int            union_int;
 std::string    *union_string;  // MUST be a pointer to a string (this sucks!)
 double         union_double;
 Gpl_type				union_gpl_type;
 Expression     *union_expression;
 Variable       *union_variable;
 Operator_type  union_operator_type;
 Symbol 				*union_symbol;
 Window::Keystroke			union_keystroke;
 Statement_block        *union_statement_block;
 Statement							*union_statement;
}

// turn on verbose (longer) error messages
%error-verbose

%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"
%token <union_int> T_FORWARD "forward" // value is line number
%token T_INITIALIZATION      "initialization"
%token T_TERMINATION         "termination"

%token T_TRUE                "true"
%token T_FALSE               "false"

%token T_TOUCHES             "touches"
%token T_NEAR                "near"

%token T_ANIMATION           "animation"

%token T_IF                  "if"
%token T_FOR                 "for"
%token T_ELSE                "else"
%token <union_int> T_PRINT           "print" // value is line number
%token <union_int> T_EXIT            "exit" // value is line number

%token T_LPAREN              "("
%token T_RPAREN              ")"
%token T_LBRACE              "{"
%token T_RBRACE              "}"
%token T_LBRACKET            "["
%token T_RBRACKET            "]"
%token T_SEMIC               ";"
%token T_COMMA               ","
%token T_PERIOD              "."

%token T_ASSIGN              "="
%token T_PLUS_ASSIGN         "+="
%token T_MINUS_ASSIGN        "-="
%token T_PLUS_PLUS           "++"
%token T_MINUS_MINUS         "--"

%token T_MULTIPLY            "*"
%token T_DIVIDE              "/"
%token T_MOD                 "%"
%token T_PLUS                "+"
%token T_MINUS               "-"
%token T_SIN                 "sin"
%token T_COS                 "cos"
%token T_TAN                 "tan"
%token T_ASIN                "asin"
%token T_ACOS                "acos"
%token T_ATAN                "atan"
%token T_SQRT                "sqrt"
%token T_FLOOR               "floor"
%token T_ABS                 "abs"
%token T_RANDOM              "random"

%token T_LESS                "<"
%token T_GREATER             ">"
%token T_LESS_EQUAL          "<="
%token T_GREATER_EQUAL       ">="
%token T_EQUAL               "=="
%token T_NOT_EQUAL           "!=" %token T_AND                 "&&"
%token T_OR                  "||"
%token T_NOT                 "!"

%token T_ON                  "on"
%token T_SPACE               "space"
%token T_LEFTARROW           "leftarrow"
%token T_RIGHTARROW          "rightarrow"
%token T_UPARROW             "uparrow"
%token T_DOWNARROW           "downarrow"
%token T_LEFTMOUSE_DOWN      "leftmouse_down"
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down"
%token T_RIGHTMOUSE_DOWN     "rightmouse_down"
%token T_LEFTMOUSE_UP        "leftmouse_up"
%token T_MIDDLEMOUSE_UP      "middlemouse_up"
%token T_RIGHTMOUSE_UP       "rightmouse_up"
%token T_MOUSE_MOVE          "mouse_move"
%token T_MOUSE_DRAG          "mouse_drag"
%token T_F1                  "f1"
%token T_AKEY                "akey"
%token T_SKEY                "skey"
%token T_DKEY                "dkey"
%token T_FKEY                "fkey"
%token T_HKEY                "hkey"
%token T_JKEY                "jkey"
%token T_KKEY                "kkey"
%token T_LKEY                "lkey"
%token T_WKEY                "wkey"

%token <union_string> T_ID            	 "identifier"
%token <union_int> T_INT_CONSTANT        "int constant"
%token <union_double> T_DOUBLE_CONSTANT  "double constant"
%token <union_string> T_STRING_CONSTANT  "string constant"
%type  <union_gpl_type> simple_type
%type  <union_expression> optional_initializer
%type  <union_expression> expression
%type  <union_expression> primary_expression
%type  <union_variable> variable
%type  <union_operator_type> math_operator 
%type  <union_gpl_type> object_type
%type  <union_symbol>  animation_parameter
%type  <union_keystroke> keystroke
%type  <union_statement_block> statement_block
%type  <union_statement_block> statement_block_creator
%type  <union_statement> statement
%type  <union_statement> print_statement
%type  <union_statement> if_statement
%type  <union_statement> exit_statement
%type  <union_statement> assign_statement
%type  <union_statement> for_statement
%type  <union_statement_block> on_block
%type  <union_statement_block> if_block


// special token that does not match any production
// used for characters that are not part of the language
%token T_ERROR               "error"

%left 	T_OR
%left 	T_AND
%left 	T_EQUAL T_NOT_EQUAL
%left 	T_LESS T_GREATER T_GREATER_EQUAL T_LESS_EQUAL
%left 	T_PLUS T_MINUS
%left 	T_MULTIPLY T_DIVIDE T_MOD
%nonassoc T_NOT
%nonassoc T_UNARY_OPS
%nonassoc IF_NO_ELSE
%nonassoc T_ELSE
%left 	T_TOUCHES T_NEAR

%% // indicates the start of the rules

//---------------------------------------------------------------------
program:
    declaration_list block_list
    ;

//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration
    | empty
    ;

//---------------------------------------------------------------------
declaration:
    variable_declaration T_SEMIC
    | object_declaration T_SEMIC
    | forward_declaration T_SEMIC
    ;

//---------------------------------------------------------------------
variable_declaration:
    simple_type  T_ID  optional_initializer
    {
      static Symbol_table *symbol_table = Symbol_table::instance();
	  if( symbol_table->lookup(*$2) != NULL)
	  {
	  	Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
	  }
	  else
	  {
	    if($1 == INT)
	    {
	      int initial_value = 0;
	      if($3 != NULL)
	      {
		      if($3->get_type() == DOUBLE || $3->get_type() == STRING || $3->get_type() == ANIMATION_BLOCK)
		      {
		        Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->get_type()), *$2, gpl_type_to_string($1));
		      }
		    else
	      initial_value = $3->eval_int();
	      }
   	      Symbol* my_symbol = new Symbol(initial_value, *$2);
   	      symbol_table->insert(*$2, my_symbol);
      }
	    if($1 == DOUBLE)
	    {
	      double initial_value = 0.0;
	      if($3 != NULL)
	      { 
		      if($3->get_type() == STRING || $3->get_type() == ANIMATION_BLOCK)
		      {
		        Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->get_type()), *$2, gpl_type_to_string($1));
		      }
		      if($3->get_type() == INT)
						initial_value = $3->eval_int();
				  else
       	  	initial_value = $3->eval_double();
    	  }
          Symbol* my_symbol = new Symbol(initial_value, *$2);
      	  symbol_table->insert(*$2, my_symbol);
      }	
	    if($1 == STRING)
	    {
				std::string initial_value = "";
				if($3 != NULL)
				{
					if($3->get_type() == ANIMATION_BLOCK)
          {
            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->get_type()), *$2, gpl_type_to_string($1));
					}
					else
	      	{
						std::ostringstream num;
	        	if($3->get_type() == INT)
						{
		  				num << $3->eval_int();
		  				initial_value = num.str();
						}
          	else if($3->get_type() == DOUBLE)
          	{
           	  num << $3->eval_double();
            	initial_value = num.str();
          	}
						else
	      	  	initial_value = $3->eval_string();
	      	}
				}
      	Symbol* my_symbol = new Symbol(initial_value, *$2);
        symbol_table->insert(*$2, my_symbol);
      }  
	  }
    }
    | simple_type  T_ID  T_LBRACKET expression T_RBRACKET
    {
			
	  if($4->get_type() != INT || $4->eval_int() <= 0)
	  {
			if($4->get_type() != INT)
				Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, gpl_type_to_base_string($4->get_type()), *$2);
			else
				Error::error(Error::INVALID_ARRAY_SIZE, *$2, std::to_string($4->eval_int()));
	  }
		else
		{
      static Symbol_table *symbol_table = Symbol_table::instance();
	    if( symbol_table->lookup(*$2) != NULL)
      {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
      }
			else
			{
      	Symbol* my_symbol = new Symbol($1, *$2, $4->eval_int());
      	symbol_table->insert(*$2, my_symbol);
			}
		}
    }
    ;

//---------------------------------------------------------------------
simple_type:
    T_INT 
    {
      $$ = INT;
    }
    | T_DOUBLE
    {
      $$ = DOUBLE; 
    }
    | T_STRING
    {
      $$ = STRING;
    }
    ;

//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression
    {
      $$ = $2;
    }
    | empty
    {
      $$ = NULL;
    }
    ;

//---------------------------------------------------------------------
object_declaration:
    object_type T_ID 
		{
    	static Symbol_table *symbol_table = Symbol_table::instance();
			error_object = false;
			if(symbol_table->lookup(*$2) != NULL)
			{
				Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
				error_object = true;
			}
			else
			{
				Symbol* sym = new Symbol($1, *$2); 
				cur_object_under_construction = sym->get_game_object_value();
				cur_object_under_construction_name = *$2;
      	symbol_table->insert(*$2, sym);
			}
		}
		T_LPAREN parameter_list_or_empty T_RPAREN
    | object_type T_ID T_LBRACKET expression T_RBRACKET
		{
			static Symbol_table *symbol_table = Symbol_table::instance();
			error_object = false;
	  	if($4->get_type() != INT || $4->eval_int() <= 0)
	  	{
				if($4->get_type() != INT)
				Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, gpl_type_to_base_string($4->get_type()), *$2);
				else
					Error::error(Error::INVALID_ARRAY_SIZE, *$2, std::to_string($4->eval_int()));
	  	}
			else
			{
				if(symbol_table->lookup(*$2) != NULL)
				{
					Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
					error_object = true;
				}
				else
				{
					Symbol* sym = new Symbol($1, *$2, $4->eval_int());
        	symbol_table->insert(*$2, sym);
				}
			}
		}
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
		{
			$$ = TRIANGLE;
		}
    | T_PIXMAP
    {
      $$ = PIXMAP;
    }
    | T_CIRCLE
    {
      $$ = CIRCLE;
    }
    | T_RECTANGLE
    {
      $$ = RECTANGLE;
    }
    | T_TEXTBOX
    {
      $$ = TEXTBOX;
    }
    ;

//---------------------------------------------------------------------
parameter_list_or_empty :
    parameter_list
    | empty
    ;

//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter
    | parameter
    ;

//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression
		{
			if(error_object == true)
			{
			
			}
			else
			{
				Status status;
				Gpl_type type;
				status = cur_object_under_construction->get_member_variable_type(*$1, type);
				if(status == MEMBER_NOT_DECLARED)
					Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, gpl_type_to_string(cur_object_under_construction->get_type()), *$1);
			else
			{
				status = cur_object_under_construction->get_member_variable_type(*$1, type);
				if(type == INT)
				{
					if($3->get_type() == STRING || $3->get_type() == DOUBLE)
					{
						Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, cur_object_under_construction_name, *$1);
					}
					else
						status = cur_object_under_construction->set_member_variable(*$1, $3->eval_int());
				}
				if(type == DOUBLE)
				{
					if($3->get_type() == STRING)
					{
						Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, cur_object_under_construction_name, *$1);
					}
			  	/*else if($3->get_type() == INT)
					{
						status = cur_object_under_construction->set_member_variable(*$1, $3->eval_int());
					}
					else*/
						status = cur_object_under_construction->set_member_variable(*$1, $3->eval_double());
			  }
        if(type == STRING)
        {
          /*if($3->get_type() == DOUBLE)
          {
            status = cur_object_under_construction->set_member_variable(*$1, $3->eval_double());
          }
          else if($3->get_type() == INT)
          {
						std::cout << "BITCH" << std::endl;
            status = cur_object_under_construction->set_member_variable(*$1, $3->eval_int());
          }
          else*/
            status = cur_object_under_construction->set_member_variable(*$1, $3->eval_string());
        }
				if(type == ANIMATION_BLOCK)
				{
					if(cur_object_under_construction->get_type() != (($3->eval_animation_block())->get_parameter_symbol())->get_type())
						Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT, cur_object_under_construction_name, animation_block_just_created_name);
					else
						status = cur_object_under_construction->set_member_variable(*$1, $3->eval_animation_block());
				}	
			}
			}
		}				
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
		{
      static Symbol_table *symbol_table = Symbol_table::instance();
			error_object = false;
			if(symbol_table->lookup(*$3) != NULL)
			{
				Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$3);
				error_object = true;
			}
			else
			{
				Symbol* sym = new Symbol(ANIMATION_BLOCK, *$3);
      	symbol_table->insert(*$3, sym);
				animation_block_just_created = sym->get_animation_block_value();
				animation_block_just_created->initialize($5, *$3);
				animation_block_just_created_name = *$3;
			}
		}
    ;

//---------------------------------------------------------------------
block_list:
    block_list block
    | empty
    ;

//---------------------------------------------------------------------
block:
    initialization_block
    | termination_block
    | animation_block
    | on_block
    ;

//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block
    ;

//---------------------------------------------------------------------
termination_block:
    T_TERMINATION statement_block
    ;

//---------------------------------------------------------------------
animation_block:
    T_ANIMATION T_ID T_LPAREN check_animation_parameter T_RPAREN T_LBRACE statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    {
      static Symbol_table *symbol_table = Symbol_table::instance();
			if(error_object == true)
			{
				$$ = NULL;
			}
			else
			{
				if(symbol_table->lookup(*$2) != NULL)
				{
					Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *$2);
					$$ = NULL;
				}
				else
				{
      		Symbol* sym = new Symbol($1, *$2);
      		symbol_table->insert(*$2, sym);
					cur_object_under_construction = sym->get_game_object_value();
					cur_object_under_construction->never_animate();
					cur_object_under_construction->never_draw();
					$$ = sym;
				}
			}
    }
    ;

//---------------------------------------------------------------------
check_animation_parameter:
    object_type T_ID
    ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block
		{
			static Event_manager *event_manager	= Event_manager::instance();
			event_manager->insert($3, $2);
		}
    ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
		{
			$$ = Window::SPACE;
		}
    | T_UPARROW
    {
      $$ = Window::UPARROW;
    }
    | T_DOWNARROW
    {
      $$ = Window::DOWNARROW;
    }
    | T_LEFTARROW 
    {
      $$ = Window::LEFTARROW;
    }
    | T_RIGHTARROW
    {
      $$ = Window::RIGHTARROW;
    }
    | T_LEFTMOUSE_DOWN
    {
      $$ = Window::LEFTMOUSE_DOWN;
    }
    | T_MIDDLEMOUSE_DOWN
    {
      $$ = Window::MIDDLEMOUSE_DOWN;
    }
    | T_RIGHTMOUSE_DOWN
    {
      $$ = Window::RIGHTMOUSE_DOWN;
    }
    | T_LEFTMOUSE_UP
    {
      $$ = Window::LEFTMOUSE_UP;
    }
    | T_MIDDLEMOUSE_UP
    {
      $$ = Window::MIDDLEMOUSE_UP;
    }
    | T_RIGHTMOUSE_UP
    {
      $$ = Window::RIGHTMOUSE_UP;
    }
    | T_MOUSE_MOVE
    {
      $$ = Window::MOUSE_MOVE;
    }
    | T_MOUSE_DRAG
    {
      $$ = Window::MOUSE_DRAG;
    }
    | T_AKEY
    {
      $$ = Window::AKEY;
    }
    | T_SKEY
    {
      $$ = Window::SKEY;
    }
    | T_DKEY
    {
      $$ = Window::DKEY;
    }
    | T_FKEY
    {
      $$ = Window::FKEY;
    }
    | T_HKEY
    {
      $$ = Window::HKEY;
    }
    | T_JKEY
    {
      $$ = Window::JKEY;
    }
    | T_KKEY
    {
      $$ = Window::KKEY;
    }
    | T_LKEY
    {
      $$ = Window::LKEY;
    }
    | T_WKEY
    {
      $$ = Window::WKEY;
    }
    | T_F1
    {
      $$ = Window::F1;
    }
    ;

//---------------------------------------------------------------------
if_block:
    statement_block_creator statement end_of_statement_block
		{
			$$ = $1;
		}
    | statement_block
		{
			$$ = $1;
		}
    ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
		{
			$$ = $2;
		}
    ;

//---------------------------------------------------------------------
statement_block_creator:
		{
			Statement_block *temp_block = new Statement_block;
			m_stack.push(temp_block);
			$$ = temp_block;
		}
    ;

//---------------------------------------------------------------------
end_of_statement_block:
		{
			m_stack.pop();
		}
    ;

//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | empty
    ;

//---------------------------------------------------------------------
statement:
    if_statement
		{
			$$ = $1;
		}
    | for_statement
		{
			$$ = $1;
		}
    | assign_statement T_SEMIC
		{
			$$ = $1;
		}
    | print_statement T_SEMIC
		{
			$$ = $1;
		}
    | exit_statement T_SEMIC
		{
			$$ = $1;
		}
    ;

//---------------------------------------------------------------------
if_statement:
    T_IF T_LPAREN expression T_RPAREN if_block %prec IF_NO_ELSE
		{
      if($3->get_type() != INT)
      {
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
      }
			Statement *m_if = new If_stmt($3, $5);
			(m_stack.top())->insert(m_if);
		}
    | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block
		{
      if($3->get_type() != INT)
      {
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
      }
			Statement *m_if = new If_stmt($3, $5, $7);
			(m_stack.top())->insert(m_if);
		}
    ;

//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN statement_block_creator assign_statement end_of_statement_block T_SEMIC expression T_SEMIC statement_block_creator assign_statement end_of_statement_block T_RPAREN statement_block
		{
			if($7->get_type() != INT)
			{
				Error::error(Error::INVALID_TYPE_FOR_FOR_STMT_EXPRESSION);
			}
			Statement *m_for = new For_stmt($3, $9, $13, $7);
			(m_stack.top())->insert(m_for);
		}
    ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN
		{
			if($3->get_type() == ANIMATION_BLOCK || $3->get_type() == CIRCLE ||$3->get_type() == RECTANGLE || $3->get_type() == TRIANGLE || $3->get_type() == PIXMAP || $3->get_type() == TEXTBOX)
			{
				Error::error(Error::INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION);
			}
			else
			{
				Statement *print = new Print_stmt($3, $1);
				(m_stack.top())->insert(print);
			}
		}
    ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN
		{
			if($3->get_type() != INT)
			{
				Error::error(Error::EXIT_STATUS_MUST_BE_AN_INTEGER, gpl_type_to_string($3->get_type()));
			}
			else
			{
				Statement *exit = new Exit_stmt($3, $1);
				(m_stack.top())->insert(exit);
			}
		}
    ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
		{
 		 if($1->get_type() == INT && $3->get_type() != INT)
			{
				Error::error(Error::ASSIGNMENT_TYPE_ERROR, gpl_type_to_string($1->get_type()), gpl_type_to_string($3->get_type()));
			}
 		 if($1->get_type() == RECTANGLE || $1->get_type() == CIRCLE || $1->get_type() == TRIANGLE || $1->get_type() == TEXTBOX || $1->get_type() == PIXMAP)
			{
				Error::error(Error::INVALID_LHS_OF_ASSIGNMENT, $1->get_id(), gpl_type_to_string($1->get_type()));
			}
 		 if($1->get_type() == DOUBLE && $3->get_type() == STRING)
			{
				Error::error(Error::ASSIGNMENT_TYPE_ERROR, gpl_type_to_string($1->get_type()), gpl_type_to_string($3->get_type()));
			}
			Statement *assign = new Assignment_stmt($1, $3, ASSIGN);
			(m_stack.top())->insert(assign);
		}
    | variable T_PLUS_ASSIGN expression
		{
		if($1->get_type() == INT && $3->get_type() != INT)
			{
				Error::error(Error::PLUS_ASSIGNMENT_TYPE_ERROR, gpl_type_to_string($1->get_type()), gpl_type_to_string($3->get_type()));
			}
		if($1->get_type() == DOUBLE && $3->get_type() == STRING)
			{
				Error::error(Error::PLUS_ASSIGNMENT_TYPE_ERROR, gpl_type_to_string($1->get_type()), gpl_type_to_string($3->get_type()));
			}
     if($1->get_type() == RECTANGLE || $1->get_type() == CIRCLE || $1->get_type() == TRIANGLE || $1->get_type() == TEXTBOX || $1->get_type() == PIXMAP || $1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LHS_OF_PLUS_ASSIGNMENT, $1->get_id(), gpl_type_to_string($1->get_type()));
      }
			Statement *assign = new Assignment_stmt($1, $3, PLUS_ASSIGN);
			(m_stack.top())->insert(assign);
		}
    | variable T_MINUS_ASSIGN expression
		{
		if($1->get_type() != INT && $1->get_type() != DOUBLE)
			{
				Error::error(Error::INVALID_LHS_OF_MINUS_ASSIGNMENT, $1->get_id(), gpl_type_to_string($1->get_type()));
			}
		if($1->get_type() == INT && $3->get_type() == DOUBLE)
		{
				Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR, gpl_type_to_string($1->get_type()), gpl_type_to_string($3->get_type()));
		}
		if($1->get_type() == DOUBLE && $3->get_type() == STRING)
		{
				Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR, gpl_type_to_string($1->get_type()), gpl_type_to_string($3->get_type()));
		}
			else 
			{
				Statement *assign = new Assignment_stmt($1, $3, MINUS_ASSIGN);
				(m_stack.top())->insert(assign);
			}
		}
    | variable T_PLUS_PLUS
		{
		if($1->get_type() != INT)
			{
				Error::error(Error::INVALID_LHS_OF_PLUS_PLUS, $1->get_id(), gpl_type_to_string($1->get_type()));
			}
			Statement *assign = new Assignment_stmt($1, NULL, PLUS_PLUS);
			(m_stack.top())->insert(assign);
		}
    | variable T_MINUS_MINUS
		{
			if($1->get_type() != INT)
			{
				Error::error(Error::INVALID_LHS_OF_MINUS_MINUS, $1->get_id(), gpl_type_to_string($1->get_type()));
			}
			Statement *assign = new Assignment_stmt($1, NULL, MINUS_MINUS);
			(m_stack.top())->insert(assign);
		}
    ;

//---------------------------------------------------------------------
variable:
    T_ID
    {
      static Symbol_table *symbol_table = Symbol_table::instance();
      Symbol *my_sym = symbol_table->lookup(*$1);
			if(my_sym == NULL)
			{
				Error::error(Error::UNDECLARED_VARIABLE, *$1);
				$$ = new Variable(new Symbol(0, ""));
			}
			else
				$$ = new Variable(my_sym);
    } 
    | T_ID T_LBRACKET expression T_RBRACKET
    {
			static Symbol_table *symbol_table = Symbol_table::instance();
			Symbol *my_sym = symbol_table->lookup(*$1);
			if(my_sym == NULL)
			{
				Error::error(Error::UNDECLARED_VARIABLE, *$1+"[]");
				$$ = new Variable(new Symbol(0, ""));
			}
			else if(my_sym->get_size() == -1)
			{
				Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
				$$ = new Variable(new Symbol(0, ""));
			}
			else if($3->get_type() != INT)
			{
				if($3->get_type() == DOUBLE || $3->get_type() == STRING)
				{
					Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A " +gpl_type_to_string($3->get_type())+" expression");
					$$ = new Variable(new Symbol(0, ""));
				}
			}
		  else $$ = new Variable(my_sym, $3);
    }
    | T_ID T_PERIOD T_ID
    {
      static Symbol_table *symbol_table = Symbol_table::instance();
      Symbol *my_sym = symbol_table->lookup(*$1);
      if(my_sym == NULL)
      { 
        Error::error(Error::UNDECLARED_VARIABLE, *$1);
        $$ = new Variable(new Symbol(0, ""));
      }
			else if(my_sym->get_type() == INT || my_sym->get_type() == DOUBLE || my_sym->get_type() == STRING)
			{
				Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
				$$ = new Variable(new Symbol(0, ""));
			}
			else 
			{
				Gpl_type type;
				Status status = ((my_sym->get_game_object_value())->get_member_variable_type(*$3, type));
				if(status != OK)
				{
					Error::error(Error::UNDECLARED_MEMBER, *$1, *$3);
					$$ = new Variable(new Symbol(0, ""));
				}
				else        
					$$ = new Variable(my_sym, *$3);
			}
			
    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
    {
			static Symbol_table *symbol_table = Symbol_table::instance();
		  Symbol *my_sym = symbol_table->lookup(*$1);
			if(my_sym == NULL)
			{
				Error::error(Error::UNDECLARED_VARIABLE, *$1);
				$$ = new Variable(new Symbol(0, ""));
			}
      else if(my_sym->get_type() == INT_ARRAY || my_sym->get_type() == DOUBLE_ARRAY || my_sym->get_type() == STRING_ARRAY)
      {
        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
        $$ = new Variable(new Symbol(0, ""));
      }
       else if($3->get_type() == DOUBLE || $3->get_type() == STRING)
        { 
          Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A " +gpl_type_to_string($3->get_type())+" expression");
          $$ = new Variable(new Symbol(0, ""));
        }
      else
      {
        Gpl_type type;
        Status status = ((my_sym->get_game_object_value())->get_member_variable_type(*$6, type));
        if(status != OK)
        {
          Error::error(Error::UNDECLARED_MEMBER, *$1, *$6);
          $$ = new Variable(new Symbol(0, ""));
        }
        else
          $$ = new Variable(my_sym, $3, *$6);
      }
    }
    ;

//---------------------------------------------------------------------
expression:
    primary_expression
    {
      $$ = $1;
    }
    | expression T_OR expression
    {
      if($1->get_type() == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||");
        $$ = new Expression(0);
      }
      if($3->get_type() == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||");
        $$ = new Expression(0);
      }
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||");
        $$ = new Expression(0);
      }
      else
        $$ = new Expression($1, OR, $3);
    }
    | expression T_AND expression
    {
      if($1->get_type() == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&");
        $$ = new Expression(0);
      }
      if($3->get_type() == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
        $$ = new Expression(0);
      }
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
        $$ = new Expression(0);
      }
      else
        $$ = new Expression($1, AND, $3);
    }
    | expression T_LESS_EQUAL expression 
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "<=");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "<=");
        $$ = new Expression(0);
      }
      $$ = new Expression($1, LESS_EQUAL, $3);
    }
    | expression T_GREATER_EQUAL  expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, ">=");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, ">=");
        $$ = new Expression(0);
      }
      $$ = new Expression($1, GREATER_EQUAL, $3);
    }
    | expression T_LESS expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "<");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "<");
        $$ = new Expression(0);
      }
      $$ = new Expression($1, LESS_THAN, $3);
    }
    | expression T_GREATER  expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, ">");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, ">");
        $$ = new Expression(0);
      }
      $$ = new Expression($1, GREATER_THAN, $3);
    }
    | expression T_EQUAL expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "==");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "==");
        $$ = new Expression(0);
      }
      $$ = new Expression($1, EQUAL, $3);
    }
    | expression T_NOT_EQUAL expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "!=");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!=");
        $$ = new Expression(0);
      }
      $$ = new Expression($1, NOT_EQUAL, $3);
    }
    | expression T_PLUS expression
    {
      if($1->get_type() == ANIMATION_BLOCK || $1->get_type() & GAME_OBJECT)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "+");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK || $3->get_type() & GAME_OBJECT)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "+");
        $$ = new Expression(0);
      }
      else
			  $$ = new Expression($1, PLUS, $3);
    }
    | expression T_MINUS expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-");
        $$ = new Expression(0);
      }
      if($1->get_type() == STRING)
      { 
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-");
        $$ = new Expression(0);
      }
      if($3->get_type() == STRING)
      { 
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-");
        $$ = new Expression(0);
      }
      if($1->get_type() != STRING && $3->get_type() != STRING)
      { 
        $$ = new Expression($1, MINUS, $3);
      }
    }
    | expression T_MULTIPLY expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*");
        $$ = new Expression(0);
      }
      if($1->get_type() == STRING)
      {
	Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*");
        $$ = new Expression(0);
      }
      if($3->get_type() == STRING)
      {
	Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*");
        $$ = new Expression(0);
      }
      if($1->get_type() != STRING && $3->get_type() != STRING)
      {
        $$ = new Expression($1, MULTIPLY, $3);
      }
    }
    | expression T_DIVIDE expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/");
        $$ = new Expression(0);
      }
      if($1->get_type() == STRING)
      {
	Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/");
        $$ = new Expression(0);
      }
      if($3->get_type() == STRING)
      {
	Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/");
        $$ = new Expression(0);
      }
			if($3->get_type() != STRING)
			{
      	if($3->eval_double() == 0)
      	{
        	Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME, "/");
					$$ = new Expression(0);
      	}
			}
      if($1->get_type() != STRING && $3->get_type() != STRING && $3->eval_double() != 0)
      {
        $$ = new Expression($1, DIVIDE, $3);
      }
    }
    | expression T_MOD expression
    {
      if($1->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%");
        $$ = new Expression(0);
      }
      if($3->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%");
        $$ = new Expression(0);
      }
      if($1->get_type() == STRING || $1->get_type() == DOUBLE)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%");
        $$ = new Expression(0);
      }
      if($3->get_type() == STRING || $3->get_type() == DOUBLE)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%");
        $$ = new Expression(0);
      }
			else
			{
      	if($3->eval_int() == 0)
      	{
        	Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME, "%");
        	$$ = new Expression(0);
      	}
				else
        $$ = new Expression($1, MOD, $3);
			}
    }
    | T_MINUS  expression %prec T_UNARY_OPS
    {
      if($2->get_type() == STRING)
      {
        Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR, "-");
        $$ = new Expression(0);
      }
      else if($2->get_type() == INT)
      {
        $$ = new Expression($2, UNARY_MINUS);
      }
      else if($2->get_type() == DOUBLE)
      {
        $$ = new Expression($2, UNARY_MINUS);
      }
    }
    | T_NOT %prec T_UNARY_OPS expression  
    {
      if($2->get_type() == ANIMATION_BLOCK)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!");
        $$ = new Expression(0);
      }
      if($2->get_type() == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!");
        $$ = new Expression(0);
      }
      else
        $$ = new Expression($2, NOT);
    }
    | math_operator T_LPAREN expression T_RPAREN
    {
      if($3->get_type() == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string($1));
        $$ = new Expression(0);
      }
			else if($1 == RANDOM)
			{
				if($3->eval_double() < 1)
				{
					std::ostringstream num;
					num << $3->eval_double();
					Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, num.str());
					$$ = new Expression(0);
				}
				else
					$$ = new Expression($3, $1);
			}
      else
        $$ = new Expression($3, $1);
    }
    | expression T_NEAR expression
    | expression T_TOUCHES expression
    ;

//---------------------------------------------------------------------
primary_expression:
    T_LPAREN  expression T_RPAREN
    {
      $$ = $2;
    }
    | variable
    {
      $$ = new Expression($1);
    }
    | T_INT_CONSTANT
    {
      $$ = new Expression($1);
    }
    | T_TRUE
    {
      $$ = new Expression(1);
    }
    | T_FALSE
    {
      $$ = new Expression(0);
    }
    | T_DOUBLE_CONSTANT
    {
      $$ = new Expression($1);
    }
    | T_STRING_CONSTANT
    {
      $$ = new Expression($1);
    }
    ;

//---------------------------------------------------------------------
math_operator:
    T_SIN
    {
      $$ = SIN;
    }
    | T_COS
    {
      $$ = COS;
    }
    | T_TAN
    {
      $$ = TAN;
    }
    | T_ASIN
    {
      $$ = ASIN;
    }
    | T_ACOS
    {
      $$ = ACOS;
    }
    | T_ATAN
    {
      $$ = ATAN;
    }
    | T_SQRT
    {
      $$ = SQRT;
    }
    | T_ABS
    {
      $$ = ABS;
    }
    | T_FLOOR
    {
      $$ = FLOOR;
    }
    | T_RANDOM
    {
      $$ = RANDOM;
    }
    ;

//---------------------------------------------------------------------
empty:
    // empty goes to nothing so that you can use empty in productions
    // when you want a production to go to nothing
    ;
