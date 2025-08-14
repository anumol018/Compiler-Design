#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    for (int i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int isSeparator(char ch) {
    char separators[] = "();{}[],:";
    for (int i = 0; i < strlen(separators); i++) {
        if (ch == separators[i]) return 1;
    }
    return 0;
}

int isOperator(char ch) {
    char operators[] = "+-*/%=<>&|!";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[50];
    FILE *fp;
    int i = 0;
    int insideSingleLineComment = 0, insideMultiLineComment = 0;

    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Handle comments
        if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                insideSingleLineComment = 1;
            } else if (next == '*') {
                insideMultiLineComment = 1;
            } else {
                ungetc(next, fp); // it's just /
            }

            if (insideSingleLineComment || insideMultiLineComment) continue;
        }

        if (insideSingleLineComment) {
            if (ch == '\n') insideSingleLineComment = 0;
            continue;
        }

        if (insideMultiLineComment) {
            if (ch == '*') {
                char next = fgetc(fp);
                if (next == '/') {
                    insideMultiLineComment = 0;
                } else {
                    ungetc(next, fp);
                }
            }
            continue;
        }

        // Handle identifiers and numbers
        if (isalnum(ch) || ch == '_' || (ch == '.' && i > 0 && isdigit(buffer[i - 1]))) {
            buffer[i++] = ch;
        } else {
            if (i > 0) {
                buffer[i] = '\0';
                i = 0;

                // Check if it's a floating point number
                int isFloat = 0, hasAlpha = 0;
                for (int k = 0; buffer[k]; k++) {
                    if (buffer[k] == '.') isFloat = 1;
                    if (isalpha(buffer[k]) && buffer[k] != '.') hasAlpha = 1;
                }

                if (isFloat && !hasAlpha) {
                    printf("%s is a floating-point number\n", buffer);
                } else if (isKeyword(buffer)) {
                    printf("%s is a keyword\n", buffer);
                } else if (isdigit(buffer[0])) {
                    printf("%s is a number\n", buffer);
                } else {
                    printf("%s is an identifier\n", buffer);
                }
            }

            // Check for separators
            if (isSeparator(ch)) {
                printf("%c is a separator\n", ch);
            }

            // Check for operators
            else if (isOperator(ch)) {
                printf("%c is an operator\n", ch);
            }
        }
    }

    // Final token flush at EOF
    if (i > 0) {
        buffer[i] = '\0';

        int isFloat = 0, hasAlpha = 0;
        for (int k = 0; buffer[k]; k++) {
            if (buffer[k] == '.') isFloat = 1;
            if (isalpha(buffer[k]) && buffer[k] != '.') hasAlpha = 1;
        }

        if (isFloat && !hasAlpha) {
            printf("%s is a floating-point number\n", buffer);
        } else if (isKeyword(buffer)) {
            printf("%s is a keyword\n", buffer);
        } else if (isdigit(buffer[0])) {
            printf("%s is a number\n", buffer);
        } else {
            printf("%s is an identifier\n", buffer);
        }
    }

    fclose(fp);
    return 0;
}
