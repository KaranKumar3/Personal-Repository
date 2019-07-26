//
// Created by Karan Kumar
//

#ifndef PROJECT2_PARSER_H
#define PROJECT2_PARSER_H

#include "lexer.h"
#include <string>

struct symTableNode {
    symTableNode* next;
    symTableNode* prev;
    std::string name;
    std::string scope;
    int pp;
};

class Parser{

    public:
        void parse_Input();
        void syntax_error();
        Token peek();
        Token expect(TokenType expected_type);

        void parse_program();
        void parse_global_vars();
        void parse_var_list();
        void parse_scope();
        void parse_public_vars();
        void parse_private_vars();
        void parse_stmt_list();
        void parse_stmt();

        void addList(symTableNode * node);
        void search(std::string ID);
};


#endif //PROJECT2_PARSER_H
