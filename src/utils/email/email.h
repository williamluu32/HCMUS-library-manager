#ifndef EMAIL_H
#define EMAIL_H

/**
 * Xác định xem có phải là email hợp lệ không
 *
 * @param email địa chỉ email cần kiểm tra
 * @return 1 nếu địa chỉ email hợp lệ, ngược lại trả về 0
 */
int is_valid_email(const char *email);

#endif // EMAIL_H