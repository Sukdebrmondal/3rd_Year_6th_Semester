

%{
#include<stdio.h>
%}

%%

"create"|"CREATE"   { printf("CREATE command detected\n"); }
"select"|"SELECT"   { printf("SELECT command detected\n"); }
"insert"|"INSERT"   { printf("INSERT command detected\n"); }
"delete"|"DELETE"   { printf("DELETE command detected\n"); }

[a-zA-Z]+   { printf("Other word: %s\n", yytext); }
.   ;

%%


int yywrap(){
    return 1;
}

int main(){
    printf("Enter a SQL command: ");
    yylex();
    return 0;
}

// flex q6.l && lex.yy.c && ./a.out
