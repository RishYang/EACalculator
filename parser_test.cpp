#include <iostream>
#include <cstdlib>
#include <list>
#include "lexer.h"
#include "parser.h"

int main(int argv, char* argc[])
{
    //string str = "-(-1+2);
    
    string str("-(-1*(-1))");
    if(argv == 2)
        str=argc[1] ;
    //getline(cin, str);
    list<Token> tokens={};
    Lexer::run_lexer(str, tokens);
    for(auto &a : tokens)
    {
        cout<<a.tok_name()<< " : "<<a.de.num<<" : "<<a.err_col<<endl;
    }
    
    AST* tree = AST::Eparser(tokens);
    if(tree == nullptr)
        cout<<"AST dose not exist"<<endl;
    else
    {
        AST::prt_ast(tree);
        cout<<"= "<<AST::eval(tree);
    }
        
    delete tree;

    return EXIT_SUCCESS;
}