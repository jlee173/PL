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

using namespace std;

// bison syntax to indicate the end of the header
%}

%union {
 int            union_int;
 std::string    *union_string;  // MUST be a pointer to a string (this sucks!)
 double         union_double;
 Gpl_type	union_gpl_type;
 Expression     *union_expression;
 Variable       *union_variable;
 Operator_type  union_operator_type;
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
%token < > T_PRINT           "print" // value is line number
%token < > T_EXIT            "exit" // value is line number

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
%token T_NOT_EQUAL           "!="

%token T_AND                 "&&"
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
		      if($3->get_type() == STRING)
		      {
		        Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->get_type()), *$2, gpl_type_to_string($1));
		      }
		    else
	      initial_value = $3->eval_int();
	      }
   	      Symbol* my_symbol = new Symbol(initial_value, *$2);
   	      symbol_table->insert(*$2, my_symbol);
      }
	    else if($1 == DOUBLE)
	    {
	      double initial_value = 0.0;
	      if($3 != NULL)
	      { 
		      if($3->get_type() == STRING)
		      {
		        Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->get_type()), *$2, gpl_type_to_string($1));
		      }
		      else
		      {
       	  initial_value = $3->eval_double();
	        }
    	  }
          Symbol* my_symbol = new Symbol(initial_value, *$2);
      	  symbol_table->insert(*$2, my_symbol);
      }	
	    else if($1 == STRING)
	    {
	      std::string initial_value = "";
	      if($3 != NULL)
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
      	  Symbol* my_symbol = new Symbol(initial_value, *$2);
          symbol_table->insert(*$2, my_symbol);
      }  
	  }
    }
    | simple_type  T_ID  T_LBRACKET expression T_RBRACKET
    {
	  if( $4 == 0)
	  {
		Error::error(Error::INVALID_ARRAY_SIZE, *$2, "0");
	  }
      static Symbol_table *symbol_table = Symbol_table::instance();
	    if( symbol_table->lookup(*$2) != NULL)
      {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
      }
      Symbol* my_symbol = new Symbol($1, *$2);
      symbol_table->insert(*$2, my_symbol);
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
    object_type T_ID T_LPAREN parameter_list_or_empty T_RPAREN
    | object_type T_ID T_LBRACKET expression T_RBRACKET
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    | T_PIXMAP
    | T_CIRCLE
    | T_RECTANGLE
    | T_TEXTBOX
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
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
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
    ;

//---------------------------------------------------------------------
check_animation_parameter:
    object_type T_ID
    ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block
    ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
    | T_UPARROW
    | T_DOWNARROW
    | T_LEFTARROW 
    | T_RIGHTARROW
    | T_LEFTMOUSE_DOWN
    | T_MIDDLEMOUSE_DOWN
    | T_RIGHTMOUSE_DOWN
    | T_LEFTMOUSE_UP
    | T_MIDDLEMOUSE_UP
    | T_RIGHTMOUSE_UP
    | T_MOUSE_MOVE
    | T_MOUSE_DRAG
    | T_AKEY
    | T_SKEY
    | T_DKEY
    | T_FKEY
    | T_HKEY
    | T_JKEY
    | T_KKEY
    | T_LKEY
    | T_WKEY
    | T_F1
    ;

//---------------------------------------------------------------------
if_block:
    statement_block_creator statement end_of_statement_block
    | statement_block
    ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
statement_block_creator:
    // this goes to nothing so that you can put an action here in p7
    ;

//---------------------------------------------------------------------
end_of_statement_block:
    // this goes to nothing so that you can put an action here in p7
    ;

//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | empty
    ;

//---------------------------------------------------------------------
statement:
    if_statement
    | for_statement
    | assign_statement T_SEMIC
    | print_statement T_SEMIC
    | exit_statement T_SEMIC
    ;

//---------------------------------------------------------------------
if_statement:
    T_IF T_LPAREN expression T_RPAREN if_block %prec IF_NO_ELSE
    | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block
    ;

//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN statement_block_creator assign_statement end_of_statement_block T_SEMIC expression T_SEMIC statement_block_creator assign_statement end_of_statement_block T_RPAREN statement_block
    ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    | variable T_PLUS_ASSIGN expression
    | variable T_MINUS_ASSIGN expression
    | variable T_PLUS_PLUS
    | variable T_MINUS_MINUS
    ;

//---------------------------------------------------------------------
variable:
    T_ID
    {
      static Symbol_table *symbol_table = Symbol_table::instance();
      Symbol *my_sym = symbol_table->lookup(*$1);
      $$ = new Variable(my_sym);
    } 
    | T_ID T_LBRACKET expression T_RBRACKET
    {
      assert(false && "not implemented yet");
    }
    | T_ID T_PERIOD T_ID
    {
      assert(false && "not implemented yet");
    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
    {
      assert(false && "not implemented yet");
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
      else
        $$ = new Expression($1, AND, $3);
    }
    | expression T_LESS_EQUAL expression 
    {
      $$ = new Expression($1, LESS_EQUAL, $3);
    }
    | expression T_GREATER_EQUAL  expression
    {
      $$ = new Expression($1, GREATER_EQUAL, $3);
    }
    | expression T_LESS expression
    {
      $$ = new Expression($1, LESS_THAN, $3);
    }
    | expression T_GREATER  expression
    {
      $$ = new Expression($1, GREATER_THAN, $3);
    }
    | expression T_EQUAL expression
    {
      $$ = new Expression($1, EQUAL, $3);
    }
    | expression T_NOT_EQUAL expression
    {
      $$ = new Expression($1, NOT_EQUAL, $3);
    }
    | expression T_PLUS expression
    {
        $$ = new Expression($1, PLUS, $3);
    }
    | expression T_MINUS expression
    {
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
      if($3->eval_double() == 0)
      {
        Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME, "/");
	$$ = new Expression(0);
      }
      if($1->get_type() != STRING && $3->get_type() != STRING && $3->eval_double() != 0)
      {
        $$ = new Expression($1, DIVIDE, $3);
      }
    }
    | expression T_MOD expression
    {
      if($1->get_type() == STRING)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%");
        $$ = new Expression(0);
      }
      if($3->get_type() == STRING)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%");
        $$ = new Expression(0);
      }
      if($1->get_type() == DOUBLE)
      {
        Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%");
        $$ = new Expression(0);
      }
      if($3->get_type() == DOUBLE)
      {
        Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%");
        $$ = new Expression(0);
      }
      else if($3->eval_int() == 0)
      {
        Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME, "%");
        $$ = new Expression(0);
      }
      else
        $$ = new Expression($1, MOD, $3);
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
    | T_NOT  expression 
    {
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
			/*else if($1 == RANDOM)
				ERROR RANDOM GUY FOR N < 1
				--there is an error for runtime and an error for parse time--
			*/
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
