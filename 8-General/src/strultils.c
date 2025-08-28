#include "strutils.h"
#include <stdlib.h>
#include <string.h>

void str_reverse(char* str)
{
    size_t length = strlen(str);
    if (str == NULL || length < 2) {
        return;
    }

    char* dummy = (char*)malloc(length);
    if (dummy == NULL) {
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        dummy[i] = str[length - i - 1];
        //printf("%c\n", dummy[i]);
    }
    for (size_t i = 0; i < length; ++i) {
        str[i] = dummy[i];
        //printf("%c\n", dummy[i]);
    }

    free(dummy);
}

char* str_trim(char* str)
{
    if (str == NULL) {
        return str;
    }

    size_t length = strlen(str);
    //printf("str before = %p\n", str);
    while (length > 0 && (char)str[0] == ' ') {
        str++;
        length--;
    }
    //printf("str after = %p\n", str);s
    //printf("\'%c\'\n", str[length-1]);
    while (length > 0 && (char)str[length-1] == ' ') {
        length--;
        //printf("length = %zu\n", length);
    }
    str[length] = '\0';
    return str;
}

int str_to_int(const char* str)
{
    if (str == NULL) {
        return 0;
    }

    return atoi(str);
}