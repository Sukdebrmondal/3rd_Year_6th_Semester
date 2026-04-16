

%{
#include<stdio.h>
//Write a Lex Program to Scan and Count the number of characters, words, and lines in a file.
int chars = 0;
int words = 0;
int lines = 0;

FILE *fp;
%}


%%
[a-zA-Z]+   { words++; chars+=yyleng; };
\n          { lines++; chars++; }
[ \t]+      {}
.           { chars++; }

%%


int yywrap(){
    return 1;
}


int main(){
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("File can't open!\n");
        return 1;
    }

    yyin = fp;

    yylex();

    printf("\nCharacters:%d",chars);
    printf("\nwords:%d",words);
    printf("\nLine:%d",lines);

    fclose(fp);
    return 0;
}