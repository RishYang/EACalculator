#include "lexer.h"


string Token::tk_name[] =
{
    "Op_multiply", "Op_divide", "Op_add", 
    "Op_subtract", "Op_negate", "LeftParen",
    "RightParen", "Integer"
};

short Token::tk_Lasso[] =
{
    1, 1, 1, 
    1, -1, -1,
    -1, -1
};

short Token::tk_prec[] =
{
    5, 5, 3, 
    3, 4, -1,
    -1, -1
};

bool Token::tk_isB[] =
{
    true, true, true, 
    true, false, false,
    false, false
};

Token::Token(TokenType tok_t, int col, detail v)
{
    this->tok_t = tok_t;
    this->err_col = col;
    this->de = v;
}

Token::Token(Token *tk)
{
    this->tok_t = tk->tok_t;
    this->err_col = tk->err_col;
    this->de = tk->de;
}

Token::Token(const Token& tk)
{
    this->tok_t = tk.tok_t;
    this->err_col = tk.err_col;
    this->de = tk.de;
}

Token::~Token()
{
    if(this->isSymbol())
        delete this->de.ident;
}


void Lexer::run_lexer(string str, list<Token>& list_tk)
{
    regex space_p("^ +"), num_p("^[0-9]+"), symbol_p("^\\+|\\-|\\*|/|\\(|\\)");
    smatch m;
    int col=0;
    while(str.size() !=0 )
    {
        //debug cout<<str<<endl;
        if(regex_search(str, space_p))
        {
            regex_search(str, m, space_p);
        }
        else if(regex_search(str, num_p))
        {
            regex_search(str, m, num_p);
            list_tk.push_back(Token(tk_Integer, col, {stoi(m[0].str())}));
        }
        else if(regex_search(str, symbol_p))
        {
            regex_search(str, m, symbol_p);
            TokenType tmp;
            switch(m[0].str()[0])
            {
                case '*':
                    tmp = tk_Mul;
                break;
                case '/':
                    tmp = tk_Div;
                break;
                case '+':
                    tmp = tk_Add;
                break;
                case '-':
                    tmp = tk_Sub;
                break;
                case '(':
                    tmp = tk_Lparen;
                break;
                case ')':
                    tmp = tk_Rparen;
                break;
                default:
                    throw runtime_error("Unrecognized Symbol");
            }

            list_tk.push_back(Token(tmp, col, {0}));
            
        }
        else
            throw runtime_error("Invalid Input");
        
        str = str.substr(m[0].str().size(), str.size()-m[0].str().size());
        col += m[0].str().size();
    }
}
