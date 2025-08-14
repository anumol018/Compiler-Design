%{
#include <stdio.h>
%}

%%
abc       { printf("ABC"); }  // Step 4.i: Replace "abc" with "ABC"
.|\n      { ECHO; }           // Step 4.ii: Copy other characters
%%

int main() {
    printf("Enter text :\n");
    yylex(); // Step 2: Read input and process tokens
    return 0;
}

int yywrap() {
    return 1;
}
