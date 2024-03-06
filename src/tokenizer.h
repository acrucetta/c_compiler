#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "symbol_table.h"
#define FOREACH_TOKEN(TOKEN)                                                   \
  TOKEN(TOKEN_ERROR)                                                           \
  TOKEN(TOKEN_SYMBOL)                                                          \
  TOKEN(TOKEN_NUMBER)                                                          \
  TOKEN(TOKEN_STRING)                                                          \
  TOKEN(TOKEN_CLASS)                                                           \
  TOKEN(TOKEN_METHOD)                                                          \
  TOKEN(TOKEN_FUNCTION)                                                        \
  TOKEN(TOKEN_CONSTRUCTOR)                                                     \
  TOKEN(TOKEN_INT)                                                             \
  TOKEN(TOKEN_BOOLEAN)                                                         \
  TOKEN(TOKEN_CHAR)                                                            \
  TOKEN(TOKEN_VOID)                                                            \
  TOKEN(TOKEN_VAR)                                                             \
  TOKEN(TOKEN_STATIC)                                                          \
  TOKEN(TOKEN_FIELD)                                                           \
  TOKEN(TOKEN_LET)                                                             \
  TOKEN(TOKEN_DO)                                                              \
  TOKEN(TOKEN_IF)                                                              \
  TOKEN(TOKEN_ELSE)                                                            \
  TOKEN(TOKEN_WHILE)                                                           \
  TOKEN(TOKEN_RETURN)                                                          \
  TOKEN(TOKEN_TRUE)                                                            \
  TOKEN(TOKEN_FALSE)                                                           \
  TOKEN(TOKEN_NULL)                                                            \
  TOKEN(TOKEN_THIS)                                                            \
  TOKEN(TOKEN_EOF)                                                             \
  TOKEN(TOKEN_IDENTIFIER)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum TokenType { FOREACH_TOKEN(GENERATE_ENUM) };
static const char *token_string[] = {FOREACH_TOKEN(GENERATE_STRING)};

typedef struct {
  const char *start;
  const char *current;
  int line;
} Scanner;

typedef struct {
  enum TokenType type;
  const char *start;
  const char *name;
  int length;
  int line;
} Token;

void init_scanner(const char *source);
Token scan_token(SymbolTable *table);
Token *scan_tokens(const char *source, SymbolTableStack *stack);

#endif
