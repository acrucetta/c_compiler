#include "../src/file_io.h"
#include "../src/tokenizer.h"
#include <assert.h>
#include <stdio.h>

int main() {
  char *out_file = "test.xml";
  char *in_file = "tests/Prog.jack";
  char *file_contents = read_file(in_file);
  Token *tokens = scan_tokens(file_contents);
  write_xml_from_tokens(out_file, tokens);
}
