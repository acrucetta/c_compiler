/*
Tokenizer High Level:
- Split each line into blank spaces
- Parse each set of chars and determine
what type of symbol they are
- Append the symbols to some kind of array
of enums or types
*/

#include "tokenizer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  const char *start;
  const char *current;
  int line;
} Scanner;

Scanner scanner;

void init_scanner(const char *source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
};

static bool is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool is_digit(char c) { return c >= '0' && c <= '9'; }

static bool is_at_end() { return *scanner.current == '\0'; }

static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

static char peek() { return *scanner.current; }

static char peek_next() {
  if (is_at_end())
    return '\0';
  return scanner.current[1];
}

void skip_whitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    case '\n':
      scanner.line++;
      advance();
      break;
    case '/':
      if (peek_next() == '/') {
        while (peek() != '\n' && !is_at_end())
          advance();
      } else {
        return;
      }
    default:
      return;
    }
  }
}

TokenType identifier() {
  while (is_alpha(peek()) || is_digit(peek()))
    advance();
  return IDENTIFIER;
}

TokenType number() {
  while (is_digit(peek()))
    advance();
  if (peek() == '.' && is_digit(peek_next())) {
    advance();
    while (is_digit(peek_next()))
      advance();
  }
  return INT_CONST;
}

TokenType string() {}

Token make_token(Symbol type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;
  return token;
}

TokenType scan_token_types() {
  skip_whitespace();
  scanner.start = scanner.current;
  if (is_at_end())
    return _EOF;
  char c;
  advance();

  if (is_alpha(c)) {
    return identifier();
  }
  if (is_digit(c)) {
    return number();
  }
  switch (c) {
  case '"':
    return string();
  default:
    return SYMBOL;
  }
}
