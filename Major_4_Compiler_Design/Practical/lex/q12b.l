

%{
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int count = 0;

int isVowel(char c) {
    c = tolower(c);
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u');
}
%}

%%
[a-zA-Z]+   {
                count++;

                if(isVowel(yytext[0])) {
                    printf("%sly", yytext);
                } else {
                    printf("%s", yytext);
                }
            }

[^a-zA-Z]+  {
                printf("%s", yytext);   // print non-letters as it is
            }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a sentence:\n");
    yylex();
    printf("\nTotal tokens = %d\n", count);
    return 0;
}

/* flex q12b.l && gcc lex.yy.c && ./a.out */