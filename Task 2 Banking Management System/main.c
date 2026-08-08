#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>  // REQUIRED for SetConsoleTextAttribute

// Structure for transaction
typedef struct {
    char type[20];
    float amount;
    float balance_after;
    char date[30];
    char description[50];
} Transaction;

// Structure for account
typedef struct {
    int account_no;
    char name[50];
    char password[20];
    float balance;
    Transaction transactions[200];
    int transaction_count;
    char creation_date[30];
    char account_type[15];
    float daily_withdrawal_limit;
    float daily_withdrawn;
    char last_withdrawal_date[30];
    int is_active;
} Account;

// Color constants for Windows
#define COLOR_WHITE 15
#define COLOR_YELLOW 14
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_CYAN 11
#define COLOR_MAGENTA 13
#define COLOR_BLUE 9
#define COLOR_GRAY 8

// Global variables
int current_color = COLOR_WHITE;
Account accounts[100];
int account_count = 0;

// Function prototypes
void setColor(int color);
void resetColor();
void displayHeader(const char *title);
void createAccount();
void depositMoney();
void withdrawMoney();
void balanceInquiry();
void transactionHistory();
void accountSearch();
void deleteAccount();
void transferMoney();
void viewAllAccounts();
void freezeAccount();
void changePassword();
void monthlyStatement();
void saveToFile();
void loadFromFile();
int findAccount(int acc_no, Account *found);
int validatePassword(int acc_no, char *password);
void getCurrentDate(char *date);
void clearScreen();
void pauseScreen();
int getValidInt(const char *prompt, int min, int max);
float getValidFloat(const char *prompt, float min);
void getPassword(char *password, int max_len);

// Set text color (Windows)
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    current_color = color;
}

// Reset to default color
void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
    current_color = 7;
}

// Display header
void displayHeader(const char *title) {
    setColor(COLOR_YELLOW);
    printf("\n\t\t+====================================================+\n");
    setColor(COLOR_CYAN);
    printf("\t\t|                                                    |\n");
    setColor(COLOR_WHITE);
    printf("\t\t|  %-50s |\n", title);
    setColor(COLOR_CYAN);
    printf("\t\t|                                                    |\n");
    setColor(COLOR_YELLOW);
    printf("\t\t+====================================================+\n");
    resetColor();
}

// Clear screen
void clearScreen() {
    system("cls");
}

// Pause screen
void pauseScreen() {
    setColor(COLOR_GRAY);
    printf("\n\t\tPress any key to continue...");
    resetColor();
    getch();
}

// Get password with *** display
void getPassword(char *password, int max_len) {
    int i = 0;
    char ch;

    while(1) {
        ch = getch();
        if(ch == 13) {  // Enter key
            break;
        } else if(ch == 8) {  // Backspace
            if(i > 0) {
                printf("\b \b");
                i--;
            }
        } else if(i < max_len - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

// Get current date
void getCurrentDate(char *date) {
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    strftime(date, 30, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Get valid integer input
int getValidInt(const char *prompt, int min, int max) {
    int value;
    char input[10];

    while(1) {
        if(strlen(prompt) > 0) printf("%s", prompt);
        scanf("%s", input);

        if(sscanf(input, "%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        setColor(COLOR_RED);
        printf("\t\tInvalid input! Please enter a number between %d and %d: ", min, max);
        resetColor();
    }
}

// Get valid float input
float getValidFloat(const char *prompt, float min) {
    float value;
    char input[20];

    while(1) {
        if(strlen(prompt) > 0) printf("%s", prompt);
        scanf("%s", input);

        if(sscanf(input, "%f", &value) == 1 && value >= min) {
            return value;
        }
        setColor(COLOR_RED);
        printf("\t\tInvalid input! Please enter a valid amount (minimum %.2f): ", min);
        resetColor();
    }
}

// Load accounts from file
void loadFromFile() {
    FILE *file = fopen("accounts.dat", "rb");
    if(file == NULL) {
        account_count = 0;
        return;
    }

    account_count = fread(accounts, sizeof(Account), 100, file);
    fclose(file);
}

// Save accounts to file
void saveToFile() {
    FILE *file = fopen("accounts.dat", "wb");
    if(file != NULL) {
        fwrite(accounts, sizeof(Account), account_count, file);
        fclose(file);
        setColor(COLOR_GREEN);
        printf("\n\t\tAccounts saved successfully!\n");
        resetColor();
    }
}

// Find account by number
int findAccount(int acc_no, Account *found) {
    for(int i = 0; i < account_count; i++) {
        if(accounts[i].account_no == acc_no) {
            *found = accounts[i];
            return i;
        }
    }
    return -1;
}

// Validate password
int validatePassword(int acc_no, char *password) {
    Account acc;
    int index = findAccount(acc_no, &acc);
    if(index == -1) return 0;
    return strcmp(accounts[index].password, password) == 0;
}

int main() {
    loadFromFile();
    int choice;

    while(1) {
        clearScreen();
        displayHeader(" ADVANCED BANKING SYSTEM ");

        setColor(COLOR_YELLOW);
        printf("\n\n");
        printf("\t\t+====================================================+\n");
        printf("\t\t|                  MAIN MENU                        |\n");
        printf("\t\t+====================================================+\n");
        setColor(COLOR_WHITE);
        printf("\t\t|  1.  Create New Account                          |\n");
        setColor(COLOR_GREEN);
        printf("\t\t|  2.  Deposit Money                               |\n");
        setColor(COLOR_CYAN);
        printf("\t\t|  3.  Withdraw Money                              |\n");
        setColor(COLOR_MAGENTA);
        printf("\t\t|  4.  Balance Inquiry                             |\n");
        setColor(COLOR_BLUE);
        printf("\t\t|  5.  Transaction History                         |\n");
        setColor(COLOR_YELLOW);
        printf("\t\t|  6.  Account Search                              |\n");
        setColor(COLOR_RED);
        printf("\t\t|  7.  Delete Account                              |\n");
        setColor(COLOR_GREEN);
        printf("\t\t|  8.  Transfer Money                              |\n");
        setColor(COLOR_CYAN);
        printf("\t\t|  9.  View All Accounts                           |\n");
        setColor(COLOR_MAGENTA);
        printf("\t\t|  10. Freeze/Unfreeze Account                     |\n");
        setColor(COLOR_BLUE);
        printf("\t\t|  11. Change Password                             |\n");
        setColor(COLOR_YELLOW);
        printf("\t\t|  12. Monthly Statement                           |\n");
        setColor(COLOR_RED);
        printf("\t\t|  0.  Exit                                        |\n");
        setColor(COLOR_WHITE);
        printf("\t\t+====================================================+\n");
        printf("\n\t\tEnter your choice: ");

        choice = getValidInt("", 0, 12);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: balanceInquiry(); break;
            case 5: transactionHistory(); break;
            case 6: accountSearch(); break;
            case 7: deleteAccount(); break;
            case 8: transferMoney(); break;
            case 9: viewAllAccounts(); break;
            case 10: freezeAccount(); break;
            case 11: changePassword(); break;
            case 12: monthlyStatement(); break;
            case 0:
                saveToFile();
                clearScreen();
                setColor(COLOR_GREEN);
                printf("\n\n\t\t================================================\n");
                printf("\t\t    Thank you for using our Banking System!\n");
                printf("\t\t           Have a great day!\n");
                printf("\t\t================================================\n\n");
                resetColor();
                exit(0);
            default:
                setColor(COLOR_RED);
                printf("\n\t\tInvalid choice! Please try again.");
                resetColor();
                pauseScreen();
        }
    }
    return 0;
}

// Create Account
void createAccount() {
    clearScreen();
    displayHeader(" CREATE NEW ACCOUNT ");

    Account new_acc;
    new_acc.transaction_count = 0;
    new_acc.balance = 0.0;
    new_acc.is_active = 1;
    new_acc.daily_withdrawal_limit = 10000.0;
    new_acc.daily_withdrawn = 0.0;
    strcpy(new_acc.last_withdrawal_date, "");

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Details:\n");
    printf("\t\t----------------------------\n\n");
    resetColor();

    printf("\t\tAccount Holder Name: ");
    fflush(stdin);
    fgets(new_acc.name, 50, stdin);
    new_acc.name[strcspn(new_acc.name, "\n")] = 0;

    printf("\t\tAccount Type (Savings/Current): ");
    fflush(stdin);
    fgets(new_acc.account_type, 15, stdin);
    new_acc.account_type[strcspn(new_acc.account_type, "\n")] = 0;

    printf("\t\tSet Password: ");
    getPassword(new_acc.password, 20);

    srand(time(NULL));
    new_acc.account_no = 10000 + rand() % 90000;

    getCurrentDate(new_acc.creation_date);

    strcpy(new_acc.transactions[0].type, "Account Created");
    new_acc.transactions[0].amount = 0;
    new_acc.transactions[0].balance_after = 0;
    strcpy(new_acc.transactions[0].date, new_acc.creation_date);
    strcpy(new_acc.transactions[0].description, "Account opened");
    new_acc.transaction_count = 1;

    accounts[account_count++] = new_acc;
    saveToFile();

    setColor(COLOR_GREEN);
    printf("\n\t\tAccount Created Successfully!\n");
    printf("\t\t--------------------------------\n");
    resetColor();
    setColor(COLOR_YELLOW);
    printf("\t\tAccount Number: %d\n", new_acc.account_no);
    printf("\t\tAccount Holder: %s\n", new_acc.name);
    printf("\t\tAccount Type: %s\n", new_acc.account_type);
    printf("\t\tInitial Balance: $0.00\n");
    printf("\t\tCreated: %s\n", new_acc.creation_date);
    resetColor();
    setColor(COLOR_RED);
    printf("\n\t\tIMPORTANT: Please save your account number!\n");
    printf("\t\tYou'll need it for all future transactions.\n");
    resetColor();

    pauseScreen();
}

// Deposit Money
void depositMoney() {
    clearScreen();
    displayHeader(" DEPOSIT MONEY ");

    int acc_no, index;
    float amount;
    char password[20];
    Account acc;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    if(!accounts[index].is_active) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount is FROZEN! Contact bank.\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Password: ");
    getPassword(password, 20);

    if(!validatePassword(acc_no, password)) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\n\t\tEnter amount to deposit: $");
    amount = getValidFloat("", 0.01);

    if(amount > 50000) {
        setColor(COLOR_RED);
        printf("\n\t\tMaximum deposit per transaction is $50,000!\n");
        resetColor();
        pauseScreen();
        return;
    }

    accounts[index].balance += amount;

    strcpy(accounts[index].transactions[accounts[index].transaction_count].type, "Deposit");
    accounts[index].transactions[accounts[index].transaction_count].amount = amount;
    accounts[index].transactions[accounts[index].transaction_count].balance_after = accounts[index].balance;
    getCurrentDate(accounts[index].transactions[accounts[index].transaction_count].date);
    sprintf(accounts[index].transactions[accounts[index].transaction_count].description, "Cash deposit");
    accounts[index].transaction_count++;

    saveToFile();

    setColor(COLOR_GREEN);
    printf("\n\t\tDeposit Successful!\n");
    printf("\t\t----------------------------\n");
    resetColor();
    setColor(COLOR_YELLOW);
    printf("\t\tNew Balance: $%.2f\n", accounts[index].balance);
    printf("\t\tTransaction Date: %s\n", accounts[index].transactions[accounts[index].transaction_count-1].date);
    resetColor();

    pauseScreen();
}

// Withdraw Money
void withdrawMoney() {
    clearScreen();
    displayHeader(" WITHDRAW MONEY ");

    int acc_no, index;
    float amount;
    char password[20];
    Account acc;
    char current_date[30];

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    if(!accounts[index].is_active) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount is FROZEN! Contact bank.\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Password: ");
    getPassword(password, 20);

    if(!validatePassword(acc_no, password)) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\n\t\tCurrent Balance: $%.2f\n", accounts[index].balance);
    printf("\t\tDaily Withdrawal Limit: $%.2f\n", accounts[index].daily_withdrawal_limit);

    getCurrentDate(current_date);

    char date_part[11];
    strncpy(date_part, current_date, 10);
    date_part[10] = '\0';

    char last_date[11];
    strncpy(last_date, accounts[index].last_withdrawal_date, 10);
    last_date[10] = '\0';

    if(strcmp(date_part, last_date) != 0) {
        accounts[index].daily_withdrawn = 0.0;
        strcpy(accounts[index].last_withdrawal_date, current_date);
    }

    float available = accounts[index].daily_withdrawal_limit - accounts[index].daily_withdrawn;
    setColor(COLOR_CYAN);
    printf("\t\tAvailable for today: $%.2f\n", available);
    resetColor();

    printf("\t\tEnter amount to withdraw: $");
    amount = getValidFloat("", 0.01);

    if(amount > accounts[index].balance) {
        setColor(COLOR_RED);
        printf("\n\t\tInsufficient balance!\n");
        printf("\t\tAvailable balance: $%.2f\n", accounts[index].balance);
        resetColor();
        pauseScreen();
        return;
    }

    if(amount > available) {
        setColor(COLOR_RED);
        printf("\n\t\tDaily withdrawal limit exceeded!\n");
        printf("\t\tRemaining limit today: $%.2f\n", available);
        resetColor();
        pauseScreen();
        return;
    }

    if(amount > 10000) {
        setColor(COLOR_RED);
        printf("\n\t\tMaximum per transaction is $10,000!\n");
        resetColor();
        pauseScreen();
        return;
    }

    accounts[index].balance -= amount;
    accounts[index].daily_withdrawn += amount;

    strcpy(accounts[index].transactions[accounts[index].transaction_count].type, "Withdrawal");
    accounts[index].transactions[accounts[index].transaction_count].amount = -amount;
    accounts[index].transactions[accounts[index].transaction_count].balance_after = accounts[index].balance;
    getCurrentDate(accounts[index].transactions[accounts[index].transaction_count].date);
    sprintf(accounts[index].transactions[accounts[index].transaction_count].description, "Cash withdrawal");
    accounts[index].transaction_count++;

    saveToFile();

    setColor(COLOR_GREEN);
    printf("\n\t\tWithdrawal Successful!\n");
    printf("\t\t----------------------------\n");
    resetColor();
    setColor(COLOR_YELLOW);
    printf("\t\tAmount Withdrawn: $%.2f\n", amount);
    printf("\t\tNew Balance: $%.2f\n", accounts[index].balance);
    printf("\t\tRemaining Daily Limit: $%.2f\n", accounts[index].daily_withdrawal_limit - accounts[index].daily_withdrawn);
    printf("\t\tTransaction Date: %s\n", accounts[index].transactions[accounts[index].transaction_count-1].date);
    resetColor();

    pauseScreen();
}

// Balance Inquiry
void balanceInquiry() {
    clearScreen();
    displayHeader(" BALANCE INQUIRY ");

    int acc_no, index;
    char password[20];
    Account acc;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Password: ");
    getPassword(password, 20);

    if(!validatePassword(acc_no, password)) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    setColor(COLOR_YELLOW);
    printf("\n\n\t\tAccount Details\n");
    printf("\t\t====================================================\n");
    resetColor();
    setColor(COLOR_WHITE);
    printf("\t\tAccount Number: %d\n", accounts[index].account_no);
    printf("\t\tAccount Holder: %s\n", accounts[index].name);
    printf("\t\tAccount Type: %s\n", accounts[index].account_type);
    printf("\t\tStatus: %s\n", accounts[index].is_active ? "Active" : "Frozen");
    setColor(COLOR_GREEN);
    printf("\t\tCurrent Balance: $%.2f\n", accounts[index].balance);
    resetColor();
    printf("\t\tCreated: %s\n", accounts[index].creation_date);
    printf("\t\tTotal Transactions: %d\n", accounts[index].transaction_count);
    setColor(COLOR_CYAN);
    printf("\t\tDaily Withdrawal Limit: $%.2f\n", accounts[index].daily_withdrawal_limit);
    printf("\t\tToday's Withdrawals: $%.2f\n", accounts[index].daily_withdrawn);
    resetColor();
    printf("\t\t====================================================\n");

    pauseScreen();
}

// Transaction History
void transactionHistory() {
    clearScreen();
    displayHeader(" TRANSACTION HISTORY ");

    int acc_no, index;
    char password[20];
    Account acc;
    int start, end;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Password: ");
    getPassword(password, 20);

    if(!validatePassword(acc_no, password)) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    setColor(COLOR_YELLOW);
    printf("\n\n\t\tTransaction History for Account #%d\n", acc_no);
    printf("\t\t============================================================\n");
    resetColor();
    printf("\t\tAccount Holder: %s\n", accounts[index].name);
    printf("\t\tCurrent Balance: $%.2f\n\n", accounts[index].balance);

    printf("\t\t   #  Type         Amount    Balance     Date & Time\n");
    setColor(COLOR_GRAY);
    printf("\t\t------------------------------------------------------------\n");
    resetColor();

    start = accounts[index].transaction_count > 20 ? accounts[index].transaction_count - 20 : 0;
    end = accounts[index].transaction_count;

    for(int i = start; i < end; i++) {
        if(accounts[index].transactions[i].amount > 0) {
            setColor(COLOR_GREEN);
        } else {
            setColor(COLOR_RED);
        }
        printf("\t\t  %2d  %-10s  %7.2f   %7.2f   %s\n",
               i+1,
               accounts[index].transactions[i].type,
               accounts[index].transactions[i].amount,
               accounts[index].transactions[i].balance_after,
               accounts[index].transactions[i].date);
        resetColor();
    }
    printf("\t\t============================================================\n");

    pauseScreen();
}

// Account Search
void accountSearch() {
    clearScreen();
    displayHeader(" ACCOUNT SEARCH ");

    int acc_no, index;
    Account acc;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number to search: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    setColor(COLOR_GREEN);
    printf("\n\n\t\tAccount Found!\n");
    printf("\t\t====================================================\n");
    resetColor();
    setColor(COLOR_WHITE);
    printf("\t\tAccount Number: %d\n", accounts[index].account_no);
    printf("\t\tAccount Holder: %s\n", accounts[index].name);
    printf("\t\tAccount Type: %s\n", accounts[index].account_type);
    setColor(accounts[index].is_active ? COLOR_GREEN : COLOR_RED);
    printf("\t\tStatus: %s\n", accounts[index].is_active ? "Active" : "Frozen");
    resetColor();
    printf("\t\tBalance: $%.2f\n", accounts[index].balance);
    printf("\t\tCreated: %s\n", accounts[index].creation_date);
    printf("\t\tTransactions: %d\n", accounts[index].transaction_count);
    printf("\t\t====================================================\n");

    pauseScreen();
}

// Delete Account
void deleteAccount() {
    clearScreen();
    displayHeader(" DELETE ACCOUNT ");

    int acc_no, index;
    char password[20];
    Account acc;
    char confirm;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number to delete: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Password: ");
    getPassword(password, 20);

    if(!validatePassword(acc_no, password)) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    setColor(COLOR_RED);
    printf("\n\t\tWARNING: This action is permanent!\n");
    resetColor();
    printf("\t\tAccount Holder: %s\n", accounts[index].name);
    printf("\t\tBalance: $%.2f\n", accounts[index].balance);
    setColor(COLOR_YELLOW);
    printf("\n\t\tAre you sure you want to delete this account? (y/n): ");
    resetColor();
    fflush(stdin);
    scanf("%c", &confirm);

    if(tolower(confirm) != 'y') {
        setColor(COLOR_GREEN);
        printf("\n\t\tDeletion cancelled.\n");
        resetColor();
        pauseScreen();
        return;
    }

    for(int i = index; i < account_count - 1; i++) {
        accounts[i] = accounts[i + 1];
    }
    account_count--;
    saveToFile();

    setColor(COLOR_GREEN);
    printf("\n\t\tAccount deleted successfully!\n");
    resetColor();

    pauseScreen();
}

// Transfer Money
void transferMoney() {
    clearScreen();
    displayHeader(" TRANSFER MONEY ");

    int from_index, to_index;
    float amount;
    char password[20];
    Account sender, receiver;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Your Account Number: ");
    resetColor();
    int from_acc = getValidInt("", 10000, 99999);

    from_index = findAccount(from_acc, &sender);
    if(from_index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tSender account not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    if(!accounts[from_index].is_active) {
        setColor(COLOR_RED);
        printf("\n\t\tYour account is FROZEN!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Your Password: ");
    getPassword(password, 20);

    if(!validatePassword(from_acc, password)) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Recipient Account Number: ");
    int to_acc = getValidInt("", 10000, 99999);

    to_index = findAccount(to_acc, &receiver);
    if(to_index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tRecipient account not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    if(!accounts[to_index].is_active) {
        setColor(COLOR_RED);
        printf("\n\t\tRecipient account is FROZEN!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\n\t\tYour Current Balance: $%.2f\n", accounts[from_index].balance);
    printf("\t\tEnter amount to transfer: $");
    amount = getValidFloat("", 0.01);

    if(amount > accounts[from_index].balance) {
        setColor(COLOR_RED);
        printf("\n\t\tInsufficient balance!\n");
        resetColor();
        pauseScreen();
        return;
    }

    if(amount > 50000) {
        setColor(COLOR_RED);
        printf("\n\t\tMaximum transfer per transaction is $50,000!\n");
        resetColor();
        pauseScreen();
        return;
    }

    accounts[from_index].balance -= amount;
    strcpy(accounts[from_index].transactions[accounts[from_index].transaction_count].type, "Transfer Sent");
    accounts[from_index].transactions[accounts[from_index].transaction_count].amount = -amount;
    accounts[from_index].transactions[accounts[from_index].transaction_count].balance_after = accounts[from_index].balance;
    getCurrentDate(accounts[from_index].transactions[accounts[from_index].transaction_count].date);
    sprintf(accounts[from_index].transactions[accounts[from_index].transaction_count].description, "To Account: %d", to_acc);
    accounts[from_index].transaction_count++;

    accounts[to_index].balance += amount;
    strcpy(accounts[to_index].transactions[accounts[to_index].transaction_count].type, "Transfer Received");
    accounts[to_index].transactions[accounts[to_index].transaction_count].amount = amount;
    accounts[to_index].transactions[accounts[to_index].transaction_count].balance_after = accounts[to_index].balance;
    getCurrentDate(accounts[to_index].transactions[accounts[to_index].transaction_count].date);
    sprintf(accounts[to_index].transactions[accounts[to_index].transaction_count].description, "From Account: %d", from_acc);
    accounts[to_index].transaction_count++;

    saveToFile();

    setColor(COLOR_GREEN);
    printf("\n\t\tTransfer Successful!\n");
    printf("\t\t----------------------------\n");
    resetColor();
    setColor(COLOR_YELLOW);
    printf("\t\tAmount Transferred: $%.2f\n", amount);
    printf("\t\tYour New Balance: $%.2f\n", accounts[from_index].balance);
    printf("\t\tTransaction Date: %s\n", accounts[from_index].transactions[accounts[from_index].transaction_count-1].date);
    resetColor();

    pauseScreen();
}

// View All Accounts
void viewAllAccounts() {
    clearScreen();
    displayHeader(" ALL ACCOUNTS ");

    if(account_count == 0) {
        setColor(COLOR_RED);
        printf("\n\n\t\tNo accounts found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    float total_balance = 0;
    int active_count = 0, frozen_count = 0;

    setColor(COLOR_YELLOW);
    printf("\n\n\t\tAll Registered Accounts\n");
    printf("\t\t============================================================\n");
    resetColor();
    printf("\t\t  #  Account #    Account Holder         Balance    Status\n");
    setColor(COLOR_GRAY);
    printf("\t\t------------------------------------------------------------\n");
    resetColor();

    for(int i = 0; i < account_count; i++) {
        total_balance += accounts[i].balance;
        if(accounts[i].is_active) active_count++;
        else frozen_count++;

        printf("\t\t  %2d  %9d   %-20s  %7.2f   %s\n",
               i+1,
               accounts[i].account_no,
               accounts[i].name,
               accounts[i].balance,
               accounts[i].is_active ? "Active" : "Frozen");
    }

    setColor(COLOR_YELLOW);
    printf("\t\t============================================================\n");
    resetColor();
    setColor(COLOR_GREEN);
    printf("\t\tTotal Accounts: %d\n", account_count);
    printf("\t\tActive Accounts: %d\n", active_count);
    setColor(COLOR_RED);
    printf("\t\tFrozen Accounts: %d\n", frozen_count);
    resetColor();
    setColor(COLOR_YELLOW);
    printf("\t\tTotal Balance: $%.2f\n", total_balance);
    printf("\t\tAverage Balance: $%.2f\n", account_count > 0 ? total_balance/account_count : 0);
    resetColor();

    pauseScreen();
}

// Freeze/Unfreeze Account
void freezeAccount() {
    clearScreen();
    displayHeader(" FREEZE/UNFREEZE ACCOUNT ");

    int acc_no, index;
    char password[20];
    Account acc;
    char choice;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Admin Password: ");
    getPassword(password, 20);

    if(strcmp(password, "admin123") != 0) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid admin password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\n\t\tAccount: %s (Account #%d)\n", accounts[index].name, accounts[index].account_no);
    printf("\t\tCurrent Status: %s\n", accounts[index].is_active ? "Active" : "Frozen");
    printf("\n\t\tPress 'F' to Freeze or 'U' to Unfreeze: ");
    fflush(stdin);
    scanf("%c", &choice);

    if(tolower(choice) == 'f') {
        accounts[index].is_active = 0;
        setColor(COLOR_RED);
        printf("\n\t\tAccount FROZEN successfully!\n");
    } else if(tolower(choice) == 'u') {
        accounts[index].is_active = 1;
        setColor(COLOR_GREEN);
        printf("\n\t\tAccount UNFROZEN successfully!\n");
    } else {
        setColor(COLOR_YELLOW);
        printf("\n\t\tInvalid choice! Operation cancelled.\n");
    }
    resetColor();

    saveToFile();
    pauseScreen();
}

// Change Password
void changePassword() {
    clearScreen();
    displayHeader(" CHANGE PASSWORD ");

    int acc_no, index;
    char old_password[20], new_password[20], confirm_password[20];
    Account acc;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Current Password: ");
    getPassword(old_password, 20);

    if(!validatePassword(acc_no, old_password)) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter New Password: ");
    getPassword(new_password, 20);

    printf("\t\tConfirm New Password: ");
    getPassword(confirm_password, 20);

    if(strcmp(new_password, confirm_password) != 0) {
        setColor(COLOR_RED);
        printf("\n\t\tPasswords do not match!\n");
        resetColor();
        pauseScreen();
        return;
    }

    strcpy(accounts[index].password, new_password);
    saveToFile();

    setColor(COLOR_GREEN);
    printf("\n\t\tPassword changed successfully!\n");
    resetColor();

    pauseScreen();
}

// Monthly Statement
void monthlyStatement() {
    clearScreen();
    displayHeader(" MONTHLY STATEMENT ");

    int acc_no, index;
    char password[20];
    Account acc;
    char month[10];
    float monthly_credit = 0, monthly_debit = 0;
    int transaction_count = 0;

    setColor(COLOR_CYAN);
    printf("\n\n\t\tEnter Account Number: ");
    resetColor();
    acc_no = getValidInt("", 10000, 99999);

    index = findAccount(acc_no, &acc);
    if(index == -1) {
        setColor(COLOR_RED);
        printf("\n\t\tAccount not found!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Password: ");
    getPassword(password, 20);

    if(!validatePassword(acc_no, password)) {
        setColor(COLOR_RED);
        printf("\n\t\tInvalid password!\n");
        resetColor();
        pauseScreen();
        return;
    }

    printf("\t\tEnter Month (YYYY-MM): ");
    fflush(stdin);
    fgets(month, 10, stdin);
    month[strcspn(month, "\n")] = 0;

    setColor(COLOR_YELLOW);
    printf("\n\n\t\tMonthly Statement for %s\n", month);
    printf("\t\t============================================================\n");
    resetColor();
    printf("\t\tAccount: %d - %s\n", accounts[index].account_no, accounts[index].name);
    printf("\t\tAccount Type: %s\n\n", accounts[index].account_type);

    printf("\t\tDate         Description           Amount     Balance\n");
    setColor(COLOR_GRAY);
    printf("\t\t------------------------------------------------------------\n");
    resetColor();

    for(int i = 0; i < accounts[index].transaction_count; i++) {
        char trans_month[8];
        strncpy(trans_month, accounts[index].transactions[i].date, 7);
        trans_month[7] = '\0';

        if(strcmp(trans_month, month) == 0) {
            transaction_count++;
            if(accounts[index].transactions[i].amount > 0) {
                monthly_credit += accounts[index].transactions[i].amount;
                setColor(COLOR_GREEN);
            } else {
                monthly_debit += -accounts[index].transactions[i].amount;
                setColor(COLOR_RED);
            }

            char date_short[11];
            strncpy(date_short, accounts[index].transactions[i].date, 10);
            date_short[10] = '\0';

            printf("\t\t%s  %-15s  %7.2f   %7.2f\n",
                   date_short,
                   accounts[index].transactions[i].type,
                   accounts[index].transactions[i].amount,
                   accounts[index].transactions[i].balance_after);
            resetColor();
        }
    }

    if(transaction_count == 0) {
        setColor(COLOR_YELLOW);
        printf("\t\tNo transactions found for this month.\n");
        resetColor();
    }

    setColor(COLOR_YELLOW);
    printf("\t\t------------------------------------------------------------\n");
    resetColor();
    setColor(COLOR_GREEN);
    printf("\t\tTotal Credits: $%.2f\n", monthly_credit);
    setColor(COLOR_RED);
    printf("\t\tTotal Debits: $%.2f\n", monthly_debit);
    resetColor();
    setColor(COLOR_YELLOW);
    printf("\t\tNet Change: $%.2f\n", monthly_credit - monthly_debit);
    printf("\t\tClosing Balance: $%.2f\n", accounts[index].balance);
    resetColor();
    printf("\t\t============================================================\n");
    printf("\t\tTotal Transactions: %d\n", transaction_count);

    pauseScreen();
}
