#ifndef PATRON_H
#define PATRON_H

/*
    Nhập các thông tin độc giả mới
*/
void input_patrons();

/*
    Xem thông tin chi tiết của các độc giả
*/
void output_patrons();

/*
    Cập thông tin chi tiết của các độc giả
*/
void update_patron();

/*
    Cập thông tin chi tiết của các độc giả
*/
void delete_patron();

/*
    Tìm kiếm độc giả bằng CMND/CCCD
*/
void find_patron_by_citizen_id();

/*
    Tìm kiếm độc giả bằng CMND/CCCD
*/
void find_patrons_by_full_name();

/*
    Trả về tổng số độc giả hiện có
*/
int get_total_patrons();

/*
    Trả về tổng số độc giả hiện có theo giới tính
*/
int count_patrons_by_sex(int sex);

#endif // PATRON_H