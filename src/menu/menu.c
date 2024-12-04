#include <stdio.h>
#include <stdlib.h>

#include "./menu.h"
#include "../utils/format/format.h"
#include "../../include/constants/system_const.h"

static void greeting_menu()
{
    system("cls");
    puts("\n\n\n\t\t\t\t\t\t********* CHUONG TRINH QUAN LY THU VIEN *********");
    puts("\n\t1. Dang nhap");
    puts("\n\t0. Thoat chuong trinh");
}

void handle_greeting_menu()
{
    int opt = 0;

    do
    {
        greeting_menu();
        puts(HORIZONTAL_LINE);

        printf("\n>>> Chon chuc nang: ");
        if (scanf("%d", &opt) != 1 || opt < 0 || opt > 1)
        {
            printf("\n(!) Invalid option. Please re-enter a number between %d and %d.", 0, 1);
            continue;
        }

        switch (opt)
        {
        case 1:
        {
            // login
            break;
        }
        case 0:
        {
            system("cls");
            puts("\n\n\n>>> Da thoat chuong trinh. Hen gap lai <3");
            return;
        }
        default:
            printf("\n(!) Invalid option. Please re-enter a number between %d and %d.", 0, 1);
        }
    } while (TRUE);
}
