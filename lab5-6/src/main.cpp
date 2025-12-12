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
      cout << "Add you chosen.\n";
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
    cout << "8. Find book by ISBN\n";
    cout << "9. Escape\n";
    int choice = promptInt("Chose one: ");

    try {
      switch (choice) {
        case 1:
          library.displayAllBooks();
          break;
        case 2:
          library.displayAllUsers();
          break;
        case 3: {
          string title = prompt("Book titel: ");
          string author = prompt("Author: ");
          int year = promptInt("Year: ");
          string isbn = prompt("ISBN: ");
          library.addBook(Book(title, author, year, isbn));
          cout << "Book added.\n";
          break;
        }
        case 4: {
          string name = prompt("Name: ");
          string userId = prompt("User_ID: ");
          int maxBooks = promptInt("A lot of books: ");
          library.addUser(User(name, userId, {}, maxBooks));
          cout << "Sucsess sing in.\n";
          break;
        }
        case 5: {
          string userName = prompt("Username: ");
          string isbn = prompt("ISBN: ");
          library.borrowBook(userName, isbn);
          cout << "Book add user " << userName << '\n';
          break;
        }
        case 6: {
          string isbn = prompt("ISBN for return book: ");
          library.returnBook(isbn);
          cout << "\n";
          break;
        }
        case 7:
          library.saveToFile();
          cout << "Save...\n";
          break;
        case 8: {
          string isbn = prompt("ISBN for search: ");
          Book* book = library.findBookByISBN(isbn);
          if (book) {
            book->displayInfo();
          } else {
            cout << "Book not found\n";
          }
          break;
        }
        break;
        case 9: {
          running = false;
          library.saveToFile();
        }
        default:
          cout << "Error option\n";
          break;
      }
    } catch (const exception& e) {
      cout << "Error: " << e.what() << "\n";
    }
  }

  return 0;
}
