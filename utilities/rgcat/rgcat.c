#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const* argv[]) {
  if (argc == 1) {
    // printf("Please enter one or more files as arguments.\n");
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    FILE* fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("rgcat: cannot open file\n");
      exit(1);
    }

    char buf[256];

    while (fgets(buf, sizeof(buf), fp) != NULL) {
      printf("%s", buf);
    }

    fclose(fp);
  }
  return 0;
}
