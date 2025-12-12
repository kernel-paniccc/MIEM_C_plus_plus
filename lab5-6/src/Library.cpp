#include "Library.h"
#include "User.h"
#include "Book.h"

#include <algorithm>
#include <fstream>
#include <sstream>


using namespace std;

Library::Library(const string& filePath) : dataFile(filePath) {}

void Library::addBook(const Book& book) { books.push_back(book); }

void Library::addUser(const User& user) {
  auto it = find_if(users.begin(), users.end(),
                    [&](const User& u) { return u.getUserId() == user.getUserId(); });
  if (it != users.end()) {
    throw runtime_error("User ID already exists: " + user.getUserId());
  }
  users.push_back(user);
}

void Library::borrowBook(const string& userName, const string& isbn) {
  Book* book = findBookByISBN(isbn);
  User* user = findUserByName(userName);
  if (!book || !user) {
    return;
  }
  book->borrowBook(userName);
  user->addBook(isbn);
}

void Library::returnBook(const string& isbn) {
  Book* book = findBookByISBN(isbn);
  if (!book) {
    return;
  }

  const string borrowedBy = book->getBorrowedBy();
  User* user = borrowedBy.empty() ? nullptr : findUserByName(borrowedBy);
  if (user) {
    user->removeBook(isbn);
  }
  book->returnBook();
}

Book* Library::findBookByISBN(const string& isbn) {
  auto it = find_if(books.begin(), books.end(),
                    [&](const Book& b) { return b.getIsbn() == isbn; });
  return it == books.end() ? nullptr : &(*it);
}

User* Library::findUserByName(const string& name) {
  auto it = find_if(users.begin(), users.end(),
                    [&](const User& u) { return u.getName() == name; });
  return it == users.end() ? nullptr : &(*it);
}

void Library::displayAllBooks() {
  for (const auto& book : books) {
    book.displayInfo();
  }
}

void Library::displayAllUsers() {
  for (const auto& user : users) {
    user.displayProfile();
  }
}

void Library::saveToFile() {
  ofstream out(dataFile);
  if (!out.is_open()) {
    return;
  }

  out << books.size() << '\n';
  for (const auto& book : books) {
    out << book.getTitle() << '|'
        << book.getAuthor() << '|'
        << book.getYear() << '|'
        << book.getIsbn() << '|'
        << book.getIsAvailable() << '|'
        << book.getBorrowedBy() << '\n';
  }

  out << users.size() << '\n';
  for (const auto& user : users) {
    const auto borrowed = user.getBorrowedBooks();
    out << user.getName() << '|'
        << user.getUserId() << '|'
        << user.getMaxBooksAllowed() << '|';
    for (size_t i = 0; i < borrowed.size(); ++i) {
      if (i) {
        out << ',';
      }
      out << borrowed[i];
    }
    out << '\n';
  }
}

void Library::loadFromFile() {
  ifstream in(dataFile);
  if (!in.is_open()) {
    return;
  }

  books.clear();
  users.clear();

  string line;
  size_t booksCount = 0;
  if (!(in >> booksCount)) {
    return;
  }
  getline(in, line);  // consume endline

  for (size_t i = 0; i < booksCount && getline(in, line); ++i) {
    istringstream ss(line);
    string title, author, yearStr, isbn, availableStr, borrowedBy;
    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, yearStr, '|');
    getline(ss, isbn, '|');
    getline(ss, availableStr, '|');
    getline(ss, borrowedBy, '|');

    Book book(title, author, stoi(yearStr), isbn);
    const bool available = availableStr != "0";
    if (!available) {
      book.borrowBook(borrowedBy);
    }
    books.push_back(book);
  }

  size_t usersCount = 0;
  if (!(in >> usersCount)) {
    return;
  }
  getline(in, line);  // consume endline

  for (size_t i = 0; i < usersCount && getline(in, line); ++i) {
    istringstream ss(line);
    string name, userId, maxBooksStr, borrowedStr;
    getline(ss, name, '|');
    getline(ss, userId, '|');
    getline(ss, maxBooksStr, '|');
    getline(ss, borrowedStr, '|');

    vector<string> borrowedBooks;
    istringstream borrowedStream(borrowedStr);
    string isbn;
    while (getline(borrowedStream, isbn, ',')) {
      if (!isbn.empty()) {
        borrowedBooks.push_back(isbn);
      }
    }

    users.emplace_back(name, userId, borrowedBooks, stoi(maxBooksStr));
  }
}
