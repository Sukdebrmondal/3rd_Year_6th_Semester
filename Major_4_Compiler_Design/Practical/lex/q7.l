


%{
#include<stdio.h>
%}

%%
(==|!=|<=|>=|&&|\||!|<|>|true|false)  {printf("Logical operator: %s\n", yytext);}
[ \t\n]      ;
.     {printf("Other character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter expression:\n");
    yylex();
    return 0;
}

/*flex q7.l && gcc lex.yy.c && ./a.out */