# 🏦 Advanced Banking Management System

<p align="center">
  <img src="images/01-main-menu.png" alt="Advanced Banking System Main Menu" width="850">
</p>

<h3 align="center">A Feature-Rich Console-Based Banking Management System in C</h3>

<p align="center">
  <b>InternGrow Internship — Task 2</b><br>
  Banking Management System | Week 2 | C Programming
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c">
  <img src="https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows">
  <img src="https://img.shields.io/badge/File%20Handling-Binary%20Files-success?style=for-the-badge">
  <img src="https://img.shields.io/badge/Internship-InternGrow-purple?style=for-the-badge">
</p>

---

## 📌 Project Overview

The **Advanced Banking Management System** is a menu-driven console application developed in the C programming language.

The project demonstrates practical use of:

- Structures
- Nested structures
- Functions
- Arrays
- File handling
- Binary file storage
- Conditional logic
- Loops
- String handling
- Password protection
- Input validation
- Transaction management
- Date and time handling
- Windows console customization
- Error handling

The system allows users to create and manage bank accounts, deposit and withdraw money, transfer funds between accounts, view balances, inspect transaction history, search accounts, freeze or unfreeze accounts, change passwords, and generate monthly statements.

Account information is persisted using the binary file `accounts.dat`, allowing data to remain available after the program is closed and started again.

---

# 🎯 Task Objective

### Task 2 — Banking Management System

**Scenario:**  
Create a banking application using structures and file handling.

### Required Features

| Requirement | Implementation |
|---|---|
| Create Account | ✅ |
| Deposit Money | ✅ |
| Withdraw Money | ✅ |
| Balance Inquiry | ✅ |
| Transaction History | ✅ |
| Account Search | ✅ |
| File Storage | ✅ |
| Password Protection | ✅ |
| Error Handling | ✅ |

### Additional Features Implemented

| Advanced Feature | Status |
|---|---|
| Money Transfer | ✅ |
| View All Accounts | ✅ |
| Freeze / Unfreeze Account | ✅ |
| Change Password | ✅ |
| Monthly Statement | ✅ |
| Daily Withdrawal Limit | ✅ |
| Transaction Limits | ✅ |
| Transaction Descriptions | ✅ |
| Date & Time Tracking | ✅ |
| Colored Console Interface | ✅ |
| Input Validation | ✅ |
| Account Status Management | ✅ |

---

# ✨ Key Highlights

### 🔐 Password-Protected Operations

Sensitive account operations require the account password.

Passwords are entered through a custom console function that displays `*` characters instead of showing the actual password.

```text
Enter Account Number: 20523
Enter Password: ******
````

Password validation is performed before operations such as:

* Deposits
* Withdrawals
* Balance inquiries
* Transaction history
* Account deletion
* Money transfers
* Password changes
* Monthly statements

---

### 💾 Persistent File Storage

The system stores account information in:

```text
accounts.dat
```

The program loads existing account records when it starts and saves updated records after changes.

Binary file operations are performed using:

```c
fopen()
fread()
fwrite()
fclose()
```

This means account data does not disappear when the application closes.

---

### 💰 Complete Banking Operations

The application supports:

```text
Create Account
Deposit Money
Withdraw Money
Balance Inquiry
Transaction History
Account Search
Delete Account
Transfer Money
View All Accounts
Freeze/Unfreeze Account
Change Password
Monthly Statement
Exit
```

---

# 🏗️ Project Architecture

The application follows a function-based procedural design.

```text
                    ┌───────────────────────────┐
                    │   Advanced Banking System │
                    └─────────────┬─────────────┘
                                  │
                    ┌─────────────▼─────────────┐
                    │        Main Menu           │
                    └─────────────┬─────────────┘
                                  │
          ┌───────────────────────┼────────────────────────┐
          │                       │                        │
          ▼                       ▼                        ▼
   Account Management      Banking Operations       Administration
          │                       │                        │
          ├─ Create Account       ├─ Deposit               ├─ View All
          ├─ Search Account       ├─ Withdraw              ├─ Freeze
          ├─ Delete Account       ├─ Transfer              └─ Unfreeze
          └─ Change Password      ├─ Balance
                                  └─ Transactions
                                           │
                                           ▼
                                  Monthly Statement
                                           │
                                           ▼
                                   accounts.dat
```

---

# 🧱 Data Structures

The system uses two main structures.

## 1. Transaction Structure

Each transaction stores information about a banking operation.

```c
typedef struct {
    char type[20];
    float amount;
    float balance_after;
    char date[30];
    char description[50];
} Transaction;
```

### Transaction Fields

| Field           | Purpose                            |
| --------------- | ---------------------------------- |
| `type`          | Transaction type                   |
| `amount`        | Transaction amount                 |
| `balance_after` | Balance after transaction          |
| `date`          | Transaction date and time          |
| `description`   | Additional transaction information |

Examples of transaction types include:

```text
Account Created
Deposit
Withdrawal
Transfer Sent
Transfer Received
```

---

## 2. Account Structure

The main account structure stores complete customer information.

```c
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
```

### Account Fields

| Field                    | Purpose                                           |
| ------------------------ | ------------------------------------------------- |
| `account_no`             | Unique account identifier generated by the system |
| `name`                   | Account holder name                               |
| `password`               | Account password                                  |
| `balance`                | Current account balance                           |
| `transactions`           | Transaction history                               |
| `transaction_count`      | Number of recorded transactions                   |
| `creation_date`          | Account creation timestamp                        |
| `account_type`           | Savings or Current                                |
| `daily_withdrawal_limit` | Maximum daily withdrawal amount                   |
| `daily_withdrawn`        | Amount withdrawn during current day               |
| `last_withdrawal_date`   | Date of last withdrawal                           |
| `is_active`              | Active/Frozen status                              |

---

# 📊 System Capacity

The current implementation uses fixed-size arrays.

```c
Account accounts[100];
```

Therefore, the application can maintain up to:

**100 accounts**

Each account can store:

```c
Transaction transactions[200];
```

Therefore, each account can maintain up to:

**200 transaction records**

The transaction-history display shows the most recent 20 transactions.

---

# 🧭 Main Menu

The application starts with an interactive main menu.

```text
+====================================================+
|              ADVANCED BANKING SYSTEM               |
+====================================================+

1. Create New Account
2. Deposit Money
3. Withdraw Money
4. Balance Inquiry
5. Transaction History
6. Account Search
7. Delete Account
8. Transfer Money
9. View All Accounts
10. Freeze/Unfreeze Account
11. Change Password
12. Monthly Statement
0. Exit
```

The program continuously displays this menu until the user selects `0`.

---

# 👤 1. Create New Account

The account creation process collects:

* Account holder name
* Account type
* Password

The system automatically generates:

* Account number
* Creation date
* Initial transaction
* Initial balance
* Daily withdrawal limit
* Active status

### Initial Account State

```text
Initial Balance: $0.00
Status: Active
Daily Withdrawal Limit: $10,000
```

A first transaction named:

```text
Account Created
```

is automatically stored in the transaction history.

### Screenshot

<table>
<tr>
<td align="center">

<b>01 — Main Menu</b>

<br><br>

<img src="images/01-main-menu.png" alt="Main Menu" width="500">

</td>

<td align="center">

<b>02 — Create New Account</b>

<br><br>

<img src="images/02-create-account.png" alt="Create Account" width="500">

</td>
</tr>
</table>

---

# 💵 2. Deposit Money

The deposit feature allows an active account holder to add money to the account.

### Process

```text
Account Number
        ↓
Password Verification
        ↓
Enter Deposit Amount
        ↓
Validate Amount
        ↓
Update Balance
        ↓
Create Transaction Record
        ↓
Save to File
```

### Deposit Limit

The maximum deposit allowed per transaction is:

```text
$50,000
```

The system rejects invalid amounts and deposits exceeding the limit.

### Screenshot

<table>
<tr>
<td align="center">

<b>03 — Deposit Money</b>

<br><br>

<img src="images/03-deposit-money.png" alt="Deposit Money" width="500">

</td>

<td align="center">

<b>04 — Withdraw Money</b>

<br><br>

<img src="images/04-withdraw-money.png" alt="Withdraw Money" width="500">

</td>
</tr>
</table>

---

# 💳 3. Withdraw Money

The withdrawal system performs multiple checks before processing a transaction.

### Validation Rules

The system checks:

* Account existence
* Account status
* Password
* Available balance
* Daily withdrawal limit
* Per-transaction withdrawal limit

### Withdrawal Limits

```text
Daily Withdrawal Limit: $10,000
Maximum Per Transaction: $10,000
```

The system also tracks the amount withdrawn during the current day.

If a new date is detected, the daily withdrawal counter is reset automatically.

### Example

```text
Current Balance: $8,190.00
Daily Withdrawal Limit: $10,000.00
Available for today: $9,900.00

Enter amount to withdraw: $800
```

After a successful transaction:

```text
Amount Withdrawn: $800.00
New Balance: $7,390.00
Remaining Daily Limit: $9,100.00
```

---

# 💰 4. Balance Inquiry

Balance Inquiry displays detailed information about an account after password verification.

It shows:

* Account number
* Account holder
* Account type
* Account status
* Current balance
* Creation date
* Total transactions
* Daily withdrawal limit
* Today's withdrawals

### Screenshot

<img src="images/05-balance-inquiry.png" alt="Balance Inquiry" width="850">

---

# 📜 5. Transaction History

Every important banking operation creates a transaction record.

Transaction history displays:

| Information | Description               |
| ----------- | ------------------------- |
| Number      | Transaction sequence      |
| Type        | Transaction category      |
| Amount      | Transaction value         |
| Balance     | Balance after transaction |
| Date & Time | Transaction timestamp     |

Positive transactions are displayed in green while outgoing transactions are displayed in red.

The system displays up to the most recent **20 transactions** for an account.

### Screenshot

<img src="images/06-transaction-history.png" alt="Transaction History" width="850">

---

# 🔎 6. Account Search

Account Search allows the user to locate an account using its account number.

The search result displays:

```text
Account Number
Account Holder
Account Type
Status
Balance
Created Date
Transaction Count
```

This operation does not require the account password because it is designed as an account lookup feature.

### Screenshot

<img src="images/07-account-search.png" alt="Account Search" width="850">

---

# 🗑️ 7. Delete Account

The delete operation is protected by password verification.

Before deletion, the program displays a warning:

```text
WARNING: This action is permanent!
```

The user must explicitly confirm:

```text
Are you sure you want to delete this account? (y/n)
```

If the user enters `y`, the account is removed from the in-memory account array and the updated data is saved to `accounts.dat`.

### Screenshot

<img src="images/12-delete-account.png" alt="Delete Account" width="850">

---

# 🔄 8. Transfer Money

The system supports direct transfers between two registered accounts.

### Transfer Flow

```text
Sender Account
      ↓
Sender Password
      ↓
Recipient Account
      ↓
Recipient Validation
      ↓
Balance Validation
      ↓
Transfer Limit Validation
      ↓
Deduct Sender Balance
      ↓
Add Recipient Balance
      ↓
Create Two Transaction Records
      ↓
Save to File
```

The sender receives:

```text
Transfer Sent
```

and the recipient receives:

```text
Transfer Received
```

### Transfer Limit

The maximum transfer allowed per transaction is:

```text
$50,000
```

### Frozen Account Protection

A transfer cannot be completed if:

* Sender account is frozen
* Recipient account is frozen
* Sender account does not exist
* Recipient account does not exist
* Sender has insufficient balance

### Error Handling Example

<img src="images/08-transfer-frozen-account.png" alt="Transfer to Frozen Account" width="850">

### Successful Transfer

<img src="images/09-transfer-money-success.png" alt="Successful Money Transfer" width="850">

---

# 🔒 9. Freeze / Unfreeze Account

The system supports account status management.

An account can have either:

```text
Active
```

or

```text
Frozen
```

A frozen account cannot perform normal banking operations such as:

* Deposit
* Withdrawal
* Transfer

The feature requires an administrator password.

### Admin Authentication

The current implementation uses:

```text
admin123
```

for the freeze/unfreeze administrative operation.

> ⚠️ This password is hard-coded in the source code for this educational project. It should be replaced with secure credential management in a production system.

### Available Actions

```text
F = Freeze
U = Unfreeze
```

### Screenshot

<img src="images/10-freeze-unfreeze-account.png" alt="Freeze and Unfreeze Account" width="850">

---

# 🔑 10. Change Password

Users can change their account password.

### Process

```text
Account Number
        ↓
Current Password
        ↓
New Password
        ↓
Confirm New Password
        ↓
Password Match Check
        ↓
Save Updated Account
```

If the confirmation does not match, the operation is cancelled.

### Screenshot

<img src="images/11-change-password.png" alt="Change Password" width="850">

---

# 📊 11. View All Accounts

The View All Accounts feature displays a summary of registered accounts.

The table includes:

```text
Account Number
Account Holder
Balance
Status
```

The system also calculates:

* Total accounts
* Active accounts
* Frozen accounts
* Total balance
* Average balance

### Example

```text
Total Accounts: 2
Active Accounts: 1
Frozen Accounts: 1
Total Balance: $8206.00
Average Balance: $4103.00
```

### Initial Account List

<img src="images/13-all-accounts-initial.png" alt="Initial All Accounts View" width="850">

### Updated Account List

<img src="images/14-all-accounts-updated.png" alt="Updated All Accounts View" width="850">

---

# 📅 12. Monthly Statement

The Monthly Statement feature allows an account holder to request transactions for a specific month.

The user enters:

```text
YYYY-MM
```

For example:

```text
2026-08
```

The system searches transaction dates and displays transactions belonging to the selected month.

### Statement Information

The statement includes:

* Account number
* Account holder
* Account type
* Transaction date
* Transaction type
* Transaction amount
* Balance after transaction
* Total credits
* Total debits
* Net change
* Closing balance
* Total transactions

### Monthly Calculations

```text
Net Change = Total Credits - Total Debits
```

### Screenshot

<img src="images/15-monthly-statement.png" alt="Monthly Statement" width="850">

---

# 💾 File Handling

Persistent storage is implemented using the binary file:

```text
accounts.dat
```

### Loading Data

When the program starts:

```c
loadFromFile();
```

is called.

The system attempts to open:

```text
accounts.dat
```

in binary read mode:

```c
fopen("accounts.dat", "rb");
```

Account records are then loaded using:

```c
fread()
```

### Saving Data

Whenever account information changes, the program calls:

```c
saveToFile();
```

The file is opened using:

```c
fopen("accounts.dat", "wb");
```

and account records are written using:

```c
fwrite()
```

### Data Persistence Flow

```text
                 Program Starts
                       │
                       ▼
                Load accounts.dat
                       │
                       ▼
                Account Operations
                       │
             ┌─────────┼─────────┐
             │         │         │
             ▼         ▼         ▼
          Deposit   Withdraw   Transfer
             │         │         │
             └─────────┼─────────┘
                       ▼
                 saveToFile()
                       │
                       ▼
                  accounts.dat
```

---

# 🔐 Password Protection

The project implements masked password entry using:

```c
getPassword()
```

The function reads keyboard input character-by-character using `getch()`.

Instead of displaying the actual password, it prints:

```text
******
```

Password verification is performed through:

```c
validatePassword()
```

which compares the entered password with the stored account password.

### Security Note

This is an educational C console application.

The current implementation stores passwords directly inside the `Account` structure and therefore does **not** use hashing or encryption.

For a real banking application, passwords should never be stored as plaintext. A production system should use secure password hashing, access control, encryption, and a proper authentication architecture.

---

# 🛡️ Error Handling & Validation

The system includes multiple validation checks.

## Account Validation

```text
Account not found
Invalid account number
Frozen account
Invalid password
```

## Deposit Validation

```text
Invalid amount
Amount below minimum
Deposit exceeds $50,000
Frozen account
```

## Withdrawal Validation

```text
Insufficient balance
Daily withdrawal limit exceeded
Per-transaction limit exceeded
Frozen account
Invalid password
```

## Transfer Validation

```text
Sender account not found
Recipient account not found
Sender account frozen
Recipient account frozen
Insufficient balance
Transfer exceeds $50,000
Invalid password
```

## Password Validation

```text
Invalid current password
New password mismatch
```

## Account Deletion

```text
Account not found
Invalid password
Deletion confirmation
```

---

# 🎨 Console Interface

The application uses the Windows console API:

```c
#include <windows.h>
```

and:

```c
SetConsoleTextAttribute()
```

to create a colored terminal interface.

Different colors are used for different types of information:

| Color   | Purpose                            |
| ------- | ---------------------------------- |
| Green   | Successful operations              |
| Red     | Errors and warnings                |
| Cyan    | Input prompts / informational data |
| Yellow  | Important information              |
| Blue    | Menu categories                    |
| Magenta | Additional system sections         |
| Gray    | Secondary information              |

The application also uses formatted headers such as:

```text
+====================================================+
|                                                    |
|             ADVANCED BANKING SYSTEM                |
|                                                    |
+====================================================+
```

---

# 🧩 Important Functions

The program is divided into reusable functions.

```c
setColor()
resetColor()
displayHeader()

createAccount()
depositMoney()
withdrawMoney()
balanceInquiry()
transactionHistory()
accountSearch()
deleteAccount()
transferMoney()
viewAllAccounts()
freezeAccount()
changePassword()
monthlyStatement()

saveToFile()
loadFromFile()

findAccount()
validatePassword()

getCurrentDate()
getValidInt()
getValidFloat()
getPassword()

clearScreen()
pauseScreen()
```

This function-based organization keeps each banking operation separated and easier to maintain.

---

# 🗂️ Project Structure

```text
Task 2 Banking Management System/
│
├── 📁 images/
│   │
│   ├── 01-main-menu.png
│   ├── 02-create-account.png
│   ├── 03-deposit-money.png
│   ├── 04-withdraw-money.png
│   ├── 05-balance-inquiry.png
│   ├── 06-transaction-history.png
│   ├── 07-account-search.png
│   ├── 08-transfer-frozen-account.png
│   ├── 09-transfer-money-success.png
│   ├── 10-freeze-unfreeze-account.png
│   ├── 11-change-password.png
│   ├── 12-delete-account.png
│   ├── 13-all-accounts-initial.png
│   ├── 14-all-accounts-updated.png
│   ├── 15-monthly-statement.png
│   └── 16-thank-you-exit.png
│
├── 📄 main.c
├── 📄 README.md
│
└── 📄 accounts.dat
    └── Generated automatically when the program runs
```

> `accounts.dat` is generated at runtime by the application. It does not need to be manually created before the first run.

---

# 🛠️ Technologies Used

### Programming Language

```text
C
```

### Libraries

```c
stdio.h
stdlib.h
string.h
time.h
ctype.h
conio.h
windows.h
```

### Concepts

```text
Structures
Nested Structures
Functions
Arrays
Pointers
File Handling
Binary Files
String Handling
Conditional Statements
Loops
Input Validation
Password Handling
Date & Time
Console Formatting
```

---

# 💻 Requirements

The current source uses:

```c
#include <conio.h>
#include <windows.h>
```

and Windows-specific console functions.

Therefore, the application is designed primarily for:

```text
Windows
```

A compiler/environment with support for these headers is required.

Recommended environments include:

* Code::Blocks with MinGW
* Dev-C++
* MinGW GCC
* Visual Studio configured for C
* VS Code with a Windows C compiler

---

# ▶️ How to Run

## Option 1 — GCC / MinGW

Open Command Prompt or the VS Code terminal inside the project folder.

Compile:

```bash
gcc main.c -o banking.exe
```

Run:

```bash
banking.exe
```

---

## Option 2 — Code::Blocks

1. Open Code::Blocks.
2. Create or open a C project.
3. Add `main.c`.
4. Build the project.
5. Run the application.
6. Use the displayed menu to perform banking operations.

---

# 🔄 Application Workflow

```text
                 ┌───────────────────┐
                 │   Start Program   │
                 └─────────┬─────────┘
                           │
                           ▼
                 ┌───────────────────┐
                 │ Load accounts.dat │
                 └─────────┬─────────┘
                           │
                           ▼
                 ┌───────────────────┐
                 │    Main Menu      │
                 └─────────┬─────────┘
                           │
          ┌────────────────┼─────────────────┐
          │                │                 │
          ▼                ▼                 ▼
     Account Setup     Transactions      Management
          │                │                 │
          ├─ Create        ├─ Deposit        ├─ Search
          ├─ Search        ├─ Withdraw       ├─ View All
          └─ Delete        ├─ Transfer       ├─ Freeze
                           └─ Balance        └─ Password
                                  │
                                  ▼
                         Transaction Records
                                  │
                                  ▼
                            Save to File
                                  │
                                  ▼
                           accounts.dat
```

---

# 📸 Complete Application Screenshots

The following screenshots demonstrate the actual working application.

---

## 🖥️ Main Menu

<table>
<tr>
<td align="center" width="100%">

### 01 — Advanced Banking System Main Menu

<img src="images/01-main-menu.png" alt="Advanced Banking System Main Menu" width="850">

<p>The main menu provides access to all banking and account-management operations.</p>

</td>
</tr>
</table>

---

## 👤 Account Creation

<table>
<tr>
<td align="center" width="100%">

### 02 — Create New Account

<img src="images/02-create-account.png" alt="Create New Account" width="850">

<p>A new account is created with an automatically generated account number, account type, password, timestamp, and initial transaction.</p>

</td>
</tr>
</table>

---

## 💵 Deposit

<table>
<tr>
<td align="center" width="100%">

### 03 — Deposit Money

<img src="images/03-deposit-money.png" alt="Deposit Money" width="850">

<p>Authenticated users can deposit money into an active account.</p>

</td>
</tr>
</table>

---

## 💳 Withdrawal

<table>
<tr>
<td align="center" width="100%">

### 04 — Withdraw Money

<img src="images/04-withdraw-money.png" alt="Withdraw Money" width="850">

<p>The withdrawal system checks balance, daily limits, transaction limits, account status, and password.</p>

</td>
</tr>
</table>

---

## 💰 Balance Inquiry

<table>
<tr>
<td align="center" width="100%">

### 05 — Balance Inquiry

<img src="images/05-balance-inquiry.png" alt="Balance Inquiry" width="850">

<p>Displays detailed account information including balance, account status, transaction count, and withdrawal statistics.</p>

</td>
</tr>
</table>

---

## 📜 Transaction History

<table>
<tr>
<td align="center" width="100%">

### 06 — Transaction History

<img src="images/06-transaction-history.png" alt="Transaction History" width="850">

<p>Displays recorded banking transactions with amounts, balances, transaction types, and timestamps.</p>

</td>
</tr>
</table>

---

## 🔎 Account Search

<table>
<tr>
<td align="center" width="100%">

### 07 — Account Search

<img src="images/07-account-search.png" alt="Account Search" width="850">

<p>Searches for an account using its account number and displays the matching account information.</p>

</td>
</tr>
</table>

---

## 🔒 Frozen Account Protection

<table>
<tr>
<td align="center" width="100%">

### 08 — Transfer to Frozen Account

<img src="images/08-transfer-frozen-account.png" alt="Transfer to Frozen Account" width="850">

<p>The system correctly blocks transfers when the recipient account is frozen.</p>

</td>
</tr>
</table>

---

## 🔄 Successful Transfer

<table>
<tr>
<td align="center" width="100%">

### 09 — Successful Money Transfer

<img src="images/09-transfer-money-success.png" alt="Successful Money Transfer" width="850">

<p>A successful transfer updates both accounts and records the transfer in transaction history.</p>

</td>
</tr>
</table>

---

## 🔐 Freeze / Unfreeze

<table>
<tr>
<td align="center" width="100%">

### 10 — Freeze / Unfreeze Account

<img src="images/10-freeze-unfreeze-account.png" alt="Freeze Unfreeze Account" width="850">

<p>Administrative account status management allows accounts to be frozen or unfrozen.</p>

</td>
</tr>
</table>

---

## 🔑 Change Password

<table>
<tr>
<td align="center" width="100%">

### 11 — Change Password

<img src="images/11-change-password.png" alt="Change Password" width="850">

<p>Users can securely verify their current password and set a new password.</p>

</td>
</tr>
</table>

---

## 🗑️ Delete Account

<table>
<tr>
<td align="center" width="100%">

### 12 — Delete Account

<img src="images/12-delete-account.png" alt="Delete Account" width="850">

<p>The system verifies the password and asks for explicit confirmation before permanently deleting an account.</p>

</td>
</tr>
</table>

---

## 📋 All Accounts — Initial View

<table>
<tr>
<td align="center" width="100%">

### 13 — All Registered Accounts

<img src="images/13-all-accounts-initial.png" alt="All Accounts Initial View" width="850">

<p>Displays registered accounts with their balances and active/frozen status.</p>

</td>
</tr>
</table>

---

## 📊 All Accounts — Updated View

<table>
<tr>
<td align="center" width="100%">

### 14 — Updated Account Summary

<img src="images/14-all-accounts-updated.png" alt="All Accounts Updated View" width="850">

<p>Displays updated balances and calculates total accounts, active accounts, frozen accounts, total balance, and average balance.</p>

</td>
</tr>
</table>

---

## 📅 Monthly Statement

<table>
<tr>
<td align="center" width="100%">

### 15 — Monthly Statement

<img src="images/15-monthly-statement.png" alt="Monthly Statement" width="850">

<p>Generates a month-specific transaction summary with credits, debits, net change, closing balance, and transaction count.</p>

</td>
</tr>
</table>

---

## 👋 Exit Screen

<table>
<tr>
<td align="center" width="100%">

### 16 — Thank You / Exit

<img src="images/16-thank-you-exit.png" alt="Thank You Exit Screen" width="850">

<p>The application saves the latest account data before displaying the final exit message.</p>

</td>
</tr>
</table>

---

# 🧪 Tested Scenarios

The application has been demonstrated with the following scenarios:

### Account Management

* Account creation
* Account search
* Account deletion
* View all accounts

### Banking Operations

* Deposit
* Withdrawal
* Balance inquiry
* Money transfer

### Security & Control

* Password verification
* Password change
* Freeze account
* Unfreeze account
* Frozen-account transaction rejection

### Reporting

* Transaction history
* Monthly statement
* Account statistics

### Error Handling

* Invalid account number
* Invalid password
* Insufficient balance
* Frozen account
* Invalid transaction amount
* Withdrawal limit exceeded
* Transfer limit exceeded
* Invalid menu choice

---

# 📏 Banking Rules Implemented

| Rule                               | Limit / Behavior  |
| ---------------------------------- | ----------------- |
| Account number input               | 10000–99999       |
| Maximum accounts                   | 100               |
| Transactions per account           | 200               |
| Transaction history display        | Latest 20         |
| Initial balance                    | $0.00             |
| Daily withdrawal limit             | $10,000           |
| Maximum withdrawal per transaction | $10,000           |
| Maximum deposit per transaction    | $50,000           |
| Maximum transfer per transaction   | $50,000           |
| Account status                     | Active / Frozen   |
| Account type                       | Savings / Current |
| Password input                     | Masked with `*`   |
| Monthly statement format           | `YYYY-MM`         |

---

# 🧠 Programming Concepts Demonstrated

## Structures

The application uses custom structures to model accounts and transactions.

```c
typedef struct {
    ...
} Transaction;

typedef struct {
    ...
} Account;
```

---

## Nested Structures

Each `Account` contains an array of `Transaction` structures:

```c
Transaction transactions[200];
```

This demonstrates how complex records can be represented using nested structures.

---

## Functions

Each major operation is implemented as a separate function.

For example:

```c
createAccount();
depositMoney();
withdrawMoney();
transferMoney();
transactionHistory();
monthlyStatement();
```

This improves modularity and code organization.

---

## File Handling

The project uses binary file handling:

```c
fopen()
fread()
fwrite()
fclose()
```

to provide persistent storage.

---

## Conditional Logic

The application makes extensive use of:

```c
if
else
switch
```

for:

* Authentication
* Account status
* Transaction validation
* Balance checks
* Limits
* Menu navigation
* Confirmation handling

---

## Loops

Loops are used for:

* Menu repetition
* Input validation
* Account searching
* Transaction history
* Monthly statement generation
* Displaying all accounts

---

## String Handling

The project uses standard C string functions including:

```c
strcpy()
strcmp()
strlen()
strncpy()
strcspn()
sprintf()
```

---

## Date & Time

The application uses:

```c
time.h
```

and:

```c
time()
localtime()
strftime()
```

to generate timestamps for accounts and transactions.

---

# ⚙️ Design Decisions

### Fixed-Size Storage

The system uses arrays with predefined capacities:

```c
Account accounts[100];
```

and:

```c
Transaction transactions[200];
```

This keeps the implementation straightforward for a C programming internship task.

### Binary Storage

Binary storage is used instead of text files so complete structures can be written and read directly.

### Function-Based Architecture

Each operation is isolated into a function, making the code easier to understand and maintain.

### Console-Based UI

The project intentionally uses a console interface to focus on core C programming concepts rather than GUI development.

---

# ⚠️ Current Limitations

This project is designed as an educational C programming application and is **not intended for real banking use**.

Current limitations include:

* Passwords are stored as plaintext inside the account structure.
* The administrative password is hard-coded.
* Account numbers are randomly generated without a dedicated collision-check mechanism.
* Data is stored in a local binary file.
* The application is Windows-specific because of `conio.h` and `windows.h`.
* The system uses fixed-size arrays rather than dynamic memory allocation.
* There is no database backend.
* There is no network authentication.
* There is no encryption.
* There is no multi-user or concurrent access control.

These limitations are acceptable for demonstrating structures, functions, file handling, validation, and procedural programming in C.

---

# 🚀 Possible Future Improvements

The project can be further enhanced with:

* Secure password hashing
* Encrypted account storage
* Database integration
* Dynamic memory allocation
* Duplicate account-number detection
* Admin login system
* User login dashboard
* Interest calculation for savings accounts
* Beneficiary management
* Transfer receipts
* Account statements exported to files
* ATM-style interface
* Login attempt limits
* Audit logs
* Backup and restore functionality
* Cross-platform console support
* GUI implementation
* SQLite/MySQL integration

---

# 📚 Learning Outcomes

Through this project, the following practical concepts are demonstrated:

```text
✔ Structures
✔ Nested Structures
✔ Arrays
✔ Functions
✔ Function Prototypes
✔ Conditional Logic
✔ Switch Statements
✔ Loops
✔ String Handling
✔ File Handling
✔ Binary Files
✔ Password Input
✔ Authentication
✔ Input Validation
✔ Error Handling
✔ Date & Time
✔ Transaction Processing
✔ Data Persistence
✔ Console UI Design
```

---

# 🎓 Internship Context

**Program:** InternGrow Internship

**Task:** Task 2 — Banking Management System

**Week:** Week 2

**Language:** C

**Task Focus:**

```text
Structures
File Handling
Functions
Conditional Logic
Password Protection
Error Handling
```

This project extends the required task by implementing additional banking operations and management features while maintaining a procedural C programming approach.

---

# 📌 Quick Feature Summary

```text
╔════════════════════════════════════════════════════╗
║           ADVANCED BANKING SYSTEM                  ║
╠════════════════════════════════════════════════════╣
║                                                    ║
║  👤 Create New Account                             ║
║  💵 Deposit Money                                  ║
║  💳 Withdraw Money                                 ║
║  💰 Balance Inquiry                                ║
║  📜 Transaction History                            ║
║  🔎 Account Search                                 ║
║  🗑️ Delete Account                                 ║
║  🔄 Transfer Money                                 ║
║  📋 View All Accounts                              ║
║  🔒 Freeze / Unfreeze Account                      ║
║  🔑 Change Password                                ║
║  📅 Monthly Statement                              ║
║  💾 Binary File Storage                            ║
║  🛡️ Input Validation & Error Handling              ║
║                                                    ║
╚════════════════════════════════════════════════════╝
```

---

# 🏁 Conclusion

The **Advanced Banking Management System** demonstrates how core C programming concepts can be combined to build a practical, menu-driven application.

Starting from the basic requirements of account creation, deposits, withdrawals, balance inquiry, transaction history, account search, file storage, password protection, and error handling, the project extends the functionality with money transfers, account status management, password changes, account statistics, daily withdrawal controls, and monthly statements.

The result is a structured console application that demonstrates practical use of **structures, functions, arrays, file handling, validation, conditional logic, transaction processing, and persistent data storage**.

---

<p align="center">

### 🏦 Advanced Banking Management System

<b>Built with C • Structures • Functions • File Handling</b>

<br><br>

⭐ <b>InternGrow Internship — Task 2</b> ⭐

</p>

---

## 📁 Repository Structure Reference

```text
InternGrow_Internship/
│
└── Task 2 Banking Management System/
    │
    ├── images/
    │   ├── 01-main-menu.png
    │   ├── 02-create-account.png
    │   ├── 03-deposit-money.png
    │   ├── 04-withdraw-money.png
    │   ├── 05-balance-inquiry.png
    │   ├── 06-transaction-history.png
    │   ├── 07-account-search.png
    │   ├── 08-transfer-frozen-account.png
    │   ├── 09-transfer-money-success.png
    │   ├── 10-freeze-unfreeze-account.png
    │   ├── 11-change-password.png
    │   ├── 12-delete-account.png
    │   ├── 13-all-accounts-initial.png
    │   ├── 14-all-accounts-updated.png
    │   ├── 15-monthly-statement.png
    │   └── 16-thank-you-exit.png
    │
    ├── main.c
    └── README.md
```

> **Runtime file:** `accounts.dat` is created automatically by the application when account data is saved.
