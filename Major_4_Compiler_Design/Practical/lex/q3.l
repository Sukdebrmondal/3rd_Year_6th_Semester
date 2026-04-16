%{
#include <stdio.h>
%}

DIGIT      [0-9]
SIGN       [+-]?
INT        {DIGIT}+
FRAC       (\.{DIGIT}+)
EXP        ([eE]{SIGN}{DIGIT}+)

%%

{SIGN}{INT}{FRAC}?{EXP}?    {
                                printf("Real Number: %s\n", yytext);
                            }

\n                          ;

.                           {
                                printf("Invalid: %s\n", yytext);
                            }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter input:\n");
    yylex();
    return 0;
}