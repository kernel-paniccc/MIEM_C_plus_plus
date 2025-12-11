#include "Book.h"

#include <iostream>

using namespace std;

Book::Book(const string& title,
           const string& author,
           int year,
           const string& isbn)
    : title(title),
      author(author),
      year(year),
      isbn(isbn),
      isAvailable(true),
      borrowedBy() {
  const int currentYear = 2025;
  if (year < 1450 || year > currentYear) {
    throw invalid_argument("Некорректный год издания" + title);
  }
}

const string& Book::getTitle() const 
{ return title; }

const string& Book::getAuthor() const
{ return author; }

int Book::getYear() const 
{ return year; }

const string& Book::getIsbn() const 
{ return isbn; }

bool Book::getIsAvailable() const 
{ return isAvailable; }

const string& Book::getBorrowedBy() const 
{ return borrowedBy; }

void Book::borrowBook(const string& userName) {
  if (!isAvailable) {
    throw invalid_argument("Книга " + title + " не доступна");
  }
  isAvailable = false;
  borrowedBy = userName;
}

void Book::returnBook() {
  if (isAvailable) {
    throw invalid_argument("Книга " + title + "никому не выдана");
  }
  borrowedBy.clear();
  isAvailable = true;
}

void Book::displayInfo() const {
  cout << "BOOK" << endl;
  cout << "Title: " << title << endl;
  cout << "Author: " << author << endl;
  cout << "Year: " << year << endl;
  cout << "ISBN: " << isbn << endl;
  cout << "Avaible: " << (isAvailable ? "1" : "0") << endl;
  cout << "BorrowedBy" << (isAvailable ? "" : borrowedBy) << endl;
}