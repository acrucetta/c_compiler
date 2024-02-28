// tokenizer.h

typedef enum {
  TOKEN_ERROR,
  TOKEN_SYMBOL,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_CLASS,
  TOKEN_METHOD,
  TOKEN_FUNCTION,
  TOKEN_CONSTRUCTOR,
  TOKEN_INT,
  TOKEN_BOOLEAN,
  TOKEN_CHAR,
  TOKEN_VOID,
  TOKEN_VAR,
  TOKEN_STATIC,
  TOKEN_FIELD,
  TOKEN_LET,
  TOKEN_DO,
  TOKEN_IF,
  TOKEN_ELSE,
  TOKEN_WHILE,
  TOKEN_RETURN,
  TOKEN_TRUE,
  TOKEN_FALSE,
  TOKEN_NULL,
  TOKEN_THIS,
  TOKEN_EOF,
  TOKEN_IDENTIFIER
} TokenType;

typedef struct {
  const char *start;
  const char *current;
  int line;
} Scanner;

typedef struct {
  TokenType type;
  const char *start;
  int length;
  int line;
} Token;

void init_scanner(const char *source);
Token scan_token();
