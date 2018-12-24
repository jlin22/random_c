#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

int main(int argc, char *argv[]) {
    int c;
    
    int (*convert)(int);
    if (*(argv[1]) == '-') {
        if (*(argv[1] + 1) == 'l')
            convert = tolower;
        else if (*(argv[1] + 1) == 'u')
            convert = toupper;
    }
    while ((c = getchar()) != EOF) 
        putchar(convert(c));
    return 0;
}
