#include "User.h"

#include <algorithm>
#include <iostream>

using namespace std;

User::User(string name,
           string userId,
           vector<string> borrowedBooks,
           int maxBooksAllowed)
    : name(name),
      userId(userId),
      borrowedBooks(borrowedBooks),
      maxBooksAllowed(maxBooksAllowed) {}

string User::getName() const 
{ return name; }
string User::getUserId() const 
{ return userId; }
vector<std::string> User::getBorrowedBooks() const 
{return borrowedBooks;}


int User::getMaxBooksAllowed() const { return maxBooksAllowed; }

bool User::canBorrowMore() { return (maxBooksAllowed > borrowedBooks.size()); }

void User::addBook(const std::string& isbn) {
  if (!canBorrowMore()) {
    throw runtime_error("User " + name + "can`t get this book");
  }
  borrowedBooks.push_back(isbn);
}

void User::removeBook(const string& isbn) {
  auto it = find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
  if (it != borrowedBooks.end()) {
    borrowedBooks.erase(it);
    return;
  }
  throw runtime_error("User" + name + " not have books " + isbn);
}

void User::displayProfile() const {
  cout << "USER" << endl;
  cout << "Name: " << name << endl;
  cout << "Id: " << userId << endl;
  cout << "All user books:";
  if (borrowedBooks.size() == 0) {
    cout << "Zero books" << std::endl;
  } else {
    for (size_t i = 0; i < borrowedBooks.size(); ++i)
      cout << borrowedBooks[i] << std::endl;
  }
  cout << "Can get: " << maxBooksAllowed << "books" << endl;
}
