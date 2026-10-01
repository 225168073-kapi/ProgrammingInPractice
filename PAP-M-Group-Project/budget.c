#include <stdio.h>
#include <string.h>
#include "budget.h"

Budget budgets[MAX_BUDGETS];
int budgetCount = 0;

static void cleanNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

void addBudget(void) {
    if (budgetCount >= MAX_BUDGETS) {
        printf("\n[ERROR] Maximum budget records reached.\n");
        return;
    }
    Budget b;
    getchar();
    printf("\nEnter Department Name: ");
    fgets(b.department, STR_LEN, stdin);
    cleanNewline(b.department);

    do {
        printf("Enter Allocated Budget (N$): ");
        scanf("%lf", &b.allocatedBudget);
        if (b.allocatedBudget < 0) printf("[VALIDATION] Budget cannot be negative!\n");
    } while (b.allocatedBudget < 0);

    b.expenditure = 0.0;
    b.remainingBudget = b.allocatedBudget;
    b.isOverBudget = 0;

    budgets[budgetCount++] = b;
    printf("[SUCCESS] Departmental budget recorded.\n");
}

void addExpenditure(void) {
    if (budgetCount == 0) {
        printf("\nNo departments registered.\n");
        return;
    }
    char dept[STR_LEN];
    double amount;
    getchar();
    printf("\nEnter Department Name to log expense: ");
    fgets(dept, STR_LEN, stdin);
    cleanNewline(dept);

    for (int i = 0; i < budgetCount; i++) {
        if (strcmp(budgets[i].department, dept) == 0) {
            do {
                printf("Enter Expenditure Amount (N$): ");
                scanf("%lf", &amount);
                if (amount < 0) printf("[VALIDATION] Amount cannot be negative!\n");
            } while (amount < 0);

            budgets[i].expenditure += amount;
            budgets[i].remainingBudget = budgets[i].allocatedBudget - budgets[i].expenditure;
            budgets[i].isOverBudget = (budgets[i].remainingBudget < 0) ? 1 : 0;
            printf("[SUCCESS] Expenditure logged. Remaining: N$%.2f\n", budgets[i].remainingBudget);
            return;
        }
    }
    printf("Department not found.\n");
}

void displayBudgets(void) {
    if (budgetCount == 0) {
        printf("\nNo budget records found.\n");
        return;
    }
    printf("\n%-20s %-15s %-15s %-15s %-15s\n", 
           "Department", "Allocated(N$)", "Spent(N$)", "Remaining(N$)", "Status");
    printf("----------------------------------------------------------------------------------\n");
    for (int i = 0; i < budgetCount; i++) {
        printf("%-20s %-15.2f %-15.2f %-15.2f %-15s\n",
               budgets[i].department, budgets[i].allocatedBudget,
               budgets[i].expenditure, budgets[i].remainingBudget,
               budgets[i].isOverBudget ? "EXCEEDED" : "WITHIN BUDGET");
    }
}

void budgetMenu(void) {
    int choice;
    do {
        printf("\n=== BUDGET MANAGEMENT ===\n");
        printf("1. Enter Departmental Budget\n");
        printf("2. Log Expenditure\n");
        printf("3. Display Budget Overview\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBudget(); break;
            case 2: addExpenditure(); break;
            case 3: displayBudgets(); break;
            case 4: break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
}