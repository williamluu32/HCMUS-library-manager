#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "patron.h"
#include "../util/format.h"
#include "../util/my_string.h"
#include "../util/console.h"
#include "../util/date/date.h"
#include "../util/email/email.h"
#include "../menu/menu.h"

#define MAX_PATRONS 20000
#define CARD_NUMBER_SIZE 20
#define STUDENT_ID_SIZE 20
#define FULL_NAME_SIZE 50
#define CITIZEN_ID_SIZE 12
#define EMAIL_SIZE 320
#define ADDRESS_SIZE 100
#define UNDERGRADUATE 0
#define GRADUATE 1
#define UNDERGRADUATE_PREFIX 12000
#define GRADUATE_PREFIX 120003
#define MALE 0
#define FEMALE 1
#define FALSE 0
#define TRUE 1
#define EQUALS 0
#define SUCCESS 1

static char card_numbers[MAX_PATRONS][CARD_NUMBER_SIZE + 1]; // Mã thẻ
static char student_ids[MAX_PATRONS][STUDENT_ID_SIZE + 1];   // Mã sinh viên/học viên
static char full_names[MAX_PATRONS][FULL_NAME_SIZE + 1];     // Họ và tên
static char citizen_ids[MAX_PATRONS][CITIZEN_ID_SIZE + 1];   // CMND/CCCD
static char emails[MAX_PATRONS][EMAIL_SIZE + 1];             // Email
static char addresses[MAX_PATRONS][ADDRESS_SIZE + 1];        // Địa chỉ
static int sexes[MAX_PATRONS];                               // Giới tính
static int dobs[MAX_PATRONS];                                // Ngày sinh
static int categories[MAX_PATRONS];                          // Loại độc giả

static int total_patrons = 0; // Tổng số độc giả hiện có

/*
    Nhập loại độc giả.
    Có 2 loại độc giả:
    1. Sinh viên
    2. Học viên cao học
*/
static void input_category(int i)
{
    int category;

    while (TRUE)
    {
        printf("\t- Category (Undergraduate student for 0 - Graduate student for 1): ");

        if (scanf("%d", &category) != 1 || (category != UNDERGRADUATE && category != GRADUATE))
        {
            puts("\n(!) Invalid input. Please enter 0 for undergraduate student or 1 for graduate student.\n");
            _flushall();
        }
        else
            break;
    }

    categories[total_patrons + i] = category;
}

/*
    Nhập mã sinh viên/học viên cao học của độc giả
*/
static void input_student_id(int i)
{
    char student_id[STUDENT_ID_SIZE + 1];

    while (TRUE)
    {
        printf("\t- Student ID: ");
        _flushall();

        if (fgets(student_id, STUDENT_ID_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(student_id);
            strcpy(student_ids[total_patrons + i], student_id);
            break;
        }
    }
}

/*
    Tự sinh mã thẻ từ loại và mã sinh viên/học viên học của độc giả
*/
static void input_card_number(int i)
{
    if (categories[total_patrons + i] == UNDERGRADUATE)
    {
        sprintf(card_numbers[total_patrons + i], "%d%s", UNDERGRADUATE_PREFIX, student_ids[total_patrons + i]);
    }
    else
    {
        sprintf(card_numbers[total_patrons + i], "%d%s", GRADUATE_PREFIX, student_ids[total_patrons + i]);
    }
}

/*
    Nhập họ tên của độc giả
*/
static void input_full_name(int i)
{
    char full_name[FULL_NAME_SIZE + 1];

    while (TRUE)
    {
        printf("\t- Full name: ");
        _flushall();

        if (fgets(full_name, FULL_NAME_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(full_name);
            strcpy(full_names[total_patrons + i], full_name);
            break;
        }
    }
}

/*
    Nhập giới tính của độc giả
*/
static void input_sex(int i)
{
    int sex;

    while (TRUE)
    {
        printf("\t- Sex (Male for 0 - Female for 1): ");

        if (scanf("%d", &sex) != 1 || (sex != MALE && sex != FEMALE))
        {
            puts("\n(!) Invalid input. Please enter 0 for male or 1 for female.\n");
            _flushall();
        }
        else
            break;
    }

    sexes[total_patrons + i] = sex;
}

/*
    Nhập CMND/CCCD của độc giả
*/
static void input_citizen_id(int i)
{
    char citizen_id[CITIZEN_ID_SIZE + 1];

    while (TRUE)
    {
        printf("\t- Citizen ID: ");
        _flushall();

        if (fgets(citizen_id, CITIZEN_ID_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(citizen_id);
            strcpy(citizen_ids[total_patrons + i], citizen_id);
            break;
        }
    }
}

/*
    Nhập địa chỉ email của độc giả
*/
static void input_email(int i)
{
    char email[EMAIL_SIZE + 1];

    while (TRUE)
    {
        printf("\t- Email: ");
        _flushall();

        if (fgets(email, EMAIL_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else if (!is_valid_email(email))
        {
            puts("\n(!) Invalid email.\n");
        }
        else
        {
            remove_trailing_newline(email);
            strcpy(emails[total_patrons + i], email);
            break;
        }
    }
}

/*
    Nhập địa chỉ của độc giả
*/
static void input_address(int i)
{
    char address[ADDRESS_SIZE + 1];

    while (TRUE)
    {
        printf("\t- Address: ");
        _flushall();

        if (fgets(address, ADDRESS_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(address);
            strcpy(addresses[total_patrons + i], address);
            break;
        }
    }
}

/*
    Nhập ngày sinh của độc giả và lưu trữ dưới dạng số nguyên 4 byte. Mỗi byte sẽ đại diện cho một thành phần của ngày sinh:
    - Byte 1 (LSB): ngày
    - Byte 2: tháng
    - Byte 3 + 4 (MSB): năm

*/
static void input_dob(int i)
{
    int dd, mm, yyyy;

    // Nhập ngày sinh theo định dạng dd/mm/yyyy
    while (TRUE)
    {
        printf("\t- Date of birth (dd/mm/yyyy): ");

        if (scanf("%d/%d/%d", &dd, &mm, &yyyy) != 3 || !is_valid_date(dd, mm, yyyy))
        {
            puts("\n(!) Invalid input. Please re-enter a valid date.\n");
            _flushall();
        }
        else
            break;
    }

    // 0xff: tương đương với 11111111 trong hệ nhị phân
    // 0xffff: tương đương với 11111111 11111111 trong hệ nhị phân
    dobs[total_patrons + i] |= dd & 0xff;             // Lấy 8 bit cuối cùng của dd lưu vào byte 4 của ngày sinh
    dobs[total_patrons + i] |= (mm & 0xff) << 8;      //  Lấy 8 bit cuối cùng của mm rồi dịch trái 8 bit để lưu vào byte 3 của ngày sinh
    dobs[total_patrons + i] |= (yyyy & 0xffff) << 16; //  Lấy 16 bit cuối cùng của mm rồi dịch trái 16 bit để lưu vào cả byte 1 và byte 2 của ngày sinh
}

/*
    Xuất ngày sinh của độc giả
*/
static char *output_dob(int i)
{
    int dd = 0;
    int mm = 0;
    int yyyy = 0;
    dd = (dobs[i] & 0xff);
    mm = (dobs[i] >> 8) & 0xff;
    yyyy = (dobs[i] >> 16 & 0xffff);
    char *dob = (char *)malloc(11);

    sprintf(dob, "%d/%d/%d", dd, mm, yyyy);
    return dob;
}

/*
    Xuất ra màn hình giới tính của độc giả
*/
static char *output_sex(int i)
{
    if (sexes[i] == MALE)
        return "Male";
    else
        return "Female";
}

/*
    Tìm vị trí index của độc giả bằng mã thẻ độc giả
*/
static int find_patron_index_by_card_number(const char *card_number)
{
    for (int i = 0; i < total_patrons; i++)
    {
        if (strcmp(card_numbers[i], card_number) == EQUALS)
        {
            return i; // Trả về vị trí index của độc giả được tìm thấy
        }
    }
    return -1; // Không tìm thấy độc giả
}

/*
    Cập nhật loại độc giả
*/
static void update_category(int k)
{
    int new_category;

    while (TRUE)
    {
        printf("\t- New category (0 for undergraduate student - 1 for graduate student): ");

        if (scanf("%d", &new_category) != 1 || (new_category != UNDERGRADUATE && new_category != GRADUATE))
        {
            puts("\n(!) Invalid input. Please enter 0 for undergraduate student or 1 for graduate student.\n");
            _flushall();
        }
        else
            break;
    }

    categories[k] = new_category; // cập nhật loại độc giả

    // cập nhật lại mã thẻ độc giả
    if (new_category == UNDERGRADUATE)
    {
        sprintf(card_numbers[k], "%d%s", UNDERGRADUATE_PREFIX, student_ids[k]);
    }
    else
    {
        sprintf(card_numbers[k], "%d%s", GRADUATE_PREFIX, student_ids[k]);
    }

    puts("\nUpdate category successfully!");
}

/*
    Cập nhật địa chỉ của độc giả
*/
static void update_address(int k)
{
    char new_address[ADDRESS_SIZE + 1];

    while (TRUE)
    {
        printf("\t- New address: ");
        _flushall();

        if (fgets(new_address, ADDRESS_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(new_address);

            // Nếu trường địa chỉ mới trống thì không cần cập nhật
            if (strlen(new_address) != 0)
            {
                strcpy(addresses[k], new_address);
            }
            break;
        }
    }
    puts("\nUpdate address successfully!");
}

/*
    Cập nhật mã sinh viên/học viên cao học
*/
static void update_student_id(int k)
{
    char new_student_id[STUDENT_ID_SIZE + 1];

    while (TRUE)
    {
        printf("\t- New student ID: ");
        _flushall();

        if (fgets(new_student_id, STUDENT_ID_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(new_student_id);

            // Nếu để trống thì không cần cập nhật
            if (strlen(new_student_id) != 0)
            {
                strcpy(student_ids[k], new_student_id); // cập nhật lại mã sinh viên/học viên
                if (categories[k] == UNDERGRADUATE)
                    sprintf(card_numbers[k], "%d%s", UNDERGRADUATE_PREFIX, new_student_id);
                else
                    sprintf(card_numbers[k], "%d%s", GRADUATE_PREFIX, new_student_id);
            }
            break;
        }
    }

    puts("\nUpdate student id successfully!");
}

/*
    Cập nhật địa chỉ email của độc giả
*/
static void update_email(int k)
{
    char new_email[EMAIL_SIZE + 1];

    while (TRUE)
    {
        printf("\t- New Email: ");
        _flushall();

        if (fgets(new_email, EMAIL_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else if (!is_valid_email(new_email))
        {
            puts("\n(!) Invalid email.\n");
        }
        else
        {
            remove_trailing_newline(new_email);

            // Nếu trường email mới trống thì không cần cập nhật
            if (strlen(new_email) != 0)
            {
                strcpy(emails[k], new_email);
            }
            break;
        }
    }
    puts("\nUpdate email successfully!");
}

/*
    Cập nhật họ tên của độc giả
*/
static void update_full_name(int k)
{
    char new_full_name[FULL_NAME_SIZE + 1];

    while (TRUE)
    {
        printf("\t- New full name: ");
        _flushall();

        if (fgets(new_full_name, FULL_NAME_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(new_full_name);

            // Nếu trường trống thì không cần cập nhật
            if (strlen(new_full_name) != 0)
            {
                strcpy(full_names[k], new_full_name);
            }
            break;
        }
    }
    puts("\nUpdate full name successfully!");
}

/*
    Cập nhật giới tính của tác giả
*/
static void update_sex(int k)
{
    int new_sex;

    while (TRUE)
    {
        printf("\t- New sex (0 for male - 1 for female): ");

        if (scanf("%d", &new_sex) != 1 || (new_sex != MALE && new_sex != FEMALE))
        {
            puts("\n(!) Invalid input. Please enter 0 for male or 1 for female.\n");
            _flushall();
        }
        else
            break;
    }

    sexes[k] = new_sex; // cập nhật lại giới tính

    puts("\nUpdate sex successfully!");
}

/*
    Cập nhật ngày sinh
 */
static void update_dob(int k)
{
    int new_dd, new_mm, new_yyyy, new_dob;

    while (TRUE)
    {
        printf("\t- New date of birth (dd/mm/yyyy): ");

        if (scanf("%d/%d/%d", &new_dd, &new_mm, &new_yyyy) != 3 || !is_valid_date(new_dd, new_mm, new_yyyy))
        {
            puts("\n(!) Invalid input. Please re-enter a valid date.\n");
            _flushall();
        }
        else
            break;
    }

    new_dob |= new_dd & 0xff;
    new_dob |= (new_mm & 0xff) << 8;
    new_dob |= (new_yyyy & 0xffff) << 16;

    dobs[k] = new_dob; // Cập nhật lại ngày sinh tại vị trí k

    puts("\nUpdate date of birth successfully!");
}

/*
    Cập nhật số CMND/CCCD
*/
static void update_citizen_id(int k)
{
    char new_citizen_id[CITIZEN_ID_SIZE + 1];

    while (TRUE)
    {
        printf("\t- New citizen: ");
        _flushall();

        if (fgets(new_citizen_id, CITIZEN_ID_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(new_citizen_id);

            // Nếu trường trống thì không cần cập nhật
            if (strlen(new_citizen_id) != 0)
            {
                strcpy(citizen_ids[k], new_citizen_id);
            }
            break;
        }
    }
    puts("\nUpdate citizen id successfully!");
}

/*
    Hiển thị danh sách các trường thông tin của độc giả có thể cập nhật
*/
static void patron_fields()
{
    system("cls");
    puts(HORIZONTAL_LINE);
    puts("\n\t1. Category");
    puts("\t2. Student ID");
    puts("\t3. Full name");
    puts("\t4. Sex");
    puts("\t5. Date of birth");
    puts("\t6. Citizen ID");
    puts("\t7. Email");
    puts("\t8. Address");
    puts("\t0. Return");
    puts(HORIZONTAL_LINE);
}

/////////////////////////////////////////////////////////////
void input_patrons()
{
    int number_of_patrons = 0; // Số lượng độc giả mới cần thêm vào

    // Nhập số lượng độc giả cần thêm
    while (TRUE)
    {
        system("cls");
        puts(HORIZONTAL_LINE);
        printf("\nEnter the number of patrons: ");

        if (scanf("%d", &number_of_patrons) != SUCCESS || total_patrons + number_of_patrons < 0 || total_patrons + number_of_patrons > MAX_PATRONS)
        {
            puts("\n(!) Invalid input. Please enter a positive number of patrons.");
            pause();
        }
        else
            break;
    }

    // Thực hiện nhập các thông tin chi tiết của một độc giả
    for (int i = 0; i < number_of_patrons; i++)
    {
        printf("\n\t[PATRON %d]\n", i + 1);

        input_category(i);
        input_student_id(i);
        input_card_number(i);
        input_full_name(i);
        input_sex(i);
        input_dob(i);
        input_citizen_id(i);
        input_email(i);
        input_address(i);
    }

    // Cập nhật lại tổng số độc giả hiện có
    total_patrons += number_of_patrons;
}
void output_patrons()
{
    puts(HORIZONTAL_LINE);
    printf("\n\tTotal: %d\n", total_patrons);
    printf("\n\t%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "Card Number", "Citizen ID", "Full Name", "DOB", "Sex", "Email", "Address");
    _flushall();

    for (int i = 0; i < total_patrons; i++)
    {
        printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------");
        printf("\n\t%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", card_numbers[i], citizen_ids[i], full_names[i], output_dob(i), output_sex(i), emails[i], addresses[i]);
    }
}
void update_patron()
{
    char card_number[CARD_NUMBER_SIZE + 1];

    // Nhập mã thẻ độc giả
    while (TRUE)
    {
        printf("\n\tEnter card number: ");
        _flushall();

        if (fgets(card_number, CARD_NUMBER_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(card_number);
            break;
        }
    }

    // Tìm vị trí index của độc giả có mã thẻ vừa tìm thấy
    int k = find_patron_index_by_card_number(card_number);

    if (k == -1)
    {
        puts("\nPatron is not found");
        return;
    }
    else
    {
        int opt = 0;
        int should_exit = 0;

        do
        {
            patron_fields();
            printf("\nSelect a field to need to update: ");
            if (scanf("%d", &opt) != 1 || opt < 0 || opt > 8)
            {

                puts("\n(!) Invalid option. Please re-enter a number between 0 and 8.");
                _flushall();
                continue;
            }

            switch (opt)
            {
            case 1:
            {
                update_category(k);
                puts("\n\n\n\n\nPress any key to continue...");
                getch();
                break;
            }
            case 2:
            {
                update_student_id(k);
                puts("\n\n\n\n\nPress any key to continue...");
                getch();
                break;
            }
            case 3:
            {
                update_full_name(k);
                puts("\n\n\n\n\nPress any key to continue...");
                getch();
                break;
            }
            case 4:
            {
                update_sex(k);
                puts("\n\n\n\n\nPress any key to continue...");
                getch();
                break;
            }
            case 5:
            {
                update_dob(k);
                puts("\n\n\n\n\nPress any key to continue...");
                getch();
                break;
            }
            case 6:
            {
                update_citizen_id(k);
                puts("\n\n\n\n\nPress any key to continue...");
                getch();
                break;
            }
            case 7:
            {
                update_email(k);
                puts("\n\n\n\n\nPress any key to continue...");
                getch();
                break;
            }
            case 8:
            {
                update_address(k);
                puts("\n\n\n\n\nPress any key to continue...");
                getch();
                break;
            }

            case 0:
            {
                input_patron_menu();
                should_exit = 1;
                break;
            }
            }
        } while (!should_exit);
    }
}
void delete_patron()
{
    char card_number[CARD_NUMBER_SIZE + 1];

    // Nhập mã thẻ độc giả
    while (TRUE)
    {
        printf("\n\tEnter card number: ");
        _flushall();

        if (fgets(card_number, CARD_NUMBER_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(card_number);
            break;
        }
    }

    // Tìm vị trí index của độc giả vừa tìm được bằng mã thẻ độc giả
    int k = find_patron_index_by_card_number(card_number);

    if (k == -1)
    {
        printf("\nPatron is not found");
        return;
    }
    else
    {
        // Thế chổ độc giả cần xóa ở vị trí k bằng độc giả của cuối cùng
        strcpy(card_numbers[k], card_numbers[total_patrons - 1]);
        strcpy(student_ids[k], student_ids[total_patrons - 1]);
        strcpy(full_names[k], full_names[total_patrons - 1]);
        strcpy(citizen_ids[k], citizen_ids[total_patrons - 1]);
        strcpy(emails[k], emails[total_patrons - 1]);
        strcpy(addresses[k], addresses[total_patrons - 1]);
        sexes[k] = sexes[total_patrons - 1];
        dobs[k] = dobs[total_patrons - 1];
        categories[k] = categories[total_patrons - 1];
    }

    puts("\nDelete patron successfully!");

    // Cập nhật lại tổng số độc giả hiện có
    total_patrons--;
}
void find_patron_by_citizen_id()
{
    char citizen_id[CITIZEN_ID_SIZE + 1];

    // Nhập số CMND/CCCD
    while (TRUE)
    {
        printf("\n\tEnter citizen id: ");
        _flushall();

        if (fgets(citizen_id, CITIZEN_ID_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(citizen_id);
            break;
        }
    }

    // Tìm kiếm tuần tự độc giả
    for (int i = 0; i < total_patrons; i++)
    {
        if (strcmp(citizen_ids[i], citizen_id) == EQUALS)
        {
            // In ra thông tin chi tiết của độc giả vừa tìm được
            puts(HORIZONTAL_LINE);
            puts("\n\tPATRON INFORMATION");
            printf("\t> Card Number: %s", card_numbers[i]);
            printf("\n\t> Citizen ID: %s", citizen_ids[i]);
            printf("\n\t> Full Name: %s", full_names[i]);
            printf("\n\t> Date of Birth: %s", output_dob(i));
            printf("\n\t> Sex: %s", output_sex(i));
            printf("\n\t> Email: %s", emails[i]);
            printf("\n\t> Address: %s", addresses[i]);
            return;
        }
    }

    puts("\nPatron is not found.");
}
void find_patrons_by_full_name()
{
    char full_name[FULL_NAME_SIZE + 1];
    int is_found = FALSE;

    // Nhập họ tên cần tìm
    while (TRUE)
    {
        printf("\n\tEnter full name: ");
        _flushall();

        if (fgets(full_name, FULL_NAME_SIZE + 1, stdin) == NULL)
        {
            puts("\n(!) Invalid input.\n");
        }
        else
        {
            remove_trailing_newline(full_name);
            break;
        }
    }

    // Tìm kiếm tuần tự độc giả
    for (int i = 0; i < total_patrons; i++)
    {
        if (strcmp(full_names[i], full_name) == EQUALS)
        {
            // In ra thông tin chi tiết của độc giả vừa tìm được
            puts(HORIZONTAL_LINE);
            puts("\n\tPATRON INFORMATION");
            printf("\t> Card Number: %s", card_numbers[i]);
            printf("\n\t> Citizen ID: %s", citizen_ids[i]);
            printf("\n\t> Full Name: %s", full_names[i]);
            printf("\n\t> Date of Birth: %s", output_dob(i));
            printf("\n\t> Sex: %s", output_sex(i));
            printf("\n\t> Email: %s", emails[i]);
            printf("\n\t> Address: %s", addresses[i]);

            // Do có khả năng có nhiều độc giả trùng họ tên nên sẽ phải duyệt qua hết danh sách độc giả để tìm kiếm
            // return;

            is_found = TRUE;
        }
    }

    if (!is_found)
    {
        puts("\nPatron(s) is not found.");
    }
}
int get_total_patrons()
{
    return total_patrons;
}
int count_patrons_by_sex(int sex)
{
    int counter = 0;
    for (int i = 0; i < total_patrons; i++)
    {
        if (sexes[i] == sex)
            counter++;
    }
    return counter;
}

// !