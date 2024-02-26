typedef enum {
  KEYWORD,
  SYMBOL,
  IDENTIFIER_INT,
  INT_CONST,
  STRING_CONST
} TokenType;

typedef enum {
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
  TOKEN_THIS
} Symbol;

typedef struct {
  Symbol type;
  const char *start;
  int length;
  int line;
} Token;

void init_scanner(const char *source);
Token scan_token();
