#include "file_io.h"
#include "tokenizer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int indentation;
  FILE *out_file;
  Token token;
} CompilationEngine;

int compile_class(CompilationEngine *engine);
int compile_class_var_dec(CompilationEngine *engine);
int compile_subroutine(CompilationEngine *engine);
int compile_parameter_list(CompilationEngine *engine);
char *get_indentation(int indentation);
void _write_token(CompilationEngine *engine);

int init_compilation_engine(char *in_file, char *out_file) {
  char *file_contents = read_file(in_file);

  SymbolTableStack stack;
  init_symbol_table_stack(&stack);

  SymbolTable global_table;
  init_symbol_table(&global_table);
  push_symbol_table(&stack, global_table);

  init_scanner(file_contents);

  CompilationEngine engine;
  engine.indentation = 0;
  engine.out_file = fopen(out_file, "w+");
  if (engine.out_file == NULL) {
    printf("Error opening file!\n");
    return EXIT_FAILURE;
  }
  int err = compile_class(&engine);
  if (err) {
    return EXIT_FAILURE;
  }

  fclose(engine.out_file);
  return EXIT_SUCCESS;
}

int compile_class(CompilationEngine *engine) {
  engine->token = scan_token();
  if (engine->token.type != TOKEN_CLASS) {
    printf("Expected class got %s\n", token_string[engine->token.type]);
    return EXIT_FAILURE;
  }

  fprintf(engine->out_file, "<class>\n");
  engine->indentation += 1;
  _write_token(engine);

  engine->token = scan_token();
  if (engine->token.type != TOKEN_IDENTIFIER) {
    printf("Expected identifier got %s\n", token_string[engine->token.type]);
    return EXIT_FAILURE;
  }
  _write_token(engine);

  engine->token = scan_token();
  if (engine->token.type != TOKEN_SYMBOL || engine->token.name[0] != '{') {
    return EXIT_FAILURE;
  }
  _write_token(engine);

  engine->token = scan_token();
  while (engine->token.type == TOKEN_STATIC ||
         engine->token.type == TOKEN_FIELD) {
    compile_class_var_dec(engine);
  }
  while (engine->token.type == TOKEN_CONSTRUCTOR ||
         engine->token.type == TOKEN_FUNCTION ||
         engine->token.type == TOKEN_METHOD) {
    compile_subroutine(engine);
  }
  _write_token(engine);
  fprintf(engine->out_file, "</class>\n");
  return EXIT_SUCCESS;
}

int compile_class_var_dec(CompilationEngine *engine) {
  char *ind1 = get_indentation(engine->indentation);
  fprintf(engine->out_file, &ind1);
  fprintf(engine->out_file, "<classVarDec>\n");
  engine->indentation += 1;
  _write_token(engine);
  engine->token = scan_token();
  engine->indentation -= 1;
  char *ind2 = get_indentation(engine->indentation);
  fprintf(engine->out_file, &ind2);
  fprintf(engine->out_file, "</classVarDec>\n");
}

int compile_subroutine(CompilationEngine *engine) {
  char *ind1 = get_indentation(engine->indentation);
  fprintf(engine->out_file, &ind1);
  fprintf(engine->out_file, "<subroutineDec>\n");
  engine->indentation += 1;
  _write_token(engine); // Writing Keyword

  engine->token = scan_token();
  _write_token(engine); // Writing Identifier

  engine->token = scan_token();
  _write_token(engine); // Writing Symbol

  engine->token = scan_token(); // Writing Keyword
  compile_parameter_list(engine);
}

int compile_parameter_list(CompilationEngine *engine) {
  char *ind1 = get_indentation(engine->indentation);
  fprintf(engine->out_file, &ind1);
  fprintf(engine->out_file, "<parameterList>\n");
  engine->indentation += 1;

  while (engine->token.type != TOKEN_SYMBOL) {
    _write_token(engine); // Writing Keyword or Identifier
    engine->token = scan_token();
    _write_token(engine); // Writing Identifier
    engine->token = scan_token();
    if (engine->token.type == TOKEN_SYMBOL && engine->token.name[0] == ',') {
      _write_token(engine); // Writing Symbol
      engine->token = scan_token();
    }
  }
  engine->indentation -= 1;
  char *ind2 = get_indentation(engine->indentation);
  fprintf(engine->out_file, &ind2);
  fprintf(engine->out_file, "</parameterList>\n");
}
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

char *get_indentation(int indentation) {
  char *indentation_str = malloc(indentation + 1);
  for (int i = 0; i < indentation; i++) {
    indentation_str[i] = ' ';
  }
  indentation_str[indentation] = '\0';
  return indentation_str;
}

void _write_token(CompilationEngine *engine) {
  for (int i = 0; i < engine->indentation; i++) {
    fprintf(engine->out_file, ' ');
  }
  fprintf(engine->out_file, "<%s> %s </%s>\n", token_string[engine->token.type],
          engine->token.name, token_string[engine->token.type]);
}
