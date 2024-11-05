#include "patron.h"
#include "../utils/format.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATRONS 20000
#define CARD_NUMBER_SIZE 20
#define FULL_NAME_SIZE 50
#define CITIZEN_ID_SIZE 12
#define EMAIL_ADDRESS_SIZE 320
#define PHYSICAL_ADDRESS_SIZE 100
#define MALE 0
#define FEMALE 1

static char card_numbers[MAX_PATRONS][CARD_NUMBER_SIZE + 1];
static char full_names[MAX_PATRONS][FULL_NAME_SIZE + 1];
static char citizen_ids[MAX_PATRONS][CITIZEN_ID_SIZE + 1];
static char email_addresses[MAX_PATRONS][EMAIL_ADDRESS_SIZE + 1];
static char physical_addresses[MAX_PATRONS][PHYSICAL_ADDRESS_SIZE + 1];
static unsigned int sexes[MAX_PATRONS];
static unsigned int dobs[MAX_PATRONS]; // Date of Birth
static unsigned int dois[MAX_PATRONS]; // Date of Issuance
static unsigned int exps[MAX_PATRONS]; // Expired Date

static unsigned int total_patrons = 0;

static void input_card_number(int i)
{
    printf("\t- Patron ID: ");
    _flushall();
    if (fgets(card_numbers[total_patrons + i], CARD_NUMBER_SIZE + 1, stdin) == NULL)
    {
        puts("Something was wrong");
    }
    else
    {
        card_numbers[total_patrons + i][strcspn(card_numbers[total_patrons + i], "\n")] = 0;
    }
}
static void input_full_name(int i)
{
    printf("\t- Full name: ");
    _flushall();
    if (fgets(full_names[total_patrons + i], FULL_NAME_SIZE + 1, stdin) == NULL)
    {
        puts("Something was wrong.");
    }
    else
    {
        full_names[total_patrons + i][strcspn(full_names[total_patrons + i], "\n")] = 0;
    }
}
static void input_dob(int i)
{
    unsigned int dd = 0;
    unsigned int mm = 0;
    unsigned int yyyy = 0;

    printf("\t- Date of birth (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &dd, &mm, &yyyy);
    dobs[total_patrons + i] |= dd & 0xff;             // Byte 4 (LSB)
    dobs[total_patrons + i] |= (mm & 0xff) << 8;      // Byte 3
    dobs[total_patrons + i] |= (yyyy & 0xffff) << 16; // Byte 1 (MSB) + Byte 2
}
static void input_sex(int i)
{
    printf("\t- Sex (0 for male, 1 for female): ");
    scanf("%d", &sexes[total_patrons + i]);
}
static void input_email_address(int i)
{
    _flushall();
    printf("\t- Email: ");
    scanf("%s", email_addresses[total_patrons + i]);
}
static void input_physical_address(int i)
{
    _flushall();
    printf("\t- Address: ");
    scanf("%s", &physical_addresses[total_patrons + i]);
}
static void input_citizen_id(int i)
{
    _flushall();
    printf("\t- Citizen ID: ");
    scanf("%s", &citizen_ids[total_patrons + i]);
}
static char *output_sex(int i)
{
    char *sex;

    switch (i)
    {
    case MALE:
    {
        sex = "Male";
        break;
    }
    case FEMALE:
    {
        sex = "Female";
        break;
    }
    default:
    {
        sex = "Invalid sex";
        break;
    }
    }
    return sex;
}
static char *output_dob(int i)
{
    int dd = 0;
    int mm = 0;
    int yyyy = 0;
    dd = (dobs[i] & 0xff);
    mm = (dobs[i] >> 8) & 0xff;
    yyyy = (dobs[i] >> 16 & 0xffff);
    char *dob = (char *)malloc(20);
    sprintf(dob, "%d/%d/%d", dd, mm, yyyy);
    return dob;
}
static void output_patrons_format()
{
    puts(HORIZONTAL_LINE);
    printf("%-25s%-25s%-25s%-25s%-25s%-25s%-25s\n", "Card Number", "Citizen ID", "Full Name", "DOB", "Sex", "Email", "Address");
    printf("%-25s%-25s%-25s%-25s%-25s%-25s%-25s\n", HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN);
}
static void output_patrons_data()
{
    for (int i = 0; i < total_patrons; i++)
    {
        printf("%-25s%-25s%-25s%-25s%-25s%-25s%-25s\n", card_numbers[i], citizen_ids[i], full_names[i], output_dob(i), output_sex(i), email_addresses[i], physical_addresses[i]);
    }
}

/////////////////////////////////////////////////////////////
void input_patrons()
{
    int number_of_patrons = 0;

    while (1)
    {
        puts(HORIZONTAL_LINE);
        printf("Enter the number of patrons: ");

        if (scanf("%d", &number_of_patrons) != 1 || total_patrons + number_of_patrons < 0 || total_patrons + number_of_patrons > MAX_PATRONS)
        {
            puts("Invalid input. Please enter a positive number of students");
        }
        else
            break;
    }

    for (int i = 0; i < number_of_patrons; i++)
    {
        printf("\t[PATRON %d]\n", i + 1);

        input_card_number(i);
        input_full_name(i);
        input_dob(i);
        input_sex(i);
        input_email_address(i);
        input_physical_address(i);
        input_citizen_id(i);
    }

    total_patrons += number_of_patrons;
}

void output_patrons()
{
    output_patrons_format();
    output_patrons_data();
}
