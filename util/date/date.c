#include "date.h"
#include <stdio.h>

#define MIN_YEAR 1900
#define MAX_YEAR 10000
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_DAY 1
#define MAX_DAY 31
#define INVALID -1
#define FALSE 0
#define TRUE 1

/*
    Kiểm tra xem một năm có phải là năm nhuận hay không
*/
static int is_leap_year(int year)
{
    int res;
    if (year < MIN_YEAR || year > MAX_YEAR)
        res = INVALID;
    else if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        res = TRUE;
    else
        res = FALSE;
    return res;
}

/*
    Trả về số ngày của một tháng trong năm
*/
static int get_days_in_month(int month, int year)
{
    int n_days;
    int is_leap = is_leap_year(year);

    if (is_leap == INVALID || month < MIN_MONTH || month > MAX_MONTH)
    {
        n_days = -1;
    }
    else
    {
        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        {
            n_days = 31;
            break;
        }
        case 4:
        case 6:
        case 9:
        case 11:
        {
            n_days = 30;
            break;
        }
        default:
        {
            if (is_leap)
                n_days = 29;
            else
                n_days = 28;
        }
        }
    }

    return n_days;
}

int is_valid_date(int day, int month, int year)
{
    int res;
    int n_days = get_days_in_month(month, year);

    if (year < MIN_YEAR || year > MAX_YEAR)
        return FALSE;
    else if (day < MIN_DAY || day > n_days)
        return FALSE;
    else
        return TRUE;
}