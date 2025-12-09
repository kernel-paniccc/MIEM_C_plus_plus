#ifndef BOOK_H
#define BOOK_H

#include <iostream>

using namespace std;

class Book {
    string titel;
    string autor;
    int year;
    string isbn;
    bool isAvailable;
    string borrowedBy;

    public:
        Book(std::string title, std::string author, int year, std::string isbn, bool isAbaible, std::string borrowedBy);

        string getTitle() const;
        string getAuthor() const;
        int getYear() const;
        string getIsbn() const;
        bool getIsAvaible() const;
        string getBorrowedBy() const;

        void borrowBook(const string& userName);
        void returnBook();
        void displayInfo();

};


#endif //BOOK_H