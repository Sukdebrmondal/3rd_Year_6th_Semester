/*write a LEX program to identify a fraction number.*/
%{
#include<stdio.h>
%}
%%
[0-9]+"/"[0-9]+    {printf("Fraction Number: %s\n",yytext);}
[ \t\n]+          ;
.                 ;
%%

int yywrap(){
    return 1;
}
int main(){
    yylex();
    return 0;
}

/* flex fraction.l && gcc lex.yy.c && ./a.out */