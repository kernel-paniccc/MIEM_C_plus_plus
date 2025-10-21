#include <iostream> // For console input/output (cin, cout)
#include <fstream>  // For file operations (ifstream, ofstream)
#include <cstring>  // For string operations (char[])
#include <iomanip>  // For formatted output (setw, left)

using namespace std;
const int MAX_BOOKS = 1000;


struct Book {
	char name[100];
	char author[50];
	int year;
	float value;
};

Book AllBooks[MAX_BOOKS];
int bookCount = 0;

void saveBookToFile(const char *filename, Book B)
{
	ofstream fout(filename, ios::app);
	if (!fout)
	{
		cout << "�訡�� ����� � 䠩�!" << endl;
		return;
	}

	fout << B.name << " " << B.author << " " << B.year << " " << B.value << endl;
	fout.close();
}

void loadBooks(const char *filename)
{
	ifstream fin(filename);
	if (!fin)
		return;
	while (fin >> AllBooks[bookCount].name >> AllBooks[bookCount].author >> AllBooks[bookCount].year >> AllBooks[bookCount].value)
	{
		bookCount++;
	}

	fin.close();
}



bool Validation(Book book) {
	if (strlen(book.name) == 0) {
		cout << "����� ��ப�" << endl;
		return 1;
	}
	if (strlen(book.name) >= sizeof(book.name)) {
		cout << "���誮� ������� ��������" << endl;
		return 1;
	}

	if (strlen(book.author) == 0) {
		cout << "����� ��ப�" << endl;
		return 1;
	}
	if (strlen(book.author) >= sizeof(book.author)) {
		cout << "���誮� ������� ��� ����!" << endl;
		return 1;
	}

	if (book.year < 0 || book.year > 2025) {
		cout << "�訡�� ����" << endl;
		return 1;
	}

	if (book.value < 0 || book.value > 10) {
		cout << "�訡�� �業�� ���짮��⥫�" << endl;
		return 1;
	}

	return 0;
}


void input_book() {

	if (bookCount >= MAX_BOOKS) {
		cout << "�訡�� �����." << endl;
		return;
	}

	Book NewBook;

	cout << "������ ��������: ";
	cin.ignore();
	cin.getline(NewBook.name, 100);
	cout << "������ ����: ";
	cin.getline(NewBook.author, 50);

	cout << "������ ��� ���᪠: ";
	while (!(cin >> NewBook.year)) {
		cout << "�訡��! ������ 楫�� �᫮ ��� ����: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	cout << "������ ���� �業��: ";
	while (!(cin >> NewBook.value)) {
		cout << "�訡��! ������ �᫮ ��� �業��: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	if (Validation(NewBook) == 0) {
		saveBookToFile("books.txt", NewBook);
		AllBooks[bookCount++] = NewBook;
		cout << "����� ���������" << endl;
	}
	else {
		cout << "�訡�� ������樨\n";
		input_book();

	}
}


void return_books(){
	if (bookCount == 0)
	{
		cout << "����� ����������, ������� ��� �� ����.\n";
		return;
	}
	else {
		for (int i = 0; i < bookCount; i++) {
			cout << "�����:" << i+1 << endl;
			cout << "��������:"<< AllBooks[i].name << endl;
			cout << "����:" << AllBooks[i].author << endl;
			cout << "��� ���᪠:" << AllBooks[i].year << endl;
			cout << "�業��:" << AllBooks[i].value <<"\n"<< endl;
		}

	}
};

void Menu()
{
	cout << "\n=== ���� ===\n";
	cout << "1. �������� �����\n";
	cout << "2. �������� �� �����\n";
	cout << "3. �������� ����⨪� �� ������\n";
	cout << "4. ��室\n";
	cout << "�롥�� �㭪�: ";
}

void stat_books() {
	if (bookCount == 0) {
		cout << "��� ���� ��� ����⨪�." << endl;
		return;
	}

	float max_score = AllBooks[0].value;
	float sum_score = 0;
	char max_name[100];
	strcpy(max_name, AllBooks[0].name);

	for (int i = 0; i < bookCount; i++) {
		if (AllBooks[i].value > max_score) {
			max_score = AllBooks[i].value;
			strcpy(max_name, AllBooks[i].name);
		}
		sum_score += AllBooks[i].value;
	}
	cout << "������⢮ ����: " << bookCount << endl;
	cout << "����� �業��: " << max_name << " ---> " << max_score << endl;
	cout << "�।��� �業��: " <<  (sum_score / bookCount) << endl;
}


int main() {
	cout << "==�४�� ����==" << endl;
	loadBooks("books.txt");

	int choice;

	do
	{
		Menu();
		cin >> choice;

		switch (choice)
		{
			case 1:
				input_book();
				break;
			case 2:
				return_books();
				break;
			case 3:
				stat_books();
				break;
			case 4:
				cout << "��室 �� �ணࠬ��.\n\n";
				break;
			default:
				cout << "�訡�� �����\n\n";
				cin.clear();
				cin.ignore(10000, '\n');
		}

	} while (choice != 4);

	return 0;
}