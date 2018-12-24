#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define BLOCKSIZE 4096

void stdcat(int argc, char *argv[]);
void lowcat(int argc, char *argv[]);
int fun_time(void (*fun)(int, int));

int main(int argc, char *argv[]) {
    long int start, time1, time2;
    start = time(NULL);
    stdcat(argc, argv);
    time1 = time(NULL) - start;
    
    start = time(NULL);
    lowcat(argc, argv);
    time2 = time(NULL) - start;

    printf("time elapsed for lowcat: %ld\n", time2);
    printf("time elapsed for stdcat: %ld\n", time1);
}

void filecopy(FILE *in, FILE *out) {
    int c;
    while ((c = getc(in)) != EOF)
        putc(c, out);
}
void stdcat(int argc, char *argv[]) {
    int i;
    FILE *f;
    for (i = 1; i < argc; i++) {
        f = fopen(*(argv + i), "r"); 
        if (f == NULL) {
            fprintf(stderr, "failed to read %s", *(argv + i));
            exit(1);
        }
        filecopy(f, stdout); 
    }
}

void lowcat(int argc, char *argv[]) {
    int i, n, fd;
    char buf[BLOCKSIZE];
    for (i = 1; i < argc; i++) {
        fd = open(*(argv + i), O_RDONLY); 
        if (fd < 0) {
            fprintf(stderr, "failed to read %s", *(argv + i));
            exit(1);
        }
        while ((n = read(fd, buf, BLOCKSIZE)) > 0) 
            write(1, buf, n);
        close(fd);
    } 
}
