#include "date.h"
#include "../../../include/constants/system_const.h"

int is_leap(int year)
{
    if (year % 4 == 0)
        return TRUE;
    else
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return TRUE;
            else
                return FALSE;
        }
        else
            return FALSE;
    }
}

int get_days_of_month(const Date *d)
{

    return 0;
}

int is_valid_date(const Date *d)
{
    // valid year
    // valid month
    // valid date by dateofmonth
    return 0;
}