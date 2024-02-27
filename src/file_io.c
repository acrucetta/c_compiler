#include "file_io.h"

// Function to read .jack
// files into a string
char *read_file(const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file: %s\n", path);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc(file_size + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Could not allocate memory for file: %s\n", path);
    exit(1);
  }

  size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
  if (bytes_read < file_size) {
    fprintf(stderr, "Could not read file: %s\n", path);
    exit(1);
  }

  buffer[bytes_read] = '\0';
  fclose(file);
  return buffer;
}

// Function to write a XML file
void write_xml_file(const char *path, const char *xml) {
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    fprintf(stderr, "Could not open file: %s\n", path);
    exit(1);
  }

  fprintf(file, "%s", xml);
  fclose(file);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: jack_analyzer <file.jack>\n");
    exit(1);
  }

  const char *input_path = argv[1];
  char *source = read_file(input_path);
  printf("Read file: %s\n", input_path);

  // Print contents of file
  printf("%s\n", source);
}
