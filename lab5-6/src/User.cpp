#include "User.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>

using namespace std;

// задаём неймспейс для удобной валидации userID
namespace {
bool isValidUserId(const string& userId) {
  const string prefix = "USR_";
  if (userId.size() <= prefix.size() || userId.rfind(prefix, 0) != 0) {
    return false;
  }
  return all_of(userId.begin() + static_cast<long>(prefix.size()), userId.end(),
                [](unsigned char ch) { return isdigit(ch); });
}
}

User::User(string name,
           string userId,
           vector<string> borrowedBooks,
           int maxBooksAllowed)
    : name(name),
      userId(userId),
      borrowedBooks(borrowedBooks),
      maxBooksAllowed(maxBooksAllowed) {
  if (!isValidUserId(userId)) {
    throw invalid_argument("Invalid user ID: " + userId);
  }
}
// гетерсы
string User::getName() const 
{ return name; }
string User::getUserId() const 
{ return userId; }
vector<string> User::getBorrowedBooks() const 
{return borrowedBooks;}

// основной функцианал для пользователя
int User::getMaxBooksAllowed() const { return maxBooksAllowed; }

bool User::canBorrowMore() { return (maxBooksAllowed > borrowedBooks.size()); }

void User::addBook(const string& isbn) {
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
// вывод профиля юзера
void User::displayProfile() const {
  cout << "USER" << endl;
  cout << "Name: " << name << endl;
  cout << "Id: " << userId << endl;
  cout << "All user books:";
  if (borrowedBooks.size() == 0) {
    cout << "Zero books" << endl;
  } else {
    for (size_t i = 0; i < borrowedBooks.size(); ++i)
      cout << borrowedBooks[i] << endl;
  }
  cout << "Can get: " << maxBooksAllowed << " books" << endl;
}
