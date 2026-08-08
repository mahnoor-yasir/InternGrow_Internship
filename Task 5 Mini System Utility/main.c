#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN() system("cls")
#else
    #include <unistd.h>
    #define CLEAR_SCREEN() system("clear")
#endif

// Color codes for Windows console
#ifdef _WIN32
    #define RESET_COLOR() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
    #define SET_COLOR(c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c)
#else
    #define RESET_COLOR() printf("\033[0m")
    #define SET_COLOR(c) printf("\033[%dm", c)
#endif

// Color constants
#define COLOR_WHITE 7
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_CYAN 11
#define COLOR_RED 12
#define COLOR_MAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_BRIGHT_WHITE 15

// Structure for a single contact
typedef struct Contact {
    int id;
    char firstName[50];
    char lastName[50];
    char phone[20];
    char email[100];
    char address[200];
    char category[30];
    char birthday[20];
    char notes[200];
    struct Contact* next;
} Contact;

// Structure for managing contacts
typedef struct {
    Contact* head;
    int totalContacts;
    int nextId;
    char dataFile[100];
    char backupFile[100];
    char logFile[100];
} ContactManager;

// Function prototypes
void initializeManager(ContactManager* manager);
void displayMenu(int screenIndex);
int getChoice();
void addContact(ContactManager* manager);
void viewAllContacts(ContactManager* manager);
void searchContact(ContactManager* manager);
void updateContact(ContactManager* manager);
void deleteContact(ContactManager* manager);
void generateReport(ContactManager* manager);
void backupData(ContactManager* manager);
void restoreData(ContactManager* manager);
void viewErrorLogs(ContactManager* manager);
void saveToFile(ContactManager* manager);
void loadFromFile(ContactManager* manager);
void logError(const char* message);
void freeMemory(ContactManager* manager);
int isValidPhone(const char* phone);
int isValidEmail(const char* email);
void toLowerCase(char* str);
void clearInputBuffer();
void displayContact(Contact* contact);
void displayHeader(const char* title, int color);
void displayDivider(int color);

// Global variables
int currentScreenColor = COLOR_WHITE;
char logFilePath[100] = "error_logs.txt";

// Main function
int main() {
    ContactManager manager;
    initializeManager(&manager);

    int screenIndex = 0;
    int choice;

    // Load existing data
    loadFromFile(&manager);

    do {
        currentScreenColor = (screenIndex % 6) + 9; // Cycle through colors 9-14
        displayMenu(screenIndex);
        choice = getChoice();

        switch(choice) {
            case 1:
                addContact(&manager);
                screenIndex++;
                break;
            case 2:
                viewAllContacts(&manager);
                screenIndex++;
                break;
            case 3:
                searchContact(&manager);
                screenIndex++;
                break;
            case 4:
                updateContact(&manager);
                screenIndex++;
                break;
            case 5:
                deleteContact(&manager);
                screenIndex++;
                break;
            case 6:
                generateReport(&manager);
                screenIndex++;
                break;
            case 7:
                backupData(&manager);
                screenIndex++;
                break;
            case 8:
                restoreData(&manager);
                screenIndex++;
                break;
            case 9:
                viewErrorLogs(&manager);
                screenIndex++;
                break;
            case 0:
                printf("\n");
                SET_COLOR(COLOR_YELLOW);
                printf("Saving data and exiting...\n");
                RESET_COLOR();
                saveToFile(&manager);
                freeMemory(&manager);
                printf("Goodbye!\n");
                break;
            default:
                SET_COLOR(COLOR_RED);
                printf("Invalid choice! Please try again.\n");
                RESET_COLOR();
                sleep(1);
        }
    } while(choice != 0);

    return 0;
}

// Initialize the contact manager
void initializeManager(ContactManager* manager) {
    manager->head = NULL;
    manager->totalContacts = 0;
    manager->nextId = 1;
    strcpy(manager->dataFile, "contacts_data.txt");
    strcpy(manager->backupFile, "contacts_backup.txt");
    strcpy(manager->logFile, "error_logs.txt");
}

// Display colorful menu
void displayMenu(int screenIndex) {
    CLEAR_SCREEN();

    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    #endif

    int headerColor = (screenIndex % 6) + 9;
    int menuColor = ((screenIndex + 2) % 6) + 9;
    int borderColor = ((screenIndex + 4) % 6) + 9;

    SET_COLOR(borderColor);
    printf("\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                                                           |\n");

    SET_COLOR(headerColor);
    printf("|               CONTACT MANAGEMENT SYSTEM                   |\n");

    SET_COLOR(borderColor);
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                                                           |\n");

    SET_COLOR(menuColor);
    printf("|   [1] Add New Contact          [2] View All Contacts      |\n");
    printf("|   [3] Search Contacts          [4] Update Contact         |\n");
    printf("|   [5] Delete Contact           [6] Generate Report        |\n");
    printf("|   [7] Backup Data              [8] Restore Data           |\n");
    printf("|   [9] View Error Logs          [0] Exit                   |\n");

    SET_COLOR(borderColor);
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");

    SET_COLOR(COLOR_BRIGHT_WHITE);
    printf("\n");
    printf("Enter your choice: ");
    RESET_COLOR();
}

// Get user choice with validation
int getChoice() {
    int choice;
    char input[10];

    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &choice) != 1) {
        return -1;
    }
    return choice;
}

// Validate phone number
int isValidPhone(const char* phone) {
    if (strlen(phone) < 10 || strlen(phone) > 15) return 0;

    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isdigit(phone[i]) && phone[i] != '-' && phone[i] != '+') {
            return 0;
        }
    }
    return 1;
}

// Validate email
int isValidEmail(const char* email) {
    int atCount = 0;
    int dotCount = 0;
    int len = strlen(email);

    if (len < 5) return 0;

    for (int i = 0; i < len; i++) {
        if (email[i] == '@') atCount++;
        if (email[i] == '.') dotCount++;
    }

    return (atCount == 1 && dotCount >= 1);
}

// Convert string to lowercase
void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Add a new contact
void addContact(ContactManager* manager) {
    SET_COLOR(COLOR_GREEN);
    printf("\n--- ADD NEW CONTACT ---\n\n");
    RESET_COLOR();

    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (!newContact) {
        logError("Memory allocation failed for new contact");
        SET_COLOR(COLOR_RED);
        printf("Error: Memory allocation failed!\n");
        RESET_COLOR();
        return;
    }

    newContact->id = manager->nextId++;
    newContact->next = NULL;

    SET_COLOR(COLOR_CYAN);
    printf("Contact ID: %d\n\n", newContact->id);
    RESET_COLOR();

    SET_COLOR(COLOR_YELLOW);
    printf("First Name: ");
    RESET_COLOR();
    fgets(newContact->firstName, sizeof(newContact->firstName), stdin);
    newContact->firstName[strcspn(newContact->firstName, "\n")] = '\0';

    printf("Last Name: ");
    fgets(newContact->lastName, sizeof(newContact->lastName), stdin);
    newContact->lastName[strcspn(newContact->lastName, "\n")] = '\0';

    do {
        printf("Phone Number (10-15 digits): ");
        fgets(newContact->phone, sizeof(newContact->phone), stdin);
        newContact->phone[strcspn(newContact->phone, "\n")] = '\0';

        if (!isValidPhone(newContact->phone)) {
            SET_COLOR(COLOR_RED);
            printf("Invalid phone number! Please enter valid phone number.\n");
            RESET_COLOR();
        }
    } while (!isValidPhone(newContact->phone));

    do {
        printf("Email Address: ");
        fgets(newContact->email, sizeof(newContact->email), stdin);
        newContact->email[strcspn(newContact->email, "\n")] = '\0';

        if (!isValidEmail(newContact->email)) {
            SET_COLOR(COLOR_RED);
            printf("Invalid email address! Please enter valid email.\n");
            RESET_COLOR();
        }
    } while (!isValidEmail(newContact->email));

    printf("Address: ");
    fgets(newContact->address, sizeof(newContact->address), stdin);
    newContact->address[strcspn(newContact->address, "\n")] = '\0';

    printf("Category (Family/Friend/Work/Other): ");
    fgets(newContact->category, sizeof(newContact->category), stdin);
    newContact->category[strcspn(newContact->category, "\n")] = '\0';

    printf("Birthday (DD/MM/YYYY): ");
    fgets(newContact->birthday, sizeof(newContact->birthday), stdin);
    newContact->birthday[strcspn(newContact->birthday, "\n")] = '\0';

    printf("Notes: ");
    fgets(newContact->notes, sizeof(newContact->notes), stdin);
    newContact->notes[strcspn(newContact->notes, "\n")] = '\0';

    if (manager->head == NULL) {
        manager->head = newContact;
    } else {
        Contact* current = manager->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newContact;
    }

    manager->totalContacts++;
    saveToFile(manager);

    SET_COLOR(COLOR_GREEN);
    printf("\n[SUCCESS] Contact added successfully! (ID: %d)\n", newContact->id);
    RESET_COLOR();

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// View all contacts with pagination
void viewAllContacts(ContactManager* manager) {
    if (manager->head == NULL) {
        SET_COLOR(COLOR_YELLOW);
        printf("\nNo contacts found!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    SET_COLOR(COLOR_BLUE);
    printf("\n--- ALL CONTACTS ---\n\n");
    RESET_COLOR();

    Contact* current = manager->head;
    int count = 0;
    int colorIndex = 0;
    int colors[] = {COLOR_CYAN, COLOR_GREEN, COLOR_MAGENTA, COLOR_YELLOW};

    while (current != NULL) {
        SET_COLOR(colors[colorIndex % 4]);
        printf("+-------------------------------------------------+\n");
        printf("| ID: %-5d | Name: %s %s\n", current->id, current->firstName, current->lastName);
        printf("| Phone: %-15s | Email: %s\n", current->phone, current->email);
        printf("| Category: %-10s | Birthday: %s\n", current->category, current->birthday);
        printf("| Address: %s\n", current->address);
        if (strlen(current->notes) > 0) {
            printf("| Notes: %s\n", current->notes);
        }
        printf("+-------------------------------------------------+\n\n");
        RESET_COLOR();

        current = current->next;
        count++;
        colorIndex++;

        if (count % 5 == 0 && current != NULL) {
            SET_COLOR(COLOR_YELLOW);
            printf("Press Enter to see more contacts...");
            RESET_COLOR();
            clearInputBuffer();
            CLEAR_SCREEN();
        }
    }

    SET_COLOR(COLOR_CYAN);
    printf("\nTotal Contacts: %d\n", manager->totalContacts);
    RESET_COLOR();

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Search contacts
void searchContact(ContactManager* manager) {
    if (manager->head == NULL) {
        SET_COLOR(COLOR_YELLOW);
        printf("\nNo contacts to search!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    int searchChoice;
    char searchTerm[100];
    int found = 0;

    SET_COLOR(COLOR_MAGENTA);
    printf("\n--- SEARCH CONTACTS ---\n\n");
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Category\n");
    printf("Enter choice: ");
    RESET_COLOR();

    scanf("%d", &searchChoice);
    clearInputBuffer();

    printf("Enter search term: ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0';

    char searchLower[100];
    strcpy(searchLower, searchTerm);
    toLowerCase(searchLower);

    Contact* current = manager->head;
    int colorIndex = 0;
    int colors[] = {COLOR_CYAN, COLOR_GREEN, COLOR_MAGENTA};

    SET_COLOR(COLOR_CYAN);
    printf("\n--- SEARCH RESULTS ---\n\n");
    RESET_COLOR();

    while (current != NULL) {
        char firstNameLower[50], lastNameLower[50], phoneLower[20];
        char emailLower[100], categoryLower[30];

        strcpy(firstNameLower, current->firstName);
        strcpy(lastNameLower, current->lastName);
        strcpy(phoneLower, current->phone);
        strcpy(emailLower, current->email);
        strcpy(categoryLower, current->category);

        toLowerCase(firstNameLower);
        toLowerCase(lastNameLower);
        toLowerCase(phoneLower);
        toLowerCase(emailLower);
        toLowerCase(categoryLower);

        int match = 0;
        switch(searchChoice) {
            case 1:
                if (strstr(firstNameLower, searchLower) || strstr(lastNameLower, searchLower))
                    match = 1;
                break;
            case 2:
                if (strstr(phoneLower, searchLower)) match = 1;
                break;
            case 3:
                if (strstr(emailLower, searchLower)) match = 1;
                break;
            case 4:
                if (strstr(categoryLower, searchLower)) match = 1;
                break;
            default:
                SET_COLOR(COLOR_RED);
                printf("Invalid search option!\n");
                RESET_COLOR();
                printf("\nPress Enter to continue...");
                clearInputBuffer();
                return;
        }

        if (match) {
            SET_COLOR(colors[colorIndex % 3]);
            printf("+-------------------------------------------------+\n");
            printf("| ID: %-5d | Name: %s %s\n", current->id, current->firstName, current->lastName);
            printf("| Phone: %-15s | Email: %s\n", current->phone, current->email);
            printf("| Category: %-10s | Birthday: %s\n", current->category, current->birthday);
            printf("| Address: %s\n", current->address);
            if (strlen(current->notes) > 0) {
                printf("| Notes: %s\n", current->notes);
            }
            printf("+-------------------------------------------------+\n\n");
            RESET_COLOR();
            found++;
            colorIndex++;
        }
        current = current->next;
    }

    if (found == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("No contacts found matching '%s'\n", searchTerm);
        RESET_COLOR();
    } else {
        SET_COLOR(COLOR_GREEN);
        printf("Found %d contact(s)\n", found);
        RESET_COLOR();
    }

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Update a contact
void updateContact(ContactManager* manager) {
    if (manager->head == NULL) {
        SET_COLOR(COLOR_YELLOW);
        printf("\nNo contacts to update!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    int id;
    SET_COLOR(COLOR_YELLOW);
    printf("\n--- UPDATE CONTACT ---\n\n");
    printf("Enter contact ID to update: ");
    RESET_COLOR();
    scanf("%d", &id);
    clearInputBuffer();

    Contact* current = manager->head;
    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        SET_COLOR(COLOR_RED);
        printf("Contact with ID %d not found!\n", id);
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    SET_COLOR(COLOR_CYAN);
    printf("\nCurrent details:\n");
    printf("Name: %s %s\n", current->firstName, current->lastName);
    printf("Phone: %s\n", current->phone);
    printf("Email: %s\n", current->email);
    printf("Address: %s\n", current->address);
    printf("Category: %s\n", current->category);
    printf("Birthday: %s\n", current->birthday);
    printf("Notes: %s\n", current->notes);
    RESET_COLOR();

    SET_COLOR(COLOR_YELLOW);
    printf("\nWhich field to update?\n");
    printf("1. First Name\n");
    printf("2. Last Name\n");
    printf("3. Phone\n");
    printf("4. Email\n");
    printf("5. Address\n");
    printf("6. Category\n");
    printf("7. Birthday\n");
    printf("8. Notes\n");
    printf("Enter choice: ");
    RESET_COLOR();

    int fieldChoice;
    scanf("%d", &fieldChoice);
    clearInputBuffer();

    printf("Enter new value: ");
    char newValue[200];
    fgets(newValue, sizeof(newValue), stdin);
    newValue[strcspn(newValue, "\n")] = '\0';

    switch(fieldChoice) {
        case 1: strcpy(current->firstName, newValue); break;
        case 2: strcpy(current->lastName, newValue); break;
        case 3:
            if (isValidPhone(newValue)) {
                strcpy(current->phone, newValue);
            } else {
                SET_COLOR(COLOR_RED);
                printf("Invalid phone number!\n");
                RESET_COLOR();
                printf("\nPress Enter to continue...");
                clearInputBuffer();
                return;
            }
            break;
        case 4:
            if (isValidEmail(newValue)) {
                strcpy(current->email, newValue);
            } else {
                SET_COLOR(COLOR_RED);
                printf("Invalid email address!\n");
                RESET_COLOR();
                printf("\nPress Enter to continue...");
                clearInputBuffer();
                return;
            }
            break;
        case 5: strcpy(current->address, newValue); break;
        case 6: strcpy(current->category, newValue); break;
        case 7: strcpy(current->birthday, newValue); break;
        case 8: strcpy(current->notes, newValue); break;
        default:
            SET_COLOR(COLOR_RED);
            printf("Invalid option!\n");
            RESET_COLOR();
            printf("\nPress Enter to continue...");
            clearInputBuffer();
            return;
    }

    saveToFile(manager);
    SET_COLOR(COLOR_GREEN);
    printf("\n[SUCCESS] Contact updated successfully!\n");
    RESET_COLOR();

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Delete a contact
void deleteContact(ContactManager* manager) {
    if (manager->head == NULL) {
        SET_COLOR(COLOR_YELLOW);
        printf("\nNo contacts to delete!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    int id;
    SET_COLOR(COLOR_RED);
    printf("\n--- DELETE CONTACT ---\n\n");
    printf("Enter contact ID to delete: ");
    RESET_COLOR();
    scanf("%d", &id);
    clearInputBuffer();

    Contact* current = manager->head;
    Contact* previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        SET_COLOR(COLOR_RED);
        printf("Contact with ID %d not found!\n", id);
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    char confirm;
    SET_COLOR(COLOR_YELLOW);
    printf("Are you sure you want to delete contact '%s %s'? (y/n): ",
           current->firstName, current->lastName);
    RESET_COLOR();
    scanf("%c", &confirm);
    clearInputBuffer();

    if (tolower(confirm) != 'y') {
        printf("Deletion cancelled.\n");
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    if (previous == NULL) {
        manager->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    manager->totalContacts--;
    saveToFile(manager);

    SET_COLOR(COLOR_GREEN);
    printf("\n[SUCCESS] Contact deleted successfully!\n");
    RESET_COLOR();

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Generate report
void generateReport(ContactManager* manager) {
    if (manager->head == NULL) {
        SET_COLOR(COLOR_YELLOW);
        printf("\nNo contacts to generate report!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    SET_COLOR(COLOR_MAGENTA);
    printf("\n--- CONTACT REPORT ---\n\n");
    RESET_COLOR();

    int family = 0, friend = 0, work = 0, other = 0;
    Contact* current = manager->head;

    while (current != NULL) {
        char categoryLower[30];
        strcpy(categoryLower, current->category);
        toLowerCase(categoryLower);

        if (strstr(categoryLower, "family")) family++;
        else if (strstr(categoryLower, "friend")) friend++;
        else if (strstr(categoryLower, "work")) work++;
        else other++;
        current = current->next;
    }

    SET_COLOR(COLOR_CYAN);
    printf("+-------------------------------------------+\n");
    printf("|         CONTACT STATISTICS                 |\n");
    printf("+-------------------------------------------+\n");
    printf("| Total Contacts: %-22d |\n", manager->totalContacts);
    printf("|                                           |\n");
    printf("| By Category:                              |\n");
    printf("|   Family:   %-22d |\n", family);
    printf("|   Friend:   %-22d |\n", friend);
    printf("|   Work:     %-22d |\n", work);
    printf("|   Other:    %-22d |\n", other);
    printf("+-------------------------------------------+\n");
    RESET_COLOR();

    FILE* reportFile = fopen("contact_report.txt", "w");
    if (reportFile) {
        time_t t = time(NULL);
        struct tm* tm = localtime(&t);

        fprintf(reportFile, "CONTACT MANAGEMENT SYSTEM REPORT\n");
        fprintf(reportFile, "Generated: %s", asctime(tm));
        fprintf(reportFile, "=================================\n\n");
        fprintf(reportFile, "Total Contacts: %d\n\n", manager->totalContacts);
        fprintf(reportFile, "Category Breakdown:\n");
        fprintf(reportFile, "  Family: %d\n", family);
        fprintf(reportFile, "  Friend: %d\n", friend);
        fprintf(reportFile, "  Work: %d\n", work);
        fprintf(reportFile, "  Other: %d\n\n", other);

        fprintf(reportFile, "Contact List:\n");
        fprintf(reportFile, "=================================\n");
        current = manager->head;
        while (current != NULL) {
            fprintf(reportFile, "ID: %d | Name: %s %s\n", current->id,
                    current->firstName, current->lastName);
            fprintf(reportFile, "Phone: %s | Email: %s\n", current->phone, current->email);
            fprintf(reportFile, "Category: %s | Birthday: %s\n", current->category, current->birthday);
            fprintf(reportFile, "Address: %s\n", current->address);
            if (strlen(current->notes) > 0) {
                fprintf(reportFile, "Notes: %s\n", current->notes);
            }
            fprintf(reportFile, "---------------------------------\n");
            current = current->next;
        }
        fclose(reportFile);
        SET_COLOR(COLOR_GREEN);
        printf("\n[SUCCESS] Report saved to 'contact_report.txt'\n");
        RESET_COLOR();
    } else {
        logError("Failed to create report file");
        SET_COLOR(COLOR_RED);
        printf("\nError: Could not save report!\n");
        RESET_COLOR();
    }

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Backup data
void backupData(ContactManager* manager) {
    SET_COLOR(COLOR_CYAN);
    printf("\n--- BACKUP DATA ---\n\n");
    RESET_COLOR();

    char backupFile[100];
    strcpy(backupFile, manager->backupFile);

    FILE* source = fopen(manager->dataFile, "r");
    if (source == NULL) {
        SET_COLOR(COLOR_RED);
        printf("No data file found to backup!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    FILE* dest = fopen(backupFile, "w");
    if (dest == NULL) {
        fclose(source);
        logError("Failed to create backup file");
        SET_COLOR(COLOR_RED);
        printf("Error creating backup!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    char ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);

    SET_COLOR(COLOR_GREEN);
    printf("[SUCCESS] Backup created successfully: %s\n", backupFile);
    RESET_COLOR();

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Restore data
void restoreData(ContactManager* manager) {
    SET_COLOR(COLOR_YELLOW);
    printf("\n--- RESTORE DATA ---\n\n");
    RESET_COLOR();

    char backupFile[100];
    strcpy(backupFile, manager->backupFile);

    FILE* source = fopen(backupFile, "r");
    if (source == NULL) {
        SET_COLOR(COLOR_RED);
        printf("No backup file found!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    char confirm;
    SET_COLOR(COLOR_YELLOW);
    printf("Restoring will overwrite current data. Continue? (y/n): ");
    RESET_COLOR();
    scanf("%c", &confirm);
    clearInputBuffer();

    if (tolower(confirm) != 'y') {
        fclose(source);
        printf("Restore cancelled.\n");
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    FILE* dest = fopen(manager->dataFile, "w");
    if (dest == NULL) {
        fclose(source);
        logError("Failed to restore data");
        SET_COLOR(COLOR_RED);
        printf("Error restoring data!\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    char ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);

    freeMemory(manager);
    initializeManager(manager);
    loadFromFile(manager);

    SET_COLOR(COLOR_GREEN);
    printf("[SUCCESS] Data restored successfully!\n");
    RESET_COLOR();

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// View error logs
void viewErrorLogs(ContactManager* manager) {
    SET_COLOR(COLOR_RED);
    printf("\n--- ERROR LOGS ---\n\n");
    RESET_COLOR();

    FILE* logFile = fopen(manager->logFile, "r");
    if (logFile == NULL) {
        SET_COLOR(COLOR_YELLOW);
        printf("No error logs found.\n");
        RESET_COLOR();
        printf("\nPress Enter to continue...");
        clearInputBuffer();
        return;
    }

    char line[256];
    int count = 0;

    SET_COLOR(COLOR_YELLOW);
    printf("Recent error logs:\n");
    printf("=================================\n\n");
    RESET_COLOR();

    while (fgets(line, sizeof(line), logFile)) {
        count++;
        SET_COLOR(COLOR_RED);
        printf("%d. %s", count, line);
        RESET_COLOR();
    }

    fclose(logFile);

    if (count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("No error logs found.\n");
        RESET_COLOR();
    } else {
        SET_COLOR(COLOR_CYAN);
        printf("\nTotal errors logged: %d\n", count);
        RESET_COLOR();
    }

    printf("\nPress Enter to continue...");
    clearInputBuffer();
}

// Save data to file
void saveToFile(ContactManager* manager) {
    FILE* file = fopen(manager->dataFile, "w");
    if (file == NULL) {
        logError("Failed to save data file");
        return;
    }

    fprintf(file, "%d\n", manager->nextId);
    fprintf(file, "%d\n", manager->totalContacts);

    Contact* current = manager->head;
    while (current != NULL) {
        fprintf(file, "%d\n", current->id);
        fprintf(file, "%s\n", current->firstName);
        fprintf(file, "%s\n", current->lastName);
        fprintf(file, "%s\n", current->phone);
        fprintf(file, "%s\n", current->email);
        fprintf(file, "%s\n", current->address);
        fprintf(file, "%s\n", current->category);
        fprintf(file, "%s\n", current->birthday);
        fprintf(file, "%s\n", current->notes);
        current = current->next;
    }

    fclose(file);
}

// Load data from file
void loadFromFile(ContactManager* manager) {
    FILE* file = fopen(manager->dataFile, "r");
    if (file == NULL) {
        return;
    }

    fscanf(file, "%d\n", &manager->nextId);
    fscanf(file, "%d\n", &manager->totalContacts);

    for (int i = 0; i < manager->totalContacts; i++) {
        Contact* newContact = (Contact*)malloc(sizeof(Contact));
        if (!newContact) {
            logError("Memory allocation failed during load");
            break;
        }

        fscanf(file, "%d\n", &newContact->id);
        fgets(newContact->firstName, sizeof(newContact->firstName), file);
        newContact->firstName[strcspn(newContact->firstName, "\n")] = '\0';

        fgets(newContact->lastName, sizeof(newContact->lastName), file);
        newContact->lastName[strcspn(newContact->lastName, "\n")] = '\0';

        fgets(newContact->phone, sizeof(newContact->phone), file);
        newContact->phone[strcspn(newContact->phone, "\n")] = '\0';

        fgets(newContact->email, sizeof(newContact->email), file);
        newContact->email[strcspn(newContact->email, "\n")] = '\0';

        fgets(newContact->address, sizeof(newContact->address), file);
        newContact->address[strcspn(newContact->address, "\n")] = '\0';

        fgets(newContact->category, sizeof(newContact->category), file);
        newContact->category[strcspn(newContact->category, "\n")] = '\0';

        fgets(newContact->birthday, sizeof(newContact->birthday), file);
        newContact->birthday[strcspn(newContact->birthday, "\n")] = '\0';

        fgets(newContact->notes, sizeof(newContact->notes), file);
        newContact->notes[strcspn(newContact->notes, "\n")] = '\0';

        newContact->next = NULL;

        if (manager->head == NULL) {
            manager->head = newContact;
        } else {
            Contact* temp = manager->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newContact;
        }
    }

    fclose(file);
}

// Log error
void logError(const char* message) {
    FILE* logFile = fopen(logFilePath, "a");
    if (logFile == NULL) return;

    time_t t = time(NULL);
    struct tm* tm = localtime(&t);

    fprintf(logFile, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec, message);

    fclose(logFile);
}

// Free memory
void freeMemory(ContactManager* manager) {
    Contact* current = manager->head;
    while (current != NULL) {
        Contact* temp = current;
        current = current->next;
        free(temp);
    }
    manager->head = NULL;
    manager->totalContacts = 0;
    manager->nextId = 1;
}
