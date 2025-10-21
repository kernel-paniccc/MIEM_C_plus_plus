#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*�89 �⠭���� */

#define MAX_EXPENSES 1000

struct Expense {
    char date[11];
    char category[30];
    float amount;
};

struct Expense expenses[MAX_EXPENSES];
int expenseCount = 0;


void loadExpenses(const char *filename)
{
    FILE *fin = fopen(filename, "r");
    if (!fin)
        return;

    while (fscanf(fin, "%10s %29s %f", expenses[expenseCount].date, expenses[expenseCount].category, &expenses[expenseCount].amount) == 3) {
        expenseCount++;
        if (expenseCount >= MAX_EXPENSES)
            break;
    }
    fclose(fin);
}


void saveExpenseToFile(const char *filename, struct Expense e)
{
    FILE *fout = fopen(filename, "a");
    if (!fout) {
        printf("�訡�� �� ��࠭���� 䠩��!\n");
        return;
    }
    fprintf(fout, "%s %s %.2f\n", e.date, e.category, e.amount);
    fclose(fout);
}


void addExpense()
{
    struct Expense e;
    if (expenseCount >= MAX_EXPENSES) {
        printf("�ॢ�襭 ����� ��室��!\n");
        return;
    }
    printf("������ ���� (��.��.����): ");
    scanf("%10s", e.date);

    printf("������ ��⥣���: ");
    scanf("%29s", e.category);

    printf("������ �㬬�: ");
    scanf("%f", &e.amount);

    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    printf("���室 ��������!\n");
}


void showAllExpenses()
{
    int i;
    if (expenseCount == 0) {
        printf("��� ������ � ��室��.\n");
        return;
    }
    printf("\n--- �� ��室� ---\n");
    printf("%-12s%-15s%s\n", "���", "��⥣���", "�㬬�");
    printf("------------------------------\n");
    for (i = 0; i < expenseCount; i++) {
        printf("%-12s%-15s%.2f ��.\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
}


void showStats()
{
    int i;
    float total = 0, max;
    if (expenseCount == 0) {
        printf("��� ������ ��� �������.\n");
        return;
    }
    max = expenses[0].amount;
    for (i = 0; i < expenseCount; i++) {
        total += expenses[i].amount;
        if (expenses[i].amount > max)
            max = expenses[i].amount;
    }
    printf("\n--- ����⨪� ---\n");
    printf("�ᥣ� ����祭�: %.2f ��.\n", total);
    printf("�।��� ���: %.2f ��.\n", total / expenseCount);
    printf("���ᨬ��쭠� ���: %.2f ��.\n", max);
}


void showMenu()
{
    printf("\n=== �४�� ��室�� ===\n");
    printf("1. �������� ��室\n");
    printf("2. �������� �� ��室�\n");
    printf("3. �������� ����⨪�\n");
    printf("4. ��室\n");
    printf("�롥�� �㭪�: ");
}

int main()
{
    int choice;
    loadExpenses("expenses.txt");
    do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                showAllExpenses();
                break;
            case 3:
                showStats();
                break;
            case 4:
                printf("��室 �� �ணࠬ��.\n");
                break;
            default:
                printf("������ �롮�.\n");
        }
    } while (choice != 4);

    return 0;
}