#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

enum NodeType{
    nd_Mul, nd_Div, nd_Add, nd_Sub, nd_Negate, nd_Integer
};
/*
struct tok_atr{
    char       *text, *enum_text;
    TokenType   tok;
    bool        right_associative, is_binary, is_unary;
    int         precedence;
    NodeType    node_type;
};
tok_atr atr[] = {
    {"*",               "Op_multiply"    , tk_Mul,     false, true,  false, 13, nd_Mul    },
    {"/",               "Op_divide"      , tk_Div,     false, true,  false, 13, nd_Div    },
    {"+",               "Op_add"         , tk_Add,     false, true,  false, 12, nd_Add    },
    {"-",               "Op_subtract"    , tk_Sub,     false, true,  false, 12, nd_Sub    },
    {"-",               "Op_negate"      , tk_Negate,  false, false, true,  14, nd_Negate },
    {"(",               "LeftParen"      , tk_Lparen,  false, false, false, -1, {-1}        },
    {")",               "RightParen"     , tk_Rparen,  false, false, false, -1, {-1}        },
    {"Integer literal", "Integer"        , tk_Integer, false, false, false, -1, nd_Integer}
};

class Parser
{
public:
    static void run_parser(list<Token>&);
};*/

class AST
{
public:
    AST(AST*, AST*, Token*);
    AST();
    ~AST();
    
    AST *left;
    AST *right;
    
    Token *tk;
    NodeType type;

    static AST *mkNode(Token*, AST*, AST*);
    static AST *mkNode(Token*, AST*);
    static AST *mkLeaf(Token*);
    
    #ifndef PC
    static AST *Eparser(list<Token>&);
    static AST *E(list<Token>&);
    static AST *T(list<Token>&);
    static AST *F(list<Token>&);
    static AST *P(list<Token>&);    
    #endif
    
    #ifdef PC
    static AST *Eparser(list<Token>&);
    static AST *Exp(list<Token>&, int prec);
    static AST *P(list<Token>&);
    #endif

    static void expect(const TokenType&, const list<Token>&);
    static void expect(const list<Token>&);
    static void prt_ast(AST*);
    
    static double eval(AST*);
};



#endif