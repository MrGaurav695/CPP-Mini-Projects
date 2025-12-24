#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
};

struct CartItem {
    string name;
    double price;
    int quantity;
};

vector<Product> products = {
    {"Apple", 2.99, 20},
    {"Orange", 3.99, 15},
    {"Banana", 1.99, 25},
    {"Grapes", 5.99, 10},
    {"Milk", 2.49, 30},
    {"Eggs", 1.99, 40},
    {"Bread", 3.49, 25}
};

vector<CartItem> cart;

double getTotal() {
    double total = 0;
    for (const auto &item : cart) {
        total += item.price * item.quantity;
    }
    return total;
}

void displayProducts() {
    cout << "\nAvailable Products:\n";
    for (int i = 0; i < products.size(); i++) {
        cout << i + 1 << ". " << products[i].name
             << " - $" << products[i].price
             << " (" << products[i].quantity << " in stock)\n";
    }
}

void addToCart(int index, int quantity) {
    if (index < 0 || index >= products.size()) {
        cout << "Invalid product index.\n";
        return;
    }
    if (quantity > products[index].quantity) {
        cout << "Not enough stock.\n";
        return;
    }

    cart.push_back({products[index].name, products[index].price, quantity});
    products[index].quantity -= quantity;
    cout << "Added to cart successfully.\n";
}

void displayCart() {
    if (cart.empty()) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "\nYour Cart:\n";
    for (int i = 0; i < cart.size(); i++) {
        cout << i + 1 << ". " << cart[i].name
             << " - $" << cart[i].price
             << " x " << cart[i].quantity << endl;
    }
    cout << "Total: $" << getTotal() << endl;
}

void checkout() {
    if (cart.empty()) {
        cout << "Your cart is empty.\n";
        return;
    }

    displayCart();
    cout << "\nThank you for shopping with us!\n";
    cart.clear();
}

int main() {
    int choice;

    while (true) {
        cout << "\n1. Display Products\n";
        cout << "2. Add to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayProducts();
                break;
            case 2: {
                int index, quantity;
                cout << "Enter product number: ";
                cin >> index;
                cout << "Enter quantity: ";
                cin >> quantity;
                addToCart(index - 1, quantity);
                break;
            }
            case 3:
                displayCart();
                break;
            case 4:
                checkout();
                break;
            case 5:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
