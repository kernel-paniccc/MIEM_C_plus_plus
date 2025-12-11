#include "Book.h"
#include "User.h"
#include <iostream>

int main() {
    Book book("title", "nameBook", 1450, "650-543-12-10-1239");
    User user("test_name", "USR_123", {"650-543-12-10-1239"});

    book.displayInfo();
    user.displayProfile();

    return 0;;

}
