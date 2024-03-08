#include "file_io.h"
#include "tokenizer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int compile_class();

int init_compilation_engine(char *in_file, char *out_file) {
  char *file_contents = read_file(in_file);

  SymbolTableStack stack;
  init_symbol_table_stack(&stack);

  SymbolTable global_table;
  init_symbol_table(&global_table);
  push_symbol_table(&stack, global_table);

  init_scanner(file_contents);
  int err = compile_class();
  if (err) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int compile_class() {
  Token token = scan_token();
  if (token.type != TOKEN_CLASS) {
    printf("Expected class got %s\n", token_string[token.type]);
    return EXIT_FAILURE;
  }
  token = scan_token();
  if (token.type != TOKEN_IDENTIFIER) {
    printf("Expected identifier got %s\n", token_string[token.type]);
    return EXIT_FAILURE;
  }
  token = scan_token();
  if (token.type != TOKEN_SYMBOL || token.name[0] != '{') {
    return EXIT_FAILURE;
  }
  while (true) {
    token = scan_token();
    if (token.type == TOKEN_STATIC || token.type == TOKEN_FIELD) {
      printf("classVarDec\n");
      // compile_class_var_dec();
    } else if (token.type == TOKEN_CONSTRUCTOR ||
               token.type == TOKEN_FUNCTION || token.type == TOKEN_METHOD) {
      printf("subroutineDec\n");
      // compile_subroutine();
    } else {
      break;
    }
  }
  if (token.type != TOKEN_SYMBOL || token.name[0] != '}') {
    return EXIT_FAILURE;
  }

  printf("Passed\n");
}

int compile_class_var_dec();
int compile_subroutine();
int compile_parameter_list();
int compile_var_dec();
int compile_statements();
int compile_do();
int compile_let();
int compile_while();
int compile_return();
int compile_if();
int compile_expression();
int compile_term();
int compile_expression_list();
