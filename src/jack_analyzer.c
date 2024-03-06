#include "../src/file_io.h"
#include "../src/symbol_table.h"
#include "../src/tokenizer.h"
#include <assert.h>
#include <stdio.h>

int main() {
  char *out_file = "test.xml";
  char *in_file = "tests/Prog.jack";
  char *file_contents = read_file(in_file);

  SymbolTableStack stack;
  init_symbol_table_stack(&stack);

  SymbolTable global_table;
  init_symbol_table(&global_table);
  push_symbol_table(&stack, global_table);

  Token *tokens = scan_tokens(file_contents, &stack);
  write_xml_from_tokens(out_file, tokens);
}
