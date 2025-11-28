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
		cout << "Ошибка записи в файл!" << endl;
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
		cout << "Пустая строка" << endl;
		return 1;
	}
	if (strlen(book.name) >= sizeof(book.name)) {
		cout << "Слишком длинное название" << endl;
		return 1;
	}

	if (strlen(book.author) == 0) {
		cout << "Пустая строка" << endl;
		return 1;
	}
	if (strlen(book.author) >= sizeof(book.author)) {
		cout << "Слишком длинное имя автора!" << endl;
		return 1;
	}

	if (book.year < 0 || book.year > 2025) {
		cout << "Ошибка даты" << endl;
		return 1;
	}

	if (book.value < 0 || book.value > 10) {
		cout << "Ошибка оценки пользователя" << endl;
		return 1;
	}

	return 0;
}


void input_book() {

	if (bookCount >= MAX_BOOKS) {
		cout << "Ошибка ввода." << endl;
		return;
	}

	Book NewBook;

<<<<<<< HEAD
	cout << "������ ��������:\n";
	cin.ignore();
	cin.getline(NewBook.name, 100);
	cout << "������ ����:\n";
	cin.getline(NewBook.author, 50);

	cout << "������ ��� ���᪠:\n";
	while (!(cin >> NewBook.year)) {
		cout << "�訡��! ������ 楫�� �᫮ ��� ����:\n";
=======
	cout << "Введите название: ";
	cin.ignore();
	cin.getline(NewBook.name, 100);
	cout << "Введите автора: ";
	cin.getline(NewBook.author, 50);

	cout << "Введите год выпуска: ";
	while (!(cin >> NewBook.year)) {
		cout << "Ошибка! Введите целое число для года: ";
>>>>>>> f32618659c7c29b1237b57a1fd3c0bc606035f24
		cin.clear();
		cin.ignore(10000, '\n');
	}

<<<<<<< HEAD
	cout << "������ ���� �業��:\n";
	while (!(cin >> NewBook.value)) {
		cout << "�訡��! ������ �᫮ ��� �業��:\n";
=======
	cout << "Введите вашу оценку: ";
	while (!(cin >> NewBook.value)) {
		cout << "Ошибка! Введите число для оценки: ";
>>>>>>> f32618659c7c29b1237b57a1fd3c0bc606035f24
		cin.clear();
		cin.ignore(10000, '\n');
	}

	if (Validation(NewBook) == 0) {
		saveBookToFile("books.txt", NewBook);
		AllBooks[bookCount++] = NewBook;
		cout << "Книга добавлена" << endl;
	}
	else {
<<<<<<< HEAD
=======
		cout << "Ошибка валидации\n";
>>>>>>> f32618659c7c29b1237b57a1fd3c0bc606035f24
		input_book();

	}
}


void return_books() {
	if (bookCount == 0) {
		cout << "Книги отсутствуют, добавьте хотя бы одну.\n";
		return;
	}
<<<<<<< HEAD
	else {
		for (int i = 0; i < bookCount; i++) {
			cout << "�����:" << i + 1 << endl;
			cout << "��������:" << AllBooks[i].name << endl;
			cout << "����:" << AllBooks[i].author << endl;
			cout << "��� ���᪠:" << AllBooks[i].year << endl;
			cout << "�業��:" << AllBooks[i].value << "\n" << endl;
		}
=======
	cout << "\n----------------------------Список книг---------------------------\n";
	cout << left << setw(6)  << "№"
		 << setw(25) << "Название"
		 << setw(20) << "Автор"
		 << setw(10) << "Год"
		 << setw(8)  << "Оценка" << "\n";
	cout << "------------------------------------------------------------------\n";
>>>>>>> f32618659c7c29b1237b57a1fd3c0bc606035f24

	for (int i = 0; i < bookCount; i++) {
		cout << left << setw(6)  << i + 1
			 << setw(25) << AllBooks[i].name
			 << setw(20) << AllBooks[i].author
			 << setw(10) << AllBooks[i].year
			 << setw(8)  << AllBooks[i].value << "\n";
	}
}

void Menu()
{
	cout << "\n=== МЕНЮ ===\n";
	cout << "1. Добавить книгу\n";
	cout << "2. Показать все книги\n";
	cout << "3. Показать статистику по книгам\n";
	cout << "4. Выход\n";
	cout << "Выберите пункт: ";
}

void stat_books() {
	if (bookCount == 0) {
		cout << "Нет книг для статистики." << endl;
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
	cout << "Количество книг: " << bookCount << endl;
	cout << "Высшая оценка: " << max_name << " ---> " << max_score << endl;
	cout << "Средняя оценка: " <<  (sum_score / bookCount) << endl;
}


int main() {
	cout << "==Трекер книг==" << endl;
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
				cout << "Выход из программы.\n\n";
				break;
			default:
				cout << "Ошибка ввода\n\n";
				cin.clear();
				cin.ignore(10000, '\n');
		}

	} while (choice != 4);

	return 0;
}
