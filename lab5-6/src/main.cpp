#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
#include "Library.h"
#include "User.h"

using namespace std;

namespace {
string prompt(const string& text) {
  cout << text;
  string value;
  getline(cin, value);
  return value;
}

int promptInt(const string& text) {
  while (true) {
    cout << text;
    string line;
    getline(cin, line);
    try {
      return stoi(line);
    } catch (...) {
      cout << "Введите число.\n";
    }
  }
}
}  // namespace

int main() {
  Library library("data/library_data.txt");
  library.loadFromFile();

  bool running = true;
  while (running) {
    cout << "\n=== Library ===\n";
    cout << "1. List books\n";
    cout << "2. List users\n";
    cout << "3. Add books\n";
    cout << "4. Register\n";
    cout << "5. Give books for user\n";
    cout << "6. Get books from library\n";
    cout << "7. Save datafile\n";
    cout << "8. Escape\n";
    cout << "Chose one: ";

    string choice;
    getline(cin, choice);

    try {
      if (choice == "1") {
        library.displayAllBooks();
      } else if (choice == "2") {
        library.displayAllUsers();
      } else if (choice == "3") {
        string title = prompt("Book titel: ");
        string author = prompt("Author: ");
        int year = promptInt("Year: ");
        string isbn = prompt("ISBN: ");
        library.addBook(Book(title, author, year, isbn));
        cout << "Book added.\n";
      } else if (choice == "4") {
        string name = prompt("Name: ");
        string userId = prompt("User_ID: ");
        int maxBooks = promptInt("A lot of books: ");
        library.addUser(User(name, userId, {}, maxBooks));
        cout << "Sucsess sing in.\n";
      } else if (choice == "5") {
        string name = prompt("Username: ");
        string isbn = prompt("ISBN: ");
        library.borrowBook(name, isbn);
        cout << "Book add user" << name << '\n';
      } else if (choice == "6") {
        string isbn = prompt("ISBN for return book: ");
        library.returnBook(isbn);
        cout << "\n";
      } else if (choice == "7") {
        library.saveToFile();
        cout << "Save...\n";
      } else if (choice == "8") {
        running = false;
        library.saveToFile();
      } else {
        cout << "Error option\n";
      }
    } catch (const exception& e) {
      cout << "Error: " << e.what() << "\n";
    }
  }

  return 0;
}
