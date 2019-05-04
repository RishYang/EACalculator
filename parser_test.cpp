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
    #ifdef TEST
    for(auto &a : tokens)
    {
        cout<<a.tok_name()<< " : "<<a.de.num<<" : "<<a.err_col<<endl;
    }
    #endif
    AST* tree = AST::Eparser(tokens);
    if(tree == nullptr)
        cout<<"AST dose not exist"<<endl;
    else
    {   
        #ifdef TEST
        AST::prt_ast(tree);
        #endif
        cout<<"= "<<AST::eval(tree)<<endl;
    }
        
    delete tree;

    return EXIT_SUCCESS;
}