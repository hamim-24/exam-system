#include "menu.h"
#include "utils.h"
#include "admin.h"
#include "exam.h"
#include "student.h"

void menu() {
    heading();
    int option;
    char *main_menu[] = {
        "Main Menu",
        "Administration",
        "Notice Board", 
        "Search Question",
        "Exam",
        "Result",
        "Registration",
        "Exit"};

    int size = sizeof main_menu / sizeof main_menu[0];
    menu_shape(main_menu, size);
    
    char *admin_name[] = {"rabin", "alex"};
    char u_admin_name[30];
    int ad_name_size = sizeof admin_name / sizeof admin_name[0];
    char code[30], file[30];

    printf("Please select an option : ");
    scanf("%d", &option);
    while (getchar() != '\n'); // Clear input buffer

    switch (option) {
    case 1:
        heading();
        printf("Enter your name : ");
        
        fgets(u_admin_name, sizeof u_admin_name, stdin);
        u_admin_name[strcspn(u_admin_name, "\n")] = '\0';

        for (int i = 0; i < ad_name_size; i++) {
            if (!strcmp(u_admin_name, admin_name[i])) {
                if (pwdchecker()) {
                    fptr = fopen("AdminInfo.txt", "a");
                    fprintf(fptr, "> %s tried but failed TIME:%s ", u_admin_name, generateTime());
                    fclose(fptr);
                }
                else {
                    fptr = fopen("AdminInfo.txt", "a");
                    fprintf(fptr, "> %s logged in TIME:%s ", u_admin_name, generateTime());
                    fclose(fptr);
                    loading("Loading", "Logged in.");
                    administration(u_admin_name);
                }
                break;
            }
            else if (i == ad_name_size - 1) {
                printf("\n\t**You cannot enter.**\n\n");
                ending();
            }
        }
        break;
        
    case 2:
        sub_heading(main_menu, option);
        file_print("Notice");
        ending();
        break;
        
    case 3:
        sub_heading(main_menu, option);
        printf("Enter the code of question : ");

        strcpy(code, "");
        fgets(code, sizeof code, stdin);
        code[strcspn(code, "\n")] = '\0';

        fptr = fopen("QuestionSubmit.txt", "r");
        fgets(file, sizeof file, fptr);
        fclose(fptr);

        if (!strcmp(file, code)) {
            loading("Searching", "The exam is running, you can't see this question.");
            menu();
        }

        strcpy(file, code);
        strcat(file, ".txt");
        fptr = fopen(file, "r");
        if (fptr == NULL)    
            loading("Searching", "Question not found."); 
        else {
            loading("Searching", "Question found."); 
            sub_heading(main_menu, option);
            fclose(fptr);

            printf("\n");
            file_print(code);

            printf("\nPress enter to see the answer.\n");
            getchar();

            strcpy(file, code);
            strcat(file, "Ans");

            printf("Answer (serially) : ");
            file_print(file);
            ending();
        }
        break;
        
    case 4:
        sub_heading(main_menu, option);
        handle_exam_option();
        break;
        
    case 5:
        sub_heading(main_menu, option);
        display_results();
        break;
        
    case 6:
        sub_heading(main_menu, option);
        registration();
        break;
        
    case 7:
        loading("Exiting", "Successfully exited. Thank You.");
        exit(0);
        break;
        
    default:
        menu();
        break;
    }
    menu();
}
