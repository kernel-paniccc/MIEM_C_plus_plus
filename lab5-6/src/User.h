#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Описание класс и методов для пользователя
class User {
    private:
        string name;
        string userId;
        vector <string> borrowedBooks;
        int maxBooksAllowed;
    
    public:
        User(string name, string userId, vector <string> borrowedBooks, int maxBooksAllowed = 3);
      

        string getName() const;
        string getUserId() const;
        vector <string> getBorrowedBooks() const;
        int getMaxBooksAllowed() const;
      
        bool canBorrowMore();
        void addBook(const string& isbn);
        void removeBook(const string& isbn);
        void displayProfile() const;


};


#endif //USER_H
