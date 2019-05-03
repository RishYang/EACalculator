#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <regex>
#include <list>
#include <stdexcept>
#include <iostream>

using namespace std;

enum TokenType{
    tk_Mul, tk_Div, tk_Add, tk_Sub, tk_Negate,
    tk_Lparen, tk_Rparen, tk_Integer
};

union detail
{
    int num;
    string *ident;
};

class Token
{
public:
    Token(Token*);
    Token(const Token&);
    Token(TokenType, int, detail);
    ~Token();
    
    TokenType tok_t;
    int err_col;

    detail de;
    
    static string tk_name[];
    static short tk_Lasso[];
    static short tk_prec[];
    static bool tk_isB[];
    
    const string tok_name() const{ 
        return this->tk_name[static_cast<int>(tok_t)];};
        
    Token operator=(const Token& tk){return Token(tk);}
    
    bool isNumber() const{return this->tok_t == tk_Integer;};
    bool isSymbol() const{return ! this->isNumber();};
    
    bool is(const TokenType& operand) const{return this->tok_t == operand;};
    bool operator==(const TokenType& operand) const{return this->tok_t == operand;};
    bool operator!=(const TokenType& operand) const{return this->tok_t != operand;};
    
    bool isL_asso() const{return this->tk_Lasso[static_cast<int>(this->tok_t)]==1;};
    short prec() const{return this->tk_prec[static_cast<int>(this->tok_t)];};
    bool isBinary() const{return this->tk_isB[static_cast<int>(this->tok_t)];};
    bool isUnary() const{return this->tok_t==tk_Sub;};
};


class Lexer
{
public:
    static void run_lexer(string, list<Token>&);
};



#endif