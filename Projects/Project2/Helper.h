#include "lexer.h"
#include <vector>
#include <string>

#include <iostream>
#include <algorithm>

using namespace std;

//LexicalAnalyzer lexer;
//vector<string> allSymbols;

/*Rules Class */
class Rule {
	private:
		int LHS;
		std::vector<int>* RHS;

	public:
		Rule(int);
		int getLHS();
		void addToRHS(int);
		
		std::vector<int>* getRHS();
};

/*Symbol Class */
class Symbol {
	
	private:
		bool terminal;
		std::string representation;
		int id;
		
		//First & Follow
		std::vector<int> *firstSet;
		std::vector<int> *followSet;

	public:
		Symbol(bool ter, std::string rep);
		std::string toString();
		int getID();
		
		//First & Follow
		std::vector<int>* getFirstSet();
		std::vector<int>* getFollowSet();
		bool isInFirstSet(int thisId);
		bool isInFollowSet(int thisId);
		bool addFirst(int thisId);
		bool addFollow(int thisId);
		bool firstHasEpsilon();
		bool isTerminal();
};

/*Grammar Class */
class SymbolTable {
	private:
		enum MyEnum	{ EPSILON = 0, EnOF = 1	};
		std::vector<Symbol*> *symbolList;
		std::vector<Rule*> *ruleList;
		std::vector<bool> *canLengthOne;
		int countOfSpecialSymbols;
		bool addFirstToFollowTo(Symbol *thisSymbol, Symbol *fromThisSymbol);
		bool addFirstSetsTo(Symbol *thisSymbol, Symbol *fromThisSymbol);
		bool addFollowSetsTo(Symbol *thisSymbol, Symbol *fromThisSymbol);
		bool computeCanLengthOne();
		void applyFirstSetRuleOne();
		void applyFirstSetRuleTwo();
		bool applyFirstSetRuleThreeFourFive();
		void applyFollowSetRuleOne();
		bool applyFollowSetRuleTwoThree();
		void applyFollowSetRuleFourFive();
		std::string printFirstSetOf(int index);
		std::string printFollowSetOf(int index);
		std::string printCanSingletOf(int index);

	public:
		SymbolTable();
		int getCountOfSpecialSymbols();
		int findSymbolIDBy(std::string thisString);
		void addRule(Rule* newRule);
		void addTerminal(std::string newTerminal);
		void addNonTerminal(std::string newNonTerminal);
		void computeFirstSets();
		void computeFollowSets();
		bool isTerminalAtIndex(int thisIndex);
		void printFirstSets();
		void printFollowSets();
		void printLengthOne();
		// Some Test Functions
		void printRuleTable();
};



