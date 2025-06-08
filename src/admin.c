#include "admin.h"
#include "utils.h"
#include "exam.h"
#include "menu.h"

// pwdchecker: Prompts the admin for a password (up to 3 attempts),
// disables echo for password entry, masks input with '*',
// checks the entered password against the stored password in AdminPassword.txt.
// Returns 0 if the password is correct, 1 otherwise.
int pwdchecker() {
    int value = 1;
    char pwd[12];
    char u_pwd[12];

    fptr = fopen("AdminPassword.txt", "r");
    fgets(pwd, sizeof pwd, fptr);
    fclose(fptr);

    heading();
    // Loop for up to 3 password attempts
    for (int i = 2; i >= 0; i--) {
        printf("Enter password : ");
        char ch;
        int j = 0;
        disable_echo_mode(); // Disable terminal echo for password masking
        // Read password character by character, mask with '*', handle backspace
        while ((ch = getchar()) != 10 && j < 11) {
            if (ch == 127) { // Handle backspace
                if (j > 0) {
                    j--;
                    printf("\b \b");
                }
            }
            else {
                u_pwd[j++] = ch;
                printf("*");
            }
        }
        u_pwd[j] = '\0'; // Null-terminate the entered password
        enable_echo_mode(); // Re-enable terminal echo
        printf("\n");
        
        // Check password correctness and handle attempts
        if (i == 0) {
            printf("\n**Incorrect Password.**\nAction Failed.\n");
            usleep(1000000);
        }
        else if (strcmp(pwd, u_pwd))
            printf("\n**Incorrect Password.**\nTry again for %d time(s).\n", i);
        else {
            printf("\n**Correct Password**.\n");
            value = 0;
            break;
        }
    }
    usleep(1000000);
    fflush(stdout);
    system("clear");
    return value;
}

void administration(char name[30]) {
    heading();
    char *admin_menu[] = {
        "Administration",
        "Notifications", 
        "Question",
        "Search Student & Delete",
        "Notice Control",
        "Settings",  
        "Back"};
    int size = sizeof admin_menu / sizeof admin_menu[0];
    menu_shape(admin_menu, size);

    int option;
    printf("Please select an option : ");
    scanf("%d", &option);
    while (getchar() != '\n'); // Clear input buffer

    switch (option) {
    case 1:
        if (!pwdchecker()) {
            sub_heading(admin_menu, option);
            file_print("AdminInfo");
            ending();
        }
        break;
    case 2:
        if (!pwdchecker()) {
            question(name);
        }
        break;
    case 3:
        if (!pwdchecker()) {
            sub_heading(admin_menu, option);
            char id[30];
            char file[30];

            printf("Enter student ID : ");
            fgets(id, sizeof id, stdin);
            id[strcspn(id, "\n")] = '\0';

            strcpy(file, id);
            strcat(file, "Info.txt");
            fptr = fopen(file, "r");
            if (fptr == NULL)
                loading("Searching", "Student does not exist.");
            else {
                fclose(fptr);
                loading("Searching", "Student exists."); 
                sub_heading(admin_menu, option);
                printf(" > ID : %s\n", id);
                strcpy(file, id);
                strcat(file, "Info");

                file_print(file);

                printf("\n\nDeleting ID...\n");
                if (!securityChecker()) {
                    strcat(file, ".txt");
                    remove(file);

                    fptr = fopen("AdminInfo.txt", "a");
                    fprintf(fptr, "> ID:%s Deleted, TIME:%s ", id, generateTime());
                    fclose(fptr);
                }
                ending();
            }
        }
        break;
    case 4:
        if (!pwdchecker())
            notice(name);
        break;
    case 5:
        settings(name); 
        break;
    case 6:
        menu();
        break;
    default:
        administration(name);
        break;
    }
    administration(name);
}

void settings(char name[30]) {
    heading();
    char temp[100];
    char *setting_menu[] = {
        "Settings",
        "Change school name",
        "Change school address",
        "Change school number",
        "Change Admin password",
        "Back"};
    char *filename[] = {
        "SchoolName.txt",
        "SchoolAddress.txt",
        "SchoolPhone.txt"};
    char *s_name[] = {
        "School name",
        "School address",
        "School number",
    };
    
    int size = sizeof setting_menu / sizeof setting_menu[0];
    menu_shape(setting_menu, size);

    printf("Please enter an option : ");
    int option;
    scanf("%d", &option);
    while (getchar() != '\n'); // Clear input buffer

    if (option == 1 || option == 2 || option == 3) {
        sub_heading(setting_menu, option);

        printf("Enter new %s : ", s_name[option - 1]);
        fgets(temp, sizeof temp, stdin);
        temp[strcspn(temp, "\n")] = '\0';

        printf("\n%s : %s, is (saving...)\n", s_name[option - 1], temp);
        if (!securityChecker() && !pwdchecker()) {
            loading("Saving", "Successfully changed.");
            fptr = fopen(filename[option - 1], "w");
            fprintf(fptr, "%s", temp);
            fclose(fptr);

            fptr = fopen("AdminInfo.txt", "a");
            fprintf(fptr, "> %s changed %s, TIME:%s ", name, s_name[option - 1], generateTime());
            fclose(fptr);
        }
        else {
            printf("\n\t**%s was not changed.**\n\n", s_name[option - 1]);
            ending();
        }
        settings(name); 
    }
    else if (option == 4) {
        if (!pwdchecker()) {
            char pwd[12], u_pwd[12];
            sub_heading(setting_menu, option);

            for (int i = 2; i >= 0; i--) {
                do {
                    printf("\nPassword must be 6 characters.\n"); 
                    printf("Enter new admin password : ");
                    strcpy(pwd, "");
                    fgets(pwd, sizeof pwd, stdin);
                    pwd[strcspn(pwd, "\n")] = '\0';
                } while (strlen(pwd) != 6);

                printf("Enter password again : ");
                strcpy(u_pwd, "");
                fgets(u_pwd, sizeof u_pwd, stdin);
                u_pwd[strcspn(u_pwd, "\n")] = '\0';

                char tempPwd[12];
                fptr = fopen("AdminPassword.txt", "r");
                fscanf(fptr, "%s", tempPwd);
                fclose(fptr);

                if (i == 0) { // after 3rd time
                    printf("\n**Password was not changed.**\n\n"); 
                    ending();
                }
                else if (strcmp(pwd, u_pwd)) // did'nt match
                    printf("\n**Passwords did not match.**\nTry again for %d time(s).\n", i);
                else {
                    if (!strcmp(tempPwd, pwd)) { // if the pwd remain same
                        printf("\n\t**Admin password is still the same.**\n\n");
                        ending();
                    }
                    else if (printf("\nSchool password : %s (saving...)\n", pwd) && !securityChecker()) {
                        loading("Saving", "Successfully changed.");
                        fptr = fopen("AdminPassword.txt", "w");
                        fprintf(fptr, "%s", pwd);
                        fclose(fptr);

                        fptr = fopen("AdminInfo.txt", "a");
                        fprintf(fptr, "> %s changed admin password, TIME:%s ", name, generateTime());
                        fclose(fptr);
                    }
                    else {
                        printf("\n\t**Admin password was not changed.**\n\n");
                        ending();
                    }
                    break;
                }
            }
            settings(name); 
        }
        else
            settings(name); 
    }
    else if (option == 5) {
        administration(name);
    }
    else
        settings(name); 
}

void notice(char name[30]) {
    heading();
    char *note_menu[] = {
        "Notice Control",
        "Add notice",
        "Clear notices",
        "Back"};

    int n_size, n_opt;
    n_size = sizeof note_menu / sizeof note_menu[0];
    menu_shape(note_menu, n_size);

    printf("Please select an option : ");
    scanf("%d", &n_opt);
    while (getchar() != '\n'); // Clear input buffer

    char note[100];
    switch (n_opt) {
    case 1:
        sub_heading(note_menu, n_opt);
        printf("You can add a single notice at a time.\n");
        printf("Enter the notice : ");
        fgets(note, sizeof note, stdin);
        note[strcspn(note, "\n")] = '\0';

        if (!securityChecker()) {
            loading("Adding", "Notice added.");
            fptr = fopen("Notice.txt", "a");
            fprintf(fptr, "> %s\n ", note);
            fclose(fptr);

            fptr = fopen("AdminInfo.txt", "a");
            fprintf(fptr, "> %s adds notice TIME:%s ", name, generateTime());
            fclose(fptr);
        }
        else {
            printf("\n\t**Notice was not added.**\n\n"); 
            ending();
        }
        break;
    case 2:
        sub_heading(note_menu, n_opt);
        printf("\nNotices are being cleared...\n"); 
        if (!securityChecker()) {
            loading("Clearing", "Notices cleared."); 
            fptr = fopen("Notice.txt", "w");
            fprintf(fptr, " ");
            fclose(fptr);

            fptr = fopen("AdminInfo.txt", "a");
            fprintf(fptr, "> %s clears notices TIME:%s ", name, generateTime());
            fclose(fptr);
        }
        else {
            printf("\n\t**Notices were not cleared.**\n\n");
            ending();
        }
        break;
    case 3:
        administration(name);
        break;
    default:
        notice(name);
        break;
    }
    administration(name);
}
