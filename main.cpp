#include <iostream>
#include <vector>
#include "lexer.h"

using namespace std;

int dice();

int main()
{
    Lexer lex(cin);
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    cout << lex.getNextLexem().first << endl;
    return 0;
}