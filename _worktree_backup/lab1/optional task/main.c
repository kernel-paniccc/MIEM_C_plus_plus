#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*С89 стандарт */

#define MAX_EXPENSES 1000

struct Expense {
    char date[11];
    char category[30];
    float amount;
};

struct Expense expenses[MAX_EXPaENSES];
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
        printf("Ошибка при сохранении файла!\n");
        return;
    }
    fprintf(fout, "%s %s %.2f\n", e.date, e.category, e.amount);
    fclose(fout);
}


void addExpense()
{
    struct Expense e;
    if (expenseCount >= MAX_EXPENSES) {
        printf("Превышен лимит расходов!\n");
        return;
    }
    printf("Введите дату (дд.мм.гггг): ");
    scanf("%10s", e.date);

    printf("Введите категорию: ");
    scanf("%29s", e.category);

    printf("Введите сумму: ");
    scanf("%f", &e.amount);

    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    printf("Расход добавлен!\n");
}


void showAllExpenses()
{
    int i;
    if (expenseCount == 0) {
        printf("Нет данных о расходах.\n");
        return;
    }
    printf("\n--- Все расходы ---\n");
    printf("%-12s%-15s%s\n", "Дата", "Категория", "Сумма");
    printf("------------------------------\n");
    for (i = 0; i < expenseCount; i++) {
        printf("%-12s%-15s%.2f руб.\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
}


void showStats()
{
    int i;
    float total = 0, max;
    if (expenseCount == 0) {
        printf("Нет данных для анализа.\n");
        return;
    }
    max = expenses[0].amount;
    for (i = 0; i < expenseCount; i++) {
        total += expenses[i].amount;
        if (expenses[i].amount > max)
            max = expenses[i].amount;
    }
    printf("\n--- Статистика ---\n");
    printf("Всего потрачено: %.2f руб.\n", total);
    printf("Средняя трата: %.2f руб.\n", total / expenseCount);
    printf("Максимальная трата: %.2f руб.\n", max);
}


void showMenu()
{
    printf("\n=== Трекер расходов ===\n");
    printf("1. Добавить расход\n");
    printf("2. Показать все расходы\n");
    printf("3. Показать статистику\n");
    printf("4. Выход\n");
    printf("Выберите пункт: ");
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
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор.\n");
        }
    } while (choice != 4);

    return 0;
}
