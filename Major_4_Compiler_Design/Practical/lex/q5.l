/* Write a LEX program to find the length of the longest word in a line. */

%{
#include<stdio.h>
int max =0;
char word[100];
%}

%%
[a-zA-Z]+   {
                if(yyleng > max)
                    max = yyleng;
                    strcpy(word, yytext);
            }
\n          {
                printf("Length of longest word: %d\n", max);
                printf("Longest word: %s\n", word);
                max = 0; // reset for next line
            }
.   ;    
 

%%
int yywrap(){
    return 1;
}

int main(){
    printf("Enter a line: ");
    yylex();
    return 0;

}



/* 

sukdeb@SUKDEB:~/sukdeb/Compile Design practical/lex$ flex q5.l
sukdeb@SUKDEB:~/sukdeb/Compile Design practical/lex$ gcc lex.yy.c && ./a.out
Enter a line: i am a programmer
Length of longest word: 10
Longest word: programmer

Enter a line: i am a student
Length of longest word: 7
Longest word: student


*/