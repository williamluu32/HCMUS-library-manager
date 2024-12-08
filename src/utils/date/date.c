#include "date.h"
#include "../../../include/constants/system_const.h"
#include "../../../include/constants/time_const.h"

//////////////////////////////////////////////////////////////////////////////////
/**
 * Xác định xem năm đã cho có phải hợp lệ hay không
 *
 * @param year năm
 * @return 1 nếu đó là năm hợp lệ, ngược lại trả về 0
 */
static int is_valid_year(int year)
{
    return year >= MIN_YEAR && year < MAX_YEAR;
}

/**
 * Xác định xem tháng đã cho có phải hợp lệ hay không
 *
 * @param month tháng
 * @return 1 nếu đó là tháng hợp lệ, ngược lại trả về 0
 */
static int is_valid_month(int month)
{
    return month >= MIN_MONTH && month <= MAX_MONTH;
}

/**
 * Xác định xem năm đã cho có phải năm nhuận không
 *
 * @param year năm
 * @return 1 nếu đó là năm nhuận, ngược lại trả về 0
 */
static int is_leap(int year)
{
    if (!is_valid_year(year))
        return FALSE;

    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * Xác định số ngày của tháng-năm đã cho
 *
 * @param month tháng
 * @param year năm
 * @return số ngày của tháng, hoặc -1 nếu tháng hoặc năm không hợp lệ
 */
static int get_days_of_month(int month, int year)
{
    if (!is_valid_month(month) || !is_valid_year(year))
        return INVALID;

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
    {
        return is_leap(year) ? 29 : 28;
    }
    }
}

/////////////////////////////////////////////////////////
int is_valid_date(const Date *d)
{
    if (!is_valid_month(d->month) || !is_valid_year(d->year))
        return FALSE;

    if (d->day < MIN_DAY || d->day > get_days_of_month(d->month, d->year))
        return FALSE;

    return TRUE;
}