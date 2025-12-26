#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ContactManager {
    string phoneNo, name, address, description, search;
    fstream file;

public:
    void addContact();
    void showAll();
    void searchContact();
};

int main() {
    ContactManager obj;
    char choice;

    do {
        cout << "\n====== Contact Management System ======\n";
        cout << "1 --> Add Contact\n";
        cout << "2 --> Show All Contacts\n";
        cout << "3 --> Search Contact\n";
        cout << "0 --> Exit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case '1':
                obj.addContact();
                break;
            case '2':
                obj.showAll();
                break;
            case '3':
                obj.searchContact();
                break;
            case '0':
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid selection!\n";
        }
    } while (choice != '0');
    return 0;
}

void ContactManager::addContact() {
    cout << "\nEnter Phone Number: ";
    getline(cin, phoneNo);

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Description: ";
    getline(cin, description);

    file.open("data.csv", ios::out | ios::app);
    file << phoneNo << "," << name << "," << address << "," << description << "\n";
    file.close();

    cout << "\nContact saved successfully!\n";
}

void ContactManager::showAll() {
    file.open("data.csv", ios::in);

    if (!file) {
        cout << "\nNo contacts found.\n";
        return;
    }

    cout << "\n----- All Contacts -----\n";

    while (getline(file, phoneNo, ',') &&
           getline(file, name, ',') &&
           getline(file, address, ',') &&
           getline(file, description)) {

        cout << "Phone Number : " << phoneNo << endl;
        cout << "Name         : " << name << endl;
        cout << "Address      : " << address << endl;
        cout << "Description  : " << description << endl;
        cout << "-------------------------\n";
    }
    file.close();
}

void ContactManager::searchContact() {
    cout << "\nEnter Phone Number to Search: ";
    getline(cin, search);

    file.open("data.csv", ios::in);

    if (!file) {
        cout << "\nNo contacts found.\n";
        return;
    }

    bool found = false;

    while (getline(file, phoneNo, ',') &&
           getline(file, name, ',') &&
           getline(file, address, ',') &&
           getline(file, description)) {

        if (phoneNo == search) {
            cout << "\nContact Found:\n";
            cout << "Phone Number : " << phoneNo << endl;
            cout << "Name         : " << name << endl;
            cout << "Address      : " << address << endl;
            cout << "Description  : " << description << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nContact not found.\n";
    }

    file.close();
}
