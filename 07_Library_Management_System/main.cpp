#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    int quantity;
};

vector<Book> books;
const string FILE_NAME = "library_records.txt";

void loadFromFile() {
    books.clear();
    ifstream file(FILE_NAME);

    if (!file.is_open()) return;

    Book b;
    while (file >> b.id) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.quantity;
        books.push_back(b);
    }
    file.close();
}

void saveToFile() {
    ofstream file(FILE_NAME);
    for (const auto& b : books) {
        file << b.id << "\n"
             << b.title << "\n"
             << b.author << "\n"
             << b.quantity << "\n";
    }
    file.close();
}

void addBook() {
    Book b;
    cout << "\nEnter Book ID: ";
    cin >> b.id;
    cin.ignore();

    for (const auto& book : books) {
        if (book.id == b.id) {
            cout << "Book ID already exists.\n";
            return;
        }
    }

    cout << "Enter Title: ";
    getline(cin, b.title);
    cout << "Enter Author: ";
    getline(cin, b.author);
    cout << "Enter Quantity: ";
    cin >> b.quantity;

    books.push_back(b);
    saveToFile();
    cout << "Book added successfully.\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "\nNo books available.\n";
        return;
    }

    cout << "\n"
         << left << setw(10) << "ID"
         << setw(25) << "Title"
         << setw(20) << "Author"
         << setw(10) << "Qty" << "\n";
    cout << string(65, '-') << "\n";

    for (const auto& b : books) {
        cout << left << setw(10) << b.id
             << setw(25) << b.title
             << setw(20) << b.author
             << setw(10) << b.quantity << "\n";
    }
}

void searchBook() {
    int id;
    cout << "\nEnter Book ID to search: ";
    cin >> id;

    for (const auto& b : books) {
        if (b.id == id) {
            cout << "\nBook Found:\n";
            cout << "Title   : " << b.title << "\n";
            cout << "Author  : " << b.author << "\n";
            cout << "Quantity: " << b.quantity << "\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void issueBook() {
    int id;
    cout << "\nEnter Book ID to issue: ";
    cin >> id;

    for (auto& b : books) {
        if (b.id == id) {
            if (b.quantity > 0) {
                b.quantity--;
                saveToFile();
                cout << "Book issued successfully.\n";
            } else {
                cout << "Book out of stock.\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

void returnBook() {
    int id;
    cout << "\nEnter Book ID to return: ";
    cin >> id;

    for (auto& b : books) {
        if (b.id == id) {
            b.quantity++;
            saveToFile();
            cout << "Book returned successfully.\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void deleteBook() {
    int id;
    cout << "\nEnter Book ID to delete: ";
    cin >> id;

    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->id == id) {
            books.erase(it);
            saveToFile();
            cout << "Book deleted successfully.\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void menu() {
    cout << "\n====== Library Management System ======\n";
    cout << "1. Add Book\n";
    cout << "2. Display All Books\n";
    cout << "3. Search Book\n";
    cout << "4. Issue Book\n";
    cout << "5. Return Book\n";
    cout << "6. Delete Book\n";
    cout << "0. Exit\n";
    cout << "Choose: ";
}

int main() {
    loadFromFile();

    int choice;
    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: deleteBook(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
