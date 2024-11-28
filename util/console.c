#include <conio.h>
#include <stdio.h>

#include "console.h"

void pause()
{
    puts("\n\n\n\n\nPress any key to continue...");
    getch();
    _flushall();
}

void clear_line()
{
    printf("\033[F");
    printf("\r");
    printf("\33[K");
}
