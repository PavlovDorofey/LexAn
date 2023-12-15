#include "fsm.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;
void read(char &cache, istream& stream) {
    if (stream) {
        stream.get(cache);
    }
    if (!stream) {
        cache = 0;
    }
}
map<char,string> state1 {
    {')',"rpar"},
    {'(',"lpar"},
    {'{',"lbrace"},
    {'}',"rbrace"},
    {';',"semicolon"},
    {',',"comma"},
    {'.',"colon"},
    {'>',"opgt"},
    {'*',"opmul"}
};
map<char,string> state2{
        {'=',"opeq"},
        {'<',"ople"},
        {'!',"opne"},
        {'+',"opplus"}
};
map<char,string> state3{
        {'=',"opeassing"},
        {'<',"oplt"},
        {'!',"opnot"},
        {'!',"opinc"}
};
map<char,string> state10{
        {'|',"opor"},
        {'&',"opand"},
};
set<string> keywords = {
        "int",
        "char",
        "if",
        "else",
        "while",
        "for",
        "out",
        "in",
        "switch",
        "case",
        "return"
};
string cacheString;
char cacheChar;
bool flag = false;
pair<int, Lexem> tick(int state, istream &stream, char &cache) {
    switch (state) {
        case 0:
            switch (cache) {
                case ' ':
                case '\t':
                case '\n':
                    read(cache, stream);
                    return {0, LEX_EMPTY};
                case ')':
                case ';':
                case '{':
                case '}':
                case '.':
                case ',':
                case '*':
                case '(':
                case '>':
                    return {1, LEX_EMPTY};
                case '<':
                case '=':
                case '!':
                case '+':
                    return {2, LEX_EMPTY};
                case '|':
                case '&':
                    return {10, LEX_EMPTY};
                case '\'':
                    return { 14,LEX_EMPTY};
                case '\"':
                    return { 18,LEX_EMPTY};
                case '-':
                    return { 22,LEX_EMPTY};
                case 0:
                    return {-1, LEX_EOF};
                default:if (isalpha(cache)){
                        return {21, LEX_EMPTY};
                    } else if(isdigit(cache)){
                    return {23, LEX_EMPTY};
                } return {-1, LEX_ERROR};
            }
        case 1:
            cacheString = state1[cache];
            read(cache, stream);
            return {0, {cacheString, ""}};
        case 2:
            cacheChar = cache;
            read(cache, stream);
            if(cache == '=' or (cacheChar == '+' and cache == '+')){
                read(cache, stream);
                return {0, {state2[cacheChar], ""}};
            } else return {0, {state3[cacheChar], ""}};
        case 10:
            cacheChar = cache;
            read(cache, stream);
            if(cacheChar == cache){
                read(cache, stream);
                return {0, {state10[cacheChar], ""}};
            } else return {-1,LEX_ERROR };
        case 14:
            cacheChar = cache;
            read(cache, stream);
            if(cacheChar == cache){
                return {-1,LEX_ERROR };
            } else{
                cacheChar = cache;
                read(cache, stream);
                if(cache =='\''){
                    cacheString += "char(";
                    cacheString += cacheChar;
                    return {0,{"char(" + cacheString + ")", ""}};
                }else return {-1,LEX_ERROR };
            }
        case 18:
            cacheString = "str(";
            read(cache, stream);
            while(cache!='\"'){
                cacheString += cache;
                read(cache, stream);
                if(cache == '\n'){
                    return {-1,LEX_ERROR };
                }
            }
            cacheString += ")";
            return {0,{cacheString, ""}};
        case 21:
            cacheString = "";
            while(isalnum(cache)) {
                cacheString += cache;
                read(cache, stream);
            }
            if (keywords.count(cacheString)!=0) {
                return {0, {"keyword (" + cacheString + ")", ""}};
            } return {0, {"id(" + cacheString + ")", ""}};
        case 22:
            cacheString = "";
            cacheString += cache;
            read(cache, stream);
            if (isdigit(cache)){
                flag = true;
                return {23, LEX_EMPTY};
            } else return  {0, {"opminus", ""}};
        case 23:
            cacheString = "";
            while(isdigit(cache)) {
                cacheString += cache;
                read(cache, stream);
            }
            if (flag){
                flag = false;
                return {0, {"num(-" + cacheString + ")", ""}};
            } else return {0, {"num(" + cacheString + ")", ""}};
        default:
            return {-1, LEX_EMPTY};
    }
}
