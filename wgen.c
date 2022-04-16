#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *expand(char *s1, char *s2)
{
    char *s3 = malloc(sizeof(char) * (strlen(s1) + strlen(s2)));
    strcpy(s3, s1);
    strcat(s3, s2);
    return s3;
}

void generate(size_t i, size_t len, size_t *now, char *alphabet,
        char *combination, FILE *out)
{
    if (i >= len) {
        fprintf(out, "%s\n", combination);
        free(combination);
        *now = *now + 1;
    } else {
        for (int j = 0; j < strlen(alphabet); j++) {
            char temp[1];
            temp[0] = alphabet[j];
            generate(i + 1, len, now, alphabet, expand(combination, temp), out);
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *out;
    char *alphabet = "", *combination = "", *fname = "";
    size_t min = 0, max = 0, counter = 0, now = 0;

    if (argc >= 2) {
        for (int j = 1; j < argc; j++) {
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
                assert((j + 1) < argc && "You must provide \"CHARACTERS\" after -a");
                alphabet = expand(alphabet, argv[j + 1]);
                counter++;
            }
        }

        assert(out != NULL && "You must provide -o OUT");
        assert(min >= 1 && "You must provide -min MIN");
        assert(max >= 1 && "You must provide -max MAX");
        assert(min <= max && "MIN must be smaller then or equal to MAX");
        assert(counter >= 1 && "You must provide at least one of -d -l -L -s -a");

        printf("Minimum word length set to %ld\n", min);
        printf("Maximum word length set to %ld\n", max);
        printf("Alphabet set to [%s]\n\n", alphabet);

        for (size_t len = min; len <= max; len++) {
            generate(0, len, &now, alphabet, combination, out);
        }

        printf("Wrote %lu words(s) to file named %s\n", now, fname);
        fclose(out);
        return 0;
    } else {
        printf("You must provide required arguments, please view the man page\n");
    }
}
