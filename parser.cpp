#include "parser.h"
#include <iostream>

using namespace std;

AST::AST(AST* left, AST* right, Token *tk)
{
    this->left = left;
    this->right = right;
    this->tk = tk;
    this->type = static_cast<NodeType>((static_cast<int>(tk->tok_t)));
}

AST::AST()
{
    this->left = nullptr;
    this->right = nullptr;
    this->tk = nullptr;
    this->type = static_cast<NodeType>(0);
}

AST::~AST()
{
    delete this->left;
    delete this->right;
    delete this->tk;
}

void  AST::expect(const list<Token>& input)
{
    if(!input.empty())
        throw runtime_error("Error: Non-empty token list");
}

void  AST::expect(const TokenType& type, const list<Token>& input)
{
    if(input.front() != type)
        throw runtime_error("Error: Unexpect token");
}

#ifdef PC
    
AST* AST::Eparser(list<Token>& input)
{
    AST *t = Exp(input, 0);
    expect(input);
    return t;
}
AST* AST::Exp(list<Token>& input, int prec)
{
    AST *t = P(input);
    while((!input.empty())&&(input.front().isBinary() && input.front().prec() >= prec))
    {
        Token *tk = new Token(&input.front());
        input.pop_front();
        int new_prec = tk->prec() + (tk->isL_asso()?1:0);
        AST *t1 = Exp(input, new_prec);
        t = mkNode(tk, t, t1);
    }
    return t;
}
AST* AST::P(list<Token>& input)
{
    if(input.front().isUnary())
    {
        Token *tk = new Token(&input.front());
        tk->tok_t = tk_Negate;
        input.pop_front();
        return mkNode(tk, Exp(input, tk->prec()));
    }else if(input.front()==tk_Lparen)
    {
        input.pop_front();
        AST* t = Exp(input, 0);
        expect(tk_Rparen, input);
        input.pop_front();
        return t;
    }else if(input.front()==tk_Integer)
    {
        Token *tk = new Token(&input.front());
        input.pop_front();
        return mkLeaf(tk);
    }else
        throw runtime_error("Error: Unsupported token");
}

#endif

#ifndef PC
AST* AST::Eparser(list<Token>& input)
{
    AST *t = E(input);
    expect(input); // if everything gose right, expect will not throw Exception
    return t;
}

AST* AST::E(list<Token>& input)
{
    AST *t = T(input);
    while((!input.empty())&&(input.front() == tk_Add || input.front() == tk_Sub))
    {
        Token *tk = new Token(&input.front());
        input.pop_front();
        AST *t1 = T(input);
        t  = mkNode(tk, t,  t1);
    }
    return t;
}

AST* AST::T(list<Token>& input)
{
    AST *t = F(input);
    while((!input.empty())&&(input.front() == tk_Mul || input.front() == tk_Div))
    {
        Token *tk = new Token(&input.front());
        input.pop_front();
        AST *t1 = F(input);
        t = mkNode(tk, t, t1);
    }
    return t;
}
AST* AST::F(list<Token>& input)
{
    AST *t =P(input);
    return t;
}
AST* AST::P(list<Token>& input)
{
    AST *t;
    if (input.front() == tk_Integer)
    {
        t = mkLeaf(input.front());
        input.pop_front();
        return t;
    }
    else if(input.front() == tk_Lparen)
    {
        input.pop_front();
        t = E(input);
        expect(tk_Rparen, input);
        input.pop_front();
        return t;
    }
    else if(input.front() == tk_Sub)
    {
        Token *tk = new Token(&input.front());
        tk.tok_t = tk_Negate;
        input.pop_front();
        t = F(input);
        return mkNode(tk, t);
    }
    else
        throw runtime_error("Error: Unsupported token");
}
#endif

AST* AST::mkLeaf(Token* tk)
{
    return new AST(nullptr, nullptr, tk);
}

AST* AST::mkNode(Token* tk, AST *t, AST *t1)
{
    return new AST(t, t1, tk);
}

AST* AST::mkNode(Token* tk, AST *t)
{
    return new AST(t, nullptr, tk);
}

void AST::prt_ast(AST* tree)
{
    if(tree == nullptr)
        cout<<";\n";
    else
    {
        cout<<tree->tk->tok_name()<<"\t\t";
        if(tree->tk->isNumber())
        {
            cout<<tree->tk->de.num<<endl;
        }else
        {
            cout<<endl;
            prt_ast(tree->left);
            prt_ast(tree->right);
        }
    }
}

double AST::eval(AST* tree)
{
    if(tree->tk->isNumber())
        return (double)tree->tk->de.num;
    else if(tree == nullptr)
        return 0.0;
    else
    {
        switch(tree->tk->tok_t)
        {
            case tk_Add:
                return eval(tree->left) + eval(tree->right);
            case tk_Sub:
                return eval(tree->left) - eval(tree->right);
            case tk_Mul:
                return eval(tree->left) * eval(tree->right);
            case tk_Div:
                return eval(tree->left) / eval(tree->right);
            case tk_Negate:
                return -eval(tree->left);
            default:
                throw runtime_error("Error: Unsupported Operator");
        }
            
    }
        
};
    