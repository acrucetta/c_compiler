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
  TokenType token = scan_token_type(); // Assuming scan_token exists and returns
  assert(token == KEYWORD);
  TokenType token2 = scan_token_type();
  assert(token2 == IDENTIFIER);
  TokenType token3 = scan_token_type();
  assert(token3 == IDENTIFIER);
  TokenType token4 = scan_token_type();
  assert(token4 == SYMBOL);
  printf("\nScan token test passed.\n");
}

void test_scan_declaration() {
  init_scanner("let s = \"A\";");
  TokenType token = scan_token_type();
  assert(token == KEYWORD);
  TokenType token2 = scan_token_type();
  assert(token2 == IDENTIFIER);
  TokenType token3 = scan_token_type();
  assert(token3 == SYMBOL);
  TokenType token4 = scan_token_type();
  assert(token4 == STRING_CONST);
  TokenType token5 = scan_token_type();
  assert(token5 == SYMBOL);
  printf("\nScan declaration test passed.\n");
}

void test_open_file_and_tokenize() {
  char *file = "tests/Prog.jack";
  char *file_contents = read_file(file);
  init_scanner(file_contents);
  for (int i = 0; i < 100; i++) {
    TokenType token = scan_token_type();
    if (token == _EOF) {
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
