#include "Book.h"

#include <iostream>
#include <stdexcept>

namespace {
constexpr int kMinYear = 1450;
constexpr int kMaxYear = 2025;
}

Book::Book(const std::string& title,
           const std::string& author,
           int year,
           const std::string& isbn)
    : title(title),
      author(author),
      year(year),
      isbn(isbn),
      isAvailable(true),
      borrowedBy() {
    if (title.empty() || author.empty() || isbn.empty()) {
        throw std::invalid_argument("Title, author and ISBN must not be empty.");
    }
    if (year < kMinYear || year > kMaxYear) {
        throw std::invalid_argument("Year must be between 1450 and 2025.");
    }
}

const std::string& Book::getTitle() const {
    return title;
}

const std::string& Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

const std::string& Book::getIsbn() const {
    return isbn;
}

bool Book::getIsAvailable() const {
    return isAvailable;
}

const std::string& Book::getBorrowedBy() const {
    return borrowedBy;
}

void Book::borrowBook(const std::string& userName) {
    if (userName.empty()) {
        throw std::invalid_argument("User name cannot be empty.");
    }
    if (!isAvailable) {
        throw std::runtime_error("Book is already borrowed.");
    }
    isAvailable = false;
    borrowedBy = userName;
}

void Book::returnBook() {
    if (isAvailable) {
        throw std::runtime_error("Book is not borrowed.");
    }
    isAvailable = true;
    borrowedBy.clear();
}

void Book::displayInfo() const {
    std::cout << "Title: " << title << '\n'
              << "Author: " << author << '\n'
              << "Year: " << year << '\n'
              << "ISBN: " << isbn << '\n'
              << "Available: " << (isAvailable ? "yes" : "no") << '\n'
              << "Borrowed by: " << (borrowedBy.empty() ? "-" : borrowedBy) << '\n'
              << "---------------------------\n";
}
