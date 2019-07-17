/*
 * Copyright (C) Rida Bazzi, 2016
 *
 * Do not share this file with anyone
 *
 * Edited by: Karan Kumar
 * comp code: g++ inputbuf.cc lexer.cc
 * test code: ./test.sh
 */
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

#include "lexer.h"
#include "inputbuf.h"

using namespace std;

string reserved[] = { "END_OF_FILE",
    "IF", "WHILE", "DO", "THEN", "PRINT",
    "PLUS", "MINUS", "DIV", "MULT",
    "EQUAL", "COLON", "COMMA", "SEMICOLON",
    "LBRAC", "RBRAC", "LPAREN", "RPAREN",
    "NOTEQUAL", "GREATER", "LESS", "LTEQ", "GTEQ",
    "DOT", "NUM", "ID", "ERROR", "REALNUM", "BASE08NUM", "BASE16NUM"
};

#define KEYWORDS_COUNT 5
string keyword[] = { "IF", "WHILE", "DO", "THEN", "PRINT" };

void Token::Print()
{
    cout << "{" << this->lexeme << " , "
         << reserved[(int) this->token_type] << " , "
         << this->line_no << "}\n";
}

LexicalAnalyzer::LexicalAnalyzer()
{
    this->line_no = 1;
    tmp.lexeme = "";
    tmp.line_no = 1;
    tmp.token_type = ERROR;
}

bool LexicalAnalyzer::SkipSpace()
{
    char c;
    bool space_encountered = false;

    input.GetChar(c);
    line_no += (c == '\n');

    while (!input.EndOfInput() && isspace(c)) {
        space_encountered = true;
        input.GetChar(c);
        line_no += (c == '\n');
    }

    if (!input.EndOfInput()) {
        input.UngetChar(c);
    }
    return space_encountered;
}

bool LexicalAnalyzer::IsKeyword(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return true;
        }
    }
    return false;
}

TokenType LexicalAnalyzer::FindKeywordIndex(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return (TokenType) (i + 1);
        }
    }
    return ERROR;
}

Token LexicalAnalyzer::ScanNumber()
{
    char c;
    //flags
    bool isRealNum = false;
    bool is08Num = true;
    bool is16Num = true;
    bool startsWith0 = false;
    //counters
    int stringCounter = 0;
    int baseCount = 0;

    input.GetChar(c);
    if (isdigit(c)) {
        if (c == '0') { //if the first input is a zero, we are dealing with a digit
            //tmp.lexeme = "0";
            startsWith0 = true;
        } /*else {
            tmp.lexeme = "";
            while (!input.EndOfInput() && isdigit(c)) {
                tmp.lexeme += c;
                input.GetChar(c);
            }
            if (!input.EndOfInput()) {
                input.UngetChar(c);
            }
        } */
        // TODO: You can check for REALNUM, BASE08NUM and BASE16NUM here!
        //REALNUM = NUM DOT digit digit*
        //BASE08NUM	=	((pdigit8	digit8*)	+	0)	(x)	(08)
        //BASE16NUM	=	((pdigit16	digit16*)	+	0)	(x)	(16)
        tmp.lexeme = "";
        tmp.lexeme += c;
        input.GetChar(c);
        //test base 08
        while (!input.EndOfInput() && !startsWith0 && isdigit(c)) {
            tmp.lexeme += c;
            if ((c - '0') >= 8)
            {
                is08Num = false;
            }
            input.GetChar(c);
        }
        //end test base 08
        if (c == '.')
        {
            //check next char(s) for digit
            tmp.lexeme += c;
            input.GetChar(c);
            while (!input.EndOfInput() && isdigit(c))
            {
                stringCounter++;
                if (isdigit(c)/*c != '0' */){
                    isRealNum = true;
                }
                tmp.lexeme += c;
                input.GetChar(c);
            }

            if (!input.EndOfInput()){
                input.UngetChar(c);
            }
            //if so far NUM DOT digit digit*
            if((isRealNum || !startsWith0) && isdigit(tmp.lexeme.at(tmp.lexeme.length()-1)))
            {
                tmp.token_type = REALNUM;
                tmp.line_no = line_no;
                return tmp;
            }
            //just backtrack and return num
            else{
                for(int i = 0; i < stringCounter; i++){

                    (tmp.lexeme).erase(tmp.lexeme.size() - 1);
                    input.UngetChar('0');
                }
                (tmp.lexeme).erase(tmp.lexeme.size() - 1);
                input.UngetChar('.');
                tmp.token_type = NUM;
                tmp.line_no = line_no;
                return tmp;
            }
        }
        else{
            input.UngetChar(c);
        }
        //if it got here we dont have a real num
        input.GetChar(c);
        //check for base 16 or base 8 members
        while (!input.EndOfInput() && (isdigit(c) || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F')) {
            if ((c - '0') >= 8){
                is08Num = false;
            }
            baseCount++; //keep track if still valid
            tmp.lexeme += c;
            input.GetChar(c);
        }
        //next char should be x
        if (c == 'x'){
            //if we have multiple base matches, backtrack and return NUM
            if (startsWith0 && baseCount != 0){
                input.UngetChar('x');
                for(int i = 0; i < baseCount; i++){

                    input.UngetChar(tmp.lexeme[tmp.lexeme.size()-1]);
                    (tmp.lexeme).erase(tmp.lexeme.size() - 1);
                }
                tmp.token_type = NUM;
                tmp.line_no = line_no;
                return tmp;
            }
            //check for 0 8 and return if so
            tmp.lexeme += c;
            input.GetChar(c);
            if (c == '0' && is08Num){
                tmp.lexeme += c;
                input.GetChar(c);
                if (c == '8'){
                    tmp.lexeme += c;
                    tmp.token_type = BASE08NUM;
                    tmp.line_no = line_no;
                    return tmp;
                }
                //else backtrack
                else{
                    input.UngetChar(c);
                    input.UngetChar('0');
                    input.UngetChar('x');
                    (tmp.lexeme).erase(tmp.lexeme.size() - 1);
                    (tmp.lexeme).erase(tmp.lexeme.size() - 1);
                }
            }
            //now check for 1 6 and return if so
            else if (c == '1' && is16Num){
                tmp.lexeme += c;
                input.GetChar(c);
                if (c == '6'){
                    tmp.lexeme += c;
                    tmp.token_type = BASE16NUM;
                    tmp.line_no = line_no;
                    return tmp;
                }
                //else backtrack
                else{
                    input.UngetChar(c);
                    input.UngetChar('1');
                    input.UngetChar('x');
                    (tmp.lexeme).erase(tmp.lexeme.size() - 1);
                    (tmp.lexeme).erase(tmp.lexeme.size() - 1);
                }
            }
            //otherwise the base nums are not matches, backtrack
            else{
                input.UngetChar(c);
                input.UngetChar('x');
                (tmp.lexeme).erase(tmp.lexeme.size() - 1);
            }
        }
        else{
            input.UngetChar(c);
        }

        if (baseCount > 0 && !input.EndOfInput()){
            for(int i = 0; i < baseCount; i++){
                if(!input.EndOfInput()){
                    input.UngetChar(tmp.lexeme[tmp.lexeme.size()-1]);
                    (tmp.lexeme).erase(tmp.lexeme.size() - 1);
                }
            }
        }
        //ls end
        tmp.token_type = NUM;
        tmp.line_no = line_no;
        return tmp;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
        tmp.line_no = line_no;
        return tmp;
    }
}

Token LexicalAnalyzer::ScanIdOrKeyword()
{
    char c;
    input.GetChar(c);

    if (isalpha(c)) {
        tmp.lexeme = "";
        while (!input.EndOfInput() && isalnum(c)) {
            tmp.lexeme += c;
            input.GetChar(c);
        }
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.line_no = line_no;
        if (IsKeyword(tmp.lexeme))
            tmp.token_type = FindKeywordIndex(tmp.lexeme);
        else
            tmp.token_type = ID;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
    }
    return tmp;
}

// you should unget tokens in the reverse order in which they
// are obtained. If you execute
//
//    t1 = lexer.GetToken();
//    t2 = lexer.GetToken();
//    t3 = lexer.GetToken();
//
// in this order, you should execute
//
//    lexer.UngetToken(t3);
//    lexer.UngetToken(t2);
//    lexer.UngetToken(t1);
//
// if you want to unget all three tokens. Note that it does not
// make sense to unget t1 without first ungetting t2 and t3
//
TokenType LexicalAnalyzer::UngetToken(Token tok)
{
    tokens.push_back(tok);;
    return tok.token_type;
}

Token LexicalAnalyzer::GetToken()
{
    char c;

    // if there are tokens that were previously
    // stored due to UngetToken(), pop a token and
    // return it without reading from input
    if (!tokens.empty()) {
        tmp = tokens.back();
        tokens.pop_back();
        return tmp;
    }

    SkipSpace();
    tmp.lexeme = "";
    tmp.line_no = line_no;
    input.GetChar(c);
    switch (c) {
        case '.':
            tmp.token_type = DOT;
            return tmp;
        case '+':
            tmp.token_type = PLUS;
            return tmp;
        case '-':
            tmp.token_type = MINUS;
            return tmp;
        case '/':
            tmp.token_type = DIV;
            return tmp;
        case '*':
            tmp.token_type = MULT;
            return tmp;
        case '=':
            tmp.token_type = EQUAL;
            return tmp;
        case ':':
            tmp.token_type = COLON;
            return tmp;
        case ',':
            tmp.token_type = COMMA;
            return tmp;
        case ';':
            tmp.token_type = SEMICOLON;
            return tmp;
        case '[':
            tmp.token_type = LBRAC;
            return tmp;
        case ']':
            tmp.token_type = RBRAC;
            return tmp;
        case '(':
            tmp.token_type = LPAREN;
            return tmp;
        case ')':
            tmp.token_type = RPAREN;
            return tmp;
        case '<':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = LTEQ;
            } else if (c == '>') {
                tmp.token_type = NOTEQUAL;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = LESS;
            }
            return tmp;
        case '>':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = GTEQ;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = GREATER;
            }
            return tmp;
        default:
            if (isdigit(c)) {
                input.UngetChar(c);
                return ScanNumber();
            } else if (isalpha(c)) {
                input.UngetChar(c);
                return ScanIdOrKeyword();
            } else if (input.EndOfInput())
                tmp.token_type = END_OF_FILE;
            else
                tmp.token_type = ERROR;

            return tmp;
    }
}

int main()
{
    LexicalAnalyzer lexer;
    Token token;

    token = lexer.GetToken();
    token.Print();
    while (token.token_type != END_OF_FILE)
    {
        token = lexer.GetToken();
        token.Print();
    }
}
