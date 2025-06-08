#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CHAR 80
#define MAX_NAME_LEN 50
#define MAX_ID_LEN 20
#define MAX_CODE_LEN 20
#define MAX_QUESTION_LEN 200
#define MAX_OPTION_LEN 100
#define MAX_QUESTIONS 30
#define MAX_NOTICE_LEN 200

// Student structure
typedef struct {
    char id[MAX_ID_LEN];
    char full_name[MAX_NAME_LEN];
    char roll[MAX_ID_LEN];
    char class[MAX_NAME_LEN];
    char phone[MAX_NAME_LEN];
    char father_name[MAX_NAME_LEN];
    char mother_name[MAX_NAME_LEN];
    char address[MAX_NAME_LEN * 2];
} Student;

// Question structure
typedef struct {
    char question_text[MAX_QUESTION_LEN];
    char options[4][MAX_OPTION_LEN];
    char correct_answer; // 'a', 'b', 'c', or 'd'
} Question;

// Exam structure
typedef struct {
    char code[MAX_CODE_LEN];
    char name[MAX_NAME_LEN];
    Question questions[MAX_QUESTIONS];
    int question_count;
    int is_active;
    char created_by[MAX_NAME_LEN];
    time_t created_time;
} Exam;

// Result structure
typedef struct {
    char student_id[MAX_ID_LEN];
    char exam_code[MAX_CODE_LEN];
    float marks;
    time_t exam_time;
} Result;

// Admin structure
typedef struct {
    char name[MAX_NAME_LEN];
    char password[12];
} Admin;

// School structure
typedef struct {
    char name[MAX_NAME_LEN];
    char address[MAX_NAME_LEN * 2];
    char phone[MAX_NAME_LEN];
} School;

// Notice structure
typedef struct {
    char message[MAX_NOTICE_LEN];
    time_t created_time;
    char created_by[MAX_NAME_LEN];
} Notice;

// System state structure
typedef struct {
    School school_info;
    Admin admins[10];
    int admin_count;
    Exam current_exam;
    int exam_active;
    int result_published;
    Notice notices[50];
    int notice_count;
} SystemState;

// Function prototypes for structure operations
void init_system_state(SystemState *system);
void save_student(Student *student);
Student* load_student(const char *id);
void save_exam(Exam *exam);
Exam* load_exam(const char *code);
void save_result(Result *result);
void save_system_state(SystemState *system);
void load_system_state(SystemState *system);
void add_notice(SystemState *system, const char *message, const char *created_by);
void clear_notices(SystemState *system);

#endif
