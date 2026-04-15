%{
#include<stdio.h>
#include<string.h>

int max = 0;
char word[100] = "";
FILE *yyin;
%}


%%
[a-zA-Z]+   {
                if(yyleng > max) {
                    max = yyleng;
                    strcpy(word, yytext);
                }
            }
.   ;


%%


int yywrap(){
    return 1;
}

int main(){
    yyin = fopen("fle.txt", "r");

    if(yyin == NULL){
        printf("File not found.\n");    
        return 1;
    }
    yylex();
    printf("Length of longest word: %d\n", max);
    printf("Longest word: %s\n", word);

    fclose(yyin);
    return 0;
}

/* flex q8.l && gcc lex.yy.c && ./a.out */