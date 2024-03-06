#include "tokenizer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
} Parser;

Parser parser;
