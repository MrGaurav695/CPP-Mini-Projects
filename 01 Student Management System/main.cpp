#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Student {
private:
    int rollNo;
    string name;
    float marks;

public:
    Student(int r, string n, float m) {
        rollNo = r;
        name = n;
        marks = m;
    }

    int getRollNo() const {
        return rollNo;
    }

    void display() const {
        cout << "Roll No: " << rollNo
             << " | Name: " << name
             << " | Marks: " << marks << endl;
    }
};

class StudentManager {
private:
    vector<Student> students;

public:
    void addStudent() {
        int roll;
        string name;
        float marks;

        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Marks: ";
        cin >> marks;

        students.emplace_back(roll, name, marks);
        cout << "Student added successfully.\n";
    }

    void viewStudents() const {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }

        for (const auto& student : students) {
            student.display();
        }
    }

    void removeStudent() {
        int roll;
        cout << "Enter Roll Number to remove: ";
        cin >> roll;

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getRollNo() == roll) {
                students.erase(it);
                cout << "Student removed successfully.\n";
                return;
            }
        }

        cout << "Student not found.\n";
    }
};

int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Remove Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.viewStudents();
                break;
            case 3:
                manager.removeStudent();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
