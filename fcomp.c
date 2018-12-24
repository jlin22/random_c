#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTR 1000
#define USAGE_ERR 1
#define OPEN_ERR 2
#define STDOUT_ERR 3

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "%s usage: compare two files\nEx: %s file1 file2\n", *argv, *argv);
        exit(USAGE_ERR);
    } 
    else {
        FILE *f1, *f2;
        if ((f1 = fopen(*(argv + 1), "r")) == NULL) {
            fprintf(stderr, "%s failed to open %s\n", *argv, *(argv + 1));
            exit(OPEN_ERR);
        }
        if ((f2 = fopen(*(argv + 2), "r")) == NULL) {
            fprintf(stderr, "%s failed to open %s\n", *argv, *(argv + 2));
            exit(OPEN_ERR);
        }
        int line;    
        char s1[1000], s2[1000];
        while (fgets(s1, MAXSTR, f1) && fgets(s2, MAXSTR, f2))
            if (strcmp(s1, s2) != 0) {
                fprintf(stderr, "line %d\n%s\n%s%s\n%s", line, *(argv + 1), s1, *(argv + 2), s2);
                exit(0);
            }

        // at this point, atleast one is EOF
        if (!fgets(s1, MAXSTR, f1) && !fgets(s2, MAXSTR, f2))
            printf("they have the same contents\n");
        else if (!fgets(s1, MAXSTR, f1))
            printf("%s is longer than %s", *(argv + 2), *(argv + 1));
        else
            printf("%s is longer than %s", *(argv + 1), *(argv + 2));
        exit(0);

        if (ferror(stdout)) {
            fprintf(stderr, "%s failed to write to stdout", *argv);
            exit(STDOUT_ERR);
        }
    }
}
