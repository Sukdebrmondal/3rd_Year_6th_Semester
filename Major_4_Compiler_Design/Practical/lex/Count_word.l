/*write a LEX program to identify a word and count total number of words in a string.*/


%{
#include <stdio.h>

int word_count = 0;
%}

%%
[a-zA-Z]+    { word_count++; }
\n           {printf("Total number of words = %d\n", word_count);word_count = 0;}
[ \t]+       ;
.            ;
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

/* felx Count.l && gcc lex.yy.c && ./a.out