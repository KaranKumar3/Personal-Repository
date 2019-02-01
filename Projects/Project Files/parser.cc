/*
 * Copyright (C) Rida Bazzi, 2017
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */
#include <iostream>
#include <cstdlib>
#include "parser.h"

using namespace std;
// assembly code -- g++ --std=c++11 -pedantic -Wall parser.cc inputbuf.cc lexer.cc

/**Structure Time**/
struct stmt {
    int stmt_type;
    int LHS = 0;
    int operator_type = 0;
    int op1 = 0;
    int op2 = 0;

    struct stmt * proc_code {

    };
    struct stmt * next {

    };
};

struct symbol {
    string name;
    int index;
};

struct proc {
    string name;
    struct stmt * code{

    };
};

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}

Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

Token Parser :: peek()
{
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}

// Parsing
void Parser :: input() 
{
    program();
    inputs();
}

void Parser :: program() 
{
    Token t = lexer.GetToken();

    if (t.token_type == MAIN) {
        lexer.UngetToken(t);
        parse_main();
    }
    else if (t.token_type == PROC) {
        lexer.UngetToken(t);
        proc_decl_section();
    }
    else {
         syntax_error();
    }
}

void Parser :: proc_decl_section() 
{
    proc_decl();
    Token t = peek();

    if (t.token_type == PROC) {
        proc_decl_section();
    }
    else {
        syntax_error();
    }      
}

void Parser :: proc_decl() 
{
    expect(PROC);
    procedure_name();
    procedure_body();
    expect(ENDPROC);
}

void Parser :: procedure_name() 
{
    Token t = peek();
    if (t.token_type == ID) {
        expect(ID);
    } else if (t.token_type == NUM){
        expect(NUM);
    }
    else {
        syntax_error();
    }      
}

void Parser :: procedure_body() 
{
    statement_list();
}

void Parser :: statement_list()
 {
    statement();

    Token t = lexer.GetToken();
    Token nextT = peek();

    lexer.UngetToken(t);

    if (t.token_type == NUM && nextT.token_type == SEMICOLON) {
        statement_list();
    }
    else if ((t.token_type == NUM && nextT.token_type == NUM) || t.token_type == ENDPROC) {
        return;
    }
    else if(t.token_type == INPUT || t.token_type == OUTPUT || t.token_type == NUM 
            || t.token_type == DO || t.token_type == ID) {
        statement_list();
    } 
    else {
        syntax_error();
    }

}

void Parser :: statement() {

    Token t = lexer.GetToken();
	
    if (t.token_type == INPUT) {
		lexer.UngetToken(t);
        input_statement();
    }
    else if (t.token_type == OUTPUT) {
        lexer.UngetToken(t);
        output_statement();
    }
    else if (t.token_type == NUM) {
        lexer.UngetToken(t);
        procedure_invocation();
    }
    else if (t.token_type == DO) {
        lexer.UngetToken(t);
        do_statement();
    }
    else if (t.token_type == ID) {

        Token nextT = lexer.GetToken();
        lexer.UngetToken(nextT);

        if (nextT.token_type == EQUAL) {
            lexer.UngetToken(t);
            assign_statement();
        }
        else if (nextT.token_type == SEMICOLON) {
            lexer.UngetToken(t);
            procedure_invocation();
        }
        else {
            syntax_error();
		}
    }
    else {
		syntax_error();
	}
}

void Parser :: input_statement() {
    expect(INPUT);
    expect(ID);
    expect(SEMICOLON);
}

void Parser :: output_statement() {
    expect(OUTPUT);
    expect(ID);
    expect(SEMICOLON);
}

void Parser :: procedure_invocation() {
    procedure_name();
    expect(SEMICOLON);
}

void Parser :: do_statement() {
    expect(DO);
    expect(ID);
    procedure_invocation();
}

void Parser :: assign_statement() {
    expect(ID);
    expect(EQUAL);
    expr();
    expect(SEMICOLON);
}

void Parser :: expr() {
	
    primary();

    Token t = lexer.GetToken();
	lexer.UngetToken(t);

    if (t.token_type == PLUS || t.token_type == MINUS 
        || t.token_type == MULT || t.token_type == DIV) {

        parse_operator();
        primary();
    }

    else if (t.token_type == SEMICOLON) {
        return;
    }
    else {
		syntax_error();
	}      
}

void Parser :: parse_operator(){
	
    Token t = lexer.GetToken();
    lexer.UngetToken(t);

    if (t.token_type == PLUS) {
        expect(PLUS);
    }
    else if (t.token_type == MINUS) {
        expect(MINUS);
    }
    else if (t.token_type == MULT) {
        expect(MULT);
    }
    else if (t.token_type == DIV) {
        expect(DIV);
    }
    else
        syntax_error();
}


void Parser :: primary() {

    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    if (t.token_type == ID) {
        expect(ID);
    }
    else if (t.token_type == NUM) {
        expect(NUM);
    }
    else
        syntax_error();
}

void Parser :: parse_main() {
    expect(MAIN);
    procedure_body();
}

void Parser :: inputs() {
    expect(NUM);
    Token t = lexer.GetToken();

    if (t.token_type == NUM) {
        lexer.UngetToken(t);
        inputs();
    }
    else if (t.token_type == END_OF_FILE) {
        return;
    }
    else
        syntax_error();
}

int main()
{
    LexicalAnalyzer lexer;
    Token token;
    
    Parser parse;
    parse.input();
}
