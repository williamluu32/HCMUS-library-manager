#include <stdio.h>
#include <string.h>

#include "book.h"
#include "../util/format.h"
#include "../util/my_string.h"

#define MAX_BOOKS 5000
#define ISBN_SIZE 13
#define TITLE_SIZE 100
#define AUTHORS_SIZE 1000
#define PUBLISHER_SIZE 100
#define SUBJECT_TERMS_SIZE 1000
#define FALSE 0
#define TRUE 1
#define SHOULD_CONTINUE 1
#define MIN_YEAR 1900
#define EQUALS 0

static char isbns[MAX_BOOKS][ISBN_SIZE + 1];
static char titles[MAX_BOOKS][TITLE_SIZE + 1];
static char authors[MAX_BOOKS][AUTHORS_SIZE + 1];
static char publishers[MAX_BOOKS][PUBLISHER_SIZE + 1];
static char sub_terms[MAX_BOOKS][SUBJECT_TERMS_SIZE + 1]; // subject terms
static int pub_dates[MAX_BOOKS];                          // publication date
static int quantities[MAX_BOOKS];                         // quantity
static long prices[MAX_BOOKS];
static int total_books = 0;

static int find_book_index_by_isbn(const char *isbn)
{
    for (int i = 0; i < total_books; i++)
    {
        if (strcmp(isbns[i], isbn) == 0)
        {
            return i;
        }
    }
    return -1;
}

//
void input_books()
{
    int number_of_books = 0;

    while (SHOULD_CONTINUE)
    {
        puts(HORIZONTAL_LINE);
        printf("Enter the number of books: ");
        if (scanf("%d", &number_of_books) != 1 || number_of_books <= 0 || total_books + number_of_books > MAX_BOOKS)
        {
            puts("Invalid input. Please enter a positive number of books");
            break;
        }
        else
            break;
    }

    for (int i = 0; i < number_of_books; i++)
    {
        printf("\t[BOOK %d]\n", i + 1);

        printf("\t- ISBN: ");
        _flushall();
        if (fgets(isbns[total_books + i], ISBN_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
            break;
        }
        else
        {
            remove_trailing_newline(isbns[total_books + i]);
        }

        printf("\t- Title: ");
        _flushall();
        if (fgets(titles[total_books + i], TITLE_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
            break;
        }
        else
        {
            remove_trailing_newline(titles[total_books + i]);
        }

        printf("\t- Authors: ");
        _flushall();
        if (fgets(authors[total_books + i], AUTHORS_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
            break;
        }
        else
        {
            remove_trailing_newline(authors[total_books + i]);
        }

        printf("\t- Publisher: ");
        _flushall();
        if (fgets(publishers[total_books + i], PUBLISHER_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
            break;
        }
        else
        {
            remove_trailing_newline(publishers[total_books + i]);
        }

        printf("\t- Subject terms: ");
        _flushall();
        if (fgets(sub_terms[total_books + i], SUBJECT_TERMS_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
            break;
        }
        else
        {
            remove_trailing_newline(sub_terms[total_books + i]);
        }

        printf("\t- Publication year (yyyy): ");
        scanf("%d", &pub_dates[i]);
        printf("\t- Quantity: ");
        scanf("%u", &quantities[i]);
        printf("\t- Price: ");
        scanf("%u", &prices[i]);
    }

    total_books += number_of_books;
}
void output_books()
{
    puts(HORIZONTAL_LINE);
    printf("\t%-17s%-17s%-17s%-17s%-20s%-25s%-17s%-17s\n", "ISBN", "Title", "Authors", "Publisher", "Subject Terms", "Publication date", "Price", "Quantity");
    _flushall();
    printf("\t%-17s%-17s%-17s%-17s%-20s%-25s%-17s%-17s\n", HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN);

    for (int i = 0; i < total_books; i++)
    {
        printf("\t%-17s%-17s%-17s%-17s%-20s%-25d%-17d%-17d\n", isbns[i], titles[i], authors[i], publishers[i], sub_terms[i], pub_dates[i], prices[i], quantities[i]);
    }
}
void update_book()
{
    char isbn[ISBN_SIZE + 1];
    printf("\nEnter ISBN: ");
    _flushall();
    fgets(isbn, ISBN_SIZE + 1, stdin);
    remove_trailing_newline(isbn);
    int k = find_book_index_by_isbn(isbn);

    if (k == -1)
    {
        printf("Book is not found");
        return;
    }
    else
    {
        printf("\t- ISBN: ");
        _flushall();
        if (fgets(isbns[k], ISBN_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
        }
        else
        {
            remove_trailing_newline(isbns[k]);
        }

        printf("\t- Title: ");
        _flushall();
        if (fgets(titles[k], TITLE_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
        }
        else
        {
            remove_trailing_newline(titles[k]);
        }

        printf("\t- Authors: ");
        _flushall();
        if (fgets(authors[k], AUTHORS_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
        }
        else
        {
            remove_trailing_newline(authors[k]);
        }

        printf("\t- Publisher: ");
        _flushall();
        if (fgets(publishers[k], PUBLISHER_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
        }
        else
        {
            remove_trailing_newline(publishers[k]);
        }

        printf("\t- Subject terms: ");
        _flushall();
        if (fgets(sub_terms[k], SUBJECT_TERMS_SIZE + 1, stdin) == NULL)
        {
            puts("Something was wrong");
        }
        else
        {
            remove_trailing_newline(sub_terms[k]);
        }

        printf("\t- Publication year (yyyy): ");
        scanf("%d", &pub_dates[k]);
        printf("\t- Quantity: ");
        scanf("%u", &quantities[k]);
        printf("\t- Price: ");
        scanf("%u", &prices[k]);

        //
        printf("\nUpdate boook information successfully!");
    }
}
void remove_book()
{
    char isbn[ISBN_SIZE + 1];
    printf("\nEnter ISBN: ");
    _flushall();
    fgets(isbn, ISBN_SIZE + 1, stdin);
    remove_trailing_newline(isbn);
    int k = find_book_index_by_isbn(isbn);

    if (k == -1)
    {
        printf("Book is not found");
        return;
    }
    else
    {
        strcpy(isbns[k], isbns[total_books - 1]);
        strcpy(authors[k], authors[total_books - 1]);
        strcpy(titles[k], titles[total_books - 1]);
        strcpy(publishers[k], publishers[total_books - 1]);
        strcpy(sub_terms[k], sub_terms[total_books - 1]);
        pub_dates[k] = pub_dates[total_books - 1];
        prices[k] = prices[total_books - 1];
        quantities[k] = quantities[total_books - 1];

        printf("\nRemove book successfully!");
    }

    total_books--;
}
void find_book_by_isbn()
{
    char isbn[ISBN_SIZE + 1];
    printf("\nEnter ISBN: ");
    _flushall();
    fgets(isbn, ISBN_SIZE + 1, stdin);
    remove_trailing_newline(isbn);

    for (int i = 0; i < total_books; i++)
    {
        if (strcmp(isbns[i], isbn) == EQUALS)
        {
            puts(HORIZONTAL_LINE);
            puts("\n\tBOOK INFORMATION");
            printf("\t> ISBN: %s", isbns[i]);
            printf("\n\t> Title: %s", titles[i]);
            printf("\n\t> Authors: %s", authors[i]);
            printf("\n\t> Publisher: %s", publishers[i]);
            printf("\n\t> Subject Terms: %s", sub_terms[i]);
            printf("\n\t> Publication Date: %d", pub_dates[i]);
            printf("\n\t> Price: %d", prices[i]);
            printf("\n\t> Quantity: %d", quantities[i]);
            return;
        }
    }
    puts("\nBook is not found.");
}
void find_book_by_title()
{
    char title[TITLE_SIZE + 1];
    printf("\nEnter title: ");
    _flushall();
    fgets(title, TITLE_SIZE + 1, stdin);
    remove_trailing_newline(title);

    for (int i = 0; i < total_books; i++)
    {
        if (strcmp(titles[i], title) == EQUALS)
        {
            puts(HORIZONTAL_LINE);
            puts("\n\tBOOK INFORMATION");
            printf("\t> ISBN: %s", isbns[i]);
            printf("\n\t> Title: %s", titles[i]);
            printf("\n\t> Authors: %s", authors[i]);
            printf("\n\t> Publisher: %s", publishers[i]);
            printf("\n\t> Subject Terms: %s", sub_terms[i]);
            printf("\n\t> Publication Date: %d", pub_dates[i]);
            printf("\n\t> Price: %d", prices[i]);
            printf("\n\t> Quantity: %d", quantities[i]);
            return;
        }
    }

    puts("\nBook is not found.");
}
int get_total_books()
{
    return total_books;
}
int count_books_by_title(const char *title)
{
    int counter = 0;
    for (int i = 0; i < total_books; i++)
    {
        if (strcmp(titles[i], title) == EQUALS)
        {
            counter++;
        }
    }
    return counter;
}