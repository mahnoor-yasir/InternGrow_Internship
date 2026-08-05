#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>  // For colors in Windows

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// Color definitions for Windows Console
#define RESET 7
#define RED 12
#define GREEN 10
#define YELLOW 14
#define BLUE 9
#define CYAN 11
#define MAGENTA 13
#define WHITE 15

// Structure to store student information
struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    float marks;
    char grade;
    char department[30];
    char email[50];
    char phone[15];
};

// Global array
struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void setColor(int color);
void displayHeader(const char* title, int color);
void displayMenu();
void addStudent();
void updateStudent();
void deleteStudent();
void searchStudent();
void displayAllStudents();
void calculateAverageMarks();
void displayStudentStatistics();
void sortStudents();
void saveToFile();
void loadFromFile();
void clearInputBuffer();
int isValidAge(int age);
int isValidMarks(float marks);
int findStudentById(int id);
char calculateGrade(float marks);
void displayStudentDetails(struct Student s, int color);
void printLine(int color);
void displayTopPerformers();
void displayDepartmentWise();
void updateMarks();
int countFails();

// Color function
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Print separator line
void printLine(int color) {
    setColor(color);
    printf("------------------------------------------------------------\n");
    setColor(RESET);
}

// Display header
void displayHeader(const char* title, int color) {
    system("cls");
    setColor(color);
    printf("\n");
    printf("+----------------------------------------------------------+\n");
    printf("|  %-56s |\n", title);
    printf("+----------------------------------------------------------+\n");
    setColor(RESET);
    printf("\n");
}

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Validation functions
int isValidAge(int age) {
    return (age >= 1 && age <= 100);
}

int isValidMarks(float marks) {
    return (marks >= 0 && marks <= 100);
}

// Find student by ID
int findStudentById(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Calculate grade
char calculateGrade(float marks) {
    if (marks >= 90) return 'A';
    else if (marks >= 80) return 'B';
    else if (marks >= 70) return 'C';
    else if (marks >= 60) return 'D';
    else return 'F';
}

// Display single student details
void displayStudentDetails(struct Student s, int color) {
    setColor(color);
    printf("  +--------------------------------------------------+\n");
    printf("  | ID     : %-39d |\n", s.id);
    printf("  | Name   : %-39s |\n", s.name);
    printf("  | Age    : %-39d |\n", s.age);
    printf("  | Marks  : %-39.2f |\n", s.marks);
    printf("  | Grade  : %-39c |\n", s.grade);
    printf("  | Dept   : %-39s |\n", s.department);
    printf("  | Email  : %-39s |\n", s.email);
    printf("  | Phone  : %-39s |\n", s.phone);
    printf("  +--------------------------------------------------+\n");
    setColor(RESET);
}

// Count fails
int countFails() {
    int fail = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].grade == 'F') fail++;
    }
    return fail;
}

// Display Menu
void displayMenu() {
    system("cls");
    setColor(YELLOW);
    printf("\n");
    printf("+----------------------------------------------------------+\n");
    printf("|          STUDENT RECORD MANAGEMENT SYSTEM                |\n");
    printf("|                    Main Menu                            |\n");
    printf("+----------------------------------------------------------+\n");
    setColor(RESET);

    setColor(CYAN);
    printf("\n  +--------------------------------------------------+\n");
    printf("  |  1. Add New Student                               |\n");
    printf("  |  2. Update Student Details                       |\n");
    printf("  |  3. Delete Student                               |\n");
    printf("  |  4. Search Student                               |\n");
    printf("  |  5. Display All Students                         |\n");
    printf("  |  6. Calculate Average Marks                      |\n");
    printf("  |  7. Student Statistics                           |\n");
    printf("  |  8. Sort Students                                |\n");
    printf("  |  9. Save to File                                 |\n");
    printf("  | 10. Load from File                               |\n");
    printf("  | 11. Top Performers                               |\n");
    printf("  | 12. Department-wise View                         |\n");
    printf("  | 13. Update Marks                                 |\n");
    printf("  | 14. Exit                                         |\n");
    printf("  +--------------------------------------------------+\n");
    setColor(RESET);

    setColor(GREEN);
    printf("\n  Enter your choice: ");
    setColor(RESET);
}

// Main function
int main() {
    int choice;

    loadFromFile();

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: searchStudent(); break;
            case 5: displayAllStudents(); break;
            case 6: calculateAverageMarks(); break;
            case 7: displayStudentStatistics(); break;
            case 8: sortStudents(); break;
            case 9: saveToFile(); break;
            case 10: loadFromFile(); break;
            case 11: displayTopPerformers(); break;
            case 12: displayDepartmentWise(); break;
            case 13: updateMarks(); break;
            case 14:
                setColor(YELLOW);
                printf("\n  Thank you for using Student Record Management System!\n");
                printf("  Exiting... Goodbye!\n");
                setColor(RESET);
                saveToFile();
                exit(0);
            default:
                setColor(RED);
                printf("\n  Invalid choice! Please enter a number between 1-14.\n");
                setColor(RESET);
                printf("\n  Press Enter to continue...");
                getchar();
        }
    }

    return 0;
}

// Add Student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        setColor(RED);
        printf("\n  Error: Maximum student limit reached!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    displayHeader(" ADD NEW STUDENT ", GREEN);

    struct Student newStudent;
    int id;

    printf("  Enter Student ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    if (findStudentById(id) != -1) {
        setColor(RED);
        printf("\n  Error: Student with ID %d already exists!\n", id);
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }
    newStudent.id = id;

    printf("  Enter Student Name: ");
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    do {
        printf("  Enter Student Age (1-100): ");
        scanf("%d", &newStudent.age);
        clearInputBuffer();
        if (!isValidAge(newStudent.age)) {
            setColor(RED);
            printf("  Error: Age must be between 1 and 100!\n");
            setColor(RESET);
        }
    } while (!isValidAge(newStudent.age));

    do {
        printf("  Enter Student Marks (0-100): ");
        scanf("%f", &newStudent.marks);
        clearInputBuffer();
        if (!isValidMarks(newStudent.marks)) {
            setColor(RED);
            printf("  Error: Marks must be between 0 and 100!\n");
            setColor(RESET);
        }
    } while (!isValidMarks(newStudent.marks));

    newStudent.grade = calculateGrade(newStudent.marks);

    printf("  Enter Department: ");
    fgets(newStudent.department, 30, stdin);
    newStudent.department[strcspn(newStudent.department, "\n")] = '\0';

    printf("  Enter Email: ");
    fgets(newStudent.email, 50, stdin);
    newStudent.email[strcspn(newStudent.email, "\n")] = '\0';

    printf("  Enter Phone: ");
    fgets(newStudent.phone, 15, stdin);
    newStudent.phone[strcspn(newStudent.phone, "\n")] = '\0';

    students[studentCount] = newStudent;
    studentCount++;

    setColor(GREEN);
    printf("\n  Student added successfully!\n");
    setColor(RESET);

    displayStudentDetails(newStudent, CYAN);

    printf("\n  Press Enter to continue...");
    getchar();
}

// Update Student
void updateStudent() {
    displayHeader(" UPDATE STUDENT ", YELLOW);

    int id;
    printf("  Enter Student ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = findStudentById(id);
    if (index == -1) {
        setColor(RED);
        printf("\n  Error: Student with ID %d not found!\n", id);
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    setColor(CYAN);
    printf("\n  Current Details:\n");
    displayStudentDetails(students[index], CYAN);
    setColor(RESET);

    printf("\n  Enter new details (press Enter to skip):\n");

    char newName[MAX_NAME_LENGTH];
    printf("  New Name (current: %s): ", students[index].name);
    fgets(newName, MAX_NAME_LENGTH, stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) {
        strcpy(students[index].name, newName);
    }

    int newAge;
    char ageInput[10];
    printf("  New Age (current: %d): ", students[index].age);
    fgets(ageInput, sizeof(ageInput), stdin);
    ageInput[strcspn(ageInput, "\n")] = '\0';
    if (strlen(ageInput) > 0) {
        newAge = atoi(ageInput);
        if (isValidAge(newAge)) {
            students[index].age = newAge;
        } else {
            setColor(RED);
            printf("  Invalid age! Keeping current age.\n");
            setColor(RESET);
        }
    }

    float newMarks;
    char marksInput[10];
    printf("  New Marks (current: %.2f): ", students[index].marks);
    fgets(marksInput, sizeof(marksInput), stdin);
    marksInput[strcspn(marksInput, "\n")] = '\0';
    if (strlen(marksInput) > 0) {
        newMarks = atof(marksInput);
        if (isValidMarks(newMarks)) {
            students[index].marks = newMarks;
            students[index].grade = calculateGrade(newMarks);
        } else {
            setColor(RED);
            printf("  Invalid marks! Keeping current marks.\n");
            setColor(RESET);
        }
    }

    char newDept[30];
    printf("  New Department (current: %s): ", students[index].department);
    fgets(newDept, 30, stdin);
    newDept[strcspn(newDept, "\n")] = '\0';
    if (strlen(newDept) > 0) {
        strcpy(students[index].department, newDept);
    }

    setColor(GREEN);
    printf("\n  Student record updated successfully!\n");
    setColor(RESET);

    printf("\n  Press Enter to continue...");
    getchar();
}

// Delete Student
void deleteStudent() {
    displayHeader(" DELETE STUDENT ", RED);

    int id;
    printf("  Enter Student ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = findStudentById(id);
    if (index == -1) {
        setColor(RED);
        printf("\n  Error: Student with ID %d not found!\n", id);
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    setColor(YELLOW);
    printf("\n  Are you sure you want to delete this student?\n");
    setColor(RESET);
    displayStudentDetails(students[index], RED);

    printf("\n  Enter 'Y' to confirm deletion: ");
    char confirm;
    scanf("%c", &confirm);
    clearInputBuffer();

    if (confirm == 'Y' || confirm == 'y') {
        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        setColor(GREEN);
        printf("\n  Student deleted successfully!\n");
        setColor(RESET);
    } else {
        setColor(YELLOW);
        printf("\n  Deletion cancelled.\n");
        setColor(RESET);
    }

    printf("\n  Press Enter to continue...");
    getchar();
}

// Search Student
void searchStudent() {
    displayHeader(" SEARCH STUDENT ", BLUE);

    if (studentCount == 0) {
        setColor(RED);
        printf("\n  No students in the system!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    int id;
    printf("  Enter Student ID to search: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = findStudentById(id);
    if (index == -1) {
        setColor(RED);
        printf("\n  Student with ID %d not found!\n", id);
        setColor(RESET);
    } else {
        setColor(GREEN);
        printf("\n  Student Found!\n");
        setColor(RESET);
        displayStudentDetails(students[index], CYAN);
    }

    printf("\n  Press Enter to continue...");
    getchar();
}

// Display All Students
void displayAllStudents() {
    displayHeader(" ALL STUDENTS ", CYAN);

    if (studentCount == 0) {
        setColor(RED);
        printf("\n  No students in the system!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    setColor(YELLOW);
    printf("  +----+-------------------+-----+---------+-------+------------+\n");
    printf("  | ID | Name              | Age | Marks   | Grade | Dept       |\n");
    printf("  +----+-------------------+-----+---------+-------+------------+\n");
    setColor(RESET);

    for (int i = 0; i < studentCount; i++) {
        int color = (i % 2 == 0) ? CYAN : WHITE;
        setColor(color);
        printf("  | %-2d | %-17s | %-3d | %-7.2f |   %c   | %-10s |\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].marks,
               students[i].grade,
               students[i].department);
        setColor(RESET);
    }

    setColor(YELLOW);
    printf("  +----+-------------------+-----+---------+-------+------------+\n");
    setColor(GREEN);
    printf("  Total Students: %d\n", studentCount);
    setColor(RESET);

    printf("\n  Press Enter to continue...");
    getchar();
}

// Calculate Average Marks
void calculateAverageMarks() {
    displayHeader(" AVERAGE MARKS ", MAGENTA);

    if (studentCount == 0) {
        setColor(RED);
        printf("\n  No students in the system!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    float totalMarks = 0;
    float highest = students[0].marks;
    float lowest = students[0].marks;
    int highestID = students[0].id;
    int lowestID = students[0].id;
    int gradeCount[5] = {0};

    for (int i = 0; i < studentCount; i++) {
        totalMarks += students[i].marks;

        if (students[i].marks > highest) {
            highest = students[i].marks;
            highestID = students[i].id;
        }
        if (students[i].marks < lowest) {
            lowest = students[i].marks;
            lowestID = students[i].id;
        }

        switch(students[i].grade) {
            case 'A': gradeCount[0]++; break;
            case 'B': gradeCount[1]++; break;
            case 'C': gradeCount[2]++; break;
            case 'D': gradeCount[3]++; break;
            case 'F': gradeCount[4]++; break;
        }
    }

    float average = totalMarks / studentCount;

    setColor(YELLOW);
    printf("  +--------------------------------------------------+\n");
    printf("  |              MARKS STATISTICS                    |\n");
    printf("  +--------------------------------------------------+\n");
    setColor(RESET);

    setColor(CYAN);
    printf("  | Total Students    : %-31d |\n", studentCount);
    printf("  | Average Marks     : %-31.2f |\n", average);
    setColor(GREEN);
    printf("  | Highest Marks     : %-31.2f |\n", highest);
    printf("  | Highest Student ID: %-31d |\n", highestID);
    setColor(RED);
    printf("  | Lowest Marks      : %-31.2f |\n", lowest);
    printf("  | Lowest Student ID : %-31d |\n", lowestID);
    setColor(RESET);

    setColor(YELLOW);
    printf("  +--------------------------------------------------+\n");
    printf("  | GRADE DISTRIBUTION                               |\n");
    printf("  +--------------------------------------------------+\n");
    setColor(RESET);

    setColor(GREEN);
    printf("  | A (90-100) : %-29d |\n", gradeCount[0]);
    setColor(CYAN);
    printf("  | B (80-89)  : %-29d |\n", gradeCount[1]);
    setColor(BLUE);
    printf("  | C (70-79)  : %-29d |\n", gradeCount[2]);
    setColor(YELLOW);
    printf("  | D (60-69)  : %-29d |\n", gradeCount[3]);
    setColor(RED);
    printf("  | F (0-59)   : %-29d |\n", gradeCount[4]);
    setColor(RESET);

    setColor(YELLOW);
    printf("  +--------------------------------------------------+\n");
    setColor(RESET);

    printf("\n  Press Enter to continue...");
    getchar();
}

// Student Statistics
void displayStudentStatistics() {
    displayHeader(" STUDENT STATISTICS ", MAGENTA);

    if (studentCount == 0) {
        setColor(RED);
        printf("\n  No students in the system!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    int totalAge = 0;
    for (int i = 0; i < studentCount; i++) {
        totalAge += students[i].age;
    }

    int passCount = studentCount - countFails();
    float passPercentage = (float)passCount / studentCount * 100;

    setColor(CYAN);
    printf("\n  +--------------------------------------------------+\n");
    printf("  |            STUDENT STATISTICS                    |\n");
    printf("  +--------------------------------------------------+\n");
    printf("  | Total Students : %-31d |\n", studentCount);
    printf("  | Average Age    : %-31.2f |\n", (float)totalAge / studentCount);
    printf("  | Passed Students: %-31d |\n", passCount);
    printf("  | Failed Students: %-31d |\n", countFails());
    printf("  | Pass Percentage: %-31.2f%% |\n", passPercentage);
    printf("  +--------------------------------------------------+\n");
    setColor(RESET);

    printf("\n  Press Enter to continue...");
    getchar();
}

// Sort Students
void sortStudents() {
    displayHeader(" SORT STUDENTS ", BLUE);

    if (studentCount == 0) {
        setColor(RED);
        printf("\n  No students in the system!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    int choice;
    setColor(YELLOW);
    printf("  1. Sort by ID\n");
    printf("  2. Sort by Name\n");
    printf("  3. Sort by Marks (Highest to Lowest)\n");
    printf("  4. Sort by Age\n");
    setColor(RESET);
    printf("  Enter choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    struct Student temp;

    switch(choice) {
        case 1:
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = i + 1; j < studentCount; j++) {
                    if (students[i].id > students[j].id) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            setColor(GREEN);
            printf("\n  Sorted by ID successfully!\n");
            setColor(RESET);
            break;
        case 2:
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = i + 1; j < studentCount; j++) {
                    if (strcmp(students[i].name, students[j].name) > 0) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            setColor(GREEN);
            printf("\n  Sorted by Name successfully!\n");
            setColor(RESET);
            break;
        case 3:
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = i + 1; j < studentCount; j++) {
                    if (students[i].marks < students[j].marks) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            setColor(GREEN);
            printf("\n  Sorted by Marks successfully!\n");
            setColor(RESET);
            break;
        case 4:
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = i + 1; j < studentCount; j++) {
                    if (students[i].age > students[j].age) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            setColor(GREEN);
            printf("\n  Sorted by Age successfully!\n");
            setColor(RESET);
            break;
        default:
            setColor(RED);
            printf("\n  Invalid choice!\n");
            setColor(RESET);
    }

    displayAllStudents();
    printf("\n  Press Enter to continue...");
    getchar();
}

// Save to File
void saveToFile() {
    displayHeader(" SAVE TO FILE ", GREEN);

    FILE *file = fopen("students_data.txt", "w");
    if (file == NULL) {
        setColor(RED);
        printf("\n  Error opening file for writing!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    fprintf(file, "%d\n", studentCount);
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%d\n%s\n%d\n%.2f\n%s\n%s\n%s\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].marks,
                students[i].department,
                students[i].email,
                students[i].phone);
    }

    fclose(file);
    setColor(GREEN);
    printf("\n  Data saved successfully to 'students_data.txt'!\n");
    setColor(RESET);

    printf("\n  Press Enter to continue...");
    getchar();
}

// Load from File
void loadFromFile() {
    displayHeader(" LOAD FROM FILE ", CYAN);

    FILE *file = fopen("students_data.txt", "r");
    if (file == NULL) {
        setColor(YELLOW);
        printf("\n  No saved data found. Starting with empty database.\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    fscanf(file, "%d\n", &studentCount);
    for (int i = 0; i < studentCount; i++) {
        fscanf(file, "%d\n", &students[i].id);
        fgets(students[i].name, MAX_NAME_LENGTH, file);
        students[i].name[strcspn(students[i].name, "\n")] = '\0';
        fscanf(file, "%d\n", &students[i].age);
        fscanf(file, "%f\n", &students[i].marks);
        fgets(students[i].department, 30, file);
        students[i].department[strcspn(students[i].department, "\n")] = '\0';
        fgets(students[i].email, 50, file);
        students[i].email[strcspn(students[i].email, "\n")] = '\0';
        fgets(students[i].phone, 15, file);
        students[i].phone[strcspn(students[i].phone, "\n")] = '\0';
        students[i].grade = calculateGrade(students[i].marks);
    }

    fclose(file);
    setColor(GREEN);
    printf("\n  Data loaded successfully! %d students loaded.\n", studentCount);
    setColor(RESET);

    printf("\n  Press Enter to continue...");
    getchar();
}

// Top Performers
void displayTopPerformers() {
    displayHeader(" TOP PERFORMERS ", GREEN);

    if (studentCount == 0) {
        setColor(RED);
        printf("\n  No students in the system!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    struct Student temp[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++) {
        temp[i] = students[i];
    }

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (temp[i].marks < temp[j].marks) {
                struct Student t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int topN = (studentCount < 5) ? studentCount : 5;

    setColor(YELLOW);
    printf("\n  TOP %d STUDENTS\n", topN);
    printf("  +------+-------------------+---------+----------+\n");
    printf("  | Rank | Name              | Marks   | Grade    |\n");
    printf("  +------+-------------------+---------+----------+\n");
    setColor(RESET);

    for (int i = 0; i < topN; i++) {
        int color = (i == 0) ? GREEN : (i == 1) ? CYAN : BLUE;
        setColor(color);
        printf("  |  %-2d  | %-17s | %-7.2f |    %c     |\n",
               i+1, temp[i].name, temp[i].marks, temp[i].grade);
        setColor(RESET);
    }

    setColor(YELLOW);
    printf("  +------+-------------------+---------+----------+\n");
    setColor(RESET);

    printf("\n  Press Enter to continue...");
    getchar();
}

// Department-wise View
void displayDepartmentWise() {
    displayHeader(" DEPARTMENT-WISE VIEW ", MAGENTA);

    if (studentCount == 0) {
        setColor(RED);
        printf("\n  No students in the system!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    char departments[10][30];
    int deptCount = 0;

    for (int i = 0; i < studentCount; i++) {
        int found = 0;
        for (int j = 0; j < deptCount; j++) {
            if (strcmp(students[i].department, departments[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(departments[deptCount], students[i].department);
            deptCount++;
        }
    }

    for (int d = 0; d < deptCount; d++) {
        setColor(YELLOW);
        printf("\n  Department: %s\n", departments[d]);
        printf("  +----+-------------------+-----+---------+-------+\n");
        printf("  | ID | Name              | Age | Marks   | Grade |\n");
        printf("  +----+-------------------+-----+---------+-------+\n");
        setColor(RESET);

        int count = 0;
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].department, departments[d]) == 0) {
                int color = (count % 2 == 0) ? CYAN : WHITE;
                setColor(color);
                printf("  | %-2d | %-17s | %-3d | %-7.2f |   %c   |\n",
                       students[i].id, students[i].name,
                       students[i].age, students[i].marks, students[i].grade);
                setColor(RESET);
                count++;
            }
        }

        setColor(YELLOW);
        printf("  +----+-------------------+-----+---------+-------+\n");
        setColor(CYAN);
        printf("  Total Students in %s: %d\n", departments[d], count);
        setColor(RESET);
    }

    printf("\n  Press Enter to continue...");
    getchar();
}

// Update Marks
void updateMarks() {
    displayHeader(" UPDATE MARKS ", YELLOW);

    if (studentCount == 0) {
        setColor(RED);
        printf("\n  No students in the system!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    int id;
    printf("  Enter Student ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = findStudentById(id);
    if (index == -1) {
        setColor(RED);
        printf("\n  Student not found!\n");
        setColor(RESET);
        printf("\n  Press Enter to continue...");
        getchar();
        return;
    }

    setColor(CYAN);
    printf("\n  Current Marks: %.2f (Grade: %c)\n",
           students[index].marks, students[index].grade);
    setColor(RESET);

    float newMarks;
    printf("  Enter New Marks (0-100): ");
    scanf("%f", &newMarks);
    clearInputBuffer();

    if (isValidMarks(newMarks)) {
        students[index].marks = newMarks;
        students[index].grade = calculateGrade(newMarks);
        setColor(GREEN);
        printf("\n  Marks updated successfully!\n");
        printf("  New Grade: %c\n", students[index].grade);
        setColor(RESET);
    } else {
        setColor(RED);
        printf("\n  Invalid marks! Please enter between 0-100.\n");
        setColor(RESET);
    }

    printf("\n  Press Enter to continue...");
    getchar();
}
