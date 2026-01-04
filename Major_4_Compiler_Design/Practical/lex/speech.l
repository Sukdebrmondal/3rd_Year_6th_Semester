/*write a LEX program to identify a part of speech of a word.*/

%{
#include <stdio.h>
%}

%%
(the|a|an|in|on|at|for|with|about|against|between|into|through|during|before|after|above|below|to|from|up|down|of) {printf("%s : is a Preposition\n", yytext);}
(and|but|or|nor|so|yet|for) {printf("%s : is a Conjunction\n", yytext);}
(is|am|are|was|were|be|being|been) {printf("%s : is a Verb\n", yytext);}
[0-9]+ {printf("%s : is a Number\n", yytext);}
[a-zA-Z]+ {printf("%s : is a Noun\n", yytext);}
[ \t\n]+ ;
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
/* flex speech.l && gcc lex.yy.c && ./a.out */