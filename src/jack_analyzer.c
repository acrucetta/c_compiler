#include "../src/compilation_engine.h"
#include "../src/file_io.h"
#include "../src/tokenizer.h"
#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: jack_analyzer <file.jack>\n");
    return 1;
  }

  char *in_file = argv[1];
  char *out_file = "out.xml";

  init_compilation_engine(in_file, out_file);
}
