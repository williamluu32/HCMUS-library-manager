#ifndef BOOK_H
#define BOOK_H

void input_books();
void output_books();
void update_book();
void remove_book();
void find_book_by_isbn();
void find_book_by_title();
int get_total_books();
int count_books_by_title(const char *title);

#endif // BOOK_H