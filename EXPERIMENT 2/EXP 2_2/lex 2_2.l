%{
#include <stdio.h>

int chars = 0;
int words = 0;
int lines = 0;
FILE *yyin;
%}

%%
[a-zA-Z0-9]     { chars++; }
[ \t]           { words++; chars++; }
\n              { lines++; chars++; }
.               { chars++; }  // Any other characters still count
%%

int yywrap() {
    // At EOF, as per algorithm, increment all counters once
    chars++;
    words++;
    lines++;
    return 1;
}

int main() {
    yyin = fopen("input2.txt", "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    yylex();

    printf("\nLine count: %d\nWord count: %d\nCharacter count: %d\n", lines, words,chars);

    fclose(yyin);
    return 0;
}
