//
// Created by Karan Kumar
// comp code: g++ inputbuf.cc lexer.cc parser.cpp
// test code: ./test1.sh
//

#include "parser.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>


using namespace std;


string currScope = "";
LexicalAnalyzer lexer;
Parser parser;
Token t;

symTableNode* head;
symTableNode* temp;
symTableNode* temp2;

symTableNode* n;

int pp;
string currOut = "";
string totalOut= "";

//Parser Functions

Token Parser::peek(){
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}

Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

void Parser::parse_program(){
    //program -> global_vars  scope
    t = lexer.GetToken();
    if (t.token_type == ID) {
        Token t2 = lexer.GetToken();
        if (t2.token_type == COMMA || t2.token_type == SEMICOLON) {
            lexer.UngetToken(t2);
            lexer.UngetToken(t);
            parser.parse_global_vars();
            parser.parse_scope();
        }
        else if (t2.token_type == LBRACE) {
            lexer.UngetToken(t2);
            lexer.UngetToken(t);
            parser.parse_scope();
        }
        else {
            syntax_error();
        }
    }
    else {
        syntax_error();
    }


}

void Parser::parse_global_vars(){
    //global_vars -> var_list  SEMICOLON | EPSILON
    t = peek();
    if (t.token_type == ID) {
        currScope = "::";
        pp = 0;
        parser.parse_var_list();
    }
    else {
        syntax_error();
    }

    expect(SEMICOLON);

}

void Parser::parse_var_list(){
    //global_vars -> var_list  SEMICOLON | ID
    t = lexer.GetToken();
    if (t.token_type == ID) {
        // add a new node
        if (head->pp == 21) {
            n->name = t.lexeme;
            n->scope = currScope;
            n->pp = pp;
        }
        else {
            n = new symTableNode;
            n->name = t.lexeme;
            n->scope = currScope;
            n->pp = pp;
            addList(n);
        }

        t = lexer.GetToken();
        if (t.token_type == COMMA) {
            parser.parse_var_list();
        }
        else if (t.token_type == SEMICOLON) {
            lexer.UngetToken(t);
        }
    }
    else {
        syntax_error();
    }

}

void Parser::parse_scope(){
    //scope	 ->	ID	LBRACE	public_vars	 private_vars  stmt_list  RBRACE
    t= lexer.GetToken();
    if (t.token_type == ID) {
        currScope = t.lexeme; //entering a new scope
        t = lexer.GetToken();
        if (t.token_type == LBRACE) {
            parse_public_vars();
            parse_private_vars();
            parse_stmt_list();
            expect(RBRACE);
        }
        else {
            syntax_error();
        }
    }
    else {
        syntax_error();
    }

}

void Parser::parse_public_vars(){
    //public_vars	 ->	PUBLIC	COLON	var_list	SEMICOLON  | EPSILON
    t = lexer.GetToken();
    if (t.token_type == PUBLIC) {
        pp = 1;
        t = lexer.GetToken();
        if (t.token_type == COLON) {
            t = lexer.GetToken();
            if (t.token_type == ID) {
                lexer.UngetToken(t);
                parser.parse_var_list();
            }
            else {
                syntax_error();
            }
        }
        else {
            syntax_error();
        }
    }
    else {
        lexer.UngetToken(t);
        return;
    }

    expect(SEMICOLON);

}

void Parser::parse_private_vars(){
    //private_vars	->	PRIVATE	COLON	var_list	SEMICOLON | EPSILON
    t = lexer.GetToken();
    if (t.token_type == PRIVATE) {
        pp = 2;
        t = lexer.GetToken();
        if (t.token_type == COLON) {
            t = lexer.GetToken();
            if (t.token_type == ID) {
                lexer.UngetToken(t);
                parser.parse_var_list();
            }
            else {
                syntax_error();
            }
        }
        else {
            syntax_error();
        }
    }
    else {
        lexer.UngetToken(t);
        return;
    }

    expect(SEMICOLON);
}

void Parser::parse_stmt_list(){
    //stmt_list	 ->	stmt    stmt_list   |   stmt
    t = lexer.GetToken();
    if (t.token_type == ID) {
        Token t2 = lexer.GetToken();
        if (t2.token_type == EQUAL || t2.token_type == LBRACE) {
            lexer.UngetToken(t2);
            lexer.UngetToken(t);
            parser.parse_stmt();
        }
        else {
            lexer.UngetToken(t2);
            lexer.UngetToken(t);
            return;
        }

        t = lexer.GetToken();
        if (t.token_type == ID) {
            lexer.UngetToken(t);
            parser.parse_stmt_list();
        }
        else {
            lexer.UngetToken(t);
        }
        return;
    }
}

void Parser::parse_stmt(){
    //stmt	 ->	ID	EQUAL	ID	SEMICOLON   | scope
    t = lexer.GetToken();
    if (t.token_type == ID) {
        Token t2 = lexer.GetToken();
        if (t2.token_type == EQUAL) {
            Token t3 = lexer.GetToken();
            Token t4 = lexer.GetToken();
            if (t3.token_type != ID && t4.token_type != SEMICOLON) {
                syntax_error();
            }
            else {
                // add tokens to c-out
                currOut = "";
                search(t.lexeme);
                currOut += " = ";
                search(t3.lexeme);
                currOut += "\n";
                totalOut += currOut;
            }
        }
        else if (t2.token_type == LBRACE) {
            lexer.UngetToken(t2);
            lexer.UngetToken(t);
            parser.parse_scope();
        }
        else {
            syntax_error();
        }
    }
    else {
        lexer.UngetToken(t);
    }

}

void Parser::syntax_error(){
    cout << "Syntax Error\n";
    exit(1);
}

void Parser::addList(symTableNode* node) {
    temp->next = node;
    node->prev = temp;
    node->next = NULL;
    temp = temp->next;
}

void Parser::search(string ID) {
    bool matching = false;
    temp2 = temp;
    if (temp2->prev == NULL) {
        if (temp2->name == ID) {
            if (temp2->scope != currScope && temp2->scope != "::")
                currOut += "?.";
            else {
                currOut += temp2->scope;
                if (temp2->scope != "::") currOut += ".";
            }
            currOut += ID;
        }
        else {
            currOut += "?.";
            currOut += ID;
        }
    }
    else {
        while (temp2 != NULL && !matching) {
            if (temp2->name == ID) {
                if ((temp2->scope != currScope && (temp2->pp == 0 || temp2->pp == 1))
                    || temp2->scope == currScope || temp2->scope == "::") {
                    currOut += temp2->scope;
                    if (temp2->scope != "::") currOut += ".";
                    matching = true;
                }
            }
            temp2 = temp2->prev;
        }
        if (!matching) currOut += "?.";
        currOut += ID;
    }
}

int main()
{
    n = new symTableNode;
    n->next = NULL;
    n->prev = NULL;
    n->pp = 21;//just to count for pp head
    head = n;
    temp = n;

    parser.parse_program();

    cout << totalOut ;
    return 0;
}