#ifndef PROFILE_H
#define PROFILE_H

#include "../../include/constants/profile_const.h"
#include "../../include/enumerations/sex.h"
#include "../utils/date/date.h"

struct _Profile
{
    char full_name[FULL_NAME_SIZE + 1];
    char citizen_id[CITIZEN_ID_SIZE + 1];
    char email[EMAIL_SIZE + 1];
    char address[ADDRESS_SIZE + 1];
    Sex sex;
    Date dob;
};

typedef struct _Profile Profile;

#endif // PROFILE_H