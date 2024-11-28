#ifndef STRING_H
#define STRING_H

/**
 * Xóa ký tự xuống dòng ('\n') ở cuối chuỗi ký tự.
 *
 * @param str chuỗi cần xử lý
 * @example xóa ký tự xuống dòng được tự động thêm vào cuối chuỗi sau khi đọc một dòng từ bàn phím bằng hàm fgets()
 */
void remove_trailing_newline(char *str);

/**
 * Xác định xem có phải là chuỗi rỗng không
 *
 * @param str chuỗi cần kiểm tra
 * @return 1 nếu chuỗi rỗng, ngược lại trả về 0
 */
int is_empty_string(const char *str);

#endif // STRING_H
