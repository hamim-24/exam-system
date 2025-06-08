#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include "structures.h"

// Constants
#define MAX_CHAR 80

// Global file pointer and system state
extern FILE *fptr;
extern SystemState g_system;

// Utility functions
void heading();
void sub_heading(char *sub_heading[], int option);
void ending();
void loading(char str1[40], char str2[40]);
char *generateTime();
void disable_echo_mode();
void enable_echo_mode();
int securityChecker();
void file_print(char file[30]);
int space_before(char *str);
int space_after(char *str);
void menu_shape(char *menu[], int size);
int is_id_match(const char *text, const char *id);

#endif
