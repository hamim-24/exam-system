# Exam Management System

A comprehensive console-based exam management system written in C that allows administrators to create, manage, and conduct exams while providing students with a user-friendly interface to take exams and view results.

## Features

### Administrator Features
- **Secure Authentication**: Password-protected admin access
- **Question Management**: Create, publish, and manage exam questions
- **Exam Control**: Start/stop exams and publish results
- **Student Management**: Search and delete student records
- **Notice Board**: Add and manage notices for students
- **System Settings**: Configure school information and admin passwords
- **Activity Logging**: Track all administrative activities with timestamps

### Student Features
- **Registration**: Simple student registration process
- **Exam Taking**: Interactive exam interface with multiple-choice questions
- **Result Viewing**: Access published exam results
- **Notice Board**: View important announcements
- **Question Search**: Browse available questions (when not active)

### System Features
- **File-based Storage**: Persistent data storage using text files
- **Real-time Updates**: Dynamic exam status management
- **Scoring System**: Automatic grading with negative marking
- **Time Tracking**: Timestamp logging for all activities
- **User-friendly Interface**: Clear menu navigation and formatted output

## Requirements

- **Operating System**: Linux/Unix (uses POSIX terminal functions)
- **Compiler**: GCC (GNU Compiler Collection), make
(command for mac : \`\`\`xcode-select --install\`\`\`, command for windows or linux : \`\`\`sudo apt update
sudo apt install build-essential\`\`\`)
- **Libraries**: Standard C libraries (stdio.h, stdlib.h, string.h, time.h, unistd.h, termios.h, ctype.h)

## Installation

1. **Clone or download the project files**
   ### If using git
   ```bash
   git clone https://github.com/hamim-24/exam-system.git
   cd exam-system
   ```

2. **Compile the project**
   #### Using the provided Makefile
   ```
   make
   ```
   
   #### Or compile manually
   ```
   gcc -Wall -Wextra -std=c99 -g -o exam_system \
   src/main.c \
   src/structures.c \
   src/utils.c \
   src/menu.c \
   src/admin.c \
   src/exam.c \
   src/student.c
   ```

3. **Run the application in bash**

   Direct run
   ```
   ./exam_system
   ```

## Usage

### First Time Setup

1. **Run the application**: \`./exam_system\`
2. **Default admin password**: \`111111\`
3. **Configure school information** through Administration → Settings
4. **Change default admin password** for security

### Administrator Workflow

1. **Login**: Select "Administration" from main menu
2. **Enter admin name**: Use predefined admin names (rabin, alex)
3. **Enter password**: Default is \`111111\`
4. **Available options**:
   - View notifications and logs
   - Create and manage questions
   - Search/delete student records
   - Manage notice board
   - Configure system settings

### Student Workflow

1. **Register**: Select "Registration" from main menu
2. **Take Exam**: Select "Exam" (when available)
3. **View Results**: Select "Result" (when published)
4. **Check Notices**: Select "Notice Board"

### Question Management

1. **Create Questions**:
   - Provide unique question code
   - Enter exam name
   - Add questions with 4 multiple-choice options
   - Specify correct answers

2. **Publish Questions**:
   - Questions must be published to become active
   - Only one exam can be active at a time
   - Students can take published exams

3. **Stop Exam**:
   - Stops active exam
   - Automatically publishes results

## File Structure

```
exam-management-system/
├── main.c              # Main application entry point 
├── utils.h             # Utility functions header
├── utils.c             # Utility functions implementation
├── menu.h              # Menu system header
├── menu.c              # Menu system implementation
├── admin.h             # Admin functions header
├── admin.c             # Admin functions implementation
├── exam.h              # Exam management header
├── exam.c              # Exam management implementation
├── student.h           # Student functions header
├── student.c           # Student functions implementation
├── structure.h         # Stuctures declaration header 
├── structure.c         # Stuctures declaration implementation
├── Makefile            # Build configuration
├── README.md           # This file
└── data/               # Generated data files (created at runtime)
    ├── AdminPassword.txt
    ├── AdminInfo.txt
    ├── QuestionSubmit.txt
    ├── ResultSubmit.txt
    ├── Notice.txt
    ├── SchoolName.txt
    ├── SchoolAddress.txt
    ├── SchoolPhone.txt
    ├── \{questionCode\}.txt
    ├── \{questionCode\}Ans.txt
    ├── \{questionCode\}Result.txt
    └── \{studentId\}Info.txt
```

## Default Credentials

- **Admin Names**: \`rabin\`, \`alex\`
- **Default Password**: \`111111\`
- **Password Requirements**: 6 characters (when changing)

## Data Files

The system creates and manages several data files:

- **AdminPassword.txt**: Stores admin password
- **AdminInfo.txt**: Logs all admin activities
- **QuestionSubmit.txt**: Tracks active exam status
- **ResultSubmit.txt**: Tracks result publication status
- **Notice.txt**: Stores notice board content
- **School\*.txt**: School information files
- **\{code\}.txt**: Question files for each exam
- **\{code\}Ans.txt**: Answer keys for exams
- **\{code\}Result.txt**: Results for each exam
- **\{id\}Info.txt**: Student information files

## Exam Rules

- Each question carries **1 point** for correct answer
- **-0.25 points** for incorrect answer
- **No penalty** for skipped questions
- Students can only take each exam **once**
- Must be registered to take exams

## Building and Cleaning


### Build the project
```
 make 
```

### Clean object files and executable
```
make clean
```

### Force rebuild
```
make clean && make
```

## Troubleshooting

### Common Issues

1. **Compilation Errors**:
   - Ensure GCC is installed
   - Check that all source files are present
   - Verify file permissions

2. **Runtime Issues**:
   - Ensure write permissions in the directory
   - Check available disk space
   - Verify terminal supports ANSI escape codes

3. **Password Issues**:
   - Default password is \`111111\`
   - Password must be exactly 6 characters when changing
   - Admin names are case-sensitive

### File Permissions

Ensure the application has read/write permissions in the directory:
\`\`\`bash
chmod 755 exam_system
chmod 644 *.txt  # For data files (if they exist)
