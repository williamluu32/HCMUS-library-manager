#include <string.h>
#include <ctype.h>

#include "email.h"
#include "../string/string.h"
#include "../../../include/constants/system_const.h"

////////////////////////////////////////////////////////
int is_valid_email(const char *email)
{
    if (!email || is_empty_string(email))
        return FALSE;

    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');

    if (!at || !dot || at == dot || *(dot + 1) == '\0')
        return FALSE;

    int at_index = at - email;
    int dot_index = dot - email;

    if (!at_index || !dot_index || at_index >= dot_index)
        return FALSE;

    for (int i = 0; i < at_index; i++)
    {
        if (!(isalnum(email[i]) || email[i] == '_' || email[i] == '-'))
        {
            return FALSE;
        }
    }

    for (int i = at_index + 1; i < dot_index; i++)
    {
        if (!(isalnum(email[i]) || email[i] == '-'))
        {
            return FALSE;
        }
    }

    for (int i = dot_index + 1; i < strlen(email); i++)
    {
        if (!isalnum(email[i]))
        {
            return FALSE;
        }
    }

    return TRUE;
}