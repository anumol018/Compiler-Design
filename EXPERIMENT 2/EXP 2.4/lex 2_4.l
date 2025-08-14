%{
#include <stdio.h>

int vow = 0;
int cons = 0;
%}

%%
[AaEeIiOoUu]     { vow++; }                // Step 3a: Vowels
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { cons++; } // Step 3b: Consonants
.|\n            { /* ignore other characters like digits, spaces, etc. */ }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a string :\n");
    yylex();
    printf("\nNumber of Vowels: %d\nNumber of Consonants: %d\n", vow, cons);
    return 0;
}
