#include "menu.h"
#include "../patron/patron.h"
#include <stdio.h>

void Menu()
{
    MenuInput();
}

static void MenuDetails()
{
    puts("\n-------------------------------------------------------------------------------------------");
    puts("--------------------------- HCMUS Library Manager ---------------------------");
    puts("\t(1) Show patrons");
    puts("\t(2) Add a patron");
    puts("\t(0) Exit");
}

static void MenuInput()
{
    int opt = 0;
    int shouldExit = 0;

    do
    {
        MenuDetails();
        printf("\nSelect an option: ");

        if (scanf("%d", &opt) != 1)
        {
            puts("\n(!) Invalid option. Please re-enter a number between 0 and 2.");
            _flushall();
            continue;
        }
        if (opt < 0 || opt > 2)
        {
            puts("\n(!) Invalid option. Please re-enter a number between 0 and 2.");
            continue;
        }

        switch (opt)
        {
        case 1:
        {
            InputPatrons();
            puts("\n(?) Continue?");
            break;
        }

        case 2:
        {
            OutputPatrons();
            puts("\n(?) Continue?");
            break;
        }

        case 0:
        {
            puts("\nSee you next time <3");
            shouldExit = 1;
            break;
        }
        };

    } while (!shouldExit);
}
