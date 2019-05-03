# EACalculator: Elementary Arithmetic Calculator
## Technology
* Lexer
* Parser(Precedence climbing or The classic solution)
## Compile
`g++ -pipe std=c++11 -Wall -Wextra -DPC -I. -o test.exe lexer.cpp parser.cpp patser_test.cpp`

    Compile with `-DPC` to make Parser run by precedence climbing
    Compile without `-DPC` to make Parser run by the classic solution
## Usage
`test.exe [formula]`
### Example
`test.exe 1+2-3*4/5+(-6)`
## Supported Operators
* '+' Add
* '-' Sub
* '*' Mul
* '/' Div
* '-' Negate
* '{' left parenthesis
* '}' right parenthesis

##Inpired by
* [rosettacode/Compiler](https://rosettacode.org/wiki/Compiler)
* [Parsing Expressions by Recursive Descent](https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm)
