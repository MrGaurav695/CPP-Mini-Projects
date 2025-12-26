#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Bank {
private:
    int accNo;
    string name, fname, cnic, phone, email;
    double balance;

public:
    void createAccount();
    void loginMenu(int searchAcc);
    void deposit(int searchAcc);
    void withdraw(int searchAcc);
    void checkInfo(int searchAcc);
};

int generateAccountNo() {
    srand(time(0));
    return 100000 + rand() % 900000;
}

// ================= MAIN =================
int main() {
    Bank bank;
    char choice;

    while (true) {
        cout << "\n====== Bahram's Bank ======\n";
        cout << "1. Login Account\n";
        cout << "2. Create Account\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == '1') {
            int acc;
            cout << "Enter Account Number: ";
            cin >> acc;
            bank.loginMenu(acc);
        }
        else if (choice == '2') {
            bank.createAccount();
        }
        else if (choice == '0') {
            cout << "Thank you for using Bahram's Bank.\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}

// ============ CREATE ACCOUNT ============
void Bank::createAccount() {
    accNo = generateAccountNo();

    cout << "Enter Name        : ";
    cin >> name;
    cout << "Enter Father Name : ";
    cin >> fname;
    cout << "Enter CNIC        : ";
    cin >> cnic;
    cout << "Enter Phone       : ";
    cin >> phone;
    cout << "Enter Email       : ";
    cin >> email;
    cout << "Enter Initial Amount: ";
    cin >> balance;

    ofstream file("data.txt", ios::app);
    if (!file) {
        cout << "File error!\n";
        return;
    }

    file << accNo << " " << name << " " << fname << " "
         << cnic << " " << phone << " "
         << email << " " << balance << "\n";

    file.close();

    cout << "\nAccount created successfully!\n";
    cout << "Your Account Number: " << accNo << "\n";
}

// ============ LOGIN MENU ============
void Bank::loginMenu(int searchAcc) {
    char choice;
    while (true) {
        cout << "\n--- Account Menu ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Info\n";
        cout << "0. Logout\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == '1') deposit(searchAcc);
        else if (choice == '2') withdraw(searchAcc);
        else if (choice == '3') checkInfo(searchAcc);
        else if (choice == '0') break;
        else cout << "Invalid option!\n";
    }
}

// ============ DEPOSIT ============
void Bank::deposit(int searchAcc) {
    double amt;
    cout << "Enter amount to deposit: ";
    cin >> amt;

    if (amt <= 0) {
        cout << "Invalid amount!\n";
        return;
    }

    ifstream in("data.txt");
    ofstream out("temp.txt");

    bool found = false;

    while (in >> accNo >> name >> fname >> cnic >> phone >> email >> balance) {
        if (accNo == searchAcc) {
            balance += amt;
            found = true;
            cout << "Updated Balance: " << balance << "\n";
        }
        out << accNo << " " << name << " " << fname << " "
            << cnic << " " << phone << " "
            << email << " " << balance << "\n";
    }

    in.close();
    out.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (!found) cout << "Account not found!\n";
}

// ============ WITHDRAW ============
void Bank::withdraw(int searchAcc) {
    double amt;
    cout << "Enter amount to withdraw: ";
    cin >> amt;

    if (amt <= 0) {
        cout << "Invalid amount!\n";
        return;
    }

    ifstream in("data.txt");
    ofstream out("temp.txt");

    bool found = false;

    while (in >> accNo >> name >> fname >> cnic >> phone >> email >> balance) {
        if (accNo == searchAcc) {
            found = true;
            if (amt > balance) {
                cout << "Insufficient balance!\n";
            } else {
                balance -= amt;
                cout << "Updated Balance: " << balance << "\n";
            }
        }
        out << accNo << " " << name << " " << fname << " "
            << cnic << " " << phone << " "
            << email << " " << balance << "\n";
    }

    in.close();
    out.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (!found) cout << "Account not found!\n";
}

// ============ CHECK INFO ============
void Bank::checkInfo(int searchAcc) {
    ifstream file("data.txt");
    bool found = false;

    while (file >> accNo >> name >> fname >> cnic >> phone >> email >> balance) {
        if (accNo == searchAcc) {
            cout << "\n--- Account Details ---\n";
            cout << "Account No : " << accNo << "\n";
            cout << "Name       : " << name << "\n";
            cout << "Father     : " << fname << "\n";
            cout << "CNIC       : " << cnic << "\n";
            cout << "Phone      : " << phone << "\n";
            cout << "Email      : " << email << "\n";
            cout << "Balance    : " << balance << "\n";
            found = true;
            break;
        }
    }

    if (!found) cout << "Account not found!\n";
    file.close();
}
