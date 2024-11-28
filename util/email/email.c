#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "email.h"

#define FALSE 0
#define TRUE 1

int is_valid_email(const char *email)
{
    int at_index = strchr(email, '@') - email;
    int dot_index = strrchr(email, '.') - email;

    if (!at_index || !dot_index || at_index >= dot_index)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}