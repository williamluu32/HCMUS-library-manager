#ifndef DATE_H
#define DATE_H

struct _Date
{
    int day;
    int month;
    int year;
};
typedef struct _Date Date;

////////////////////////////////////////////////////////////////////
int is_leap(int year);
int get_days_of_month(const Date *d);
int is_valid_date(const Date *d);

#endif // DATE_H