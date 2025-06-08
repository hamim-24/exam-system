#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"
#include "menu.h"

void initialize_files() {
    // Initialize system state
    init_system_state(&g_system);

    // Load existing data if available
    load_system_state(&g_system);

    // Create default files if they don't exist
    FILE *file;

    file = fopen("AdminPassword.txt", "r");
    if (file == NULL) {
        file = fopen("AdminPassword.txt", "w");
        fputs("111111", file);
        fclose(file);
    }
    else
        fclose(file);

    file = fopen("AdminInfo.txt", "r");
    if (file == NULL) {
        file = fopen("AdminInfo.txt", "w");
        fprintf(file, " ");
        fclose(file);
    }
    else
        fclose(file);

    file = fopen("QuestionSubmit.txt", "r");
    if (file == NULL) {
        file = fopen("QuestionSubmit.txt", "w");
        fprintf(file, "No EXAM is running");
        fclose(file);
    }
    else
        fclose(file);

    file = fopen("ResultSubmit.txt", "r");
    if (file == NULL) {
        file = fopen("ResultSubmit.txt", "w");
        fprintf(file, "Result is not Published");
        fclose(file);
    }
    else
        fclose(file);

    file = fopen("Notice.txt", "r");
    if (file == NULL) {
        file = fopen("Notice.txt", "w");
        fprintf(file, " ");
        fclose(file);
    }
    else
        fclose(file);

    // Save the initialized system state
    save_system_state(&g_system);
}

int main(int argc, char const *argv[]) {
    initialize_files();
    menu();
    return 0;
}
