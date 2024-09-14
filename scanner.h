#ifndef SCANNER_H
#define SCANNER_H

#include <stdbool.h>

typedef enum {
    TOK_PAREN_LEFT,
    TOK_PAREN_RIGHT,
    TOK_BRACE_RIGHT,
    TOK_BRACE_LEFT,
    TOK_SEMICOLON,
    TOK_EQUAL,
    TOK_EQUAL_EQUAL,
    TOK_LESS,
    TOK_LESS_EQUAL,
    TOK_NUMBER,
    TOK_IDENTIFIER,

    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,

    TOK_INT,
    TOK_CHAR,
    TOK_UNSIGNED,
    TOK_VOID,

    TOK_PLUS,
    TOK_MINUS,
    TOK_ASTERIX,
    TOK_SLASH,

    TOK_EOF,
    TOK_ERROR,
} TokenType;

typedef struct {
    TokenType kind;
    const char* start;
    int length;
    int line;
} Token;

typedef struct {
    const char* tokenStart;
    const char* tokenEnd;
    bool hasPeek;
    Token peekValue;
    int line;
} Scanner;

Scanner newScanner(const char* text);
Token nextToken(Scanner* scan);
//Token peek(Scanner* scan);

#endif
