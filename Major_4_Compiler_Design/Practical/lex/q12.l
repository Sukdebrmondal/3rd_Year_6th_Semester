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
                    printf("%s ", yytext);
                } else {
                    int len = strlen(yytext);

                    for(int i=1; i<len; i++)
                        printf("%c", yytext[i]);

                    printf("%cay ", yytext[0]);
                }
            }

[ \t\n]+    ;   
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

/* flex q12.l && gcc lex.yy.c && ./a.out */
