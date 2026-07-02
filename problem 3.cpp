#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    double price;
    bool isAvailable;

public:
    Book(string i, string t, string a, float p)
        : isbn(i), title(t), author(a), price(p), isAvailable(true) {}

    string getISBN() const { return isbn; }
    string getTitle() const { return title; }
    float getPrice() const { return price; }
    bool checkAvailability() const { return isAvailable; }

    void borrowBook() { isAvailable = false; }
    void returnBook() { isAvailable = true; }

    void displayBookDetails() const {
        cout << left << setw(12) << isbn
             << setw(25) << title
             << setw(20) << author
             << "$" << fixed << setprecision(2) << setw(10) << price
             << (isAvailable ? "Available" : "Borrowed/Unavailable") << "\n";
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(const Book& newBook) {
        books.push_back(newBook);
        cout << "Book \"" << newBook.getTitle() << "\" added to library database.\n";
    }

    void borrowBook(string identifier) {
        for (auto& b : books) {
            if (b.getISBN() == identifier || b.getTitle() == identifier) {
                if (b.checkAvailability()) {
                    b.borrowBook();
                    cout << "Success: You have borrowed \"" << b.getTitle() << "\".\n";
                } else {
                    cout << "Error: \"" << b.getTitle() << "\" is currently checked out.\n";
                }
                return;
            }
        }
        cout << "Error: Book not found with ISBN/Title matching: " << identifier << "\n";
    }

    void returnBook(string identifier) {
        for (auto& b : books) {
            if (b.getISBN() == identifier || b.getTitle() == identifier) {
                if (!b.checkAvailability()) {
                    b.returnBook();
                    cout << "Success: \"" << b.getTitle() << "\" has been returned safely.\n";
                } else {
                    cout << "System Alert: \"" << b.getTitle() << "\" was not marked as borrowed.\n";
                }
                return;
            }
        }
        cout << "Error: Book not found with ISBN/Title matching: " << identifier << "\n";
    }

    void searchBook(string query) const {
        cout << "\n--- Search Results for: \"" << query << "\" ---\n";
        bool matchFound = false;
        for (const auto& b : books) {
            if (b.getISBN() == query || b.getTitle() == query) {
                b.displayBookDetails();
                matchFound = true;
            }
        }
        if (!matchFound) cout << "No matching records found.\n";
    }

    void displayUnavailableBooks() const {
        cout << "\n--- Checked Out / Unavailable Books ---\n";
        bool hasUnavailable = false;
        for (const auto& b : books) {
            if (!b.checkAvailability()) {
                b.displayBookDetails();
                hasUnavailable = true;
            }
        }
        if (!hasUnavailable) cout << "All clear! Every book is currently in the library stacks.\n";
    }

    void calculateTotalValue() const {
        double totalSum = 0;
        for (const auto& b : books) {
            totalSum += b.getPrice();
        }
        cout << "\n\n";
        cout << " Total Assets Library Value: $" << fixed << setprecision(2) << totalSum << "\n";
        cout << "\n";
    }
};

int main() {
    Library cityLibrary;

    // Seeding books
    cityLibrary.addBook(Book("9780131103", "The C Programming Language", "Kernighan & Ritchie", 45.50));
    cityLibrary.addBook(Book("9780136083", "Introduction to Algorithms", "Cormen et al.", 95.00));
    cityLibrary.addBook(Book("9780596009", "Head First Design Patterns", "Freeman", 52.25));
    cityLibrary.addBook(Book("9780132350", "Clean Code", "Robert C. Martin", 42.00));

    // Operations
    cout << "\n--- Transaction Processing ---\n";
    cityLibrary.borrowBook("9780132350"); // Borrow via ISBN
    cityLibrary.borrowBook("Introduction to Algorithms"); // Borrow via Title
    cityLibrary.borrowBook("Clean Code"); // Attempt duplicate borrow

    cityLibrary.displayUnavailableBooks();

    cityLibrary.returnBook("9780132350"); // Return

    cityLibrary.searchBook("The C Programming Language");
    cityLibrary.calculateTotalValue();

    return 0;
}
