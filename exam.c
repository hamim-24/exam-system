#include "exam.h"
#include "utils.h"
#include "admin.h"
#include "menu.h"

void questionCreate(char name[30]) {
    char ques_file[30], code[30], ans_file[30], res_file[30], temp[100], ans_no;
    int size;
    printf("Code of the question : ");
    fgets(code, sizeof code, stdin);
    code[strcspn(code, "\n")] = '\0';

    strcpy(ques_file, code);
    strcat(ques_file, ".txt");
    fptr = fopen(ques_file, "r");
    while (fptr != NULL) {
        fclose(fptr);
        printf("\nThe code exists, please change it.\n");
        printf("Code of the question : ");
        strcpy(code, "");
        fgets(code, sizeof code, stdin);
        code[strcspn(code, "\n")] = '\0';

        strcpy(ques_file, code);
        strcat(ques_file, ".txt");
        fptr = fopen(ques_file, "r");
    }

    fptr = fopen(ques_file, "w");
    printf("Name of the exam : ");
    fgets(temp, sizeof temp, stdin);
    fprintf(fptr, "Welcome to the exam\nQuestion code : '%s'\n\n%*s%s", code, space_before(temp), "", temp);
    strcpy(temp, "");
    for (int i = 0; i < MAX_CHAR; i++)
        fprintf(fptr, "=");
    fprintf(fptr, "\n");
    fclose(fptr);

    printf("Number of questions : "); 
    scanf("%d", &size);
    while (getchar() != '\n'); // Clear input buffer

    strcpy(ans_file, code);
    strcat(ans_file, "Ans.txt");
    for (int i = 0; i < size; i++) {
        fptr = fopen(ques_file, "a");
        printf("\nQuestion %d : ", i + 1);
        fgets(temp, sizeof temp, stdin);
        fprintf(fptr, " %d. %s", i + 1, temp);
        for (int j = 0; j < 4; j++) { // taking 4 options
            strcpy(temp, "");
            printf("Option (%c) : ", 'a' + j);
            fgets(temp, sizeof temp, stdin);
            fprintf(fptr, "\t(%c) %s", 'a' + j, temp);
        }
        fclose(fptr);
        do {
            printf("Answer (a,b,c,d) : ");
            scanf("%c", &ans_no);
            while (getchar() != '\n'); // Clear input buffer
        } while (ans_no != 'a' && ans_no != 'b' && ans_no != 'c' && ans_no != 'd'); // answer must be a,b,c,d
        fptr = fopen(ans_file, "a");
        fprintf(fptr, "%c", ans_no);
        fclose(fptr);
    }
    fptr = fopen("AdminInfo.txt", "a");
    fprintf(fptr, "> %s creates question, code : %s TIME:%s ", name, code, generateTime());
    fclose(fptr);

    loading("Creating", "Question Created");
    heading();

    fptr = fopen("QuestionSubmit.txt", "r");
    strcpy(temp, "");
    fgets(temp, sizeof temp, fptr);
    fclose(fptr);

    if (strcmp(temp, "No EXAM is running")) {
        printf("\n\t**Exam, code : %s is running, stop it to publish.**\n\n", temp);  
        ending();
        question(name);
    }
    printf("\nThe question has been created.\nThe question is being published...\n"); 
    if (!securityChecker() && !pwdchecker()) {
        loading("Publishing", "Question Published.");

        fptr = fopen("Notice.txt", "a");
        fprintf(fptr, "> Question, code : %s is published TIME:%s ", code, generateTime());
        fclose(fptr);

        fptr = fopen("AdminInfo.txt", "a");
        fprintf(fptr, "> %s publishes question, code : %s TIME:%s ", name, code, generateTime());
        fclose(fptr);

        strcpy(res_file, code);
        strcat(res_file, "Result.txt");
        fptr = fopen(res_file, "w");
        fprintf(fptr, "  Question code%s\n ", code);
        fclose(fptr);

        fptr = fopen("ResultSubmit.txt", "w");
        fprintf(fptr, "Result is not Published");
        fclose(fptr);

        fptr = fopen("QuestionSubmit.txt", "w");
        fprintf(fptr, "%s", code);
        fclose(fptr);
        
    }
    else {
        printf("\n\t**The question, code : %s was not published.**\n\n", code);
        ending();
    }
}

void question(char name[30]) {
    heading();
    fptr = fopen("QuestionSubmit.txt", "r");
    char saved_code[30], res_file[30];
    fgets(saved_code, sizeof saved_code, fptr);
    fclose(fptr);
    
    if (!strcmp(saved_code, "No EXAM is running"))
        printf("\t**%s**\n\n", saved_code);
    else
        printf("\t**Exam is running, code : %s.**\n\n", saved_code);

    char *ques_menu[] = {
        "Question",
        "Create",
        "Publish",
        "Stop Exam and Publish Result",
        "Back"};

    int size = sizeof ques_menu / sizeof ques_menu[0];
    menu_shape(ques_menu, size);

    int ques_opt;
    printf("Please select an option : ");
    scanf("%d", &ques_opt);
    while (getchar() != '\n'); // Clear input buffer

    switch (ques_opt) {
    case 1:
        sub_heading(ques_menu, ques_opt);

        printf("\n\t**Rules for creating questions**\n\n");
        printf(" 1. Once you select question, option and answer cannot be reselected.\n"); 
        printf(" 2. You have to provide 4 options.\n");
        printf(" 3. You need to submit here or in the administration.\n");
        printf(" 4. If you submit more than one answer, the 1st will be the correct answer.\n"); 
        printf(" 5. Maximum questions: 30.\n");

        printf("\nThe question creation is starting...\n"); 
        if (!securityChecker() && !pwdchecker()) {
            sub_heading(ques_menu, ques_opt);
            questionCreate(name);
        }
        else {
            printf("\n\t**Action Failed.**\n\n");
            ending();
        }
        break;
    case 2:
        sub_heading(ques_menu, ques_opt);
        if (!strcmp(saved_code, "No EXAM is running")) {
            char search_code[30];
            printf("Enter the question code : ");
            fgets(search_code, sizeof search_code, stdin);
            search_code[strcspn(search_code, "\n")] = '\0';

            char file[30];
            strcpy(file, search_code);
            strcat(file, ".txt");
            fptr = fopen(file, "r");
            if (fptr != NULL) {
                fclose(fptr);
                printf("\nThe question, code : %s is being published...\n", search_code); 
                if (!securityChecker() && !pwdchecker())
                {
                    loading("Publishing", "Question Published");
                    fptr = fopen("Notice.txt", "a");
                    fprintf(fptr, "> Question, code : %s is published TIME:%s ", search_code, generateTime());
                    fclose(fptr);

                    fptr = fopen("AdminInfo.txt", "a");
                    fprintf(fptr, "> %s publishes question, code : %s TIME:%s ", name, search_code, generateTime());
                    fclose(fptr);

                    fptr = fopen("ResultSubmit.txt", "w");
                    fprintf(fptr, "Result is not Published");
                    fclose(fptr);

                    fptr = fopen("QuestionSubmit.txt", "w");
                    fprintf(fptr, "%s", search_code);
                    fclose(fptr);

                    strcpy(res_file, search_code);
                    strcat(res_file, "Result.txt");
                    fptr = fopen(res_file, "w");
                    fprintf(fptr, "  Question code%s\n ", search_code);
                    fclose(fptr);
                
                }
                else {
                    printf("\n\t**The exam, code : %s was not published.**\n\n", search_code); 
                    ending();
                }
            }
            else {
                printf("\n\t**The question, code : %s was not created.**\n\n", search_code);  
                ending();
            }
        }
        else {
            printf("\n\t**Exam is running, code : %s. Stop it.**\n\n", saved_code);
            ending();
        }
        break;
    case 3:
        sub_heading(ques_menu, ques_opt);
        if (strcmp(saved_code, "No EXAM is running")) {
            printf("\nThe question, code : %s is being stopped... and result is being published...\n", saved_code);  
            if (!securityChecker() && !pwdchecker()) {
                loading("Stopping", "Question Stopped and Result Published");  
                fptr = fopen("QuestionSubmit.txt", "w");
                fprintf(fptr, "No EXAM is running");
                fclose(fptr);

                fptr = fopen("ResultSubmit.txt", "w");
                fprintf(fptr, "%s", saved_code);
                fclose(fptr);

                fptr = fopen("AdminInfo.txt", "a");
                fprintf(fptr, "> %s stops question, code : %s TIME:%s ", name, saved_code, generateTime());
                fclose(fptr);

                fptr = fopen("Notice.txt", "a");
                fprintf(fptr, "> Exam (code : %s) is finished TIME:%s ", saved_code, generateTime());
                fprintf(fptr, "> Result (code : %s) is published TIME:%s ", saved_code, generateTime());
                fclose(fptr);
            }
        
            else {
                printf("\n\t**The exam code : %s has not been stopped.**\n\n", saved_code); 
                ending();
            }
        }
        else {
            printf("\n\t**%s**\n\n", saved_code);
            ending();
        }
        break;
    case 4:
        administration(name);
        return;
    default:
        question(name);
        return;
    }
    question(name);
}

void exam_system(char id[30]) {
    char saved_code[30], file[30], ans[30], stu_ans, ques[100], res_file[30];

    fptr = fopen("QuestionSubmit.txt", "r");
    fgets(saved_code, sizeof saved_code, fptr);
    fclose(fptr);

    strcpy(file, saved_code);
    strcat(file, "Ans.txt");
    fptr = fopen(file, "r");
    fgets(ans, sizeof ans, fptr);
    fclose(fptr);

    float mark = 0;
    int ques_num = strlen(ans);

    printf("\n\t**Rules of Exam**\n");
    printf("\n 1. In the exam you will find %d question(s).", ques_num);
    printf("\n 2. You need to enter 'a','b','c','d'.");
    printf("\n 3. Each question contains 1 point.");
    printf("\n 4. For each incorrect question you will obtain -0.25 points.");
    printf("\n 5. After answering, press enter for the next question.");
    printf("\n 6. To skip, just press enter."); 
    printf("\n 7. Find result in result option after publishing.");
    printf("\n 8. You will be notified through notices."); 

    ending();
    loading("Loading", "Question is loaded.");
    heading();
    strcpy(file, saved_code);
    strcat(file, ".txt");
    fptr = fopen(file, "r");
    
    for (int i = 0; i <= ques_num; i++) {
        for (int j = 0; j < 5; j++) {
            fgets(ques, sizeof ques, fptr);
            printf("%s", ques);
        }
        // skip first loop as first 5 lines are not the question these are the headings
        if (i != 0) {
            printf("Answer(a,b,c,d) : ");
            scanf("%c", &stu_ans);
            while (getchar() != '\n'); // Clear input buffer

            if (ans[i - 1] == stu_ans) //correct answer
                mark++;
            else if (stu_ans == 10) // pressing enter (skip)
                mark = mark;
            else // wrong answer
                mark = mark - 0.25;  
        }
        printf("\n");
    }
    fclose(fptr);
    
    strcpy(res_file, saved_code);
    strcat(res_file, "Result.txt");
    fptr = fopen(res_file, "a");
    fprintf(fptr, "> ID: %s   \tMARK: %.2f  \tEXAM TIME: %s ", id, mark, generateTime());
    fclose(fptr);

    printf("\t**Exam has ended.**\n\n");
    ending();
}

void handle_exam_option() {
    char text_file[1000];
    char id[100];
    char *position;
    char code[30], file[30];

    fptr = fopen("QuestionSubmit.txt", "r");
    strcpy(code, "");
    fgets(code, sizeof code, fptr);
    fclose(fptr);

    if (!strcmp(code, "No EXAM is running")) {// if no exam is running
        printf("\n\t**%s**\n\n", code);
        ending();
        menu();
        return;
    }

    printf("Enter your id : ");
    fgets(id, sizeof id, stdin);
    id[strcspn(id, "\n")] = '\0';
    int found = 0;

    strcpy(file, code);
    strcat(file, "Result.txt");
    fptr = fopen(file, "r");
    if (fptr != NULL) {
        do {// checking double attemp, result has been created or not
            fgets(text_file, sizeof text_file, fptr);
            position = text_file;
            while ((position = strstr(position, id)) != NULL) {
                if (is_id_match(position, id)) {
                    found = 1;
                    break;
                }
                position += strlen(id);
            }
        } while (!feof(fptr) && !found);
        fclose(fptr);
    }

    if (found) { // if double attempt
        printf("\n\t**You cannot participate twice.**\n\n"); 
        ending();
        menu();
        return;
    }

    strcpy(file, id);
    strcat(file, "Info.txt");
    fptr = fopen(file, "r");
    if (fptr == NULL) { // if not registered
        printf("\n\t**Register your ID.**\n\n"); 
        ending();
    }
    else {
        fclose(fptr);
        exam_system(id);
    }
}

void display_results()
{
    char code[30], file[30];
    
    fptr = fopen("ResultSubmit.txt", "r");
    fgets(code, sizeof code, fptr);
    fclose(fptr);

    if (!strcmp(code, "Result is not Published")) {
        printf("\n\t**%s**\n\n", code);
        ending();
    }
    else {
        strcpy(file, code);
        strcat(file, "Result");
        file_print(file);
        ending();
    }
}
