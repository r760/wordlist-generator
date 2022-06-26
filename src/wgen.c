#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"

char *expand(char *s1, char *s2)
{
    char *s3;
    if (s1 == NULL && s2 != NULL) {
        asprintf(&s3, "%s", s2);
    } else if (s1 != NULL && s2 == NULL) {
        asprintf(&s3, "%s", s1);
    } else {
        asprintf(&s3, "%s%s", s1, s2);
    }
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
            if (j == strlen(alphabet) -1 ) {
                free(combination);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *out = NULL;
    char *alphabet = NULL, *combination = NULL, *fname = NULL;
    size_t min = 0, max = 0, counter = 0, now = 0;

    if (argc >= 2) {
        for (int j = 1; j < argc; j++) {
            if (strcmp(argv[j], "-o") == 0) {
                LOG_ERROR((j + 1) < argc, error, "You must provide OUT after -o");
                fname = argv[j + 1];
                out = fopen(fname, "w");
            } else if (strcmp(argv[j], "-min") == 0) {
                LOG_ERROR((j + 1) < argc, error, "You must provide MIN after -min");
                min = atoi(argv[j + 1]);
            } else if (strcmp(argv[j], "-max") == 0) {
                LOG_ERROR((j + 1) < argc, error, "You must provide MAX after -max");
                max = atoi(argv[j + 1]);
            } else if (strcmp(argv[j], "-d") == 0) {
                char *back_ptr = alphabet;
                alphabet = expand(alphabet, "0123456789");
                if (back_ptr != NULL) {
                    free(back_ptr);
                }
                counter++;
            } else if (strcmp(argv[j], "-l") == 0) {
                char *back_ptr = alphabet;
                alphabet = expand(alphabet, "abcdefghijklmnopqrstuvwxyz");
                if (back_ptr != NULL) {
                    free(back_ptr);
                }
                counter++;
            } else if (strcmp(argv[j], "-L") == 0) {
                char *back_ptr = alphabet;
                alphabet = expand(alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
                if (back_ptr != NULL) {
                    free(back_ptr);
                }
                counter++;
            } else if (strcmp(argv[j], "-s") == 0) {
                char *back_ptr = alphabet;
                alphabet = expand(alphabet, " ");
                if (back_ptr != NULL) {
                    free(back_ptr);
                }
                counter++;
            } else if (strcmp(argv[j], "-c") == 0) {
                LOG_ERROR((j + 1) < argc, error, "You must provide \"CHARACTERS\" after -c");
                char *back_ptr = alphabet;
                alphabet = expand(alphabet, argv[j + 1]);
                if (back_ptr != NULL) {
                    free(back_ptr);
                }
                counter++;
            } 
        }

        LOG_ERROR(out != NULL, error, "You must provide -o OUT");
        LOG_ERROR(min >= 1, error, "You must provide -min MIN");
        LOG_ERROR(max >= 1, error, "You must provide -max MAX");
        LOG_ERROR(min <= max, error, "MIN must be smaller then or equal to MAX");
        LOG_ERROR(counter >= 1, error, "You must provide at least one of -d -l -L -s -c");

        LOG_INFO("Minimum word length set to '%ld'", min);
        LOG_INFO("Maximum word length set to '%ld'", max);
        LOG_INFO("Alphabet set to [%s]", alphabet);

        for (size_t len = min; len <= max; len++) {
            generate(0, len, &now, alphabet, combination, out);
        }

        free(alphabet);

        LOG_INFO("Wrote '%lu' words(s) to file named '%s'", now, fname);
        fclose(out);
        return 0;
    } else {
        LOG_INFO("You must provide required arguments, please view the man page\n");
        return 1;
    }

error:
    if (out != NULL) {
        fclose(out);
    }
    return 1;
}
