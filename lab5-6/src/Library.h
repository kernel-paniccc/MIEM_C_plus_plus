#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <iostream>

#include "Book.h"
#include "User.h"

using namespace std;

class Library {
    vector<Book> books;
    vector<User> users;
    string dataFile;

public:
    explicit Library(const string& filePath);

    void addBook(const Book& book);
    void addUser(const User& user);
    void borrowBook(const string& userName, const string& isbn);
    void returnBook(const string& isbn);
    Book* findBookByISBN(const string& isbn);
    User* findUserByName(const string& name);
    void displayAllBooks();
    void displayAllUsers();
    void saveToFile();
    void loadFromFile();
};

#endif // LIBRARY_H
