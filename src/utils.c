#include "utils.h"

// Define the global file pointer and system state
FILE *fptr;
extern SystemState g_system;

void heading() {
    printf("\n");
    fflush(stdout);
    system("clear");

    for (int i = 0; i < MAX_CHAR; i++)
        printf("=");

    fptr = fopen("SchoolName.txt", "r");
    fgets(g_system.school_info.name, sizeof g_system.school_info.name, fptr);
    fclose(fptr);

    fptr = fopen("SchoolAddress.txt", "r");
    fgets(g_system.school_info.address, sizeof g_system.school_info.address, fptr);
    fclose(fptr);

    fptr = fopen("SchoolPhone.txt", "r");
    fgets(g_system.school_info.phone, sizeof g_system.school_info.phone, fptr);
    fclose(fptr);

    // Display school information from structure from file
    printf("\n=%*s%s%*s=",
           space_before(g_system.school_info.name), "",
           g_system.school_info.name,
           space_after(g_system.school_info.name), "");
    printf("\n=%*s%s%*s=",
           space_before(g_system.school_info.address), "",
           g_system.school_info.address,
           space_after(g_system.school_info.address), "");
    printf("\n=%*s%s%*s=",
           space_before(g_system.school_info.phone), "",
           g_system.school_info.phone,
           space_after(g_system.school_info.phone), "");

    printf("\n");
    for (int i = 0; i < MAX_CHAR; i++)
        printf("=");

    printf("\n\n\n");
}

void sub_heading(char *sub_heading[], int option) {
    heading();
    printf("%*s%s", space_before(sub_heading[option]), "", sub_heading[option]);
    printf("\n");
    for (int i = 0; i < MAX_CHAR; i++)
        printf("=");
    printf("\n");
}

void ending() {
    for (int i = 0; i < MAX_CHAR; i++)
        printf("=");
    printf("\nPress enter to continue.");
    getchar();
}

void loading(char str1[40], char str2[40]) {
    for (int i = 0; i <= 100; i++) {
        system("clear");
        printf("\n\n\n\t\t%s : [", str1);
        for (int j = 0; j < i / 4; j++)
            printf("=");
        printf(">");
        for (int j = i / 4; j < 25; j++)
            printf(" ");
        printf("\b] %d%%", i);
        fflush(stdout);
        usleep(20000);
        printf("\r");
    }
    printf("\n\n\t**%s**\n", str2);
    fflush(stdout);
    usleep(2000000);
    fflush(stdin);
    system("clear");
}

char *generateTime() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    return asctime(local_time);
}

void disable_echo_mode() {
    fflush(stdout);
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void enable_echo_mode() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int securityChecker() {
    char ch;
    int value;
    do {
        printf("\nAre you sure(y/n) : ");
        ch = getchar();
        getchar();
        fflush(stdin);
    } while (ch != 'y' && ch != 'n');

    switch (ch) {
    case 'y':
        value = 0;
        break;
    case 'n':
        value = 1;
        break;
    default:
        value = securityChecker();
        break;
    }
    return value;
}

void file_print(char file[30]) {
    char file_name[30], temp[100];
    strcpy(file_name, file);
    strcat(file_name, ".txt");
    fptr = fopen(file_name, "r");
    if (fptr != NULL) {
        do {
            fgets(temp, sizeof temp, fptr);
            temp[strcspn(temp, "\n")] = '\0';
            puts(temp);
        } while (!feof(fptr));
        fclose(fptr);
    }
}

int space_before(char *str) {
    return ((MAX_CHAR - 2 - strlen(str)) / 2) + 1;
}

int space_after(char *str) {
    return (MAX_CHAR - strlen(str) - space_before(str)) - 2;
}

void menu_shape(char *menu[], int size) {
    char str[MAX_CHAR - 2];
    strcpy(str, menu[0]);
    printf("%*s%s\n", space_before(str), "", str);

    for (int i = 0; i < MAX_CHAR; i++)
        printf("=");

    strcpy(str, "");
    for (int i = 1; i < size; i++) {
        strcpy(str, menu[i]);
        printf("\n=%*s%d. %s%*s=\n", space_before(str) - 3, "", i, str, space_after(str), "");
        for (int j = 0; j < MAX_CHAR; j++)
            printf("=");
    }
    printf("\n");
}

int is_id_match(const char *text, const char *id) {
    int len = strlen(id);
    if ((text == id || isspace(*(text - 1)) || ispunct(*(text - 1))) &&
        (isspace(*(text + len)) || ispunct(*(text + len)) || *(text + len) == '\0')) 
        return 1;

    return 0;
}
