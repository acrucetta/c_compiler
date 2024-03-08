#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_symbol_table_stack(SymbolTableStack *stack) { stack->top = -1; }

void push_symbol_table(SymbolTableStack *stack, SymbolTable table) {
  if (stack->top >= MAX_SCOPE) {
    printf("Symbol table stack is full\n");
    exit(1);
  }
  stack->tables[++stack->top] = table;
}

void pop_symbol_table(SymbolTableStack *stack) {
  if (stack->top < 0) {
    printf("Symbol table stack is empty\n");
    exit(1);
  }
  stack->top--;
}

void init_symbol_table(SymbolTable *table) {
  table->count = 0;
  table->static_idx = 0;
  table->field_idx = 0;
  table->var_idx = 0;
  table->arg_idx = 0;
}

void reset_symbol_table(SymbolTable *table) {
  table->count = 0;
  table->var_idx = 0;
  table->arg_idx = 0;
}

void add_symbol(SymbolTable *table, char *name, char *type, Kind kind) {
  if (table->count >= MAX_SYMBOLS) {
    printf("Symbol table is full\n");
    exit(1);
  }

  Symbol *symbol = &table->symbols[table->count++];
  strncpy(symbol->name, name, MAX_NAME_LENGTH);
  strncpy(symbol->type, type, MAX_NAME_LENGTH);
  symbol->kind = kind;

  switch (kind) {
  case STATIC:
    symbol->index = table->static_idx++;
    break;
  case FIELD:
    symbol->index = table->field_idx++;
    break;
  case VAR:
    symbol->index = table->var_idx++;
    break;
  case ARG:
    symbol->index = table->arg_idx++;
    break;
  default:
    break;
  }
}

Symbol *find_symbol(SymbolTable *table, char *name) {
  for (int i = 0; i < table->count; i++) {
    if (strcmp(table->symbols[i].name, name) == 0) {
      return &table->symbols[i];
    }
  }
  return NULL;
}

void printSymbolTableStack(SymbolTableStack symbolTableStack) {
  printf("Symbol Table:\n");
  printf("Name\t\tType\t\tKind\t\tIndex\n");
  printf("----------------------------------------------------\n");
  for (int i = 0; i <= symbolTableStack.top; i++) {
    SymbolTable *table = &symbolTableStack.tables[i];
    for (int j = 0; j < table->count; j++) {
      Symbol *symbol = &table->symbols[j];
      printf("%s\t\t%s\t\t%d\t\t%d\n", symbol->name, symbol->type, symbol->kind,
             symbol->index);
    }
  }
}
