#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    int year;
    string isbn;
    bool isAvailable;
    string borrowedBy;

public:
    Book(const string& title,
         const string& author,
         int year,
         const string& isbn);

    const string& getTitle() const;
    const string& getAuthor() const;
    int getYear() const;
    const string& getIsbn() const;
    bool getIsAvailable() const;
    const string& getBorrowedBy() const;

    void borrowBook(const string& userName);
    void returnBook();
    void displayInfo() const;
};

#endif // BOOK_H
