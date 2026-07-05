#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Product {
private:
    string productID;
    string name;
    int stockQuantity;
    double price;
    int unitsSold;

public:
    Product(string id, string n, int stock, double p)
        : productID(id), name(n), stockQuantity(stock), price(p), unitsSold(0) {}

    string getID() const { return productID; }
    string getName() const { return name; }
    int getStock() const { return stockQuantity; }
    double getPrice() const { return price; }
    int getUnitsSold() const { return unitsSold; }

    void updateStock(int addedUnits) {
        if(addedUnits > 0) stockQuantity += addedUnits;
    }

    bool sell(int quantity) {
        if (quantity <= 0) return false;
        if (quantity > stockQuantity) {
            cout << "Sale Error: Insufficient stock for " << name << ". Available: " << stockQuantity << "\n";
            return false;
        }
        stockQuantity -= quantity;
        unitsSold += quantity;
        return true;
    }
};

class InventorySystem {
private:
    vector<Product> inventory;
    double totalHistoricalSales;

public:
    InventorySystem() : totalHistoricalSales(0.0) {}

    void addProduct(const Product& p) {
        inventory.push_back(p);
        cout << "Inventory Confirmed: Product \"" << p.getName() << "\" listed successfully.\n";
    }

    void restockProduct(string id, int qty) {
        for (auto& p : inventory) {
            if (p.getID() == id) {
                p.updateStock(qty);
                cout << "Restocked " << qty << " units for " << p.getName() << ". Total Stock: " << p.getStock() << "\n";
                return;
            }
        }
        cout << "Inventory Alert: Product ID not registered.\n";
    }

    void generateBill(string id, int purchaseQty) {
        for (auto& p : inventory) {
            if (p.getID() == id) {
                if (p.sell(purchaseQty)) {
                    double billCost = p.getPrice() * purchaseQty;
                    totalHistoricalSales += billCost;

                    // Printing Invoice UI Format
                    cout << "\n\n";
                    cout << "            RETAIL CUSTOMER BILL         \n";
                    cout << "\n";
                    cout << "Item:            " << p.getName() << "\n";
                    cout << "Quantity:        " << purchaseQty << "\n";
                    cout << "Unit Price:      $" << fixed << setprecision(2) << p.getPrice() << "\n";
                    cout << "\n";
                    cout << "TOTAL CHARGE:    $" << billCost << "\n";
                    cout << "\n";
                }
                return;
            }
        }
        cout << "Billing Failure: Item not in inventory.\n";
    }

    void displayTotalSales() const {
        cout << "\n>>> Cumulative Gross Register Sales: $" << fixed << setprecision(2) << totalHistoricalSales << " <<<\n";
    }

    void identifyBestSeller() const {
        if (inventory.empty()) {
            cout << "No data logged in inventory.\n";
            return;
        }

        int topIdx = 0;
        bool salesRecorded = false;

        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i].getUnitsSold() > 0) salesRecorded = true;
            if (inventory[i].getUnitsSold() > inventory[topIdx].getUnitsSold()) {
                topIdx = i;
            }
        }

        cout << "\n\n";
        cout << "        TOP PERFORMING BEST SELLER       \n";
        cout << "\n";
        if (!salesRecorded) {
            cout << "No items have been sold during this cycle yet.\n";
        } else {
            cout << "Product ID:     " << inventory[topIdx].getID() << "\n";
            cout << "Product Name:   " << inventory[topIdx].getName() << "\n";
            cout << "Units Dispatched: " << inventory[topIdx].getUnitsSold() << " units\n";
        }
        cout << "\n";
    }
};

int main() {
    InventorySystem storeRegister;

    // Populate Store Inventory
    storeRegister.addProduct(Product("P501", "Premium Crewneck Sweatshirt", 50, 24.99));
    storeRegister.addProduct(Product("P502", "Slim-Fit Denim Jeans", 35, 39.99));
    storeRegister.addProduct(Product("P503", "Classic Leather Jacket", 15, 89.95));

    // Handle Transactions
    cout << "\n--- Processing Order Checkout Invoices ---\n";
    storeRegister.generateBill("P501", 3);
    storeRegister.generateBill("P503", 1);
    storeRegister.generateBill("P502", 40); // Intentional inventory stock crash check
    storeRegister.generateBill("P502", 5);

    // Administrative Operations
    storeRegister.restockProduct("P502", 20);
    storeRegister.displayTotalSales();
    storeRegister.identifyBestSeller();

    return 0;
}
