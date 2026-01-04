/* write a LEX program to identify vowel and consonent in a given string.*/

%{
#include <stdio.h>
%}

%%
[aeiouAEIOU] {printf("%c is a vowel\n", yytext[0]);}
[a-zA-Z]   {printf("%c is a consonant\n", yytext[0]);}
[ \t\n]      ;
%%
int yywrap()
{
    return 1;
}
int main()
{
    yylex();
    return 0;
}
/* flex vowel_con.l && gcc lex.yy.c && ./a.out */