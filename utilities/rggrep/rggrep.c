#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const* argv[]) {
  if (argc == 1) {
    printf("rggrep: searchterm [file ...]\n");
    exit(1);
  }

  const char* searchTerm = argv[1];
  size_t size;
  char* line = NULL;

  if (argc == 2) {
    while (getline(&line, &size, stdin) != -1) {
      if (strstr(line, searchTerm) != NULL) {
        printf("%s", line);
      }
    }

    free(line);
    exit(0);
  }

  for (int i = 2; i < argc; i++) {
    FILE* file = fopen(argv[i], "r");

    if (file == NULL) {
      printf("rggrep: cannot open file\n");
      exit(1);
    }

    while (getline(&line, &size, file) != -1) {
      // if (searchTerm == "") {
      //   printf(line);
      //   continue;
      // }

      if (strstr(line, searchTerm) != NULL) {
        printf("%s", line);
      }
    }

    free(line);
    fclose(file);
  }

  return 0;
}
