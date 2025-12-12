#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
#include "User.h"

using namespace std;
// Описание класс и методов для самой библиотеки
class Library {
    private:
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
