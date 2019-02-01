/*
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "lexer.h"

class Parser {
  
  private:
    LexicalAnalyzer lexer;

  public:
    void syntax_error();
    Token expect(TokenType expected_type);
    Token peek();

    void input();
    void program();
    void proc_decl_section();
    void proc_decl();
    void procedure_name();
    void procedure_body();
    void statement_list();
    void statement();
    void input_statement();
    void output_statement();
    void procedure_invocation();
    void do_statement();
    void assign_statement();
    void expr();
    void parse_operator();
    void primary();
    void parse_main();
    void inputs();

};

#endif

