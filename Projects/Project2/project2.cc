/*
 * Copyright (C) Mohsen Zohrevandi, 2017
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "Helper.h"

//assembly code: g++ --std=c++11 -pedantic -Wall project2.cc inputbuf.cc lexer.cc Helper.cc
//manuel test: ./a.out 1 < tests/test01.txt
//sh test: ./test_p2.sh 1

void syntax_error() {
	cout << "SYNTAX ERROR\n";
	exit(1);
}

int main (int argc, char* argv[])
{
    int task;

    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }

    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);
	string token;
    //Token t;
    //LexicalAnalyzer lexer;
	SymbolTable *grammarTable = new SymbolTable();
	cin >> token;
	//t = lexer.GetToken();
	//cout << t << endl;
	/*
	while (token.compare("#") != 0) {
		grammarTable->addNonTerminal(token);
		cin >> token;
		cout << token << endl;
	}
	
	cin >> token; */
	
	while (token.compare("##") != 0) {
		cout << token << endl;
		grammarTable->addNonTerminal(token);
		
		cin >> token;
		if (token.compare("->") == 0) // token is currently arrow
		{
			while (token.compare("#") != 0) { 
				cin >> token;
			}
			cin >> token;
			continue;
		}
		//cout << token << endl;
	}

	while (token.compare("##") != 0) {
		
		int LHSIndex = grammarTable->findSymbolIDBy(token);
		
		if (LHSIndex < grammarTable->getCountOfSpecialSymbols() ||  grammarTable->isTerminalAtIndex(LHSIndex)) {
			syntax_error();
			return 0;
		}
		
		Rule* newRule = new Rule(LHSIndex);

		cin >> token;
	
		if (token.compare("->") != 0)
		{
			syntax_error();
			return 0;
		}
		else
		{
			cin >> token;
		}
		//expect(ARROW);
		//t = lexer.GetToken();

		if (token.compare("#") == 0) {
			newRule->addToRHS(0);
		}
		else {
			
			while (token.compare("#") != 0) {
				grammarTable->addTerminal(token);
				int RHSIndex = grammarTable->findSymbolIDBy(token);
				newRule->addToRHS(RHSIndex);
				cin >> token;
			}
		}
		grammarTable->addRule(newRule);

		cin >> token;
	} //end of while loop

	grammarTable->computeFollowSets();


    switch (task) {
        case 1:
            grammarTable->printLengthOne();
            break;

        case 2:
            // TODO: perform task 2.
            break;

        case 3:
            grammarTable->printFirstSets();
            break;

        case 4:
            grammarTable->printFollowSets();
            break;

        case 5:
            // TODO: perform task 5.
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}

