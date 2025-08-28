#include "strutils.h"

int main()
{
    char dracula[] = "-dracula+";
    printf("Befor reverse: \"%s\"\n", dracula);
    str_reverse(dracula);
    printf("After reverse: \"%s\"\n", dracula);

    char untrimmed[] = "   Alo alo 1234 alo!     ";
    char* trimmed = NULL;
    printf("Befor trim: \"%s\"\n", untrimmed);
    trimmed = str_trim(untrimmed);
    printf("After trim: \"%s\"\n", trimmed);

    const char* numstr = "a  -1234xyz123";
    int num = str_to_int(numstr);
    printf("String \"%s\" to int: %d\n", numstr, num);
    return 0;
}