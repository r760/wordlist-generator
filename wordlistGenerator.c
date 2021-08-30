#include "wordlistGenerator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *out;
char *fname, *alphabet = "";
int min = 0, max = 0, counter = 0;
unsigned long now = 0;

char *expand(char *s1, char *s2) {
  char *s3 = malloc(sizeof(char) * (strlen(s1) + strlen(s2)));
  strcpy(s3, s1);
  strcat(s3, s2);
  return s3;
}

void generate(int i, int len, char *combination) {
  if (i >= len) {
    fprintf(out, "%s\n", combination);
    now++;
    free(combination);
  } else {
    int j;
    for (j = 0; j < strlen(alphabet); j++) {
      char temp[1];
      temp[0] = alphabet[j];
      generate(i + 1, len, expand(combination, temp));
    }
  }
}

int main(int argc, char *argv[]) {

  char *combination = "";

  if (argc == 1) {
    man();
  } else {
    int j;
    for (j = 1; j < argc; j++) {
      if (strcmp(argv[j], "-o") == 0) {
        assert((j + 1) < argc && "You must provide OUT after -o");
        fname = argv[j + 1];
        out = fopen(fname, "w");
      } else if (strcmp(argv[j], "-min") == 0) {
        assert((j + 1) < argc && "You must provide MIN after -min");
        min = atoi(argv[j + 1]);
      } else if (strcmp(argv[j], "-max") == 0) {
        assert((j + 1) < argc && "You must provide MAX after -max");
        max = atoi(argv[j + 1]);
      } else if (strcmp(argv[j], "-d") == 0) {
        alphabet = expand(alphabet, "0123456789");
        counter++;
      } else if (strcmp(argv[j], "-l") == 0) {
        alphabet = expand(alphabet, "abcdefghijklmnopqrstuvwxyz");
        counter++;
      } else if (strcmp(argv[j], "-L") == 0) {
        alphabet = expand(alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        counter++;
      } else if (strcmp(argv[j], "-s") == 0) {
        alphabet = expand(alphabet, " ");
        counter++;
      } else if (strcmp(argv[j], "-a") == 0) {
        assert((j + 1) < argc && "You must provide APPEND after -a");
        alphabet = expand(alphabet, argv[j + 1]);
        counter++;
      }
    }

    assert(min >= 1 && "You must provide -min MIN");
    assert(max >= 1 && "You must provide -max MAX");
    assert(min <= max && "MIN must be smaller or equal MAX");
    assert(counter >= 1 && "You must provide at least one of -d -l -L -s -a");
    assert(out != NULL && "You must provide -o OUT");

    printf("Minimum word length set to %d\n", min);
    printf("Maximum word length set to %d\n", max);
    printf("Alphabet set to [%s]\n\n", alphabet);

    for (int len = min; len <= max; len++) {
      generate(0, len, combination);
    }

    printf("Wrote %lu words(s) to file named %s\n", now, fname);
    fclose(out);
    return 0;
  }
}