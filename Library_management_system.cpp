#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits> // For numeric_limits

using namespace std;

// --- Data Structures ---

struct Book {
    string title;
    string author;
    string isbn;
    bool isAvailable;
    int borrowerId; // ID of the person who borrowed it (if any)
};

struct Borrower {
    string name;
    int id;
};

// --- Global "Database" (Vectors) ---
vector<Book> library;
vector<Borrower> borrowers;

// --- Helper Functions ---

// Function to find a book index by ISBN
int findBookIndex(string isbn) {
    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].isbn == isbn) {
            return i;
        }
    }
    return -1;
}

// Function to find a borrower index by ID
int findBorrowerIndex(int id) {
    for (size_t i = 0; i < borrowers.size(); i++) {
        if (borrowers[i].id == id) {
            return i;
        }
    }
    return -1;
}

// --- Core Features ---

void addBook() {
    Book newBook;
    cout << "\n--- Add New Book ---\n";
    cout << "Enter ISBN: ";
    cin >> newBook.isbn;
    cin.ignore(); // Clear buffer

    cout << "Enter Title: ";
    getline(cin, newBook.title);

    cout << "Enter Author: ";
    getline(cin, newBook.author);

    newBook.isAvailable = true;
    newBook.borrowerId = -1; // -1 means no one has borrowed it

    library.push_back(newBook);
    cout << "Book added successfully!\n";
}

void searchBook() {
    string query;
    cout << "\n--- Search Books ---\n";
    cout << "Enter Title, Author, or ISBN to search: ";
    cin.ignore();
    getline(cin, query);

    bool found = false;
    cout << "\nSearch Results:\n";
    for (size_t i = 0; i < library.size(); i++) {
        // Simple search checking if the query is in title, author, or ISBN
        // Note: find() returns string::npos if not found
        if (library[i].title.find(query) != string::npos || 
            library[i].author.find(query) != string::npos || 
            library[i].isbn == query) {
            
            cout << "ISBN: " << library[i].isbn << " | Title: " << library[i].title 
                 << " | Author: " << library[i].author;
            if (library[i].isAvailable) cout << " [Available]\n";
            else cout << " [Checked Out]\n";
            found = true;
        }
    }
    
    if (!found) cout << "No books found matching '" << query << "'.\n";
}

void addBorrower() {
    Borrower newUser;
    cout << "\n--- Add Borrower ---\n";
    cout << "Enter Borrower ID (number): ";
    cin >> newUser.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, newUser.name);

    borrowers.push_back(newUser);
    cout << "Borrower added successfully!\n";
}

void checkOutBook() {
    string isbn;
    int userId;

    cout << "\n--- Check Out Book ---\n";
    cout << "Enter Borrower ID: ";
    cin >> userId;

    if (findBorrowerIndex(userId) == -1) {
        cout << "Error: Borrower ID not found.\n";
        return;
    }

    cout << "Enter Book ISBN: ";
    cin >> isbn;

    int bookIdx = findBookIndex(isbn);
    if (bookIdx != -1) {
        if (library[bookIdx].isAvailable) {
            library[bookIdx].isAvailable = false;
            library[bookIdx].borrowerId = userId;
            cout << "Book checked out successfully to User " << userId << ".\n";
        } else {
            cout << "Error: Book is already checked out.\n";
        }
    } else {
        cout << "Error: Book not found.\n";
    }
}

void returnBook() {
    string isbn;
    int daysKept;
    const int CHECKOUT_LIMIT = 14; // Books can be kept for 14 days
    const double FINE_PER_DAY = 1.50; // $1.50 fine per overdue day

    cout << "\n--- Return Book ---\n";
    cout << "Enter Book ISBN: ";
    cin >> isbn;

    int bookIdx = findBookIndex(isbn);
    if (bookIdx != -1) {
        if (!library[bookIdx].isAvailable) {
            // Fine Calculation Logic
            cout << "How many days was the book kept?: ";
            cin >> daysKept;

            if (daysKept > CHECKOUT_LIMIT) {
                int overdueDays = daysKept - CHECKOUT_LIMIT;
                double fine = overdueDays * FINE_PER_DAY;
                cout << "Book is overdue by " << overdueDays << " days.\n";
                cout << "Fine to be paid: $" << fine << "\n";
            } else {
                cout << "Book returned on time. No fine.\n";
            }

            // Reset book status
            library[bookIdx].isAvailable = true;
            library[bookIdx].borrowerId = -1;
            cout << "Book returned successfully.\n";
        } else {
            cout << "Error: This book is not currently checked out.\n";
        }
    } else {
        cout << "Error: Book not found.\n";
    }
}

// --- Main Menu ---

int main() {
    int choice = 0;

    // Pre-loading some dummy data for testing
    Book b1; b1.title = "The Great Gatsby"; b1.author = "F. Scott Fitzgerald"; b1.isbn = "101"; b1.isAvailable = true; library.push_back(b1);
    Book b2; b2.title = "1984"; b2.author = "George Orwell"; b2.isbn = "102"; b2.isAvailable = true; library.push_back(b2);
    Borrower u1; u1.name = "John Smith"; u1.id = 1; borrowers.push_back(u1);

    while (choice != 7) {
        cout << "\n==============================\n";
        cout << "  LIBRARY MANAGEMENT SYSTEM\n";
        cout << "==============================\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Add Borrower\n";
        cout << "4. Check Out Book\n";
        cout << "5. Return Book (Calculate Fine)\n";
        cout << "6. View All Books\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: addBorrower(); break;
            case 4: checkOutBook(); break;
            case 5: returnBook(); break;
            case 6: 
                cout << "\n--- Library Catalog ---\n";
                for (size_t i = 0; i < library.size(); i++) {
                     cout << library[i].isbn << " - " << library[i].title << " (" << library[i].author << ")";
                     if(!library[i].isAvailable) cout << " [OUT]";
                     cout << "\n";
                }
                break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    }
    return 0;
}
