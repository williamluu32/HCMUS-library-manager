#include <stdio.h>
#include <string.h>

#include "borrowing.h"
#include "../util/my_string.h"
#include "../util/format.h"
#include "../patron/patron.h"

#define MAX_SIZE 5000
#define ID_SIZE 20
#define CARD_NUMBER_SIZE 20
#define TITLE_SIZE 100
#define ISBN_SIZE 13
#define FALSE 0
#define TRUE 1

static char ids[MAX_SIZE][ID_SIZE + 1];
static char card_numbers[MAX_SIZE][CARD_NUMBER_SIZE + 1];
static char isbns[MAX_SIZE][ISBN_SIZE + 1]; // chuỗi các isbn phân cách bằng comma
static int borrowing_dates[MAX_SIZE];
static int expected_due_dates[MAX_SIZE];
static int total_books[MAX_SIZE];
static int total = 0;

// int get_total_borrowing_slips()
// {
//     return total;
// }

// void input_borrowing_slip()
// {
//     printf("\nTotal %d", total);
//     puts("\n\tBORROWING SLIP");
//     char card_number[CARD_NUMBER_SIZE + 1];

//     // id
//     sprintf(ids[total], "PM%d", total + 1);
//     printf("\t- ID: %s", ids[total]);

//     // card_number > phải có record mới cho phép
//     printf("\n\t- Card Number: ");
//     _flushall();
//     fgets(card_number, CARD_NUMBER_SIZE + 1, stdin);
//     remove_trailing_newline(card_number);
//     if (!is_patron_exists_by_card_number(card_number))
//     {
//         puts("Patron is not found.");
//     }
//     else
//     {
//         printf("WTF !!!");
//         printf("\n%s", card_number);

//         strcpy(card_numbers[total], card_number);
//         total++;
//     }

//     printf("card_numbers: %s", card_numbers[0]);
//     //
// }
// void output_borrowing_slip()
// {
//     puts("hello borrowing");
// }