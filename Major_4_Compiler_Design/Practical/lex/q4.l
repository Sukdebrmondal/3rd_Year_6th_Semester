%{
#include <stdio.h>

int count = 0;
int word_count = 0;
%}

%%

HE|He|he|hE   { count++; word_count++; }

[a-zA-Z]+     { word_count++; }

[ \t]+        ;   

\n            {
                printf("Occurrences of 'HE': %d\n", count);
                printf("Total words: %d\n", word_count);
              }

.             ;   // ignore other characters

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter sentence:\n");
    yylex();
    return 0;
}