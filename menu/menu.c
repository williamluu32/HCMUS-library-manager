#include "menu.h"
#include "../patron/patron.h"
#include "../book/book.h"
#include "../borrowing/borrowing.h"
#include "../util/format.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MIN_OPTION_MAIN_MENU 0
#define MAX_OPTION_MAIN_MENU 5
#define MIN_OPTION_PATRON_MENU 0
#define MAX_OPTION_PATRON_MENU 6

static void main_menu()
{
    system("cls");
    puts(HORIZONTAL_LINE);
    puts("\n\t1. Patrons");
    puts("\t2. Cataloging");
    puts("\t3. Checkout");
    puts("\t4. Checkin");
    puts("\t5. Statistics");
    puts("\t0. Exit");
    puts(HORIZONTAL_LINE);
}

static void patron_menu()
{
    system("cls");
    puts(HORIZONTAL_LINE);
    puts("\n\t1. View Patrons");
    puts("\t2. Add New Patron");
    puts("\t3. Update Patron");
    puts("\t4. Delete Patron");
    puts("\t5. Find Patron by Citizen ID");
    puts("\t6. Find Patrons by Full Name");
    puts("\t0. Return");
    puts(HORIZONTAL_LINE);
}

void input_patron_menu()
{
    int opt = 0;
    int should_exit = 0;

    do
    {
        patron_menu();
        printf("\nSelect an option: ");
        if (scanf("%d", &opt) != 1 || opt < 0 || opt > 6)
        {
            printf("\n(!) Invalid option. Please re-enter a number between %d and %d.", MIN_OPTION_PATRON_MENU, MAX_OPTION_PATRON_MENU);

            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            _flushall();
            continue;
        }

        switch (opt)
        {
        case 1:
        {
            output_patrons();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 2:
        {
            input_patrons();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 3:
        {
            update_patron();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 4:
        {
            delete_patron();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 5:
        {
            find_patron_by_citizen_id();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 6:
        {
            find_patrons_by_full_name();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 0:
        {
            input_menu();
            should_exit = 1;
            break;
        }
        }
    } while (!should_exit);
}

static void cataloging_menu()
{
    system("cls");
    puts(HORIZONTAL_LINE);
    puts("\n\t1. View Books");
    puts("\t2. Add New Book");
    puts("\t3. Update Book");
    puts("\t4. Remove Book");
    puts("\t5. Find Book by ISBN");
    puts("\t6. Find Books by Name");
    puts("\t0. Return");
    puts(HORIZONTAL_LINE);
}

static void input_cataloging_menu()
{
    int opt = 0;
    int should_exit = 0;

    do
    {
        cataloging_menu();
        printf("\nSelect an option: ");
        if (scanf("%d", &opt) != 1 || opt < 0 || opt > 6)
        {

            puts("\n(!) Invalid option. Please re-enter a number between 0 and 6.");
            _flushall();
            continue;
        }

        switch (opt)
        {
        case 1:
        {
            output_books();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 2:
        {
            input_books();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 3:
        {
            update_book();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 4:
        {
            remove_book();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 5:
        {
            find_book_by_isbn();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 6:
        {
            find_book_by_title();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 0:
        {
            input_menu();
            should_exit = 1;
            break;
        }
        }
    } while (!should_exit);
}

static void checkout_menu()
{
    system("cls");
    puts(HORIZONTAL_LINE);
    puts("\n\t1. View Borrowing Slips");
    puts("\t2. Add New Borrowing Slip");
    puts("\t0. Return");
    puts(HORIZONTAL_LINE);
}

static void input_checkout_menu()
{
    int opt = 0;
    int should_exit = 0;

    do
    {
        checkout_menu();
        printf("\nSelect an option: ");
        if (scanf("%d", &opt) != 1 || opt < 0 || opt > 6)
        {

            puts("\n(!) Invalid option. Please re-enter a number between 0 and 2.");
            _flushall();
            continue;
        }

        switch (opt)
        {
        case 1:
        {
            // output_borrowing_slip();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }
        case 2:
        {
            // input_borrowing_slip();
            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            break;
        }

        case 0:
        {
            input_menu();
            should_exit = 1;
            break;
        }
        }
    } while (!should_exit);
}

//
void input_menu()
{
    int opt = 0;
    int should_exit = 0;

    do
    {
        main_menu(); // Hiển thị main menu

        // Chọn option trong main menu
        printf("\nSelect an option: ");
        if (scanf("%d", &opt) != 1 || opt < MIN_OPTION_MAIN_MENU || opt > MAX_OPTION_MAIN_MENU)
        {
            printf("\n(!) Invalid option. Please re-enter a number between %d and %d.", MIN_OPTION_MAIN_MENU, MAX_OPTION_MAIN_MENU);

            puts("\n\n\n\n\nPress any key to continue...");
            getch();
            _flushall();
            continue;
        }

        switch (opt)
        {
        case 1:
        {
            input_patron_menu();
            should_exit = 1;
            break;
        }
        case 2:
        {
            input_cataloging_menu();
            should_exit = 1;
            break;
        }
        case 3:
        {
            input_checkout_menu();
            should_exit = 1;
            break;
        }

        case 0:
        {
            puts("\nExiting program. See you next time <3");
            should_exit = 1;
            break;
        }
        }
    } while (!should_exit);
}
