/* the %{ indicates the start of C/C++ code section */
/* you can put whatever C/C++ code in here that you want */
/* this code is copied to the generated file */
%{

#include "error.h"    // gpl file, using now to get use to it
#include "parser.h"   // gpl file, using now to get use to it

// #include <ctype.h>
#include <iostream>
using namespace std;

Error error_handler; // error reporting object

int line_count = 1;

void get_int_value()
{
  // assumes that the string in yytext is an integer
  // convert the string yytext into an integer
  // put the int into global union used to send values to the parser (record.y)
  // the union and its union_int field are declared in record.y
  yylval.union_int = atoi(yytext);
}

void get_string_value()
{
  // Would like to put a string in the union, but the way the union works
  // it has to be a pointer to a string.
  if(yytext[0] == '"')
  {
    yytext[yyleng-1] = 0;
    yylval.union_string = new string(yytext+1);
  }
  else
    yylval.union_string = new string(yytext);
}

void get_double_value()
{
  //converts the string yytext into a double
  //then stores the double value into global union yylval
  yylval.union_double = atof(yytext);
}

void error()
{
  // have the error handling object report the problem
  // note: it uses line_count as a global variable
  error_handler.error(Error::ILLEGAL_TOKEN, yytext);

  // create a string to hold the current text
  // put that string in the yylval union so it can be used by parser (.y file)
  yylval.union_string = new string(yytext);
}

void set_line_number()
{
  yylval.union_int = line_count;
}

// the %} below indicates the end of the C/C++ code section

%}

/*
The %% below indicates the start of the rules flex/lex will use
The left-hand-side (LHS) specifies a regular expression
The right-hand-side (RHS) specifies an action (code to execute) when
  the regular expression is matched.
*/

%%


[\n]            line_count++; // count the lines for error reporting
[ \t\r]         ; // ignore spaces, tabs and the microsoft line feed (\r)

"int"			return T_INT;
"double" 		return T_DOUBLE;
"string"		return T_STRING;
"triangle"		return T_TRIANGLE;
"pixmap"		return T_PIXMAP;
"circle" 		return T_CIRCLE;
"rectangle"		return T_RECTANGLE;
"textbox"		return T_TEXTBOX;
"forward"		set_line_number(); return T_FORWARD;
"initialization"	return T_INITIALIZATION;
"termination"		return T_TERMINATION;
"true"			return T_TRUE;
"false"			return T_FALSE;
"touches"		return T_TOUCHES;
"near"			return T_NEAR;
"animation"		return T_ANIMATION;
"if"			return T_IF;
"for"			return T_FOR;
"else"			return T_ELSE;
"print"			set_line_number(); return T_PRINT;
"exit"			set_line_number(); return T_EXIT;
"("			return T_LPAREN;
")"			return T_RPAREN;
"{"             	return T_LBRACE;
"}"             	return T_RBRACE;
"["			return T_LBRACKET;
"]"			return T_RBRACKET;
";"             	return T_SEMIC;
","             	return T_COMMA;
"."			return T_PERIOD;
"="			return T_ASSIGN;
"+="			return T_PLUS_ASSIGN;
"-="			return T_MINUS_ASSIGN;
"++"			return T_PLUS_PLUS;
"--"			return T_MINUS_MINUS;
"*"			return T_MULTIPLY;
"/"			return T_DIVIDE;
"%"			return T_MOD;
"+"			return T_PLUS;
"-"			return T_MINUS;
"sin"			return T_SIN;
"cos"			return T_COS;
"tan"			return T_TAN;
"asin"			return T_ASIN;
"acos"			return T_ACOS;
"atan"			return T_ATAN;
"sqrt"			return T_SQRT;
"floor"			return T_FLOOR;
"abs"			return T_ABS;
"random"		return T_RANDOM;
"<"			return T_LESS;
">"			return T_GREATER;
"<="			return T_LESS_EQUAL;
">="			return T_GREATER_EQUAL;
"=="			return T_EQUAL;
"!="			return T_NOT_EQUAL;
"&&"			return T_AND;
"||"			return T_OR;
"!"			return T_NOT;
"on"			return T_ON;
"space"			return T_SPACE;
"leftarrow"		return T_LEFTARROW;
"rightarrow"		return T_RIGHTARROW;
"uparrow"		return T_UPARROW;
"downarrow"		return T_DOWNARROW;
"leftmouse_down"	return T_LEFTMOUSE_DOWN;
"middlemouse_down"	return T_MIDDLEMOUSE_DOWN;
"rightmouse_down"	return T_RIGHTMOUSE_DOWN;
"mouse_move"		return T_MOUSE_MOVE;
"mouse_drag"		return T_MOUSE_DRAG;
"f1"			return T_F1;
"akey"			return T_AKEY;
"skey"			return T_SKEY;
"dkey"			return T_DKEY;
"fkey"			return T_FKEY;
"hkey"			return T_HKEY;
"jkey"			return T_JKEY;
"kkey"			return T_KKEY;
"lkey"			return T_LKEY;
"wkey"			return T_WKEY;

[0-9]+               get_int_value();    return T_INT_CONSTANT;
[0-9]+[.][0-9]*|[.][0-9]+  get_double_value(); return T_DOUBLE_CONSTANT;
[\"][^",;\n]*[\"]  get_string_value(); return T_STRING_CONSTANT;
[A-Za-z_]+[0-9A-Za-z]*     get_string_value(); return T_ID;
[\/][\/].*      ; //comments

.               error(); return T_ERROR;
