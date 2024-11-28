#include <string.h>

#include "string.h"

///////////////////////////////////////////////
void remove_trailing_newline(char *str)
{
    if (str == NULL)
        return;

    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

int is_empty_string(const char *str)
{
    return str[0] == '\0';
}