/*write a LEX program to identify even and odd numbers*/

%{
#include <stdio.h>
%}

%%
[0-9]*[02468]    { printf("Even Number: %s\n", yytext); }
[0-9]*[13579]    { printf("Odd Number: %s\n", yytext); }
%%

int yywrap(){
    return 1;
}

int main(){
    yylex();
    return 0;
}


/* flex even_odd.l && gcc lex.yy.c && ./a.out */

