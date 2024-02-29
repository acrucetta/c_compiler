#include "../src/tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *path);
void write_xml_from_tokens(const char *path, Token *tokens);
