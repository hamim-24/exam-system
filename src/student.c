#include "student.h"
#include "utils.h"
#include "menu.h"

void registration() {
    Student new_student;
    
    printf("Enter ID : "); 
    fgets(new_student.id, sizeof(new_student.id), stdin);
    new_student.id[strcspn(new_student.id, "\n")] = '\0';

    // Check if student already exists
    Student *existing = load_student(new_student.id);
    if (existing != NULL) {
        free(existing);
        printf("\n\t**You have already registered.**\n\n");
        ending();
        menu();
        return;
    }
    
    if (!securityChecker()) { 
        printf("\nEnter your full name : ");
        fgets(new_student.full_name, sizeof(new_student.full_name), stdin);
        new_student.full_name[strcspn(new_student.full_name, "\n")] = '\0';
        
        printf("Enter your roll number : ");
        fgets(new_student.roll, sizeof(new_student.roll), stdin);
        new_student.roll[strcspn(new_student.roll, "\n")] = '\0';
        
        printf("Enter your class : ");
        fgets(new_student.class, sizeof(new_student.class), stdin);
        new_student.class[strcspn(new_student.class, "\n")] = '\0';
        
        printf("Enter your phone number : ");
        fgets(new_student.phone, sizeof(new_student.phone), stdin);
        new_student.phone[strcspn(new_student.phone, "\n")] = '\0';
        
        printf("Enter your father's name : "); 
        fgets(new_student.father_name, sizeof(new_student.father_name), stdin);
        new_student.father_name[strcspn(new_student.father_name, "\n")] = '\0';
        
        printf("Enter your mother's name : ");
        fgets(new_student.mother_name, sizeof(new_student.mother_name), stdin);
        new_student.mother_name[strcspn(new_student.mother_name, "\n")] = '\0';
        
        printf("Enter your address (in one line) : ");
        fgets(new_student.address, sizeof(new_student.address), stdin);
        new_student.address[strcspn(new_student.address, "\n")] = '\0';

        if (securityChecker()) {
            printf("\n\t**Registration Failed.**\n\n");
            ending();
            menu();
            return;
        }
        
        // Save student data
        save_student(&new_student);
        
        // Log registration
        fptr = fopen("AdminInfo.txt", "a");
        fprintf(fptr, "> NEW ID:%s Registered, TIME:%s ", new_student.id, generateTime());
        fclose(fptr);

        loading("Loading", "Registration Complete.");
        menu();
    } 
    else {
        printf("\n\t**Registration Failed.**\n\n");
        ending();
        menu();
    }
}
