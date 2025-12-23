#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string phone;
};
vector<Patient> patients;

void loadFromFile() {
    patients.clear();
    ifstream file("patients.txt");
    if (!file) return;

    Patient p;
    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.age >> p.gender >> p.phone;
        patients.push_back(p);
    }
    file.close();
}

void saveToFile() {
    ofstream file("patients.txt");
    for (const auto &p : patients) {
        file << p.id << '\n'
             << p.name << '\n'
             << p.age << '\n'
             << p.gender << '\n'
             << p.phone << '\n';
    }
    file.close();
}

void addPatient() {
    Patient p;
    cout << "\nEnter Patient ID: ";
    cin >> p.id;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, p.name);

    cout << "Enter Age: ";
    cin >> p.age;

    cout << "Enter Gender: ";
    cin >> p.gender;

    cout << "Enter Phone: ";
    cin >> p.phone;

    patients.push_back(p);
    saveToFile();
    cout << "Patient added successfully.\n";
}

void showPatients() {
    if (patients.empty()) {
        cout << "\nNo records found.\n";
        return;
    }
    cout << "\n--- Patient Records ---\n";
    for (const auto &p : patients) {
        cout << "ID: " << p.id
             << " | Name: " << p.name
             << " | Age: " << p.age
             << " | Gender: " << p.gender
             << " | Phone: " << p.phone << endl;
    }
}

void searchPatient() {
    int id;
    cout << "\nEnter Patient ID to search: ";
    cin >> id;
    for (const auto &p : patients) {
        if (p.id == id) {
            cout << "\nRecord Found:\n";
            cout << "ID: " << p.id
                 << "\nName: " << p.name
                 << "\nAge: " << p.age
                 << "\nGender: " << p.gender
                 << "\nPhone: " << p.phone << endl;
            return;
        }
    }
    cout << "Patient not found.\n";
}

void updatePatient() {
    int id;
    cout << "\nEnter Patient ID to update: ";
    cin >> id;
    cin.ignore();
    for (auto &p : patients) {
        if (p.id == id) {
            cout << "Enter New Name: ";
            getline(cin, p.name);

            cout << "Enter New Age: ";
            cin >> p.age;

            cout << "Enter New Gender: ";
            cin >> p.gender;

            cout << "Enter New Phone: ";
            cin >> p.phone;

            saveToFile();
            cout << "Record updated successfully.\n";
            return;
        }
    }
    cout << "Patient not found.\n";
}

void deletePatient() {
    int id;
    cout << "\nEnter Patient ID to delete: ";
    cin >> id;
    for (size_t i = 0; i < patients.size(); i++) {
        if (patients[i].id == id) {
            patients.erase(patients.begin() + i);
            saveToFile();
            cout << "Record deleted successfully.\n";
            return;
        }
    }
    cout << "Patient not found.\n";
}

int main() {
    loadFromFile();
    int choice;
    do {
        cout << "\n====== Hospital Management System ======\n";
        cout << "1. Add Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Update Patient\n";
        cout << "5. Delete Patient\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addPatient(); break;
            case 2: showPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: deletePatient(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    return 0;
}
