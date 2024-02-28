// tests/test_tokenizer.c
#include "../src/file_io.h"
#include "../src/tokenizer.h"
#include <assert.h>
#include <stdio.h>

Scanner scanner;

void test_init_scanner() {
  const char *source = "var Array x;";
  init_scanner(source);
  assert(scanner.current == source);
  assert(scanner.line == 1);
  // More assertions can be added here to validate the initial state of the
  // scanner
  printf("Init scanner test passed.\n");
}

void test_scan_token() {
  // This test assumes a function scan_token() that returns the next token
  init_scanner("var Array x;");
  Token token = scan_token(); // Assuming scan_token exists and returns
  assert(token.type == TOKEN_VAR);
  Token token2 = scan_token();
  assert(token2.type == TOKEN_IDENTIFIER);
  Token token3 = scan_token();
  assert(token3.type == TOKEN_IDENTIFIER);
  Token token4 = scan_token();
  assert(token4.type == TOKEN_SYMBOL);
  printf("\nScan token test passed.\n");
}

void test_scan_declaration() {
  init_scanner("let s = \"A\";");
  Token token = scan_token();
  assert(token.type == TOKEN_LET);
  Token token2 = scan_token();
  assert(token2.type == TOKEN_IDENTIFIER);
  Token token3 = scan_token();
  assert(token3.type == TOKEN_SYMBOL);
  Token token4 = scan_token();
  assert(token4.type == TOKEN_STRING);
  Token token5 = scan_token();
  assert(token5.type == TOKEN_SYMBOL);
  printf("\nScan declaration test passed.\n");
}

void test_open_file_and_tokenize() {
  char *file = "tests/Prog.jack";
  char *file_contents = read_file(file);
  init_scanner(file_contents);
  for (int i = 0; i < 100; i++) {
    Token token = scan_token();
    if (token.type == TOKEN_EOF) {
      break;
    }
    printf("Token: %d\n", token);
  }
}

int main() {
  test_init_scanner();
  // test_scan_token();
  // test_scan_declaration();
  test_open_file_and_tokenize();
  printf("All tests passed.\n");
  return 0;
}
