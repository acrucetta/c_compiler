#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_substring(const char *source, int start, int end) {
  int length = end - start;
  char *substring = (char *)malloc(length + 1);
  if (substring == NULL) {
    fprintf(stderr, "Could not allocate memory for substring\n");
    exit(1);
  }
  strncpy(substring, source + start, length);
  substring[length] = '\0';
  return substring;
};
