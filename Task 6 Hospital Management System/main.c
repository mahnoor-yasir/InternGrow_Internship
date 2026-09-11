/*
 ============================================================================
 Name        : Hospital Management System
 Author      : InternGrow Intern
 Version     : 2.0
 Description : Complete Hospital Management System in C
               All concepts: Structures, Pointers, Dynamic Memory,
               File Handling, Searching, Sorting, Error Handling
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>

// ============================================================================
// COLOR DEFINITIONS
// ============================================================================
#define RED     "\x1B[31m"
#define GRN     "\x1B[32m"
#define YEL     "\x1B[33m"
#define BLU     "\x1B[34m"
#define MAG     "\x1B[35m"
#define CYN     "\x1B[36m"
#define WHT     "\x1B[37m"
#define BOLD    "\x1B[1m"
#define RESET   "\x1B[0m"
#define CLS     "\033[2J\033[H"

// ============================================================================
// CONSTANTS & MACROS
// ============================================================================
#define INITIAL_CAPACITY 10
#define MAX_STRING 100
#define MAX_PATIENTS 1000
#define MAX_APPOINTMENTS 500
#define DATA_FILE "patients.bin"
#define APPOINTMENT_FILE "appointments.bin"
#define BACKUP_FILE "patients_backup.bin"
#define LOG_FILE "error.log"
#define SAVE_THRESHOLD 5
#define MAX_WARDS 10
#define MAX_ROOMS_PER_WARD 50

// ============================================================================
// STRUCTURE DEFINITIONS
// ============================================================================

// Patient Structure
typedef struct {
    int id;
    char name[MAX_STRING];
    int age;
    char gender;
    char disease[MAX_STRING];
    char doctor[MAX_STRING];
    int ward;
    int room;
    char admissionDate[20];
    char dischargeDate[20];
    float bill;
    int status; // 1=Active, 0=Discharged
    char phone[15];
    char address[MAX_STRING];
    char emergencyContact[15];
} Patient;

// Appointment Structure
typedef struct {
    int appointmentId;
    int patientId;
    char doctor[MAX_STRING];
    char date[20];
    char time[10];
    int status; // 1=Scheduled, 2=Completed, 3=Cancelled
    char reason[MAX_STRING];
} Appointment;

// Payment Structure
typedef struct {
    int paymentId;
    int patientId;
    float amount;
    char date[20];
    char paymentMethod[20];
    char description[MAX_STRING];
} Payment;

// Medical Record Structure
typedef struct {
    int recordId;
    int patientId;
    char diagnosis[MAX_STRING];
    char prescription[MAX_STRING];
    char testResults[MAX_STRING];
    char date[20];
} MedicalRecord;

// Doctor Structure
typedef struct {
    int id;
    char name[MAX_STRING];
    char specialization[MAX_STRING];
    char phone[15];
    int available; // 1=Available, 0=Not Available
} Doctor;

// Ward Structure
typedef struct {
    int wardNumber;
    char name[MAX_STRING];
    int totalBeds;
    int occupiedBeds;
    int availableBeds;
} Ward;

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================
Patient *patients = NULL;
Appointment *appointments = NULL;
Payment *payments = NULL;
MedicalRecord *medicalRecords = NULL;
Doctor *doctors = NULL;
Ward *wards = NULL;

int patientCount = 0;
int appointmentCount = 0;
int paymentCount = 0;
int medicalRecordCount = 0;
int doctorCount = 0;
int wardCount = 0;

int patientCapacity = INITIAL_CAPACITY;
int appointmentCapacity = INITIAL_CAPACITY;
int paymentCapacity = INITIAL_CAPACITY;
int medicalRecordCapacity = INITIAL_CAPACITY;
int doctorCapacity = INITIAL_CAPACITY;

int operationCounter = 0;
int nextPatientId = 1;
int nextAppointmentId = 1;
int nextPaymentId = 1;
int nextRecordId = 1;
int nextDoctorId = 1;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Utility Functions
void clearScreen();
void pressAnyKey();
void displayBanner();
void displayHeader(const char *title);
void displayFooter();
void displayLoadingAnimation();
void displayProgressBar(int current, int total, const char *label);
void drawLine(int length, char character);

// Color Functions
void printSuccess(const char *msg, ...);
void printError(const char *msg, ...);
void printWarning(const char *msg, ...);
void printInfo(const char *msg, ...);
void printHeader(const char *msg);

// Input Validation
int validateInt(const char *prompt, int min, int max);
float validateFloat(const char *prompt, float min, float max);
void validateString(char *str, int maxLen, const char *prompt);
char validateGender(const char *prompt);
int validateDate(char *date);

// Memory Management
int initializeMemory();
void expandPatientArray();
void expandAppointmentArray();
void expandPaymentArray();
void expandMedicalRecordArray();
void expandDoctorArray();
void freeAllMemory();
void displayMemoryUsage();

// File Handling
int loadDataFromFile();
int saveDataToFile();
int loadAppointmentsFromFile();
int saveAppointmentsToFile();
int loadMedicalRecordsFromFile();
int saveMedicalRecordsToFile();
int loadDoctorsFromFile();
int saveDoctorsToFile();
int backupData();
int restoreData();
void logError(const char *errorMsg);
int exportToCSV();
int importFromCSV();
int exportToJSON();
void viewErrorLogs();

// Patient Management
void addPatient();
void displayAllPatients();
void displayPatientDetails(int index);
void searchPatient();
void updatePatient();
void deletePatient();
void viewPatientDetails();
void displayPatientTable();
int binarySearchByID(int id);
int linearSearchByName(const char *name);
void searchByDisease();
void searchByDoctor();
void searchByDateRange();

// Appointment Management
void scheduleAppointment();
void viewAllAppointments();
void cancelAppointment();
void completeAppointment();
void viewPatientAppointments();

// Billing System
void generateBill();
void processPayment();
void viewPaymentHistory();
void calculateBill();
void generateInvoice();

// Medical Records
void addMedicalRecord();
void viewMedicalRecords();
void updateMedicalRecord();
void viewPatientHistory();

// Doctor Management
void addDoctor();
void viewAllDoctors();
void updateDoctor();
void deleteDoctor();
void assignDoctorToPatient();

// Ward Management
void initializeWards();
void viewWardStatus();
void updateWard();
void viewWardPatients();

// Reports
void generateDailyReport();
void generateMonthlyStatistics();
void generateDoctorReport();
void generateWardReport();
void generateDiseaseReport();
void generateRevenueReport();
void generatePatientReport();

// Administration
void assignDoctor();
void manageWards();
void dischargePatient();
void viewSystemStats();

// Sorting Functions
void sortPatientsByName();
void sortPatientsByID();
void sortPatientsByDisease();
void sortPatientsByAge();

// Main Menu Functions
void displayMainMenu();
void handleChoice(int choice);
void dataManagementMenu();
void reportMenu();
void adminMenu();
void medicalMenu();

// ============================================================================
// UTILITY FUNCTIONS IMPLEMENTATION
// ============================================================================

void clearScreen() {
    printf(CLS);
}

void pressAnyKey() {
    printf("\n" YEL "Press Enter to continue..." RESET);
    getchar();
    getchar();
}

void drawLine(int length, char character) {
    for (int i = 0; i < length; i++) {
        printf("%c", character);
    }
}

void displayBanner() {
    printf(BOLD CYN);
    printf("+===============================================================+\n");
    printf("|                                                               |\n");
    printf("|   H   H  OOO  SSS  PPP  III TTTT   AAA    L                   |\n");
    printf("|   H   H O   O S    P  P  I   T    A   A   L                   |\n");
    printf("|   HHHHH O   O SSS  PPP   I   T    AAAAA   L                   |\n");
    printf("|   H   H O   O    S P     I   T   A     A  L                   |\n");
    printf("|   H   H  OOO  SSS  P    III  T   A     A  LLLLL               |\n");
    printf("|                                                               |\n");
    printf("|           HOSPITAL MANAGEMENT SYSTEM                          |\n");
    printf("|              Production Ready v2.0                            |\n");
    printf("|                                                               |\n");
    printf("+===============================================================+\n");
    printf(RESET);
}

void displayHeader(const char *title) {
    printf(BOLD CYN);
    printf("\n+-------------------------------------------------------------+\n");
    printf("| %-59s |\n", title);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
}

void displayFooter() {
    printf(BOLD BLU);
    printf("\n+-------------------------------------------------------------+\n");
    printf("| " WHT "Hospital Management System - C Programming" BLU "          |\n");
    printf("| " GRN "(c) 2024 All Rights Reserved" BLU "                         |\n");
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
}

void displayLoadingAnimation() {
    const char *anim = "|/-\\";
    printf(BLU "Loading");
    for (int i = 0; i < 10; i++) {
        printf(" %c", anim[i % 4]);
        fflush(stdout);
        for (int j = 0; j < 1000000; j++);
        printf("\b\b\b\b\b");
    }
    printf(" Done!    \n" RESET);
}

void displayProgressBar(int current, int total, const char *label) {
    int barWidth = 40;
    float progress = (float)current / total;
    int pos = barWidth * progress;

    printf(BLU "%s: [", label);
    for (int i = 0; i < barWidth; i++) {
        if (i < pos) printf(GRN "=" RESET);
        else if (i == pos) printf(YEL ">" RESET);
        else printf(" ");
    }
    printf("] %.0f%%\r", progress * 100);
    fflush(stdout);
}

// ============================================================================
// COLOR FUNCTIONS
// ============================================================================

void printSuccess(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    printf(GRN "OK " RESET);
    vprintf(msg, args);
    printf("\n");
    va_end(args);
}

void printError(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    printf(RED "ERROR: " RESET);
    vprintf(msg, args);
    printf("\n");
    va_end(args);
}

void printWarning(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    printf(YEL "WARNING: " RESET);
    vprintf(msg, args);
    printf("\n");
    va_end(args);
}

void printInfo(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    printf(BLU "INFO: " RESET);
    vprintf(msg, args);
    printf("\n");
    va_end(args);
}

void printHeader(const char *msg) {
    printf(BOLD MAG "\n>>> " RESET BOLD "%s" RESET "\n", msg);
}

// ============================================================================
// INPUT VALIDATION FUNCTIONS
// ============================================================================

int validateInt(const char *prompt, int min, int max) {
    int value;
    char buffer[100];
    while (1) {
        printf(WHT "%s" RESET, prompt);
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &value) == 1) {
            if (value >= min && value <= max) {
                return value;
            }
        }
        printError("Invalid input! Please enter a number between %d and %d", min, max);
    }
}

float validateFloat(const char *prompt, float min, float max) {
    float value;
    char buffer[100];
    while (1) {
        printf(WHT "%s" RESET, prompt);
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%f", &value) == 1) {
            if (value >= min && value <= max) {
                return value;
            }
        }
        printError("Invalid input! Please enter a value between %.2f and %.2f", min, max);
    }
}

void validateString(char *str, int maxLen, const char *prompt) {
    char buffer[500];
    while (1) {
        printf(WHT "%s" RESET, prompt);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) > 0 && strlen(buffer) <= maxLen) {
            int len = strlen(buffer);
            while (len > 0 && buffer[len-1] == ' ') {
                buffer[len-1] = '\0';
                len--;
            }
            if (strlen(buffer) > 0) {
                strcpy(str, buffer);
                return;
            }
        }
        printError("Invalid input! Please enter text (max %d characters)", maxLen);
    }
}

char validateGender(const char *prompt) {
    char input[10];
    while (1) {
        printf(WHT "%s" RESET, prompt);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 1) {
            char gender = toupper(input[0]);
            if (gender == 'M' || gender == 'F') {
                return gender;
            }
        }
        printError("Invalid input! Please enter 'M' for Male or 'F' for Female");
    }
}

int validateDate(char *date) {
    int day, month, year;
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
        return 0;
    }
    if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) {
        return 0;
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    if (day > daysInMonth[month - 1]) {
        return 0;
    }
    return 1;
}

// ============================================================================
// MEMORY MANAGEMENT FUNCTIONS
// ============================================================================

int initializeMemory() {
    patients = (Patient*)malloc(patientCapacity * sizeof(Patient));
    if (patients == NULL) {
        printError("Failed to allocate memory for patients");
        return 0;
    }

    appointments = (Appointment*)malloc(appointmentCapacity * sizeof(Appointment));
    if (appointments == NULL) {
        printError("Failed to allocate memory for appointments");
        free(patients);
        return 0;
    }

    payments = (Payment*)malloc(paymentCapacity * sizeof(Payment));
    if (payments == NULL) {
        printError("Failed to allocate memory for payments");
        free(patients);
        free(appointments);
        return 0;
    }

    medicalRecords = (MedicalRecord*)malloc(medicalRecordCapacity * sizeof(MedicalRecord));
    if (medicalRecords == NULL) {
        printError("Failed to allocate memory for medical records");
        free(patients);
        free(appointments);
        free(payments);
        return 0;
    }

    doctors = (Doctor*)malloc(doctorCapacity * sizeof(Doctor));
    if (doctors == NULL) {
        printError("Failed to allocate memory for doctors");
        free(patients);
        free(appointments);
        free(payments);
        free(medicalRecords);
        return 0;
    }

    memset(patients, 0, patientCapacity * sizeof(Patient));
    memset(appointments, 0, appointmentCapacity * sizeof(Appointment));
    memset(payments, 0, paymentCapacity * sizeof(Payment));
    memset(medicalRecords, 0, medicalRecordCapacity * sizeof(MedicalRecord));
    memset(doctors, 0, doctorCapacity * sizeof(Doctor));

    printSuccess("Memory initialized successfully");
    return 1;
}

void expandPatientArray() {
    patientCapacity *= 2;
    Patient *newPtr = (Patient*)realloc(patients, patientCapacity * sizeof(Patient));
    if (newPtr == NULL) {
        printError("Failed to expand patient array");
        return;
    }
    patients = newPtr;
    printSuccess("Patient array expanded to capacity: %d", patientCapacity);
}

void expandAppointmentArray() {
    appointmentCapacity *= 2;
    Appointment *newPtr = (Appointment*)realloc(appointments, appointmentCapacity * sizeof(Appointment));
    if (newPtr == NULL) {
        printError("Failed to expand appointment array");
        return;
    }
    appointments = newPtr;
    printSuccess("Appointment array expanded to capacity: %d", appointmentCapacity);
}

void expandPaymentArray() {
    paymentCapacity *= 2;
    Payment *newPtr = (Payment*)realloc(payments, paymentCapacity * sizeof(Payment));
    if (newPtr == NULL) {
        printError("Failed to expand payment array");
        return;
    }
    payments = newPtr;
    printSuccess("Payment array expanded to capacity: %d", paymentCapacity);
}

void expandMedicalRecordArray() {
    medicalRecordCapacity *= 2;
    MedicalRecord *newPtr = (MedicalRecord*)realloc(medicalRecords, medicalRecordCapacity * sizeof(MedicalRecord));
    if (newPtr == NULL) {
        printError("Failed to expand medical record array");
        return;
    }
    medicalRecords = newPtr;
    printSuccess("Medical record array expanded to capacity: %d", medicalRecordCapacity);
}

void expandDoctorArray() {
    doctorCapacity *= 2;
    Doctor *newPtr = (Doctor*)realloc(doctors, doctorCapacity * sizeof(Doctor));
    if (newPtr == NULL) {
        printError("Failed to expand doctor array");
        return;
    }
    doctors = newPtr;
    printSuccess("Doctor array expanded to capacity: %d", doctorCapacity);
}

void freeAllMemory() {
    if (patients != NULL) {
        free(patients);
        patients = NULL;
    }
    if (appointments != NULL) {
        free(appointments);
        appointments = NULL;
    }
    if (payments != NULL) {
        free(payments);
        payments = NULL;
    }
    if (medicalRecords != NULL) {
        free(medicalRecords);
        medicalRecords = NULL;
    }
    if (doctors != NULL) {
        free(doctors);
        doctors = NULL;
    }
    printSuccess("All memory freed successfully");
}

void displayMemoryUsage() {
    size_t totalAllocated = 0;
    totalAllocated += patientCapacity * sizeof(Patient);
    totalAllocated += appointmentCapacity * sizeof(Appointment);
    totalAllocated += paymentCapacity * sizeof(Payment);
    totalAllocated += medicalRecordCapacity * sizeof(MedicalRecord);
    totalAllocated += doctorCapacity * sizeof(Doctor);

    printHeader("Memory Usage Statistics");
    printf("+-------------------------------------------------------------+\n");
    printf("| Patient Records:       %d/%d (%.1f%%)\n",
           patientCount, patientCapacity,
           (float)patientCount / patientCapacity * 100);
    printf("| Appointments:          %d/%d (%.1f%%)\n",
           appointmentCount, appointmentCapacity,
           (float)appointmentCount / appointmentCapacity * 100);
    printf("| Payments:              %d/%d (%.1f%%)\n",
           paymentCount, paymentCapacity,
           (float)paymentCount / paymentCapacity * 100);
    printf("| Medical Records:       %d/%d (%.1f%%)\n",
           medicalRecordCount, medicalRecordCapacity,
           (float)medicalRecordCount / medicalRecordCapacity * 100);
    printf("| Doctors:               %d/%d (%.1f%%)\n",
           doctorCount, doctorCapacity,
           (float)doctorCount / doctorCapacity * 100);
    printf("| Total Memory Used:     %.2f KB\n", totalAllocated / 1024.0);
    printf("+-------------------------------------------------------------+\n");
}

// ============================================================================
// FILE HANDLING FUNCTIONS
// ============================================================================

void logError(const char *errorMsg) {
    FILE *logFile = fopen(LOG_FILE, "a");
    if (logFile == NULL) {
        return;
    }
    time_t now = time(NULL);
    char *timeStr = ctime(&now);
    timeStr[strlen(timeStr) - 1] = 0;
    fprintf(logFile, "[%s] ERROR: %s\n", timeStr, errorMsg);
    fclose(logFile);
}

int loadDataFromFile() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        printWarning("No existing patient data found. Starting fresh.");
        return 1;
    }

    if (fread(&patientCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        logError("Failed to read patient count from file");
        return 0;
    }

    if (patientCount > 0) {
        patientCapacity = patientCount + 10;
        patients = (Patient*)realloc(patients, patientCapacity * sizeof(Patient));
        if (patients == NULL) {
            fclose(file);
            logError("Failed to allocate memory for loading patients");
            return 0;
        }

        if (fread(patients, sizeof(Patient), patientCount, file) != patientCount) {
            fclose(file);
            logError("Failed to read patient data from file");
            return 0;
        }

        for (int i = 0; i < patientCount; i++) {
            if (patients[i].id >= nextPatientId) {
                nextPatientId = patients[i].id + 1;
            }
        }
    }

    fclose(file);
    printSuccess("Loaded %d patients from file", patientCount);
    return 1;
}

int saveDataToFile() {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        logError("Failed to open data file for writing");
        printError("Cannot save data. Please check file permissions.");
        return 0;
    }

    if (fwrite(&patientCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        logError("Failed to write patient count to file");
        return 0;
    }

    if (patientCount > 0) {
        if (fwrite(patients, sizeof(Patient), patientCount, file) != patientCount) {
            fclose(file);
            logError("Failed to write patient data to file");
            return 0;
        }
    }

    fclose(file);
    printSuccess("Data saved successfully (%d patients)", patientCount);
    return 1;
}

int loadAppointmentsFromFile() {
    FILE *file = fopen(APPOINTMENT_FILE, "rb");
    if (file == NULL) {
        printWarning("No existing appointment data found.");
        return 1;
    }

    if (fread(&appointmentCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    if (appointmentCount > 0) {
        appointmentCapacity = appointmentCount + 10;
        appointments = (Appointment*)realloc(appointments, appointmentCapacity * sizeof(Appointment));
        if (appointments == NULL) {
            fclose(file);
            return 0;
        }

        if (fread(appointments, sizeof(Appointment), appointmentCount, file) != appointmentCount) {
            fclose(file);
            return 0;
        }

        for (int i = 0; i < appointmentCount; i++) {
            if (appointments[i].appointmentId >= nextAppointmentId) {
                nextAppointmentId = appointments[i].appointmentId + 1;
            }
        }
    }

    fclose(file);
    printSuccess("Loaded %d appointments from file", appointmentCount);
    return 1;
}

int saveAppointmentsToFile() {
    FILE *file = fopen(APPOINTMENT_FILE, "wb");
    if (file == NULL) {
        logError("Failed to open appointment file for writing");
        return 0;
    }

    if (fwrite(&appointmentCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    if (appointmentCount > 0) {
        if (fwrite(appointments, sizeof(Appointment), appointmentCount, file) != appointmentCount) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int loadMedicalRecordsFromFile() {
    FILE *file = fopen("medical_records.bin", "rb");
    if (file == NULL) {
        printWarning("No existing medical records found.");
        return 1;
    }

    if (fread(&medicalRecordCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    if (medicalRecordCount > 0) {
        medicalRecordCapacity = medicalRecordCount + 10;
        medicalRecords = (MedicalRecord*)realloc(medicalRecords, medicalRecordCapacity * sizeof(MedicalRecord));
        if (medicalRecords == NULL) {
            fclose(file);
            return 0;
        }

        if (fread(medicalRecords, sizeof(MedicalRecord), medicalRecordCount, file) != medicalRecordCount) {
            fclose(file);
            return 0;
        }

        for (int i = 0; i < medicalRecordCount; i++) {
            if (medicalRecords[i].recordId >= nextRecordId) {
                nextRecordId = medicalRecords[i].recordId + 1;
            }
        }
    }

    fclose(file);
    printSuccess("Loaded %d medical records from file", medicalRecordCount);
    return 1;
}

int saveMedicalRecordsToFile() {
    FILE *file = fopen("medical_records.bin", "wb");
    if (file == NULL) {
        logError("Failed to open medical records file for writing");
        return 0;
    }

    if (fwrite(&medicalRecordCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    if (medicalRecordCount > 0) {
        if (fwrite(medicalRecords, sizeof(MedicalRecord), medicalRecordCount, file) != medicalRecordCount) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int loadDoctorsFromFile() {
    FILE *file = fopen("doctors.bin", "rb");
    if (file == NULL) {
        printWarning("No existing doctor data found.");
        return 1;
    }

    if (fread(&doctorCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    if (doctorCount > 0) {
        doctorCapacity = doctorCount + 10;
        doctors = (Doctor*)realloc(doctors, doctorCapacity * sizeof(Doctor));
        if (doctors == NULL) {
            fclose(file);
            return 0;
        }

        if (fread(doctors, sizeof(Doctor), doctorCount, file) != doctorCount) {
            fclose(file);
            return 0;
        }

        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].id >= nextDoctorId) {
                nextDoctorId = doctors[i].id + 1;
            }
        }
    }

    fclose(file);
    printSuccess("Loaded %d doctors from file", doctorCount);
    return 1;
}

int saveDoctorsToFile() {
    FILE *file = fopen("doctors.bin", "wb");
    if (file == NULL) {
        logError("Failed to open doctors file for writing");
        return 0;
    }

    if (fwrite(&doctorCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    if (doctorCount > 0) {
        if (fwrite(doctors, sizeof(Doctor), doctorCount, file) != doctorCount) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int backupData() {
    FILE *source = fopen(DATA_FILE, "rb");
    if (source == NULL) {
        printError("No data file to backup");
        return 0;
    }

    char backupName[50];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(backupName, sizeof(backupName), "backup_%Y%m%d_%H%M%S.bin", t);

    FILE *dest = fopen(backupName, "wb");
    if (dest == NULL) {
        fclose(source);
        printError("Cannot create backup file");
        return 0;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(source);
    fclose(dest);
    printSuccess("Backup created successfully: %s", backupName);
    return 1;
}

int restoreData() {
    char backupName[50];
    validateString(backupName, 49, "Enter backup filename: ");

    FILE *source = fopen(backupName, "rb");
    if (source == NULL) {
        printError("Backup file not found: %s", backupName);
        return 0;
    }

    FILE *dest = fopen(DATA_FILE, "wb");
    if (dest == NULL) {
        fclose(source);
        printError("Failed to restore data");
        return 0;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(source);
    fclose(dest);

    loadDataFromFile();
    printSuccess("Data restored successfully from: %s", backupName);
    return 1;
}

int exportToCSV() {
    FILE *file = fopen("patients_export.csv", "w");
    if (file == NULL) {
        printError("Cannot create CSV file");
        return 0;
    }

    fprintf(file, "ID,Name,Age,Gender,Disease,Doctor,Ward,Room,Admission Date,Discharge Date,Bill,Status,Phone,Address\n");

    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%d,%s,%d,%c,%s,%s,%d,%d,%s,%s,%.2f,%s,%s,%s\n",
                patients[i].id,
                patients[i].name,
                patients[i].age,
                patients[i].gender,
                patients[i].disease,
                patients[i].doctor,
                patients[i].ward,
                patients[i].room,
                patients[i].admissionDate,
                patients[i].dischargeDate,
                patients[i].bill,
                patients[i].status ? "Active" : "Discharged",
                patients[i].phone,
                patients[i].address);
    }

    fclose(file);
    printSuccess("Data exported to patients_export.csv successfully");
    return 1;
}

int exportToJSON() {
    FILE *file = fopen("patients_export.json", "w");
    if (file == NULL) {
        printError("Cannot create JSON file");
        return 0;
    }

    fprintf(file, "{\n");
    fprintf(file, "  \"hospital\": \"Hospital Management System\",\n");
    fprintf(file, "  \"exportDate\": \"%s\",\n", __DATE__);
    fprintf(file, "  \"totalPatients\": %d,\n", patientCount);
    fprintf(file, "  \"patients\": [\n");

    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "    {\n");
        fprintf(file, "      \"id\": %d,\n", patients[i].id);
        fprintf(file, "      \"name\": \"%s\",\n", patients[i].name);
        fprintf(file, "      \"age\": %d,\n", patients[i].age);
        fprintf(file, "      \"gender\": \"%c\",\n", patients[i].gender);
        fprintf(file, "      \"disease\": \"%s\",\n", patients[i].disease);
        fprintf(file, "      \"doctor\": \"%s\",\n", patients[i].doctor);
        fprintf(file, "      \"ward\": %d,\n", patients[i].ward);
        fprintf(file, "      \"room\": %d,\n", patients[i].room);
        fprintf(file, "      \"bill\": %.2f,\n", patients[i].bill);
        fprintf(file, "      \"status\": \"%s\"\n", patients[i].status ? "Active" : "Discharged");
        fprintf(file, "    }%s\n", (i < patientCount - 1) ? "," : "");
    }

    fprintf(file, "  ]\n");
    fprintf(file, "}\n");

    fclose(file);
    printSuccess("Data exported to patients_export.json successfully");
    return 1;
}

void viewErrorLogs() {
    clearScreen();
    displayHeader("ERROR LOGS");

    FILE *file = fopen(LOG_FILE, "r");
    if (file == NULL) {
        printWarning("No error logs found.");
        pressAnyKey();
        return;
    }

    char line[256];
    printf("\n" BOLD "Last 50 Error Entries:\n" RESET);
    printf("+-------------------------------------------------------------+\n");

    char *lines[50];
    int lineCount = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (lineCount < 50) {
            lines[lineCount] = strdup(line);
            lineCount++;
        } else {
            free(lines[0]);
            for (int i = 1; i < 50; i++) {
                lines[i-1] = lines[i];
            }
            lines[49] = strdup(line);
        }
    }

    for (int i = 0; i < lineCount; i++) {
        printf("| %s", lines[i]);
        free(lines[i]);
    }

    printf("+-------------------------------------------------------------+\n");
    fclose(file);
    pressAnyKey();
}

int importFromCSV() {
    FILE *file = fopen("patients_import.csv", "r");
    if (file == NULL) {
        printError("No import file found (patients_import.csv)");
        return 0;
    }

    char line[1024];
    int importedCount = 0;

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Patient temp;
        char status[10];

        if (sscanf(line, "%d,%[^,],%d,%c,%[^,],%[^,],%d,%d,%[^,],%[^,],%f,%s,%[^,],%[^\n]",
                   &temp.id, temp.name, &temp.age, &temp.gender,
                   temp.disease, temp.doctor, &temp.ward, &temp.room,
                   temp.admissionDate, temp.dischargeDate, &temp.bill, status,
                   temp.phone, temp.address) >= 12) {

            temp.status = (strcmp(status, "Active") == 0) ? 1 : 0;

            if (patientCount >= patientCapacity) {
                expandPatientArray();
            }

            patients[patientCount] = temp;
            patientCount++;
            importedCount++;

            if (temp.id >= nextPatientId) {
                nextPatientId = temp.id + 1;
            }
        }
    }

    fclose(file);
    printSuccess("Imported %d patients from CSV", importedCount);
    return 1;
}

// ============================================================================
// PATIENT MANAGEMENT FUNCTIONS
// ============================================================================

void addPatient() {
    clearScreen();
    displayHeader("ADD NEW PATIENT");

    if (patientCount >= patientCapacity) {
        expandPatientArray();
    }

    Patient *newPatient = &patients[patientCount];
    newPatient->id = nextPatientId++;

    printf("\n" BOLD "Patient ID: " RESET "%d\n", newPatient->id);

    validateString(newPatient->name, MAX_STRING - 1, "Enter Patient Name: ");
    newPatient->age = validateInt("Enter Age: ", 0, 150);
    newPatient->gender = validateGender("Enter Gender (M/F): ");
    validateString(newPatient->disease, MAX_STRING - 1, "Enter Disease: ");

    if (doctorCount > 0) {
        printf("\n" BOLD "Available Doctors:\n" RESET);
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].available) {
                printf("  %d. %s - %s\n", i+1, doctors[i].name, doctors[i].specialization);
            }
        }
        int doctorChoice = validateInt("Select Doctor (0 to enter manually): ", 0, doctorCount);
        if (doctorChoice > 0 && doctorChoice <= doctorCount) {
            strcpy(newPatient->doctor, doctors[doctorChoice-1].name);
        } else {
            validateString(newPatient->doctor, MAX_STRING - 1, "Enter Doctor Name: ");
        }
    } else {
        validateString(newPatient->doctor, MAX_STRING - 1, "Enter Doctor Name: ");
    }

    newPatient->ward = validateInt("Enter Ward Number (1-10): ", 1, 10);
    newPatient->room = validateInt("Enter Room Number (1-50): ", 1, 50);

    do {
        printf(WHT "Enter Admission Date (DD/MM/YYYY): " RESET);
        fgets(newPatient->admissionDate, sizeof(newPatient->admissionDate), stdin);
        newPatient->admissionDate[strcspn(newPatient->admissionDate, "\n")] = 0;
    } while (!validateDate(newPatient->admissionDate));

    strcpy(newPatient->dischargeDate, "Not Discharged");
    newPatient->bill = 0.0;
    newPatient->status = 1;

    validateString(newPatient->phone, 14, "Enter Phone Number: ");
    validateString(newPatient->address, MAX_STRING - 1, "Enter Address: ");
    validateString(newPatient->emergencyContact, 14, "Enter Emergency Contact: ");

    patientCount++;
    operationCounter++;
    printSuccess("Patient added successfully! ID: %d", newPatient->id);

    if (operationCounter >= SAVE_THRESHOLD) {
        saveDataToFile();
        operationCounter = 0;
    }

    pressAnyKey();
}

void displayPatientTable() {
    if (patientCount == 0) {
        printWarning("No patients registered.");
        return;
    }

    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+-----------------------+\n");
    printf("| ID  | Name                 | Age | Gender   | Disease               | Doctor                |\n");
    printf("+-----+----------------------+-----+----------+-----------------------+-----------------------+\n");
    printf(RESET);

    for (int i = 0; i < patientCount; i++) {
        Patient *p = &patients[i];
        printf("| %4d| %-20s| %4d| %-8c| %-21s| %-21s|\n",
               p->id,
               p->name,
               p->age,
               p->gender,
               p->disease,
               p->doctor);
    }

    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+-----------------------+\n");
    printf(RESET);
}

void displayAllPatients() {
    clearScreen();
    displayHeader("ALL PATIENTS RECORDS");
    displayPatientTable();
    printf("\n" BOLD "Total Patients: " RESET "%d\n", patientCount);
    pressAnyKey();
}

void displayPatientDetails(int index) {
    Patient *p = &patients[index];

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Patient Information" CYN "                              |\n");
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
    printf("| " BOLD "Patient ID:" RESET "      %-44d |\n", p->id);
    printf("| " BOLD "Name:" RESET "            %-44s |\n", p->name);
    printf("| " BOLD "Age:" RESET "             %-44d |\n", p->age);
    printf("| " BOLD "Gender:" RESET "          %-44c |\n", p->gender);
    printf("| " BOLD "Disease:" RESET "        %-44s |\n", p->disease);
    printf("| " BOLD "Doctor:" RESET "         %-44s |\n", p->doctor);
    printf("| " BOLD "Ward:" RESET "           %-44d |\n", p->ward);
    printf("| " BOLD "Room:" RESET "           %-44d |\n", p->room);
    printf("| " BOLD "Admission Date:" RESET " %-44s |\n", p->admissionDate);
    printf("| " BOLD "Discharge Date:" RESET " %-44s |\n", p->dischargeDate);
    printf("| " BOLD "Bill Amount:" RESET "    %-44.2f |\n", p->bill);
    printf("| " BOLD "Status:" RESET "         %-44s |\n", p->status ? "Active" : "Discharged");
    printf("| " BOLD "Phone:" RESET "          %-44s |\n", p->phone);
    printf("| " BOLD "Address:" RESET "        %-44s |\n", p->address);
    printf("| " BOLD "Emergency Contact:" RESET "%-44s |\n", p->emergencyContact);
    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
}

void searchPatient() {
    clearScreen();
    displayHeader("SEARCH PATIENT");

    printf("\n" BOLD "Search Options:\n" RESET);
    printf("+-------------------------------------------------------------+\n");
    printf("| 1. Search by ID (Binary Search)                              |\n");
    printf("| 2. Search by Name (Linear Search)                            |\n");
    printf("| 3. Search by Disease                                         |\n");
    printf("| 4. Search by Doctor                                          |\n");
    printf("| 5. Search by Date Range                                      |\n");
    printf("+-------------------------------------------------------------+\n");

    int choice = validateInt("Enter your choice: ", 1, 5);

    switch (choice) {
        case 1: {
            int id = validateInt("Enter Patient ID: ", 1, 9999);
            int index = binarySearchByID(id);
            if (index != -1) {
                clearScreen();
                displayHeader("PATIENT DETAILS");
                displayPatientDetails(index);
            } else {
                printError("Patient not found with ID: %d", id);
            }
            break;
        }
        case 2: {
            char name[MAX_STRING];
            validateString(name, MAX_STRING - 1, "Enter Patient Name: ");
            int index = linearSearchByName(name);
            if (index != -1) {
                clearScreen();
                displayHeader("PATIENT DETAILS");
                displayPatientDetails(index);
            } else {
                printError("Patient not found with name: %s", name);
            }
            break;
        }
        case 3:
            searchByDisease();
            break;
        case 4:
            searchByDoctor();
            break;
        case 5:
            searchByDateRange();
            break;
    }
    pressAnyKey();
}

int binarySearchByID(int id) {
    if (patientCount == 0) return -1;

    int *indices = (int*)malloc(patientCount * sizeof(int));
    if (indices == NULL) {
        logError("Failed to allocate memory for binary search");
        return -1;
    }

    for (int i = 0; i < patientCount; i++) {
        indices[i] = i;
    }

    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patients[indices[j]].id > patients[indices[j + 1]].id) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    int left = 0, right = patientCount - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midId = patients[indices[mid]].id;

        if (midId == id) {
            result = indices[mid];
            break;
        } else if (midId < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    free(indices);
    return result;
}

int linearSearchByName(const char *name) {
    for (int i = 0; i < patientCount; i++) {
        if (strcasecmp(patients[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void searchByDisease() {
    char disease[MAX_STRING];
    validateString(disease, MAX_STRING - 1, "Enter Disease to search: ");

    int found = 0;
    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+-----------------------+\n");
    printf("| ID  | Name                 | Age | Gender   | Disease               | Doctor                |\n");
    printf("+-----+----------------------+-----+----------+-----------------------+-----------------------+\n");
    printf(RESET);

    for (int i = 0; i < patientCount; i++) {
        if (strcasecmp(patients[i].disease, disease) == 0) {
            printf("| %4d| %-20s| %4d| %-8c| %-21s| %-21s|\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].age,
                   patients[i].gender,
                   patients[i].disease,
                   patients[i].doctor);
            found++;
        }
    }

    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+-----------------------+\n");
    printf(RESET);

    if (found == 0) {
        printWarning("No patients found with disease: %s", disease);
    } else {
        printSuccess("Found %d patients with disease: %s", found, disease);
    }
}

void searchByDoctor() {
    char doctor[MAX_STRING];
    validateString(doctor, MAX_STRING - 1, "Enter Doctor Name: ");

    int found = 0;
    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf("| ID  | Name                 | Age | Gender   | Disease               |\n");
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf(RESET);

    for (int i = 0; i < patientCount; i++) {
        if (strcasecmp(patients[i].doctor, doctor) == 0) {
            printf("| %4d| %-20s| %4d| %-8c| %-21s|\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].age,
                   patients[i].gender,
                   patients[i].disease);
            found++;
        }
    }

    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf(RESET);

    if (found == 0) {
        printWarning("No patients found for Dr. %s", doctor);
    } else {
        printSuccess("Found %d patients for Dr. %s", found, doctor);
    }
}

void searchByDateRange() {
    char startDate[20], endDate[20];

    do {
        printf(WHT "Enter Start Date (DD/MM/YYYY): " RESET);
        fgets(startDate, sizeof(startDate), stdin);
        startDate[strcspn(startDate, "\n")] = 0;
    } while (!validateDate(startDate));

    do {
        printf(WHT "Enter End Date (DD/MM/YYYY): " RESET);
        fgets(endDate, sizeof(endDate), stdin);
        endDate[strcspn(endDate, "\n")] = 0;
    } while (!validateDate(endDate));

    int found = 0;
    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf("| ID  | Name                 | Age | Gender   | Disease               |\n");
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf(RESET);

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].admissionDate, startDate) >= 0 &&
            strcmp(patients[i].admissionDate, endDate) <= 0) {
            printf("| %4d| %-20s| %4d| %-8c| %-21s|\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].age,
                   patients[i].gender,
                   patients[i].disease);
            found++;
        }
    }

    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf(RESET);

    if (found == 0) {
        printWarning("No patients found in date range");
    } else {
        printSuccess("Found %d patients in date range", found);
    }
}

void updatePatient() {
    clearScreen();
    displayHeader("UPDATE PATIENT");

    if (patientCount == 0) {
        printWarning("No patients to update.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Patient ID to update: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found with ID: %d", id);
        pressAnyKey();
        return;
    }

    Patient *p = &patients[index];

    printf("\n" BOLD "Current Patient Details:\n" RESET);
    displayPatientDetails(index);

    printf("\n" BOLD "Enter new values (press Enter to keep current):\n" RESET);
    printf("+-------------------------------------------------------------+\n");

    char buffer[MAX_STRING];
    int intTemp;
    float floatTemp;

    printf("Name [%s]: ", p->name);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(p->name, buffer);
    }

    printf("Age [%d]: ", p->age);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        intTemp = atoi(buffer);
        if (intTemp > 0 && intTemp < 150) {
            p->age = intTemp;
        }
    }

    printf("Gender (M/F) [%c]: ", p->gender);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        char gender = toupper(buffer[0]);
        if (gender == 'M' || gender == 'F') {
            p->gender = gender;
        }
    }

    printf("Disease [%s]: ", p->disease);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(p->disease, buffer);
    }

    printf("Doctor [%s]: ", p->doctor);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(p->doctor, buffer);
    }

    printf("Ward [%d]: ", p->ward);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        intTemp = atoi(buffer);
        if (intTemp > 0 && intTemp <= 10) {
            p->ward = intTemp;
        }
    }

    printf("Room [%d]: ", p->room);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        intTemp = atoi(buffer);
        if (intTemp > 0 && intTemp <= 50) {
            p->room = intTemp;
        }
    }

    printf("Bill [%.2f]: ", p->bill);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        floatTemp = atof(buffer);
        if (floatTemp >= 0) {
            p->bill = floatTemp;
        }
    }

    printf("Phone [%s]: ", p->phone);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(p->phone, buffer);
    }

    printf("Address [%s]: ", p->address);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(p->address, buffer);
    }

    printSuccess("Patient updated successfully!");
    saveDataToFile();
    pressAnyKey();
}

void deletePatient() {
    clearScreen();
    displayHeader("DELETE/DISCHARGE PATIENT");

    if (patientCount == 0) {
        printWarning("No patients to delete.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Patient ID to delete: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found with ID: %d", id);
        pressAnyKey();
        return;
    }

    displayPatientDetails(index);

    int confirm = validateInt("\nAre you sure you want to discharge this patient? (1=Yes, 0=No): ", 0, 1);

    if (confirm) {
        patients[index].status = 0;
        do {
            printf(WHT "Enter Discharge Date (DD/MM/YYYY): " RESET);
            fgets(patients[index].dischargeDate, sizeof(patients[index].dischargeDate), stdin);
            patients[index].dischargeDate[strcspn(patients[index].dischargeDate, "\n")] = 0;
        } while (!validateDate(patients[index].dischargeDate));

        printSuccess("Patient discharged successfully!");
        saveDataToFile();
    } else {
        printInfo("Operation cancelled.");
    }

    pressAnyKey();
}

void viewPatientDetails() {
    int id = validateInt("Enter Patient ID to view: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found with ID: %d", id);
        pressAnyKey();
        return;
    }

    clearScreen();
    displayHeader("PATIENT DETAILS");
    displayPatientDetails(index);
    pressAnyKey();
}

// ============================================================================
// SORTING FUNCTIONS
// ============================================================================

void sortPatientsByName() {
    if (patientCount < 2) {
        printInfo("Not enough patients to sort.");
        return;
    }

    printInfo("Sorting patients by name using Bubble Sort...");
    displayProgressBar(0, patientCount, "Sorting");

    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (strcasecmp(patients[j].name, patients[j + 1].name) > 0) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
        displayProgressBar(i + 1, patientCount, "Sorting");
    }

    printf("\n");
    printSuccess("Patients sorted by name successfully!");
    displayAllPatients();
}

void sortPatientsByID() {
    if (patientCount < 2) {
        printInfo("Not enough patients to sort.");
        return;
    }

    printInfo("Sorting patients by ID using Selection Sort...");
    displayProgressBar(0, patientCount, "Sorting");

    for (int i = 0; i < patientCount - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < patientCount; j++) {
            if (patients[j].id < patients[minIdx].id) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Patient temp = patients[i];
            patients[i] = patients[minIdx];
            patients[minIdx] = temp;
        }
        displayProgressBar(i + 1, patientCount, "Sorting");
    }

    printf("\n");
    printSuccess("Patients sorted by ID successfully!");
    displayAllPatients();
}

void sortPatientsByDisease() {
    if (patientCount < 2) {
        printInfo("Not enough patients to sort.");
        return;
    }

    printInfo("Sorting patients by disease using Bubble Sort...");

    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (strcasecmp(patients[j].disease, patients[j + 1].disease) > 0) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }

    printSuccess("Patients sorted by disease successfully!");
    displayAllPatients();
}

void sortPatientsByAge() {
    if (patientCount < 2) {
        printInfo("Not enough patients to sort.");
        return;
    }

    printInfo("Sorting patients by age using Bubble Sort...");

    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patients[j].age > patients[j + 1].age) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }

    printSuccess("Patients sorted by age successfully!");
    displayAllPatients();
}

// ============================================================================
// APPOINTMENT MANAGEMENT FUNCTIONS
// ============================================================================

void scheduleAppointment() {
    clearScreen();
    displayHeader("SCHEDULE APPOINTMENT");

    if (patientCount == 0) {
        printWarning("No patients registered. Please add a patient first.");
        pressAnyKey();
        return;
    }

    if (appointmentCount >= appointmentCapacity) {
        expandAppointmentArray();
    }

    Appointment *newAppointment = &appointments[appointmentCount];
    newAppointment->appointmentId = nextAppointmentId++;

    printf("\n" BOLD "Appointment ID: " RESET "%d\n", newAppointment->appointmentId);

    displayAllPatients();

    newAppointment->patientId = validateInt("Enter Patient ID: ", 1, 9999);
    int patientIndex = binarySearchByID(newAppointment->patientId);
    if (patientIndex == -1) {
        printError("Patient not found!");
        return;
    }

    strcpy(newAppointment->doctor, patients[patientIndex].doctor);
    validateString(newAppointment->date, 19, "Enter Date (DD/MM/YYYY): ");
    validateString(newAppointment->time, 9, "Enter Time (HH:MM): ");
    validateString(newAppointment->reason, MAX_STRING - 1, "Enter Reason for Appointment: ");

    newAppointment->status = 1;

    appointmentCount++;
    operationCounter++;
    printSuccess("Appointment scheduled successfully! ID: %d", newAppointment->appointmentId);

    saveAppointmentsToFile();
    pressAnyKey();
}

void viewAllAppointments() {
    clearScreen();
    displayHeader("ALL APPOINTMENTS");

    if (appointmentCount == 0) {
        printWarning("No appointments scheduled.");
        pressAnyKey();
        return;
    }

    printf(BOLD CYN);
    printf("+------+----------+-----------------------+------------+---------+---------------+----------------------+\n");
    printf("| App  | Patient  | Doctor                | Date       | Time    | Status        | Reason               |\n");
    printf("+------+----------+-----------------------+------------+---------+---------------+----------------------+\n");
    printf(RESET);

    for (int i = 0; i < appointmentCount; i++) {
        Appointment *a = &appointments[i];
        printf("| %5d| %8d| %-21s| %-10s| %-9s| %-13s| %-20s|\n",
               a->appointmentId,
               a->patientId,
               a->doctor,
               a->date,
               a->time,
               a->status == 1 ? "Scheduled" :
               a->status == 2 ? "Completed" : "Cancelled",
               a->reason);
    }

    printf(BOLD CYN);
    printf("+------+----------+-----------------------+------------+---------+---------------+----------------------+\n");
    printf(RESET);

    printf("\n" BOLD "Total Appointments: " RESET "%d\n", appointmentCount);
    pressAnyKey();
}

void cancelAppointment() {
    clearScreen();
    displayHeader("CANCEL APPOINTMENT");

    if (appointmentCount == 0) {
        printWarning("No appointments to cancel.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Appointment ID to cancel: ", 1, 9999);

    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].appointmentId == id) {
            if (appointments[i].status == 1) {
                appointments[i].status = 3;
                printSuccess("Appointment cancelled successfully!");
                saveAppointmentsToFile();
            } else {
                printWarning("Appointment is already %s",
                           appointments[i].status == 2 ? "Completed" : "Cancelled");
            }
            pressAnyKey();
            return;
        }
    }

    printError("Appointment not found with ID: %d", id);
    pressAnyKey();
}

void completeAppointment() {
    clearScreen();
    displayHeader("COMPLETE APPOINTMENT");

    if (appointmentCount == 0) {
        printWarning("No appointments to complete.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Appointment ID to complete: ", 1, 9999);

    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].appointmentId == id) {
            if (appointments[i].status == 1) {
                appointments[i].status = 2;
                printSuccess("Appointment marked as completed!");
                saveAppointmentsToFile();
            } else {
                printWarning("Appointment is already %s",
                           appointments[i].status == 2 ? "Completed" : "Cancelled");
            }
            pressAnyKey();
            return;
        }
    }

    printError("Appointment not found with ID: %d", id);
    pressAnyKey();
}

void viewPatientAppointments() {
    clearScreen();
    displayHeader("PATIENT APPOINTMENTS");

    if (patientCount == 0) {
        printWarning("No patients registered.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Patient ID: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found!");
        pressAnyKey();
        return;
    }

    printf("\n" BOLD "Appointments for Patient: %s (ID: %d)\n" RESET, patients[index].name, id);

    int found = 0;
    printf(BOLD CYN);
    printf("+------+------------+---------+---------------+----------------------+\n");
    printf("| App  | Date       | Time    | Status        | Reason               |\n");
    printf("+------+------------+---------+---------------+----------------------+\n");
    printf(RESET);

    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].patientId == id) {
            printf("| %5d| %-10s| %-9s| %-13s| %-20s|\n",
                   appointments[i].appointmentId,
                   appointments[i].date,
                   appointments[i].time,
                   appointments[i].status == 1 ? "Scheduled" :
                   appointments[i].status == 2 ? "Completed" : "Cancelled",
                   appointments[i].reason);
            found++;
        }
    }

    printf(BOLD CYN);
    printf("+------+------------+---------+---------------+----------------------+\n");
    printf(RESET);

    if (found == 0) {
        printWarning("No appointments found for this patient.");
    } else {
        printSuccess("Found %d appointments for this patient.", found);
    }

    pressAnyKey();
}

// ============================================================================
// BILLING SYSTEM FUNCTIONS
// ============================================================================

void calculateBill() {
    int id = validateInt("Enter Patient ID to calculate bill: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found!");
        return;
    }

    Patient *p = &patients[index];

    printf("\n" BOLD "Bill Calculation for %s:\n" RESET, p->name);
    printf("+-------------------------------------------------------------+\n");
    printf("| Base Consultation Fee:  $%45.2f |\n", 50.00);
    printf("| Daily Room Charge:      $%45.2f |\n", 100.00);
    printf("| Medication:             $%45.2f |\n", 75.00);
    printf("| Lab Tests:              $%45.2f |\n", 60.00);
    printf("| Surgery Fee:            $%45.2f |\n", 200.00);
    printf("| Emergency Services:     $%45.2f |\n", 150.00);
    printf("+-------------------------------------------------------------+\n");
    printf("| " BOLD "Total:" RESET "                  $%45.2f |\n", 635.00);
    printf("+-------------------------------------------------------------+\n");

    p->bill = 635.00;
    printSuccess("Bill calculated: $%.2f", p->bill);
    saveDataToFile();
}

void generateBill() {
    clearScreen();
    displayHeader("GENERATE BILL");

    if (patientCount == 0) {
        printWarning("No patients registered.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Patient ID: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found!");
        pressAnyKey();
        return;
    }

    Patient *p = &patients[index];

    clearScreen();
    displayHeader("HOSPITAL BILL");

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Patient Bill" CYN "                                    |\n");
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
    printf("| " BOLD "Patient ID:" RESET "      %-44d |\n", p->id);
    printf("| " BOLD "Name:" RESET "            %-44s |\n", p->name);
    printf("| " BOLD "Doctor:" RESET "         %-44s |\n", p->doctor);
    printf("| " BOLD "Ward/Room:" RESET "      %d / %-40d |\n", p->ward, p->room);
    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Charges" CYN "                                       |\n");
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
    printf("| " BOLD "Consultation Fee:" RESET "   $%-42.2f |\n", 50.00);
    printf("| " BOLD "Room Charges:" RESET "       $%-42.2f |\n", 100.00);
    printf("| " BOLD "Medication:" RESET "          $%-42.2f |\n", 75.00);
    printf("| " BOLD "Lab Tests:" RESET "           $%-42.2f |\n", 60.00);
    printf("| " BOLD "Surgery Fee:" RESET "         $%-42.2f |\n", 200.00);
    printf("| " BOLD "Emergency Services:" RESET "  $%-42.2f |\n", 150.00);
    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " BOLD "Total Amount:" RESET "       $%-42.2f |\n", p->bill);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    pressAnyKey();
}

void processPayment() {
    clearScreen();
    displayHeader("PROCESS PAYMENT");

    if (patientCount == 0) {
        printWarning("No patients registered.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Patient ID: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found!");
        pressAnyKey();
        return;
    }

    Patient *p = &patients[index];

    printf("\n" BOLD "Patient: %s\n" RESET, p->name);
    printf("Current Bill: $%.2f\n", p->bill);

    if (p->bill <= 0) {
        printWarning("Patient has no outstanding bill.");
        pressAnyKey();
        return;
    }

    if (paymentCount >= paymentCapacity) {
        expandPaymentArray();
    }

    Payment *payment = &payments[paymentCount];
    payment->paymentId = nextPaymentId++;
    payment->patientId = id;
    payment->amount = p->bill;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(payment->date, sizeof(payment->date), "%d/%m/%Y", t);

    validateString(payment->paymentMethod, 19, "Payment Method (Cash/Card/Bank): ");
    validateString(payment->description, MAX_STRING - 1, "Payment Description: ");

    p->bill = 0;
    paymentCount++;

    printSuccess("Payment processed successfully! Amount: $%.2f", payment->amount);
    saveDataToFile();
    pressAnyKey();
}

void viewPaymentHistory() {
    clearScreen();
    displayHeader("PAYMENT HISTORY");

    if (paymentCount == 0) {
        printWarning("No payment records found.");
        pressAnyKey();
        return;
    }

    printf(BOLD CYN);
    printf("+----------+----------+------------+------------+-------------------+----------------------+\n");
    printf("| Pay ID   | Patient  | Amount     | Date       | Method            | Description          |\n");
    printf("+----------+----------+------------+------------+-------------------+----------------------+\n");
    printf(RESET);

    for (int i = 0; i < paymentCount; i++) {
        Payment *p = &payments[i];
        printf("| %8d| %8d| %10.2f| %-10s| %-17s| %-20s|\n",
               p->paymentId,
               p->patientId,
               p->amount,
               p->date,
               p->paymentMethod,
               p->description);
    }

    printf(BOLD CYN);
    printf("+----------+----------+------------+------------+-------------------+----------------------+\n");
    printf(RESET);

    pressAnyKey();
}

void generateInvoice() {
    clearScreen();
    displayHeader("GENERATE INVOICE");

    if (paymentCount == 0) {
        printWarning("No payments to generate invoice.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Payment ID for invoice: ", 1, 9999);

    for (int i = 0; i < paymentCount; i++) {
        if (payments[i].paymentId == id) {
            FILE *invoice = fopen("invoice.txt", "w");
            if (invoice == NULL) {
                printError("Cannot create invoice file");
                return;
            }

            fprintf(invoice, "================================================\n");
            fprintf(invoice, "         HOSPITAL MANAGEMENT SYSTEM\n");
            fprintf(invoice, "               INVOICE\n");
            fprintf(invoice, "================================================\n");
            fprintf(invoice, "Invoice ID: %d\n", payments[i].paymentId);
            fprintf(invoice, "Patient ID: %d\n", payments[i].patientId);
            fprintf(invoice, "Date: %s\n", payments[i].date);
            fprintf(invoice, "Amount: $%.2f\n", payments[i].amount);
            fprintf(invoice, "Method: %s\n", payments[i].paymentMethod);
            fprintf(invoice, "Description: %s\n", payments[i].description);
            fprintf(invoice, "================================================\n");
            fprintf(invoice, "Thank you for choosing our hospital!\n");

            fclose(invoice);
            printSuccess("Invoice generated: invoice.txt");
            pressAnyKey();
            return;
        }
    }

    printError("Payment not found with ID: %d", id);
    pressAnyKey();
}

// ============================================================================
// MEDICAL RECORDS FUNCTIONS
// ============================================================================

void addMedicalRecord() {
    clearScreen();
    displayHeader("ADD MEDICAL RECORD");

    if (patientCount == 0) {
        printWarning("No patients registered.");
        pressAnyKey();
        return;
    }

    if (medicalRecordCount >= medicalRecordCapacity) {
        expandMedicalRecordArray();
    }

    int id = validateInt("Enter Patient ID: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found!");
        pressAnyKey();
        return;
    }

    MedicalRecord *record = &medicalRecords[medicalRecordCount];
    record->recordId = nextRecordId++;
    record->patientId = id;

    printf("\n" BOLD "Record ID: " RESET "%d\n", record->recordId);
    printf(BOLD "Patient: %s\n" RESET, patients[index].name);

    validateString(record->diagnosis, MAX_STRING - 1, "Enter Diagnosis: ");
    validateString(record->prescription, MAX_STRING - 1, "Enter Prescription: ");
    validateString(record->testResults, MAX_STRING - 1, "Enter Test Results: ");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(record->date, sizeof(record->date), "%d/%m/%Y", t);

    medicalRecordCount++;
    printSuccess("Medical record added successfully!");
    saveMedicalRecordsToFile();
    pressAnyKey();
}

void viewMedicalRecords() {
    clearScreen();
    displayHeader("MEDICAL RECORDS");

    if (medicalRecordCount == 0) {
        printWarning("No medical records found.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Patient ID to view records: ", 1, 9999);

    int found = 0;
    printf(BOLD CYN);
    printf("+----------+----------------------+----------------------+----------------------+------------+\n");
    printf("| Record   | Diagnosis            | Prescription         | Test Results         | Date       |\n");
    printf("+----------+----------------------+----------------------+----------------------+------------+\n");
    printf(RESET);

    for (int i = 0; i < medicalRecordCount; i++) {
        if (medicalRecords[i].patientId == id) {
            printf("| %8d| %-20s| %-20s| %-20s| %-10s|\n",
                   medicalRecords[i].recordId,
                   medicalRecords[i].diagnosis,
                   medicalRecords[i].prescription,
                   medicalRecords[i].testResults,
                   medicalRecords[i].date);
            found++;
        }
    }

    printf(BOLD CYN);
    printf("+----------+----------------------+----------------------+----------------------+------------+\n");
    printf(RESET);

    if (found == 0) {
        printWarning("No medical records found for this patient.");
    } else {
        printSuccess("Found %d medical records for this patient.", found);
    }

    pressAnyKey();
}

void updateMedicalRecord() {
    clearScreen();
    displayHeader("UPDATE MEDICAL RECORD");

    if (medicalRecordCount == 0) {
        printWarning("No medical records to update.");
        pressAnyKey();
        return;
    }

    int recordId = validateInt("Enter Record ID to update: ", 1, 9999);

    for (int i = 0; i < medicalRecordCount; i++) {
        if (medicalRecords[i].recordId == recordId) {
            printf("\n" BOLD "Current Record:\n" RESET);
            printf("Diagnosis: %s\n", medicalRecords[i].diagnosis);
            printf("Prescription: %s\n", medicalRecords[i].prescription);
            printf("Test Results: %s\n", medicalRecords[i].testResults);

            printf("\n" BOLD "Enter new values (press Enter to keep current):\n" RESET);
            char buffer[MAX_STRING];

            printf("Diagnosis [%s]: ", medicalRecords[i].diagnosis);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) {
                strcpy(medicalRecords[i].diagnosis, buffer);
            }

            printf("Prescription [%s]: ", medicalRecords[i].prescription);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) {
                strcpy(medicalRecords[i].prescription, buffer);
            }

            printf("Test Results [%s]: ", medicalRecords[i].testResults);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) {
                strcpy(medicalRecords[i].testResults, buffer);
            }

            printSuccess("Medical record updated successfully!");
            saveMedicalRecordsToFile();
            pressAnyKey();
            return;
        }
    }

    printError("Record not found with ID: %d", recordId);
    pressAnyKey();
}

void viewPatientHistory() {
    clearScreen();
    displayHeader("PATIENT HISTORY");

    if (patientCount == 0) {
        printWarning("No patients registered.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Patient ID: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found!");
        pressAnyKey();
        return;
    }

    printf("\n" BOLD "Patient: %s (ID: %d)\n" RESET, patients[index].name, id);
    printf(BOLD "Medical History:\n" RESET);

    int found = 0;
    for (int i = 0; i < medicalRecordCount; i++) {
        if (medicalRecords[i].patientId == id) {
            printf("\n  Record ID: %d\n", medicalRecords[i].recordId);
            printf("  Date: %s\n", medicalRecords[i].date);
            printf("  Diagnosis: %s\n", medicalRecords[i].diagnosis);
            printf("  Prescription: %s\n", medicalRecords[i].prescription);
            printf("  Test Results: %s\n", medicalRecords[i].testResults);
            printf("  +-------------------------------------------------+\n");
            found++;
        }
    }

    if (found == 0) {
        printWarning("No medical history found for this patient.");
    }

    pressAnyKey();
}

// ============================================================================
// DOCTOR MANAGEMENT FUNCTIONS
// ============================================================================

void addDoctor() {
    clearScreen();
    displayHeader("ADD DOCTOR");

    if (doctorCount >= doctorCapacity) {
        expandDoctorArray();
    }

    Doctor *newDoctor = &doctors[doctorCount];
    newDoctor->id = nextDoctorId++;

    printf("\n" BOLD "Doctor ID: " RESET "%d\n", newDoctor->id);

    validateString(newDoctor->name, MAX_STRING - 1, "Enter Doctor Name: ");
    validateString(newDoctor->specialization, MAX_STRING - 1, "Enter Specialization: ");
    validateString(newDoctor->phone, 14, "Enter Phone Number: ");
    newDoctor->available = validateInt("Is Doctor Available? (1=Yes, 0=No): ", 0, 1);

    doctorCount++;
    printSuccess("Doctor added successfully! ID: %d", newDoctor->id);
    saveDoctorsToFile();
    pressAnyKey();
}

void viewAllDoctors() {
    clearScreen();
    displayHeader("ALL DOCTORS");

    if (doctorCount == 0) {
        printWarning("No doctors registered.");
        pressAnyKey();
        return;
    }

    printf(BOLD CYN);
    printf("+-----+----------------------+----------------------+--------------+------------------+\n");
    printf("| ID  | Name                 | Specialization       | Phone        | Availability     |\n");
    printf("+-----+----------------------+----------------------+--------------+------------------+\n");
    printf(RESET);

    for (int i = 0; i < doctorCount; i++) {
        printf("| %4d| %-20s| %-20s| %-12s| %-16s|\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialization,
               doctors[i].phone,
               doctors[i].available ? "Available" : "Not Available");
    }

    printf(BOLD CYN);
    printf("+-----+----------------------+----------------------+--------------+------------------+\n");
    printf(RESET);

    pressAnyKey();
}

void updateDoctor() {
    clearScreen();
    displayHeader("UPDATE DOCTOR");

    if (doctorCount == 0) {
        printWarning("No doctors to update.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Doctor ID to update: ", 1, 9999);

    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == id) {
            printf("\n" BOLD "Current Doctor Details:\n" RESET);
            printf("Name: %s\n", doctors[i].name);
            printf("Specialization: %s\n", doctors[i].specialization);
            printf("Phone: %s\n", doctors[i].phone);
            printf("Available: %s\n", doctors[i].available ? "Yes" : "No");

            printf("\n" BOLD "Enter new values (press Enter to keep current):\n" RESET);
            char buffer[MAX_STRING];

            printf("Name [%s]: ", doctors[i].name);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) {
                strcpy(doctors[i].name, buffer);
            }

            printf("Specialization [%s]: ", doctors[i].specialization);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) {
                strcpy(doctors[i].specialization, buffer);
            }

            printf("Phone [%s]: ", doctors[i].phone);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) {
                strcpy(doctors[i].phone, buffer);
            }

            doctors[i].available = validateInt("Available? (1=Yes, 0=No): ", 0, 1);

            printSuccess("Doctor updated successfully!");
            saveDoctorsToFile();
            pressAnyKey();
            return;
        }
    }

    printError("Doctor not found with ID: %d", id);
    pressAnyKey();
}

void deleteDoctor() {
    clearScreen();
    displayHeader("DELETE DOCTOR");

    if (doctorCount == 0) {
        printWarning("No doctors to delete.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Doctor ID to delete: ", 1, 9999);

    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == id) {
            printf("\n" BOLD "Doctor to delete:\n" RESET);
            printf("Name: %s\n", doctors[i].name);
            printf("Specialization: %s\n", doctors[i].specialization);

            int confirm = validateInt("Are you sure? (1=Yes, 0=No): ", 0, 1);
            if (confirm) {
                for (int j = i; j < doctorCount - 1; j++) {
                    doctors[j] = doctors[j + 1];
                }
                doctorCount--;
                printSuccess("Doctor deleted successfully!");
                saveDoctorsToFile();
            } else {
                printInfo("Deletion cancelled.");
            }
            pressAnyKey();
            return;
        }
    }

    printError("Doctor not found with ID: %d", id);
    pressAnyKey();
}

void assignDoctorToPatient() {
    clearScreen();
    displayHeader("ASSIGN DOCTOR TO PATIENT");

    if (patientCount == 0 || doctorCount == 0) {
        printWarning("Need both patients and doctors registered.");
        pressAnyKey();
        return;
    }

    int id = validateInt("Enter Patient ID: ", 1, 9999);
    int index = binarySearchByID(id);

    if (index == -1) {
        printError("Patient not found!");
        pressAnyKey();
        return;
    }

    printf("\n" BOLD "Current Doctor: " RESET "%s\n", patients[index].doctor);
    printf(BOLD "Available Doctors:\n" RESET);

    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].available) {
            printf("  %d. %s - %s\n", i+1, doctors[i].name, doctors[i].specialization);
        }
    }

    int choice = validateInt("Select Doctor (0 to enter manually): ", 0, doctorCount);
    if (choice > 0 && choice <= doctorCount) {
        strcpy(patients[index].doctor, doctors[choice-1].name);
        printSuccess("Doctor assigned successfully!");
    } else {
        validateString(patients[index].doctor, MAX_STRING - 1, "Enter Doctor Name: ");
    }

    saveDataToFile();
    pressAnyKey();
}

// ============================================================================
// WARD MANAGEMENT FUNCTIONS
// ============================================================================

void initializeWards() {
    wardCount = 10;
    wards = (Ward*)malloc(wardCount * sizeof(Ward));
    if (wards == NULL) {
        printError("Failed to initialize wards");
        return;
    }

    char *wardNames[] = {
        "General Medicine", "Surgery", "Cardiology", "Neurology",
        "Pediatrics", "Orthopedics", "Gynecology", "ICU",
        "Emergency", "Maternity"
    };
    int capacities[] = {50, 40, 30, 25, 35, 30, 30, 20, 25, 30};

    for (int i = 0; i < wardCount; i++) {
        wards[i].wardNumber = i + 1;
        strcpy(wards[i].name, wardNames[i]);
        wards[i].totalBeds = capacities[i];
        wards[i].occupiedBeds = 0;
        wards[i].availableBeds = capacities[i];
    }
}

void viewWardStatus() {
    clearScreen();
    displayHeader("WARD STATUS");

    if (wards == NULL) {
        initializeWards();
    }

    // Update occupancy
    for (int i = 0; i < wardCount; i++) {
        wards[i].occupiedBeds = 0;
        for (int j = 0; j < patientCount; j++) {
            if (patients[j].status == 1 && patients[j].ward == wards[i].wardNumber) {
                wards[i].occupiedBeds++;
            }
        }
        wards[i].availableBeds = wards[i].totalBeds - wards[i].occupiedBeds;
    }

    printf(BOLD CYN);
    printf("+----------+----------------------+----------+------------+------------+------------------+\n");
    printf("| Ward     | Name                 | Total    | Occupied   | Available  | Occupancy         |\n");
    printf("+----------+----------------------+----------+------------+------------+------------------+\n");
    printf(RESET);

    for (int i = 0; i < wardCount; i++) {
        int occupancy = (wards[i].totalBeds > 0) ?
            (wards[i].occupiedBeds * 100) / wards[i].totalBeds : 0;

        const char *statusColor = (occupancy < 50) ? GRN :
                                   (occupancy < 80) ? YEL : RED;

        printf("| %8d| %-20s| %8d| %10d| %10d| ",
               wards[i].wardNumber,
               wards[i].name,
               wards[i].totalBeds,
               wards[i].occupiedBeds,
               wards[i].availableBeds);
    printf("%s%3d%%" RESET "             |\n", statusColor, occupancy);
    }

    printf(BOLD CYN);
    printf("+----------+----------------------+----------+------------+------------+------------------+\n");
    printf(RESET);

    pressAnyKey();
}

void updateWard() {
    clearScreen();
    displayHeader("UPDATE WARD");

    if (wards == NULL) {
        initializeWards();
    }

    int wardNum = validateInt("Enter Ward Number (1-10): ", 1, 10);
    int index = wardNum - 1;

    printf("\n" BOLD "Current Ward Details:\n" RESET);
    printf("Name: %s\n", wards[index].name);
    printf("Total Beds: %d\n", wards[index].totalBeds);
    printf("Occupied Beds: %d\n", wards[index].occupiedBeds);
    printf("Available Beds: %d\n", wards[index].availableBeds);

    char buffer[MAX_STRING];
    printf("\n" BOLD "Enter new ward name (press Enter to keep): " RESET);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(wards[index].name, buffer);
    }

    int newCapacity = validateInt("Enter new total beds (current: %d): ", 0, 100);
    if (newCapacity > 0) {
        wards[index].totalBeds = newCapacity;
        wards[index].availableBeds = wards[index].totalBeds - wards[index].occupiedBeds;
    }

    printSuccess("Ward updated successfully!");
    pressAnyKey();
}

void viewWardPatients() {
    clearScreen();
    displayHeader("WARD PATIENTS");

    if (patientCount == 0) {
        printWarning("No patients registered.");
        pressAnyKey();
        return;
    }

    int wardNum = validateInt("Enter Ward Number (1-10): ", 1, 10);

    printf("\n" BOLD "Patients in Ward %d:\n" RESET, wardNum);

    int found = 0;
    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf("| ID  | Name                 | Age | Gender   | Disease               |\n");
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf(RESET);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].status == 1 && patients[i].ward == wardNum) {
            printf("| %4d| %-20s| %4d| %-8c| %-21s|\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].age,
                   patients[i].gender,
                   patients[i].disease);
            found++;
        }
    }

    printf(BOLD CYN);
    printf("+-----+----------------------+-----+----------+-----------------------+\n");
    printf(RESET);

    if (found == 0) {
        printWarning("No patients in Ward %d", wardNum);
    } else {
        printSuccess("Found %d patients in Ward %d", found, wardNum);
    }

    pressAnyKey();
}

// ============================================================================
// REPORT FUNCTIONS
// ============================================================================

void generateDailyReport() {
    clearScreen();
    displayHeader("DAILY REPORT");

    if (patientCount == 0) {
        printWarning("No patients to report.");
        pressAnyKey();
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char today[20];
    strftime(today, sizeof(today), "%d/%m/%Y", t);

    int activeCount = 0, dischargedCount = 0;
    float totalRevenue = 0;
    int maleCount = 0, femaleCount = 0;

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].status == 1) {
            activeCount++;
        } else {
            dischargedCount++;
        }
        totalRevenue += patients[i].bill;
        if (patients[i].gender == 'M') maleCount++;
        else femaleCount++;
    }

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Daily Report - %s" CYN "                        |\n", today);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
    printf("| " BOLD "Total Patients:" RESET "      %-44d |\n", patientCount);
    printf("| " BOLD "Active Patients:" RESET "     %-44d |\n", activeCount);
    printf("| " BOLD "Discharged:" RESET "          %-44d |\n", dischargedCount);
    printf("| " BOLD "Male Patients:" RESET "       %-44d |\n", maleCount);
    printf("| " BOLD "Female Patients:" RESET "     %-44d |\n", femaleCount);
    printf("| " BOLD "Total Revenue:" RESET "       $%-44.2f |\n", totalRevenue);
    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    printf("\n" BOLD "Recent Admissions:\n" RESET);
    int count = 0;
    for (int i = patientCount - 1; i >= 0 && count < 5; i--) {
        if (patients[i].status == 1) {
            printf("  - %s (ID: %d) - %s\n", patients[i].name, patients[i].id, patients[i].disease);
            count++;
        }
    }

    pressAnyKey();
}

void generateMonthlyStatistics() {
    clearScreen();
    displayHeader("MONTHLY STATISTICS");

    if (patientCount == 0) {
        printWarning("No data available.");
        pressAnyKey();
        return;
    }

    int month = validateInt("Enter Month (1-12): ", 1, 12);
    int year = validateInt("Enter Year (2020-2030): ", 2020, 2030);

    int admissions = 0, discharges = 0;
    float revenue = 0;

    for (int i = 0; i < patientCount; i++) {
        char admissionMonth[5];
        strncpy(admissionMonth, patients[i].admissionDate, 2);
        admissionMonth[2] = '\0';

        int patientMonth = atoi(admissionMonth);
        if (patientMonth == month) {
            admissions++;
            revenue += patients[i].bill;
        }
    }

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Monthly Statistics - %02d/%d" CYN "                     |\n", month, year);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
    printf("| " BOLD "Total Admissions:" RESET "   %-44d |\n", admissions);
    printf("| " BOLD "Total Revenue:" RESET "      $%-44.2f |\n", revenue);
    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    pressAnyKey();
}

void generateDoctorReport() {
    clearScreen();
    displayHeader("DOCTOR REPORT");

    if (patientCount == 0) {
        printWarning("No patients to report.");
        pressAnyKey();
        return;
    }

    char doctorName[MAX_STRING];
    validateString(doctorName, MAX_STRING - 1, "Enter Doctor Name: ");

    int count = 0;
    float revenue = 0;

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Patients under Dr. %s" CYN "                      |\n", doctorName);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    for (int i = 0; i < patientCount; i++) {
        if (strcasecmp(patients[i].doctor, doctorName) == 0) {
            printf("| %-3d | %-20s | %-10s | $%8.2f |\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].disease,
                   patients[i].bill);
            count++;
            revenue += patients[i].bill;
        }
    }

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Total Patients: %-40d " CYN "|\n", count);
    printf("| " WHT "Total Revenue:  $%-39.2f " CYN "|\n", revenue);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    if (count == 0) {
        printWarning("No patients found for Dr. %s", doctorName);
    }

    pressAnyKey();
}

void generateWardReport() {
    clearScreen();
    displayHeader("WARD REPORT");

    if (patientCount == 0) {
        printWarning("No patients to report.");
        pressAnyKey();
        return;
    }

    int wardCounts[11] = {0};
    int wardPatients[11][MAX_PATIENTS] = {0};
    int wardPatientCounts[11] = {0};

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].status == 1) {
            int ward = patients[i].ward;
            if (ward >= 1 && ward <= 10) {
                wardCounts[ward]++;
                wardPatients[ward][wardPatientCounts[ward]++] = i;
            }
        }
    }

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Ward Occupancy Report" CYN "                         |\n");
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    for (int i = 1; i <= 10; i++) {
        int occupancy = (wardCounts[i] * 100) / 50;
        if (occupancy > 100) occupancy = 100;

        printf("| " BOLD "Ward %2d:" RESET " %3d patients [", i, wardCounts[i]);

        int barWidth = 30;
        int pos = (barWidth * wardCounts[i]) / 50;
        if (pos > barWidth) pos = barWidth;

        for (int j = 0; j < barWidth; j++) {
            if (j < pos) printf(GRN "=" RESET);
            else if (j == pos) printf(YEL ">" RESET);
            else printf(" ");
        }
        printf("] %3d%% |\n", occupancy);
    }

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    pressAnyKey();
}

void generateDiseaseReport() {
    clearScreen();
    displayHeader("DISEASE REPORT");

    if (patientCount == 0) {
        printWarning("No patients to report.");
        pressAnyKey();
        return;
    }

    char diseases[MAX_PATIENTS][MAX_STRING];
    int diseaseCounts[MAX_PATIENTS] = {0};
    int uniqueDiseases = 0;

    for (int i = 0; i < patientCount; i++) {
        int found = 0;
        for (int j = 0; j < uniqueDiseases; j++) {
            if (strcasecmp(diseases[j], patients[i].disease) == 0) {
                diseaseCounts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(diseases[uniqueDiseases], patients[i].disease);
            diseaseCounts[uniqueDiseases]++;
            uniqueDiseases++;
        }
    }

    for (int i = 0; i < uniqueDiseases - 1; i++) {
        for (int j = 0; j < uniqueDiseases - i - 1; j++) {
            if (diseaseCounts[j] < diseaseCounts[j + 1]) {
                int tempCount = diseaseCounts[j];
                diseaseCounts[j] = diseaseCounts[j + 1];
                diseaseCounts[j + 1] = tempCount;

                char tempName[MAX_STRING];
                strcpy(tempName, diseases[j]);
                strcpy(diseases[j], diseases[j + 1]);
                strcpy(diseases[j + 1], tempName);
            }
        }
    }

    printf(BOLD CYN);
    printf("+----------------------+----------+------------------+\n");
    printf("| Disease              | Patients | Percentage       |\n");
    printf("+----------------------+----------+------------------+\n");
    printf(RESET);

    for (int i = 0; i < uniqueDiseases && i < 20; i++) {
        int percentage = (diseaseCounts[i] * 100) / patientCount;
        printf("| %-20s | %8d | %16d%% |\n",
               diseases[i], diseaseCounts[i], percentage);
    }

    printf(BOLD CYN);
    printf("+----------------------+----------+------------------+\n");
    printf(RESET);

    pressAnyKey();
}

void generateRevenueReport() {
    clearScreen();
    displayHeader("REVENUE REPORT");

    if (paymentCount == 0) {
        printWarning("No payment records found.");
        pressAnyKey();
        return;
    }

    float totalRevenue = 0;
    float cashRevenue = 0, cardRevenue = 0, bankRevenue = 0;

    for (int i = 0; i < paymentCount; i++) {
        totalRevenue += payments[i].amount;
        if (strcasecmp(payments[i].paymentMethod, "Cash") == 0) {
            cashRevenue += payments[i].amount;
        } else if (strcasecmp(payments[i].paymentMethod, "Card") == 0) {
            cardRevenue += payments[i].amount;
        } else {
            bankRevenue += payments[i].amount;
        }
    }

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Revenue Report" CYN "                                  |\n");
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
    printf("| " BOLD "Total Revenue:" RESET "        $%-44.2f |\n", totalRevenue);
    printf("| " BOLD "Cash Payments:" RESET "       $%-44.2f |\n", cashRevenue);
    printf("| " BOLD "Card Payments:" RESET "       $%-44.2f |\n", cardRevenue);
    printf("| " BOLD "Bank Payments:" RESET "       $%-44.2f |\n", bankRevenue);
    printf("| " BOLD "Total Transactions:" RESET "  %-44d |\n", paymentCount);
    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    pressAnyKey();
}

void generatePatientReport() {
    clearScreen();
    displayHeader("PATIENT SUMMARY REPORT");

    if (patientCount == 0) {
        printWarning("No patients to report.");
        pressAnyKey();
        return;
    }

    int active = 0, discharged = 0;
    int male = 0, female = 0;
    float avgAge = 0;
    float totalBills = 0;

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].status) active++;
        else discharged++;
        if (patients[i].gender == 'M') male++;
        else female++;
        avgAge += patients[i].age;
        totalBills += patients[i].bill;
    }
    avgAge /= patientCount;

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "Patient Summary Report" CYN "                         |\n");
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
    printf("| " BOLD "Total Patients:" RESET "      %-44d |\n", patientCount);
    printf("| " BOLD "Active Patients:" RESET "     %-44d |\n", active);
    printf("| " BOLD "Discharged:" RESET "          %-44d |\n", discharged);
    printf("| " BOLD "Male/Female:" RESET "         %d / %-40d |\n", male, female);
    printf("| " BOLD "Average Age:" RESET "         %-44.1f |\n", avgAge);
    printf("| " BOLD "Total Bills:" RESET "         $%-44.2f |\n", totalBills);
    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    pressAnyKey();
}

// ============================================================================
// ADMINISTRATION FUNCTIONS
// ============================================================================

void assignDoctor() {
    assignDoctorToPatient();
}

void manageWards() {
    clearScreen();
    displayHeader("WARD MANAGEMENT");

    printf("\n" BOLD "1." RESET " View Ward Status\n");
    printf(BOLD "2." RESET " Update Ward\n");
    printf(BOLD "3." RESET " View Ward Patients\n");
    printf(BOLD "0." RESET " Back\n");

    int choice = validateInt("Enter your choice: ", 0, 3);

    switch (choice) {
        case 1: viewWardStatus(); break;
        case 2: updateWard(); break;
        case 3: viewWardPatients(); break;
        case 0: return;
    }
}

void dischargePatient() {
    deletePatient();
}

void viewSystemStats() {
    clearScreen();
    displayHeader("SYSTEM STATISTICS");

    int activePatients = 0;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].status == 1) activePatients++;
    }

    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf("| " WHT "System Overview" CYN "                                 |\n");
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);
    printf("| " BOLD "Total Patients:" RESET "       %-44d |\n", patientCount);
    printf("| " BOLD "Active Patients:" RESET "      %-44d |\n", activePatients);
    printf("| " BOLD "Appointments:" RESET "         %-44d |\n", appointmentCount);
    printf("| " BOLD "Payments:" RESET "             %-44d |\n", paymentCount);
    printf("| " BOLD "Medical Records:" RESET "      %-44d |\n", medicalRecordCount);
    printf("| " BOLD "Doctors:" RESET "              %-44d |\n", doctorCount);
    printf(BOLD CYN);
    printf("+-------------------------------------------------------------+\n");
    printf(RESET);

    pressAnyKey();
}

// ============================================================================
// DATA MANAGEMENT MENU FUNCTIONS
// ============================================================================

void dataManagementMenu() {
    clearScreen();
    displayHeader("DATA MANAGEMENT");

    printf("\n" BOLD "1." RESET " Save Data\n");
    printf(BOLD "2." RESET " Load Data\n");
    printf(BOLD "3." RESET " Backup Data\n");
    printf(BOLD "4." RESET " Restore Data\n");
    printf(BOLD "5." RESET " Export to CSV\n");
    printf(BOLD "6." RESET " Export to JSON\n");
    printf(BOLD "7." RESET " Import from CSV\n");
    printf(BOLD "8." RESET " View Memory Usage\n");
    printf(BOLD "9." RESET " View Error Logs\n");
    printf(BOLD "10." RESET " Sort Patients by Name\n");
    printf(BOLD "11." RESET " Sort Patients by ID\n");
    printf(BOLD "12." RESET " Sort Patients by Disease\n");
    printf(BOLD "13." RESET " Sort Patients by Age\n");
    printf(BOLD "0." RESET " Back to Main Menu\n");

    int choice = validateInt("\nEnter your choice: ", 0, 13);

    switch (choice) {
        case 1: saveDataToFile(); break;
        case 2: loadDataFromFile(); break;
        case 3: backupData(); break;
        case 4: restoreData(); break;
        case 5: exportToCSV(); break;
        case 6: exportToJSON(); break;
        case 7: importFromCSV(); break;
        case 8: displayMemoryUsage(); break;
        case 9: viewErrorLogs(); break;
        case 10: sortPatientsByName(); break;
        case 11: sortPatientsByID(); break;
        case 12: sortPatientsByDisease(); break;
        case 13: sortPatientsByAge(); break;
        case 0: return;
    }
    pressAnyKey();
}

// ============================================================================
// MEDICAL MENU FUNCTIONS
// ============================================================================

void medicalMenu() {
    clearScreen();
    displayHeader("MEDICAL RECORDS");

    printf("\n" BOLD "1." RESET " Add Medical Record\n");
    printf(BOLD "2." RESET " View Medical Records\n");
    printf(BOLD "3." RESET " Update Medical Record\n");
    printf(BOLD "4." RESET " View Patient History\n");
    printf(BOLD "0." RESET " Back to Main Menu\n");

    int choice = validateInt("\nEnter your choice: ", 0, 4);

    switch (choice) {
        case 1: addMedicalRecord(); break;
        case 2: viewMedicalRecords(); break;
        case 3: updateMedicalRecord(); break;
        case 4: viewPatientHistory(); break;
        case 0: return;
    }
    pressAnyKey();
}

// ============================================================================
// REPORT MENU FUNCTIONS
// ============================================================================

void reportMenu() {
    clearScreen();
    displayHeader("REPORTS");

    printf("\n" BOLD "1." RESET " Daily Report\n");
    printf(BOLD "2." RESET " Monthly Statistics\n");
    printf(BOLD "3." RESET " Doctor Report\n");
    printf(BOLD "4." RESET " Ward Report\n");
    printf(BOLD "5." RESET " Disease Report\n");
    printf(BOLD "6." RESET " Revenue Report\n");
    printf(BOLD "7." RESET " Patient Summary\n");
    printf(BOLD "0." RESET " Back to Main Menu\n");

    int choice = validateInt("\nEnter your choice: ", 0, 7);

    switch (choice) {
        case 1: generateDailyReport(); break;
        case 2: generateMonthlyStatistics(); break;
        case 3: generateDoctorReport(); break;
        case 4: generateWardReport(); break;
        case 5: generateDiseaseReport(); break;
        case 6: generateRevenueReport(); break;
        case 7: generatePatientReport(); break;
        case 0: return;
    }
    pressAnyKey();
}

// ============================================================================
// ADMIN MENU FUNCTIONS
// ============================================================================

void adminMenu() {
    clearScreen();
    displayHeader("ADMINISTRATION");

    printf("\n" BOLD "1." RESET " Doctor Management\n");
    printf(BOLD "2." RESET " Ward Management\n");
    printf(BOLD "3." RESET " Discharge Patient\n");
    printf(BOLD "4." RESET " System Statistics\n");
    printf(BOLD "5." RESET " View All Appointments\n");
    printf(BOLD "6." RESET " Schedule Appointment\n");
    printf(BOLD "7." RESET " Complete Appointment\n");
    printf(BOLD "8." RESET " Cancel Appointment\n");
    printf(BOLD "9." RESET " View Patient Appointments\n");
    printf(BOLD "0." RESET " Back to Main Menu\n");

    int choice = validateInt("\nEnter your choice: ", 0, 9);

    switch (choice) {
        case 1: {
            clearScreen();
            displayHeader("DOCTOR MANAGEMENT");
            printf("\n" BOLD "1." RESET " Add Doctor\n");
            printf(BOLD "2." RESET " View All Doctors\n");
            printf(BOLD "3." RESET " Update Doctor\n");
            printf(BOLD "4." RESET " Delete Doctor\n");
            printf(BOLD "5." RESET " Assign Doctor to Patient\n");
            printf(BOLD "0." RESET " Back\n");
            int docChoice = validateInt("Enter your choice: ", 0, 5);
            switch (docChoice) {
                case 1: addDoctor(); break;
                case 2: viewAllDoctors(); break;
                case 3: updateDoctor(); break;
                case 4: deleteDoctor(); break;
                case 5: assignDoctorToPatient(); break;
                case 0: break;
            }
            break;
        }
        case 2: manageWards(); break;
        case 3: dischargePatient(); break;
        case 4: viewSystemStats(); break;
        case 5: viewAllAppointments(); break;
        case 6: scheduleAppointment(); break;
        case 7: completeAppointment(); break;
        case 8: cancelAppointment(); break;
        case 9: viewPatientAppointments(); break;
        case 0: return;
    }
}

// ============================================================================
// MAIN MENU FUNCTIONS
// ============================================================================

void displayMainMenu() {
    clearScreen();
    displayBanner();

    printf("\n" BOLD WHT "+-------------------------------------------------------------+\n");
    printf("|                    MAIN MENU                                |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("| " RESET);
    printf(BOLD "1." RESET "  Patient Management    " BOLD "6." RESET "  Reports                       |\n");
    printf("| " RESET);
    printf(BOLD "2." RESET "  Appointments          " BOLD "7." RESET "  Administration                |\n");
    printf("| " RESET);
    printf(BOLD "3." RESET "  Billing System        " BOLD "8." RESET "  Data Management               |\n");
    printf("| " RESET);
    printf(BOLD "4." RESET "  View All Patients     " BOLD "9." RESET "  Medical Records               |\n");
    printf("| " RESET);
    printf(BOLD "5." RESET "  Search Patient        " BOLD "0." RESET "  Exit                          |\n");
    printf(BOLD WHT "+-------------------------------------------------------------+\n");
    printf(RESET);

    printf("\n" BLU "Total Patients: %d | Appointments: %d | Payments: %d | Doctors: %d" RESET "\n",
           patientCount, appointmentCount, paymentCount, doctorCount);
}

void handleChoice(int choice) {
    int subChoice;

    switch (choice) {
        case 1:
            clearScreen();
            displayHeader("PATIENT MANAGEMENT");
            printf("\n" BOLD "1." RESET " Add Patient\n");
            printf(BOLD "2." RESET " Update Patient\n");
            printf(BOLD "3." RESET " Discharge Patient\n");
            printf(BOLD "4." RESET " View All Patients\n");
            printf(BOLD "5." RESET " Search Patient\n");
            printf(BOLD "6." RESET " View Patient Details\n");
            printf(BOLD "0." RESET " Back\n");

            subChoice = validateInt("\nEnter your choice: ", 0, 6);
            switch (subChoice) {
                case 1: addPatient(); break;
                case 2: updatePatient(); break;
                case 3: deletePatient(); break;
                case 4: displayAllPatients(); break;
                case 5: searchPatient(); break;
                case 6: viewPatientDetails(); break;
                case 0: return;
            }
            break;

        case 2:
            clearScreen();
            displayHeader("APPOINTMENT MANAGEMENT");
            printf("\n" BOLD "1." RESET " Schedule Appointment\n");
            printf(BOLD "2." RESET " View All Appointments\n");
            printf(BOLD "3." RESET " Complete Appointment\n");
            printf(BOLD "4." RESET " Cancel Appointment\n");
            printf(BOLD "5." RESET " View Patient Appointments\n");
            printf(BOLD "0." RESET " Back\n");

            subChoice = validateInt("\nEnter your choice: ", 0, 5);
            switch (subChoice) {
                case 1: scheduleAppointment(); break;
                case 2: viewAllAppointments(); break;
                case 3: completeAppointment(); break;
                case 4: cancelAppointment(); break;
                case 5: viewPatientAppointments(); break;
                case 0: return;
            }
            break;

        case 3:
            clearScreen();
            displayHeader("BILLING SYSTEM");
            printf("\n" BOLD "1." RESET " Calculate Bill\n");
            printf(BOLD "2." RESET " Generate Bill\n");
            printf(BOLD "3." RESET " Process Payment\n");
            printf(BOLD "4." RESET " View Payment History\n");
            printf(BOLD "5." RESET " Generate Invoice\n");
            printf(BOLD "0." RESET " Back\n");

            subChoice = validateInt("\nEnter your choice: ", 0, 5);
            switch (subChoice) {
                case 1: calculateBill(); break;
                case 2: generateBill(); break;
                case 3: processPayment(); break;
                case 4: viewPaymentHistory(); break;
                case 5: generateInvoice(); break;
                case 0: return;
            }
            break;

        case 4:
            displayAllPatients();
            break;

        case 5:
            searchPatient();
            break;

        case 6:
            reportMenu();
            break;

        case 7:
            adminMenu();
            break;

        case 8:
            dataManagementMenu();
            break;

        case 9:
            medicalMenu();
            break;

        case 0:
            printf("\n" BOLD "Saving data..." RESET "\n");
            saveDataToFile();
            saveAppointmentsToFile();
            saveMedicalRecordsToFile();
            saveDoctorsToFile();
            displayLoadingAnimation();
            printSuccess("Data saved successfully!");
            break;

        default:
            printError("Invalid choice!");
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    if (!initializeMemory()) {
        printError("Failed to initialize memory. Exiting...");
        return 1;
    }

    initializeWards();

    printf(BOLD BLU);
    displayLoadingAnimation();
    printf(RESET);

    if (!loadDataFromFile()) {
        printWarning("Could not load patient data. Starting with empty database.");
    }

    if (!loadAppointmentsFromFile()) {
        printWarning("Could not load appointment data.");
    }

    if (!loadMedicalRecordsFromFile()) {
        printWarning("Could not load medical records.");
    }

    if (!loadDoctorsFromFile()) {
        printWarning("Could not load doctor data.");
    }

    int choice;
    do {
        displayMainMenu();
        choice = validateInt("\n" BOLD WHT "Enter your choice: " RESET, 0, 9);

        if (choice == 0) {
            char confirm;
            printf(YEL "Are you sure you want to exit? (y/n): " RESET);
            scanf(" %c", &confirm);
            getchar();

            if (tolower(confirm) == 'y') {
                break;
            } else {
                choice = -1;
            }
        } else {
            handleChoice(choice);
        }

    } while (choice != 0);

    printInfo("Saving data...");
    saveDataToFile();
    saveAppointmentsToFile();
    saveMedicalRecordsToFile();
    saveDoctorsToFile();
    freeAllMemory();

    clearScreen();
    displayBanner();
    printf("\n" GRN BOLD "Thank you for using the Hospital Management System!\n" RESET);
    printf(BOLD BLU "Goodbye!\n\n" RESET);

    return 0;
}
