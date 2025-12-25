#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Train {
public:
    int trainNo;
    string name;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;

    void input() {
        cout << "Enter Train No: ";
        cin >> trainNo;
        cin.ignore();
        cout << "Enter Train Name: ";
        getline(cin, name);
        cout << "Enter Source: ";
        getline(cin, source);
        cout << "Enter Destination: ";
        getline(cin, destination);
        cout << "Enter Total Seats: ";
        cin >> totalSeats;
        availableSeats = totalSeats;
    }

    void display() const {
        cout << trainNo << " | " << name << " | "
             << source << " -> " << destination
             << " | Seats Available: " << availableSeats << endl;
    }
};

class Booking {
public:
    int ticketId;
    int trainNo;
    string passengerName;
    int age;

    void display() const {
        cout << "Ticket ID: " << ticketId
             << " | Train No: " << trainNo
             << " | Name: " << passengerName
             << " | Age: " << age << endl;
    }
};

vector<Train> trains;
vector<Booking> bookings;

/* ---------- FILE HANDLING ---------- */

void saveTrains() {
    ofstream out("trains.dat", ios::binary);
    for (auto &t : trains)
        out.write((char*)&t, sizeof(t));
    out.close();
}

void loadTrains() {
    ifstream in("trains.dat", ios::binary);
    Train t;
    trains.clear();
    while (in.read((char*)&t, sizeof(t)))
        trains.push_back(t);
    in.close();
}

void saveBookings() {
    ofstream out("bookings.dat", ios::binary);
    for (auto &b : bookings)
        out.write((char*)&b, sizeof(b));
    out.close();
}

void loadBookings() {
    ifstream in("bookings.dat", ios::binary);
    Booking b;
    bookings.clear();
    while (in.read((char*)&b, sizeof(b)))
        bookings.push_back(b);
    in.close();
}

/* ---------- CORE FUNCTIONS ---------- */

void addTrain() {
    Train t;
    t.input();
    trains.push_back(t);
    saveTrains();
    cout << "Train added successfully!\n";
}

void viewTrains() {
    loadTrains();
    if (trains.empty()) {
        cout << "No trains available.\n";
        return;
    }
    for (const auto &t : trains)
        t.display();
}

void bookTicket() {
    loadTrains();
    loadBookings();

    int trainNo;
    cout << "Enter Train No: ";
    cin >> trainNo;

    for (auto &t : trains) {
        if (t.trainNo == trainNo && t.availableSeats > 0) {
            Booking b;
            b.ticketId = bookings.size() + 1001;
            b.trainNo = trainNo;
            cin.ignore();
            cout << "Enter Passenger Name: ";
            getline(cin, b.passengerName);
            cout << "Enter Age: ";
            cin >> b.age;

            t.availableSeats--;
            bookings.push_back(b);

            saveTrains();
            saveBookings();

            cout << "Ticket booked successfully!\n";
            cout << "Your Ticket ID is: " << b.ticketId << endl;
            return;
        }
    }
    cout << "Train not found or no seats available.\n";
}

void cancelTicket() {
    loadBookings();
    loadTrains();

    int ticketId;
    cout << "Enter Ticket ID to cancel: ";
    cin >> ticketId;

    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].ticketId == ticketId) {
            int trainNo = bookings[i].trainNo;

            for (auto &t : trains) {
                if (t.trainNo == trainNo)
                    t.availableSeats++;
            }

            bookings.erase(bookings.begin() + i);
            saveBookings();
            saveTrains();

            cout << "Ticket cancelled successfully!\n";
            return;
        }
    }
    cout << "Ticket not found.\n";
}

void viewBookings() {
    loadBookings();
    if (bookings.empty()) {
        cout << "No bookings found.\n";
        return;
    }
    for (const auto &b : bookings)
        b.display();
}

/* ---------- MAIN MENU ---------- */

int main() {
    int choice;

    do {
        cout << "\n--- Railway Reservation System ---\n";
        cout << "1. Add Train\n";
        cout << "2. View Trains\n";
        cout << "3. Book Ticket\n";
        cout << "4. Cancel Ticket\n";
        cout << "5. View Bookings\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addTrain(); break;
        case 2: viewTrains(); break;
        case 3: bookTicket(); break;
        case 4: cancelTicket(); break;
        case 5: viewBookings(); break;
        case 6: cout << "Thank you for using the system.\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}


