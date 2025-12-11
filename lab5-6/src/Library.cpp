#include "Library.h"
#include "User.h"
#include "Book.h"

#include <algorithm>
#include <fstream>


using namespace std;

Library::Library(const string& filePath) : dataFile(filePath) {}

void Library::addBook(const Book& book) { books.push_back(book); }

void Library::addUser(const User& user) { users.push_back(user); }

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

  for (auto& user : users) {
    try {
      user.removeBook(isbn);
      book->returnBook();
      return;
    }
  }
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

}

void Library::loadFromFile() {
 
}
