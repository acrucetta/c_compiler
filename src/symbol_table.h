#define MAX_SYMBOLS 100
#define MAX_NAME_LENGTH 100
#define MAX_SCOPE 100

typedef enum { STATIC, FIELD, VAR, ARG, CLASS, SUBROUTINE } Kind;

typedef struct SymbolTableEntry {
  char name[MAX_NAME_LENGTH];
  char type[MAX_NAME_LENGTH];
  Kind kind;
  int index;
} Symbol;

typedef struct {
  Symbol symbols[MAX_NAME_LENGTH];
  int count;
  int static_idx;
  int field_idx;
  int var_idx;
  int arg_idx;
} SymbolTable;

typedef struct {
  SymbolTable tables[MAX_SCOPE];
  int top;
} SymbolTableStack;

void init_symbol_table_stack(SymbolTableStack *stack);
void push_symbol_table(SymbolTableStack *stack, SymbolTable table);
void pop_symbol_table(SymbolTableStack *stack);
void init_symbol_table(SymbolTable *table);
void add_symbol(SymbolTable *table, char *name, char *type, Kind kind);
Symbol *find_symbol(SymbolTable *table, char *name);
void print_symbol_table(SymbolTableStack *stack);
