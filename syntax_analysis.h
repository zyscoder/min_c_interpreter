#pragma once
#ifndef syntax_analysis_h
#define syntax_analysis_h

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "lexical_analysis.h"

extern enum{ INT, REAL, STRING, VOID, PTR };

void next()
{
	get_next_token();
	if (token == '{') {
		ed[depth + 1] = ed[depth];
		depth++;
	}
	else if (token == '}')depth--;
}

void match(int tok) {
	if (token == tok) {
		next();
	}
	else {
		printf("%d: expected token: %d\n", line, tok);
		exit(-1);
	}
}

void function_body()
{

}

void function_parameter()
{
	int type;
	while (token != ')')
	{
		if (token == Int) { match(Int); type == INT; }
		else if (token == String) { match(String); type == STRING; }
		else if (token == Real) { match(Real); type == REAL; }
		else if (token == Void) { match(Void); type == VOID; }

		//pointer type
		while (token == Mul) {
			match(Mul);
			type = type + PTR;
		}

		//paramater name
		if (token != Id) {
			printf("%d: bad paramater declaration\n", line);
			exit(-1);
		}

		match(Id);
		cur_id->class_ = Var;
		cur_id->addr = (int)data_;
		data_ = (void *)((int)data_ + sizeof(int));

		if (token == ',')match(',');
	}
}

void function_declaration()
{
	// type func_name (...) {...}
	//               | this part

	match('(');
	function_parameter();
	match(')');

	match('{');
	function_body();
	//match("}"); //this '}' has been matched in function_body
}

void global_declaration()
{
	//EBNF: 

	// global_declaration ::= enum_decl | variable_decl | function_decl
	//
	// enum_decl ::= 'enum' [id] '{' id ['=' 'num'] {',' id ['=' 'num'} '}'
	//
	// variable_decl ::= type {'*'} id { ',' {'*'} id } ';'
	//
	// function_decl ::= type {'*'} id '(' parameter_decl ')' '{' body_decl '}'

	int type;
	int i;

	if (token == Int) { match(Int); type == INT; }
	else if (token == String) { match(String); type == STRING; }
	else if (token == Real){ match(Real); type == REAL; }
	else if (token == Void){ match(Void); type == VOID; }

	while (token != ';' && token != '}')
	{
		while (token == MUL) { //index
			match(MUL);
			type = type + PTR;
		}

		if (token != Id) {
			//invalid declaration
			printf("%d: bad global declaration\n", line);
			exit(-1);
		}
		if (cur_id->class_) {
			printf("%d: duplicate global declaration\n", line);
			exit(-1);
		}
		match(Id);
		cur_id->class_ = type;

		if (token == '(')
		{
			cur_id->class_ = Fun;
			cur_id->addr = (int)text;
			function_declaration();
		}
		else
		{
			cur_id->class_ = Var;
			cur_id->addr = (int)data_;
			data_ = (void *)((int)data_ + sizeof(int));
		}

		if (token == ',') match(',');
	}
	get_next_token();
}

void program()
{
	next();
	while (token > 0) {
		global_declaration();
	}
}

#endif