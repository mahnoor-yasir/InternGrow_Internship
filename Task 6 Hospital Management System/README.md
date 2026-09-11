<div align="center">

# 🏥 Hospital Management System

### A Complete Console-Based Hospital Administration Solution in C

[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Version](https://img.shields.io/badge/Version-2.0-00B894?style=for-the-badge)](#)
[![Platform](https://img.shields.io/badge/Platform-Console-2D3436?style=for-the-badge&logo=windows-terminal&logoColor=white)](#)
[![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)](#)
[![Internship](https://img.shields.io/badge/InternGrow-Task%206-6C5CE7?style=for-the-badge)](#)

**A feature-rich, menu-driven Hospital Management System developed in C as part of InternGrow Internship Task 6. It provides an organized and efficient solution for managing patients, doctors, appointments, wards, billing, medical records, reports, and persistent hospital data.**

[Features](#-key-features) • [Modules](#-system-modules) • [Installation](#-installation-and-setup) • [Screenshots](#-project-screenshots) • [Author](#-author)

</div>

---

## 📌 Project Overview

The **Hospital Management System** is a console-based application designed to automate essential hospital operations. The project demonstrates practical implementation of core C programming concepts, including structures, pointers, dynamic memory allocation, file handling, searching, sorting, input validation, error handling, and modular programming.

The system offers separate modules for patients, appointments, doctors, wards, billing, medical records, reporting, and data management. Records can be stored in binary files, backed up, restored, imported, and exported for future use.

> **Project Type:** Internship Capstone Project  
> **Internship:** InternGrow  
> **Task:** Task 6 — Hospital Management System  
> **Programming Language:** C  
> **Version:** 2.0

---

## ✨ Key Features

<table>
<tr>
<td width="50%" valign="top">

### 👤 Patient Management

- Add complete patient records
- Update existing patient information
- View all registered patients
- Search patients using multiple filters
- View detailed patient profiles
- Discharge or remove patients

</td>
<td width="50%" valign="top">

### 📅 Appointment Management

- Schedule new appointments
- View all appointments
- Mark appointments as completed
- Cancel scheduled appointments
- View appointments by patient ID
- Track appointment status and reason

</td>
</tr>
<tr>
<td width="50%" valign="top">

### 💳 Billing and Payments

- Calculate hospital charges
- Generate detailed patient bills
- Process payments
- Maintain payment history
- Generate invoices
- Track total hospital revenue

</td>
<td width="50%" valign="top">

### 🩺 Medical Records

- Add diagnoses and prescriptions
- Store laboratory test results
- View patient medical records
- Update existing medical records
- Review complete patient history
- Date-stamped medical entries

</td>
</tr>
<tr>
<td width="50%" valign="top">

### 👨‍⚕️ Doctor and Ward Management

- Add, view, update, and delete doctors
- Assign doctors to patients
- Track doctor availability
- View ward occupancy and capacity
- Update ward information
- View patients assigned to each ward

</td>
<td width="50%" valign="top">

### 📊 Reports and Data Management

- Daily and monthly reports
- Doctor, ward, disease, and revenue reports
- Patient summary reports
- Binary-file data persistence
- Backup and restore support
- CSV/JSON export and CSV import

</td>
</tr>
</table>

---

## 🧩 System Modules

| No. | Module | Main Capabilities |
|:---:|---|---|
| 01 | **Patient Management** | Add, update, search, view, and discharge patients |
| 02 | **Appointment Management** | Schedule, complete, cancel, and review appointments |
| 03 | **Billing System** | Calculate bills, generate invoices, and process payments |
| 04 | **Reports** | Generate daily, monthly, doctor, ward, disease, revenue, and patient reports |
| 05 | **Administration** | Manage doctors, wards, discharges, appointments, and system statistics |
| 06 | **Data Management** | Save, load, back up, restore, import, export, sort, and inspect data |
| 07 | **Medical Records** | Add, view, update, and review medical history |

---

## 🔍 Search and Sorting

The application provides multiple methods for locating and organizing records:

| Category | Available Operations |
|---|---|
| **Patient Search** | ID using binary search, name using linear search, disease, doctor, and admission-date range |
| **Patient Sorting** | Name, ID, disease, and age |
| **Record Filters** | Patient appointments, doctor patients, ward patients, and medical history |

---

## 🛠️ Programming Concepts Used

- **Structures:** Patient, Doctor, Appointment, Payment, Medical Record, and Ward data models
- **Pointers:** Dynamic arrays and memory-based record handling
- **Dynamic Memory Allocation:** `malloc()`, `realloc()`, and `free()`
- **File Handling:** Binary storage, CSV import/export, JSON export, backups, and logs
- **Searching Algorithms:** Binary search and linear search
- **Sorting Algorithms:** Record sorting by multiple patient attributes
- **Input Validation:** Integer, decimal, string, gender, and date validation
- **Error Handling:** Error logs, allocation checks, and file-operation checks
- **Modular Programming:** Separate functions for every major operation
- **ANSI Formatting:** Colored headings, warnings, status messages, and menus

---

## ⚙️ Installation and Setup

### Prerequisites

Install a C compiler such as **GCC**, **MinGW**, or use an IDE such as **Code::Blocks**, **Dev-C++**, or **Visual Studio Code** with a C compiler configured.

### 1. Clone the repository

```bash
git clone https://github.com/mahnoor-yasir/InternGrow_Internship.git
```

### 2. Open the project directory

```bash
cd "InternGrow_Internship/Task 6 Hospital Management System"
```

### 3. Compile the program

```bash
gcc main.c -o hospital_management
```

### 4. Run the program

**Windows:**

```bash
hospital_management.exe
```

**Linux/macOS:**

```bash
./hospital_management
```

---

## 🚀 How to Use

1. Compile and launch the application.
2. Select a module by entering its number in the main menu.
3. Follow the displayed prompts to add, update, search, or view records.
4. Use the **Data Management** module to save, back up, restore, import, or export data.
5. Enter `0` in a submenu to return to the previous menu or exit from the main menu.

> Enter valid values in the requested formats. Dates should use `DD/MM/YYYY`, and menu choices should be entered as numbers.

---

## 💾 Data Storage

| File | Purpose |
|---|---|
| `patients.bin` | Stores patient records persistently |
| `appointments.bin` | Stores appointment records |
| `medical_records.bin` | Stores patient medical records |
| `doctors.bin` | Stores registered doctor records |
| `backup_YYYYMMDD_HHMMSS.bin` | Stores a timestamped, recoverable backup of patient data |
| `patients_import.csv` | Provides patient records for the CSV import operation |
| `patients_export.csv` | Contains exported patient data in CSV format |
| `patients_export.json` | Contains exported patient data in JSON format |
| `invoice.txt` | Contains the latest generated payment invoice |
| `error.log` | Records application errors and diagnostic information |

---

## 📸 Project Screenshots

### 🏠 Main Interface

<table>
<tr>
<td width="50%" align="center"><strong>01 — Main Menu</strong><br><br><img src="images/01_Main_Menu.png" alt="Hospital Management System Main Menu" width="100%"></td>
<td width="50%" align="center"><strong>02 — Patient Management</strong><br><br><img src="images/02_Patient_Management.png" alt="Patient Management Menu" width="100%"></td>
</tr>
</table>

### 👤 Patient Management

<table>
<tr>
<td width="50%" align="center"><strong>03 — Add New Patient</strong><br><br><img src="images/03_Add_New_Patient.png" alt="Add New Patient" width="100%"></td>
<td width="50%" align="center"><strong>04 — Update Patient</strong><br><br><img src="images/04_Update_Patient.png" alt="Update Patient" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>05 — View All Patients</strong><br><br><img src="images/05_View_All_Patients.png" alt="View All Patients" width="100%"></td>
<td width="50%" align="center"><strong>06 — Search Patient</strong><br><br><img src="images/06_Search_Patient.png" alt="Search Patient" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>07 — View Patient Details</strong><br><br><img src="images/07_View_Patient_Details.png" alt="View Patient Details" width="100%"></td>
<td width="50%" align="center"><strong>08 — Discharge Patient</strong><br><br><img src="images/08_Discharge_Patient.png" alt="Discharge Patient" width="100%"></td>
</tr>
</table>

### 📅 Appointment Management

<table>
<tr>
<td width="50%" align="center"><strong>09 — Appointment Management</strong><br><br><img src="images/09_Appointment_Management.png" alt="Appointment Management Menu" width="100%"></td>
<td width="50%" align="center"><strong>10 — Schedule Appointment</strong><br><br><img src="images/10_Schedule_Appointment.png" alt="Schedule Appointment" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>11 — View All Appointments</strong><br><br><img src="images/11_View_All_Appointments.png" alt="View All Appointments" width="100%"></td>
<td width="50%" align="center"><strong>12 — Complete Appointment</strong><br><br><img src="images/12_Complete_Appointment.png" alt="Complete Appointment" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>13 — Cancel Appointment</strong><br><br><img src="images/13_Cancel_Appointment.png" alt="Cancel Appointment" width="100%"></td>
<td width="50%" align="center"><strong>14 — Patient Appointments</strong><br><br><img src="images/14_View_Patient_Appointments.png" alt="View Patient Appointments" width="100%"></td>
</tr>
</table>

### 💳 Billing System

<table>
<tr>
<td width="50%" align="center"><strong>15 — Billing System</strong><br><br><img src="images/15_Billing_System.png" alt="Billing System Menu" width="100%"></td>
<td width="50%" align="center"><strong>16 — Generate Hospital Bill</strong><br><br><img src="images/16_Generate_Hospital_Bill.png" alt="Generate Hospital Bill" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>17 — Process Payment</strong><br><br><img src="images/17_Process_Payment.png" alt="Process Payment" width="100%"></td>
<td width="50%" align="center"><strong>Payment Workflow</strong><br><br>Calculate charges, generate an itemized bill, process a payment, review payment history, and generate an invoice.</td>
</tr>
</table>

### 📊 Reports

<table>
<tr>
<td width="50%" align="center"><strong>18 — Reports Menu</strong><br><br><img src="images/18_Reports_Menu.png" alt="Reports Menu" width="100%"></td>
<td width="50%" align="center"><strong>19 — Daily Report</strong><br><br><img src="images/19_Daily_Report.png" alt="Daily Report" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>20 — Monthly Statistics</strong><br><br><img src="images/20_Monthly_Statistics.png" alt="Monthly Statistics" width="100%"></td>
<td width="50%" align="center"><strong>21 — Doctor Report</strong><br><br><img src="images/21_Doctor_Report.png" alt="Doctor Report" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>22 — Ward Report</strong><br><br><img src="images/22_Ward_Report.png" alt="Ward Report" width="100%"></td>
<td width="50%" align="center"><strong>23 — Disease Report</strong><br><br><img src="images/23_Disease_Report.png" alt="Disease Report" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>24 — Patient Summary Report</strong><br><br><img src="images/24_Patient_Summary_Report.png" alt="Patient Summary Report" width="100%"></td>
<td width="50%" align="center"><strong>Reporting Capabilities</strong><br><br>Monitor patient activity, revenue, doctor assignments, ward occupancy, disease statistics, and overall hospital performance.</td>
</tr>
</table>

### ⚙️ Administration

<table>
<tr>
<td width="50%" align="center"><strong>25 — Administration</strong><br><br><img src="images/25_Administration.png" alt="Administration Menu" width="100%"></td>
<td width="50%" align="center"><strong>26 — Doctor Management</strong><br><br><img src="images/26_Doctor_Management.png" alt="Doctor Management Menu" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>27 — Add Doctor</strong><br><br><img src="images/27_Add_Doctor.png" alt="Add Doctor" width="100%"></td>
<td width="50%" align="center"><strong>28 — View All Doctors</strong><br><br><img src="images/28_View_All_Doctors.png" alt="View All Doctors" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>29 — Ward Management</strong><br><br><img src="images/29_Ward_Management.png" alt="Ward Management Menu" width="100%"></td>
<td width="50%" align="center"><strong>30 — View Ward Status</strong><br><br><img src="images/30_View_Ward_Status.png" alt="View Ward Status" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>31 — View Ward Patients</strong><br><br><img src="images/31_View_Ward_Patients.png" alt="View Ward Patients" width="100%"></td>
<td width="50%" align="center"><strong>32 — System Statistics</strong><br><br><img src="images/32_System_Statistics.png" alt="System Statistics" width="100%"></td>
</tr>
</table>

### 💾 Data and Medical Records

<table>
<tr>
<td width="50%" align="center"><strong>33 — Data Management</strong><br><br><img src="images/33_Data_Management.png" alt="Data Management Menu" width="100%"></td>
<td width="50%" align="center"><strong>34 — Medical Records Menu</strong><br><br><img src="images/34_Medical_Records_Menu.png" alt="Medical Records Menu" width="100%"></td>
</tr>
<tr>
<td width="50%" align="center"><strong>35 — Add Medical Record</strong><br><br><img src="images/35_Add_Medical_Record.png" alt="Add Medical Record" width="100%"></td>
<td width="50%" align="center"><strong>36 — View Medical Records</strong><br><br><img src="images/36_View_Medical_Records.png" alt="View Medical Records" width="100%"></td>
</tr>
<tr>
<td colspan="2" align="center"><strong>37 — Exit System</strong><br><br><img src="images/37_Exit_System.png" alt="Exit Hospital Management System" width="70%"></td>
</tr>
</table>

---

## 🔮 Future Enhancements

- Graphical user interface using GTK or another C-compatible UI toolkit
- Database integration using MySQL or SQLite
- Role-based login for administrators, doctors, and reception staff
- Secure password storage and access control
- Real-time appointment reminders
- Prescription printing and downloadable invoices
- Dashboard charts for hospital analytics
- Network-based multi-user access

---

## 🎯 Learning Outcomes

This project strengthened practical understanding of:

- Designing and implementing a large modular C application
- Modeling real-world entities using structures
- Managing dynamic memory safely
- Implementing persistent file-based storage
- Applying search and sorting algorithms to structured records
- Validating user input and handling runtime errors
- Creating readable console interfaces and organized documentation

---

## 👩‍💻 Author

<div align="center">

### Mahnoor Yasir

**BS Computer Science Student | Developer & Problem Solver**

[![GitHub](https://img.shields.io/badge/GitHub-mahnoor--yasir-181717?style=for-the-badge&logo=github)](https://github.com/mahnoor-yasir)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Mahnoor%20Yasir-0A66C2?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/mahnoor-yasir/)
[![itch.io](https://img.shields.io/badge/itch.io-Game%20Portfolio-FA5C5C?style=for-the-badge&logo=itch.io&logoColor=white)](https://mahnoor-yasir.itch.io/)

</div>

---

## 📄 License and Usage

This project was created for educational and internship purposes. You may study and reference the code while providing appropriate credit to the author.

---

<div align="center">

### ⭐ If you found this project useful, consider giving the repository a star!

**Developed with dedication in C by Mahnoor Yasir**

</div>
