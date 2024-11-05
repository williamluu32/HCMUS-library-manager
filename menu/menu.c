#include "menu.h"
#include "../patron/patron.h"
#include "../utils/format.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void input_menu()
{
    int opt = 0;
    int should_exit = 0;
    do
    {
        main_menu();
        printf("\nSelect an option: ");
        if (scanf("%d", &opt) != 1 || opt < 0 || opt > 5)
        {

            puts("\n(!) Invalid option. Please re-enter a number between 0 and 5.");
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
        case 0:
        {
            puts("\nSee you next time <3");
            should_exit = 1;
            break;
        }
        }
    } while (!should_exit);
}

static void main_menu()
{
    system("cls");
    puts(HORIZONTAL_LINE);
    puts("\t1. Patron Management");
    puts("\t2. Book Management");
    puts("\t3. Book Loan");
    puts("\t4. Book Return");
    puts("\t5. Statistics");
    puts("\t0. Exit");
    puts(HORIZONTAL_LINE);
}

static void patron_menu()
{
    system("cls");
    puts(HORIZONTAL_LINE);
    puts("\t1. View Patrons");
    puts("\t2. Add New Patron");
    puts("\t3. Update Patron");
    puts("\t4. Delete Patron");
    puts("\t5. Find Patron by Citizen ID");
    puts("\t6. Find Books Borrowed by Full Name");
    puts("\t0. Return");
    puts(HORIZONTAL_LINE);
}

static void input_patron_menu()
{
    int opt = 0;
    int should_exit = 0;

    do
    {
        patron_menu();
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
        case 0:
        {
            input_menu();
            should_exit = 1;
            break;
        }
        }
    } while (!should_exit);
}
