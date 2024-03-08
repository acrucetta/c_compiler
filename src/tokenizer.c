#include "tokenizer.h"
#include "../src/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      break;
    default:
      return;
    }
  }
}

enum TokenType check_keyword(int start, int length, const char *rest,
                             enum TokenType type) {
  if (scanner.current - scanner.start == start + length &&
      memcmp(scanner.start + start, rest, length) == 0) {
    return type;
  }
  return TOKEN_IDENTIFIER;
}

enum TokenType identifier_type() {
  switch (scanner.start[0]) {
  case 'b':
    return check_keyword(1, 6, "oolean", TOKEN_BOOLEAN);
  case 'c':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'h':
        return check_keyword(2, 2, "ar", TOKEN_CHAR);
      case 'l':
        return check_keyword(2, 4, "lass", TOKEN_CLASS);
      case 'o':
        return check_keyword(2, 9, "nstructor", TOKEN_CONSTRUCTOR);
      }
    }
    break;
  case 'd':
    return check_keyword(1, 1, "o", TOKEN_DO);
  case 'e':
    return check_keyword(1, 3, "lse", TOKEN_ELSE);
  case 'f':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'i':
        return check_keyword(2, 3, "eld", TOKEN_FIELD);
      case 'a':
        return check_keyword(2, 3, "lse", TOKEN_FALSE);
      case 'u':
        return check_keyword(2, 6, "nction", TOKEN_FUNCTION);
      }
    }
    break;
  case 'l':
    return check_keyword(1, 2, "et", TOKEN_LET);
  case 'm':
    return check_keyword(1, 5, "ethod", TOKEN_METHOD);
  case 'n':
    return check_keyword(1, 3, "ull", TOKEN_NULL);
  case 's':
    return check_keyword(2, 5, "tatic", TOKEN_STATIC);
  case 'i':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'f':
        return check_keyword(2, 0, "", TOKEN_IF);
      case 'n':
        return check_keyword(2, 1, "t", TOKEN_INT);
      }
    }
    break;
  case 'r':
    return check_keyword(1, 5, "eturn", TOKEN_RETURN);
  case 't':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'h':
        return check_keyword(2, 2, "is", TOKEN_THIS);
      case 'r':
        return check_keyword(2, 2, "ue", TOKEN_TRUE);
      }
    }
    break;
  case 'v':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'a':
        return check_keyword(2, 1, "r", TOKEN_VAR);
      case 'o':
        return check_keyword(2, 2, "id", TOKEN_VOID);
      }
    }
    break;
  case 'w':
    return check_keyword(1, 4, "hile", TOKEN_WHILE);
  }
  return TOKEN_IDENTIFIER;
}

enum TokenType identifier() {
  while (is_alpha(peek()) || is_digit(peek()))
    advance();

  return identifier_type();
}

enum TokenType number() {
  while (is_digit(peek()))
    advance();
  if (peek() == '.' && is_digit(peek_next())) {
    advance();
    while (is_digit(peek_next()))
      advance();
  }
  return TOKEN_NUMBER;
}

enum TokenType string() {
  while (peek() != '"' && !is_at_end()) {
    if (peek() == '\n')
      scanner.line++;
    advance();
  }
  if (is_at_end()) {
    printf("Unterminated string.\n");
    exit(1);
  }
  advance();
  return TOKEN_STRING;
}

Token make_token(enum TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;
  token.name = get_substring(token.start, 0, token.length);
  return token;
}

Token scan_token() {
  skip_whitespace();
  scanner.start = scanner.current;
  if (is_at_end())
    return make_token(TOKEN_EOF);
  char c = advance();
  if (is_alpha(c)) {
    return make_token(identifier());
  }
  if (is_digit(c)) {
    return make_token(number());
  }
  switch (c) {
  case '"':
    return make_token(string());
  default:
    return make_token(TOKEN_SYMBOL);
  }
}

Token *scan_tokens(const char *source) {
  init_scanner(source);
  int capacity = 8;
  int count = 0;
  Token *tokens = malloc(capacity * sizeof(Token));
  for (;;) {
    printf("Scanner Current %s", scanner.current);
    Token token = scan_token();
    if (token.type == TOKEN_EOF) {
      printf("EOF");
      break;
    }
    if (count == capacity) {
      capacity *= 2;
      tokens = realloc(tokens, capacity * sizeof(Token));
    }
    tokens[count++] = token;
  }
  tokens = realloc(tokens, count * sizeof(Token));
  return tokens;
}
