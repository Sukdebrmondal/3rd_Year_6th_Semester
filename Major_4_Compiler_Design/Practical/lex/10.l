%{
    #include <stdio.h>

    FILE *fp;
%}

%%
float   {fputs("double", fp);}
.|\n    {fputs(yytext, fp);}
<<EOF>> {return 0;}

%%

/*** C Code section ***/
int main(void)
{
    char filename1[100];
    char filename2[100];

    printf("Enter the source C program file : ");
    fgets(filename1, sizeof(filename1), stdin);

    printf("Enter the destination C program file : ");
    fgets(filename2, sizeof(filename2), stdin);

    filename1[strcspn(filename1, "\n")] = '\0';
    filename2[strcspn(filename2, "\n")] = '\0';

    yyin = fopen(filename1, "r");
    fp = fopen(filename2, "w");

    yylex();
    fclose(yyin);
    fclose(fp);

    printf("Your work is done. Check the destination file for the output.\n");

    return 0;
}

int yywrap()
{
    return 1;
}

/* flex 10.l && gcc lex.yy.c && ./a.out */