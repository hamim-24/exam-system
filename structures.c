#include "structures.h"
#include "utils.h"

// Global system state
SystemState g_system;

void init_system_state(SystemState *system) {
    // Initialize school info with defaults
    strcpy(system->school_info.name, "Set school info in administration ");
    strcpy(system->school_info.address, "Default password 111111");
    strcpy(system->school_info.phone, "");

    // Initialize default admins and pwd
    system->admin_count = 2;
    strcpy(system->admins[0].name, "rabin");
    strcpy(system->admins[0].password, "111111");
    strcpy(system->admins[1].name, "alex");
    strcpy(system->admins[1].password, "111111");

    // Initialize exam state
    system->exam_active = 0;
    system->result_published = 0;
    system->current_exam.question_count = 0;
    system->current_exam.is_active = 0;

    // Initialize notices
    system->notice_count = 0;
}

void save_student(Student *student) {
    char filename[50];
    sprintf(filename, "%sInfo.txt", student->id);

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, " > Full name : %s\n", student->full_name);
        fprintf(file, " > Roll : %s\n", student->roll);
        fprintf(file, " > Class : %s\n", student->class);
        fprintf(file, " > Phone number : %s\n", student->phone);
        fprintf(file, " > Father name : %s\n", student->father_name);
        fprintf(file, " > Mother name : %s\n", student->mother_name);
        fprintf(file, " > Address : %s\n", student->address);
        fclose(file);
    }
}

Student *load_student(const char *id) {
    char filename[50];
    sprintf(filename, "%sInfo.txt", id);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return NULL;
    

    Student *student = malloc(sizeof(Student));
    strcpy(student->id, id);

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Full name"))
            sscanf(line, " > Full name : %[^\n]", student->full_name);
        
        else if (strstr(line, "Roll"))
            sscanf(line, " > Roll : %[^\n]", student->roll);
        
        else if (strstr(line, "Class"))
            sscanf(line, " > Class : %[^\n]", student->class);
        
        else if (strstr(line, "Phone"))
            sscanf(line, " > Phone number : %[^\n]", student->phone);
        
        else if (strstr(line, "Father"))
            sscanf(line, " > Father name : %[^\n]", student->father_name);
        
        else if (strstr(line, "Mother"))
            sscanf(line, " > Mother name : %[^\n]", student->mother_name);
        
        else if (strstr(line, "Address"))
            sscanf(line, " > Address : %[^\n]", student->address);
        
    }
    fclose(file);
    return student;
}

void save_exam(Exam *exam) {
    char filename[50];
    sprintf(filename, "%s.txt", exam->code);

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "Welcome to the exam\n");
        fprintf(file, "Question code : '%s'\n\n", exam->code);
        fprintf(file, "%*s%s\n", space_before(exam->name), "", exam->name);

        for (int i = 0; i < MAX_CHAR; i++)
            fprintf(file, "=");
        fprintf(file, "\n");

        for (int i = 0; i < exam->question_count; i++)
        {
            fprintf(file, " %d. %s\n", i + 1, exam->questions[i].question_text);
            for (int j = 0; j < 4; j++)
                fprintf(file, "\t(%c) %s\n", 'a' + j, exam->questions[i].options[j]);
        }
        fclose(file);
    }

    // Save answers separately
    sprintf(filename, "%sAns.txt", exam->code);
    file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < exam->question_count; i++)
            fprintf(file, "%c", exam->questions[i].correct_answer);
        
        fclose(file);
    }
}

Exam *load_exam(const char *code) {
    char filename[50];
    sprintf(filename, "%s.txt", code);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return NULL;

    Exam *exam = malloc(sizeof(Exam));
    strcpy(exam->code, code);
    exam->question_count = 0;

    // Load answers
    sprintf(filename, "%sAns.txt", code);
    FILE *ans_file = fopen(filename, "r");
    if (ans_file != NULL) {
        char answers[MAX_QUESTIONS];
        fgets(answers, sizeof(answers), ans_file);
        exam->question_count = strlen(answers);

        for (int i = 0; i < exam->question_count; i++)
            exam->questions[i].correct_answer = answers[i];
        
        fclose(ans_file);
    }

    fclose(file);
    return exam;
}

void save_result(Result *result) {
    char filename[50];
    sprintf(filename, "%sResult.txt", result->exam_code);

    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        char *time_str = ctime(&result->exam_time);
        time_str[strlen(time_str) - 1] = '\0'; // Remove newline
        fprintf(file, "> ID: %s   \tMARK: %.2f  \tEXAM TIME: %s\n",
                result->student_id, result->marks, time_str);
        fclose(file);
    }
}

void save_system_state(SystemState *system) {
    // Save school info
    FILE *file = fopen("SchoolName.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s", system->school_info.name);
        fclose(file);
    }

    file = fopen("SchoolAddress.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s", system->school_info.address);
        fclose(file);
    }

    file = fopen("SchoolPhone.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s", system->school_info.phone);
        fclose(file);
    }

    // Save admin password (first admin's password)
    file = fopen("AdminPassword.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s", system->admins[0].password);
        fclose(file);
    }

    // Save exam status
    file = fopen("QuestionSubmit.txt", "w");
    if (file != NULL) {
        if (system->exam_active)
            fprintf(file, "%s", system->current_exam.code);
        else
            fprintf(file, "No EXAM is running");
        fclose(file);
    }

    // Save result status
    file = fopen("ResultSubmit.txt", "w");
    if (file != NULL) {
        if (system->result_published)
            fprintf(file, "%s", system->current_exam.code);
        else
            fprintf(file, "Result is not Published");
        fclose(file);
    }

    // Save notices
    file = fopen("Notice.txt", "w");
    if (file != NULL) {
        if (system->notice_count == 0)
            fprintf(file, " ");
        else {
            for (int i = 0; i < system->notice_count; i++) {
                char *time_str = ctime(&system->notices[i].created_time);
                time_str[strlen(time_str) - 1] = '\0'; // Remove newline
                fprintf(file, "> %s TIME: %s\n",
                        system->notices[i].message, time_str);
            }
        }
        fclose(file);
    }
}

void load_system_state(SystemState *system) {
    FILE *file;
    char buffer[200];

    // Load school info
    file = fopen("SchoolName.txt", "r");
    if (file != NULL) {
        fgets(system->school_info.name, sizeof(system->school_info.name), file);
        system->school_info.name[strcspn(system->school_info.name, "\n")] = '\0';
        fclose(file);
    }

    file = fopen("SchoolAddress.txt", "r");
    if (file != NULL) {
        fgets(system->school_info.address, sizeof(system->school_info.address), file);
        system->school_info.address[strcspn(system->school_info.address, "\n")] = '\0';
        fclose(file);
    }

    file = fopen("SchoolPhone.txt", "r");
    if (file != NULL) {
        fgets(system->school_info.phone, sizeof(system->school_info.phone), file);
        system->school_info.phone[strcspn(system->school_info.phone, "\n")] = '\0';
        fclose(file);
    }

    // Load admin password
    file = fopen("AdminPassword.txt", "r");
    if (file != NULL) {
        fgets(system->admins[0].password, sizeof(system->admins[0].password), file);
        system->admins[0].password[strcspn(system->admins[0].password, "\n")] = '\0';
        // Copy to second admin as well
        strcpy(system->admins[1].password, system->admins[0].password);
        fclose(file);
    }

    // Load exam status
    file = fopen("QuestionSubmit.txt", "r");
    if (file != NULL) {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "No EXAM is running") != 0) {
            system->exam_active = 1;
            strcpy(system->current_exam.code, buffer);
        }
        else
            system->exam_active = 0;
        
        fclose(file);
    }

    // Load result status
    file = fopen("ResultSubmit.txt", "r");
    if (file != NULL) {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "Result is not Published") != 0)
            system->result_published = 1;
        else
            system->result_published = 0;
        fclose(file);
    }
}

void add_notice(SystemState *system, const char *message, const char *created_by) {
    if (system->notice_count < 50) {
        strcpy(system->notices[system->notice_count].message, message);
        strcpy(system->notices[system->notice_count].created_by, created_by);
        system->notices[system->notice_count].created_time = time(NULL);
        system->notice_count++;
    }
}

void clear_notices(SystemState *system) {
    system->notice_count = 0;
}
