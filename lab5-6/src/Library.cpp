#include "Library.h"
#include "User.h"
#include "Book.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>


using namespace std;

namespace {
string trim(const string& value) {
  const auto first = value.find_first_not_of(" \t\r\n");
  if (first == string::npos) {
    return "";
  }
  const auto last = value.find_last_not_of(" \t\r\n");
  return value.substr(first, last - first + 1);
}

bool toBool(const string& value) {
  string lowered = value;
  transform(lowered.begin(), lowered.end(), lowered.begin(),
            [](unsigned char ch) { return static_cast<char>(tolower(ch)); });
  return !(lowered == "no" || lowered == "false" || lowered == "0");
}

string normalizeIsbn(const string& value) {
  string normalized;
  normalized.reserve(value.size());
  for (const unsigned char ch : value) {
    if (isalnum(ch)) {
      normalized.push_back(static_cast<char>(tolower(ch)));
    }
  }
  return normalized;
}
}

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
  const string target = normalizeIsbn(isbn);
  auto it = find_if(books.begin(), books.end(),
                    [&](const Book& b) {
                      return normalizeIsbn(b.getIsbn()) == target;
                    });
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

  for (const auto& book : books) {
    out << "BOOK\n";
    out << "Title: " << book.getTitle() << '\n';
    out << "Author: " << book.getAuthor() << '\n';
    out << "Year: " << book.getYear() << '\n';
    out << "ISBN: " << book.getIsbn() << '\n';
    out << "Available: " << (book.getIsAvailable() ? "yes" : "no") << '\n';
    out << "BorrowedBy: " << book.getBorrowedBy() << "\n\n";
  }

  out << "---USERS---\n\n";
  for (const auto& book : books) {
    if (!book.getIsAvailable() && !book.getBorrowedBy().empty()) {
      out << "Currently borrowed by " << book.getBorrowedBy() << '\n';
    }
  }

  for (const auto& user : users) {
    out << "USER\n";
    out << "Name: " << user.getName() << '\n';
    out << "UserID: " << user.getUserId() << '\n';
    out << "BorrowedBooks: ";
    const auto borrowed = user.getBorrowedBooks();
    for (size_t i = 0; i < borrowed.size(); ++i) {
      if (i) {
        out << ", ";
      }
      out << borrowed[i];
    }
    out << '\n';
    out << "MaxBooks: " << user.getMaxBooksAllowed() << "\n\n";
  }
}

void Library::loadFromFile() {
  ifstream in(dataFile);
  if (!in.is_open()) {
    return;
  }

  books.clear();
  users.clear();

  in >> ws;
  const int firstChar = in.peek();
  if (firstChar == EOF) {
    return;
  }

  if (isdigit(firstChar)) {
    size_t booksCount = 0;
    in >> booksCount;
    string line;
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
      if (!available && !borrowedBy.empty()) {
        book.borrowBook(borrowedBy);
      }
      books.push_back(book);
    }

    size_t usersCount = 0;
    if (!(in >> usersCount)) {
      return;
    }
    getline(in, line); 

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
    return;
  }

  in.clear();
  in.seekg(0);

  string line;
  auto nextNonEmptyLine = [&](string& value) -> bool {
    while (getline(in, value)) {
      if (!value.empty()) {
        return true;
      }
    }
    return false;
  };

  auto readValue = [&](const string& prefix, string& value) -> bool {
    if (!nextNonEmptyLine(line)) {
      return false;
    }
    if (line.rfind(prefix, 0) != 0) {
      return false;
    }
    value = trim(line.substr(prefix.size()));
    return true;
  };

  while (nextNonEmptyLine(line)) {
    if (line == "---USERS---") {
      break;
    }
    if (line != "BOOK") {
      continue;
    }

    string title, author, yearStr, isbn, availableStr, borrowedBy;
    if (!readValue("Title:", title) || !readValue("Author:", author) ||
        !readValue("Year:", yearStr) || !readValue("ISBN:", isbn) ||
        !readValue("Available:", availableStr) ||
        !readValue("BorrowedBy:", borrowedBy)) {
      break;
    }

    Book book(title, author, stoi(yearStr), isbn);
    if (!toBool(availableStr) && !borrowedBy.empty()) {
      book.borrowBook(borrowedBy);
    }
    books.push_back(book);
  }

  while (nextNonEmptyLine(line)) {
    if (line != "USER") {
      continue;
    }

    string name, userId, borrowedStr, maxBooksStr;
    if (!readValue("Name:", name) || !readValue("UserID:", userId) ||
        !readValue("BorrowedBooks:", borrowedStr) ||
        !readValue("MaxBooks:", maxBooksStr)) {
      break;
    }

    vector<string> borrowedBooks;
    istringstream borrowedStream(borrowedStr);
    string isbn;
    while (getline(borrowedStream, isbn, ',')) {
      isbn = trim(isbn);
      if (!isbn.empty()) {
        borrowedBooks.push_back(isbn);
      }
    }

    users.emplace_back(name, userId, borrowedBooks, stoi(maxBooksStr));
  }
}
