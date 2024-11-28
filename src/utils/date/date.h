/**
 * Định nghĩa cấu trúc và các hàm xử lý liên quan tới ngày-tháng-năm (date)
 *
 * @author William Luu <24810019@student.hcmus.edu.vn>
 * @date 2024-11-28
 */

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
/**
 * Xác định xem một ngày-tháng-năm có hợp lệ không
 *
 * @param day ngày
 * @param month tháng
 * @param year năm
 * @return 1 nếu ngày hợp lệ, ngược lại trả về 0
 */
int is_valid_date(const Date *d);
#endif // DATE_H