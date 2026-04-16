
%{
// Write a Lex program to recognize any identifier or key words of c-language. (Like if, else, break, for, etc.)
#include<stdio.h>



%}

%%
if      { printf("if is the identifier\n"); }
esle    { printf("esle s ite identifier\n"); }
int      { printf("int is the keyword\n"); }
[ \t]+  {}
.       { printf("Other word: %s\n", yytext); }
%%


int yywrap(){
    return 1;
}

int main(){
    printf("Enter the sentence: ");
    yylex();
    return 0;

}