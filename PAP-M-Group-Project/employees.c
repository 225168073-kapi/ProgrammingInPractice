#include <stdio.h>
#include <string.h>
#include "employees.h"

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

static void cleanNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void addEmployee(void) {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("\n[ERROR] Maximum employee capacity reached!\n");
        return;
    }
    Employee e;
    printf("\n--- ADD NEW EMPLOYEE ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    getchar();

    printf("Enter Name: ");
    fgets(e.name, STR_LEN, stdin);
    cleanNewline(e.name);

    printf("Enter Department: ");
    fgets(e.department, STR_LEN, stdin);
    cleanNewline(e.department);

    do {
        printf("Enter Basic Salary (N$): ");
        scanf("%lf", &e.basicSalary);
        if (e.basicSalary < 0) printf("[VALIDATION] Salary cannot be negative!\n");
    } while (e.basicSalary < 0);

    do {
        printf("Enter Housing Allowance (N$): ");
        scanf("%lf", &e.housingAllowance);
        if (e.housingAllowance < 0) printf("[VALIDATION] Allowance cannot be negative!\n");
    } while (e.housingAllowance < 0);

    do {
        printf("Enter Transport Allowance (N$): ");
        scanf("%lf", &e.transportAllowance);
        if (e.transportAllowance < 0) printf("[VALIDATION] Allowance cannot be negative!\n");
    } while (e.transportAllowance < 0);

    e.netSalary = e.basicSalary + e.housingAllowance + e.transportAllowance;
    employees[employeeCount++] = e;
    printf("[SUCCESS] Employee added successfully!\n");
}

void displayEmployees(void) {
    if (employeeCount == 0) {
        printf("\nNo employees recorded in system.\n");
        return;
    }
    printf("\n%-5s %-20s %-15s %-12s %-12s %-12s %-12s\n", 
           "ID", "Name", "Department", "Basic(N$)", "House(N$)", "Trans(N$)", "Net Salary");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("%-5d %-20s %-15s %-12.2f %-12.2f %-12.2f %-12.2f\n",
               employees[i].id, employees[i].name, employees[i].department,
               employees[i].basicSalary, employees[i].housingAllowance,
               employees[i].transportAllowance, employees[i].netSalary);
    }
}

void searchEmployee(void) {
    if (employeeCount == 0) {
        printf("\nNo employees available to search.\n");
        return;
    }
    char query[STR_LEN];
    int found = 0;
    getchar();
    printf("\nEnter Employee Name or Department to search: ");
    fgets(query, STR_LEN, stdin);
    cleanNewline(query);

    printf("\n%-5s %-20s %-15s %-12s\n", "ID", "Name", "Department", "Net Salary");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < employeeCount; i++) {
        if (strstr(employees[i].name, query) != NULL || strcmp(employees[i].department, query) == 0) {
            printf("%-5d %-20s %-15s %-12.2f\n", 
                   employees[i].id, employees[i].name, employees[i].department, employees[i].netSalary);
            found = 1;
        }
    }
    if (!found) printf("No matching employee records found.\n");
}

void employeeMenu(void) {
    int choice;
    do {
        printf("\n=== EMPLOYEE MANAGEMENT ===\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
}