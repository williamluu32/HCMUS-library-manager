#ifndef MY_STRING_H
#define MY_STRING_H

/*
Khi dùng fgets() để nhập chuỗi ký tự, nó sẽ đọc ký tự đến khi gặp ký tự xuống dòng (\n) hoặc ký tự EOF thì dừng lại. Nên chuỗi vừa đọc được sẽ bao gồm cả ký tự xuống dòng ở cuối chuỗi.
Hàm này dùng để xóa ký tự xuống dòng ở cuối chuỗi ký tự.
*/
void remove_trailing_newline(char *str);

#endif // MY_STRING_H
