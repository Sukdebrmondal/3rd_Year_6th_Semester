%{
// Write a LEX program to remove all the comment lines from a given source code in c.
#include <stdio.h>
FILE *fp;
FILE *outfp;
%}

%%

"//".*                         ;   /* remove single-line comments */

"/*"([^*]|\*+[^*/])*\*+"/"     ;   /* remove multi-line comments */

\"([^\\\n]|(\\.))*\"           { ECHO; }  /* keep strings */

.|\n                           { ECHO; }  /* print rest */

%%

int yywrap() {
    return 1;
}

int main(){
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    printf("Enter the output file name: ");
    char output_filename[100];
    scanf("%s", output_filename);

    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("File can't open!\n");
        return 1;
    }

    outfp = fopen(output_filename, "w");
    if(outfp == NULL){
        printf("Output file can't open!\n");
        fclose(fp);
        return 1;
    }

    yyin = fp;
    yyout = outfp;

    yylex();

    fclose(fp);
    fclose(outfp);
    return 0;
}