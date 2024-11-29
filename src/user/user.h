#ifndef USER_H
#define USER_H

#include "../../include/constants/user_const.h"
#include "../../include/enumerations/user_status.h"
#include "../../include/enumerations/user_type.h"
#include "../profile/profile.h"

struct _User
{
    char user_name[MAX_USERNAME_SIZE + 1];
    char password[MAX_PASSWORD_SIZE + 1];
    UserStatus status;
    UserType type;
    Profile profile;
};
typedef struct _User User;

#endif // USER_H
