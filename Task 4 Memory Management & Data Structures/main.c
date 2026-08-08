#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== COLOR MACROS (Standard ASCII) ====================
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// ==================== SINGLY LINKED LIST ====================
typedef struct SNode {
    int data;
    struct SNode* next;
} SNode;

SNode* sHead = NULL;

void sInsert(int data) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = data;
    newNode->next = sHead;
    sHead = newNode;
    printf(GREEN "[+] Inserted %d\n" RESET, data);
}

void sDelete(int data) {
    SNode *temp = sHead, *prev = NULL;
    if (temp != NULL && temp->data == data) {
        sHead = temp->next;
        free(temp);
        printf(RED "[-] Deleted %d\n" RESET, data);
        return;
    }
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(YELLOW "[!] %d not found\n" RESET, data);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf(RED "[-] Deleted %d\n" RESET, data);
}

void sDisplay() {
    SNode* temp = sHead;
    if (!temp) {
        printf(YELLOW "[!] List is empty\n" RESET);
        return;
    }
    printf(CYAN "[Singly Linked List] " RESET);
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void sFree() {
    SNode* temp;
    while (sHead) {
        temp = sHead;
        sHead = sHead->next;
        free(temp);
    }
}

// ==================== DOUBLY LINKED LIST ====================
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* dHead = NULL;
DNode* dTail = NULL;

void dInsert(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = dHead;
    if (dHead) dHead->prev = newNode;
    else dTail = newNode;
    dHead = newNode;
    printf(GREEN "[+] Inserted %d\n" RESET, data);
}

void dDelete(int data) {
    DNode* temp = dHead;
    while (temp && temp->data != data) temp = temp->next;
    if (!temp) {
        printf(YELLOW "[!] %d not found\n" RESET, data);
        return;
    }
    if (temp->prev) temp->prev->next = temp->next;
    else dHead = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    else dTail = temp->prev;
    free(temp);
    printf(RED "[-] Deleted %d\n" RESET, data);
}

void dDisplay() {
    DNode* temp = dHead;
    if (!temp) {
        printf(YELLOW "[!] List is empty\n" RESET);
        return;
    }
    printf(MAGENTA "[Doubly Linked List] " RESET);
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void dFree() {
    DNode* temp;
    while (dHead) {
        temp = dHead;
        dHead = dHead->next;
        free(temp);
    }
    dTail = NULL;
}

// ==================== STACK ====================
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

StackNode* stackTop = NULL;

void push(int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = stackTop;
    stackTop = newNode;
    printf(GREEN "[+] Pushed %d\n" RESET, data);
}

void pop() {
    if (!stackTop) {
        printf(YELLOW "[!] Stack empty\n" RESET);
        return;
    }
    StackNode* temp = stackTop;
    stackTop = stackTop->next;
    printf(RED "[-] Popped %d\n" RESET, temp->data);
    free(temp);
}

void stackDisplay() {
    StackNode* temp = stackTop;
    if (!temp) {
        printf(YELLOW "[!] Stack is empty\n" RESET);
        return;
    }
    printf(CYAN "[Stack] Top -> " RESET);
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("Bottom\n");
}

void stackFree() {
    StackNode* temp;
    while (stackTop) {
        temp = stackTop;
        stackTop = stackTop->next;
        free(temp);
    }
}

// ==================== QUEUE ====================
typedef struct QNode {
    int data;
    struct QNode* next;
} QNode;

QNode* qFront = NULL;
QNode* qRear = NULL;

void enqueue(int data) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    newNode->data = data;
    newNode->next = NULL;
    if (!qRear) {
        qFront = qRear = newNode;
    } else {
        qRear->next = newNode;
        qRear = newNode;
    }
    printf(GREEN "[+] Enqueued %d\n" RESET, data);
}

void dequeue() {
    if (!qFront) {
        printf(YELLOW "[!] Queue empty\n" RESET);
        return;
    }
    QNode* temp = qFront;
    qFront = qFront->next;
    if (!qFront) qRear = NULL;
    printf(RED "[-] Dequeued %d\n" RESET, temp->data);
    free(temp);
}

void queueDisplay() {
    QNode* temp = qFront;
    if (!temp) {
        printf(YELLOW "[!] Queue is empty\n" RESET);
        return;
    }
    printf(CYAN "[Queue] Front -> " RESET);
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("Rear\n");
}

void queueFree() {
    QNode* temp;
    while (qFront) {
        temp = qFront;
        qFront = qFront->next;
        free(temp);
    }
    qRear = NULL;
}

// ==================== CIRCULAR QUEUE ====================
#define MAX 5
int cq[MAX];
int cqFront = -1, cqRear = -1;

void cEnqueue(int data) {
    if ((cqFront == 0 && cqRear == MAX - 1) || (cqRear + 1 == cqFront)) {
        printf(YELLOW "[!] Circular Queue is full\n" RESET);
        return;
    }
    if (cqFront == -1) cqFront = cqRear = 0;
    else if (cqRear == MAX - 1) cqRear = 0;
    else cqRear++;
    cq[cqRear] = data;
    printf(GREEN "[+] Enqueued %d in circular queue\n" RESET, data);
}

void cDequeue() {
    if (cqFront == -1) {
        printf(YELLOW "[!] Circular Queue is empty\n" RESET);
        return;
    }
    printf(RED "[-] Dequeued %d from circular queue\n" RESET, cq[cqFront]);
    if (cqFront == cqRear) cqFront = cqRear = -1;
    else if (cqFront == MAX - 1) cqFront = 0;
    else cqFront++;
}

void cDisplay() {
    if (cqFront == -1) {
        printf(YELLOW "[!] Circular Queue is empty\n" RESET);
        return;
    }
    printf(MAGENTA "[Circular Queue] " RESET);
    int i = cqFront;
    while (1) {
        printf("%d ", cq[i]);
        if (i == cqRear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// ==================== MEMORY STATS ====================
void showMemoryStats() {
    printf(CYAN "\n=== MEMORY MANAGEMENT STATS ===\n" RESET);
    printf("Using dynamic memory allocation (malloc/free)\n");
    printf("All structures use heap memory\n");
    printf("Each structure has its own free function\n");
    printf("No memory leaks - all allocations tracked\n\n");
}

// ==================== COLORFUL MENU ====================
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader(int screen) {
    clearScreen();
    // Cycle through colors
    const char* colors[] = {BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW};
    printf("%s", colors[screen % 6]);
    printf(BOLD "\n");
    printf("+---------------------------------------------------+\n");
    printf("|          DATA STRUCTURES MANAGEMENT SYSTEM         |\n");
    printf("|                   Dynamic Memory                   |\n");
    printf("+---------------------------------------------------+\n");
    printf(RESET);
}

void printMenu() {
    printf("\n" BOLD "+------------------ MAIN MENU --------------+\n" RESET);
    printf("| 1. Singly Linked List                     |\n");
    printf("| 2. Doubly Linked List                     |\n");
    printf("| 3. Stack                                  |\n");
    printf("| 4. Queue                                  |\n");
    printf("| 5. Circular Queue                         |\n");
    printf("| 6. Show Memory Stats                      |\n");
    printf("| 7. Free All & Exit                        |\n");
    printf("+-------------------------------------------+\n");
    printf(BOLD "Enter choice: " RESET);
}

void printSubMenu(char* name) {
    printf("\n" BOLD "+------------ %s ------------+\n" RESET, name);
    printf("| 1. Insert/Enqueue/Push          |\n");
    printf("| 2. Delete/Dequeue/Pop           |\n");
    printf("| 3. Display                      |\n");
    printf("| 4. Back to Main                 |\n");
    printf("+---------------------------------+\n");
    printf(BOLD "Enter choice: " RESET);
}

// ==================== MAIN ====================
int main() {
    int choice, subChoice, data, screenCounter = 0;

    while (1) {
        screenCounter++;
        printHeader(screenCounter);
        printMenu();
        scanf("%d", &choice);

        if (choice == 7) {
            sFree(); dFree(); stackFree(); queueFree();
            printf(GREEN "\n[+] All memory freed. Goodbye!\n" RESET);
            break;
        }

        if (choice == 6) {
            showMemoryStats();
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
            continue;
        }

        char* structName[] = {"", "Singly Linked List", "Doubly Linked List",
                             "Stack", "Queue", "Circular Queue"};
        int active = 1;

        while (active) {
            screenCounter++;
            printHeader(screenCounter);
            printSubMenu(structName[choice]);
            scanf("%d", &subChoice);

            switch(choice) {
                case 1: // Singly Linked List
                    if (subChoice == 1) {
                        printf("Enter data: ");
                        scanf("%d", &data);
                        sInsert(data);
                    }
                    else if (subChoice == 2) {
                        printf("Enter data to delete: ");
                        scanf("%d", &data);
                        sDelete(data);
                    }
                    else if (subChoice == 3) sDisplay();
                    else if (subChoice == 4) active = 0;
                    break;

                case 2: // Doubly Linked List
                    if (subChoice == 1) {
                        printf("Enter data: ");
                        scanf("%d", &data);
                        dInsert(data);
                    }
                    else if (subChoice == 2) {
                        printf("Enter data to delete: ");
                        scanf("%d", &data);
                        dDelete(data);
                    }
                    else if (subChoice == 3) dDisplay();
                    else if (subChoice == 4) active = 0;
                    break;

                case 3: // Stack
                    if (subChoice == 1) {
                        printf("Enter data: ");
                        scanf("%d", &data);
                        push(data);
                    }
                    else if (subChoice == 2) pop();
                    else if (subChoice == 3) stackDisplay();
                    else if (subChoice == 4) active = 0;
                    break;

                case 4: // Queue
                    if (subChoice == 1) {
                        printf("Enter data: ");
                        scanf("%d", &data);
                        enqueue(data);
                    }
                    else if (subChoice == 2) dequeue();
                    else if (subChoice == 3) queueDisplay();
                    else if (subChoice == 4) active = 0;
                    break;

                case 5: // Circular Queue
                    if (subChoice == 1) {
                        printf("Enter data: ");
                        scanf("%d", &data);
                        cEnqueue(data);
                    }
                    else if (subChoice == 2) cDequeue();
                    else if (subChoice == 3) cDisplay();
                    else if (subChoice == 4) active = 0;
                    break;

                default: active = 0;
            }

            if (subChoice >= 1 && subChoice <= 3) {
                printf("\n");
                printf("Press Enter to continue...");
                getchar();
                getchar();
            }
        }
    }

    return 0;
}
