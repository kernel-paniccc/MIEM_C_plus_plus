#include <iostream> // ��� �����/�뢮�� �१ ���᮫� (cin, cout)
#include <fstream>  // ��� ࠡ��� � 䠩���� (ifstream, ofstream)
#include <cstring>  // ��� ࠡ��� � ��ப��� (char[])
#include <iomanip>  // ��� ��ᨢ��� �ଠ�஢���� �뢮�� (setw, left)

using namespace std; // �⮡� �� ����� std:: ��। ����� cout, cin � �.�.

const int MAX_EXPENSES = 1000; // ���ᨬ��쭮� ������⢮ ��室��, ����� ����� ��࠭���

// ������� ��� ������ ��室�
struct Expense
{
    char date[11];     // ��ப� ��� ���� (�ଠ�: "��.��.����", ���ਬ��: "24.09.2025")
    char category[30]; // ��ப� ��� ��⥣�ਨ (���ਬ��: "���", "�࠭ᯮ��")
    float amount;      // �㬬� ��室� � �㡫��
};

// �������� ���ᨢ ��� �࠭���� ��� ��室��
Expense expenses[MAX_EXPENSES];
int expenseCount = 0; // ����饥 ������⢮ ����ᥩ ��室��

// --- �㭪�� ��� ����㧪� ��室�� �� 䠩�� ---
void loadExpenses(const char *filename)
{
    ifstream fin(filename); // ���뢠�� 䠩� �� �⥭��

    if (!fin)
        return; // �᫨ 䠩� �� ������ ? ��室�� �� �㭪樨

    // �⥭�� ������ �����筮, ���� ���� �� ����
    while (fin >> expenses[expenseCount].date >> expenses[expenseCount].category >> expenses[expenseCount].amount)
    {
        expenseCount++; // �����稢��� ����稪 ��᫥ �ᯥ譮�� �⥭��
    }

    fin.close(); // ����뢠�� 䠩�
}

// --- �㭪�� ��� ��࠭���� ������ ��室� � 䠩� ---
void saveExpenseToFile(const char *filename, Expense e)
{
    ofstream fout(filename, ios::app); // ���뢠�� 䠩� � ०��� ���������� (append)

    if (!fout)
    {
        cout << "�訡�� �� ��࠭���� 䠩��!" << endl;
        return;
    }

    // �����뢠�� ����, ��⥣��� � �㬬� � 䠩� �१ �஡��
    fout << e.date << " " << e.category << " " << e.amount << endl;

    fout.close(); // ����뢠�� 䠩�
}

// --- �㭪�� ��� ���������� ������ ��室� ---
void addExpense()
{
    // �஢��塞, �� �ॢ�襭 �� �����
    if (expenseCount >= MAX_EXPENSES)
    {
        cout << "�ॢ�襭 ����� ��室��!" << endl;
        return;
    }

    Expense e; // ������ ����� ��६����� ��� ��室�

    // ���뢠�� ����� �� ���짮��⥫�
    cout << "������ ���� (��.��.����): ";
    cin >> e.date;

    cout << "������ ��⥣���: ";
    cin >> e.category;

    cout << "������ �㬬�: ";
    cin >> e.amount;

    // ������塞 � ���ᨢ � ��࠭塞 � 䠩�
    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    cout << "���室 ��������!\n";
}

// --- �㭪�� ��� �⮡ࠦ���� ��� ��室�� ---
void showAllExpenses()
{
    if (expenseCount == 0)
    {
        cout << "��� ������ � ��室��.\n";
        return;
    }

    // ��������� ⠡����
    cout << "\n--- �� ��室� ---\n";
    cout << left << setw(12) << "���"
         << setw(15) << "��⥣���"
         << "�㬬�\n";
    cout << "------------------------------\n";

    // �뢮��� ������ ������
    for (int i = 0; i < expenseCount; i++)
    {
        cout << left << setw(12) << expenses[i].date
             << setw(15) << expenses[i].category
             << expenses[i].amount << " ��.\n";
    }
}

// --- �㭪�� ��� �뢮�� ����⨪� ---
void showStats()
{
    if (expenseCount == 0)
    {
        cout << "��� ������ ��� �������.\n";
        return;
    }

    float total = 0;                // ���� �㬬�
    float max = expenses[0].amount; // ����� ������ ��� (��稭��� � ��ࢮ�)

    // ��⠥� �㬬� � ��室�� ���ᨬ�
    for (int i = 0; i < expenseCount; i++)
    {
        total += expenses[i].amount;

        if (expenses[i].amount > max)
        {
            max = expenses[i].amount;
        }
    }

    float average = total / expenseCount; // �।��� ���祭��

    // �뢮��� ����⨪�
    cout << "\n--- ����⨪� ---\n";
    cout << "�ᥣ� ����祭�: " << total << " ��.\n";
    cout << "�।��� ���: " << average << " ��.\n";
    cout << "���ᨬ��쭠� ���: " << max << " ��.\n";
}

// --- �㭪�� ��� �⮡ࠦ���� ���� ���짮��⥫� ---
void showMenu()
{
    cout << "\n=== �४�� ��室�� ===\n";
    cout << "1. �������� ��室\n";
    cout << "2. �������� �� ��室�\n";
    cout << "3. �������� ����⨪�\n";
    cout << "4. ��室\n";
    cout << "�롥�� �㭪�: ";
}

// --- ������� �㭪�� �ணࠬ�� ---
int main()
{
    loadExpenses("expenses.txt"); // ����㦠�� ����� �� 䠩�� (�᫨ �� ����)

    int choice; // ��६����� ��� �࠭���� �롮� ���짮��⥫�

    // �᭮���� 横� ����
    do
    {
        showMenu();    // �����뢠�� ����
        cin >> choice; // ���뢠�� �롮�

        // �믮��塞 ����⢨� �� �롮��
        switch (choice)
        {
        case 1:
            addExpense(); // �������� ��室
            break;
        case 2:
            showAllExpenses(); // �������� �� ��室�
            break;
        case 3:
            showStats(); // �������� ����⨪�
            break;
        case 4:
            cout << "��室 �� �ணࠬ��.\n"; // �����襭��
            break;
        default:
            cout << "������ �롮�.\n"; // �訡�� �롮�
        }

    } while (choice != 4); // ���� ���짮��⥫� �� ��ࠫ "��室"

    return 0; // �����頥� 0 ? �ਧ��� �ᯥ譮�� �����襭��
}
