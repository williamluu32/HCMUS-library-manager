#ifndef EMAIL_H
#define EMAIL_H

/**
 * Kiểm tra cơ bản có phải là một email hợp lệ hay không
 *
 * @param email địa chỉ email cần kiểm tra
 * @return 1 nếu địa chỉ email hợp lệ, 0 thì ngược lại
 */
int is_valid_email(const char *email);

#endif // EMAIL_H