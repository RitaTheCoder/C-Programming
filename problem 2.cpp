#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Account {
private:
    string accountNumber;
    string customerName;
    float balance;
    vector<string> transactionHistory;

public:
    Account(string accNum, string name, float initialDeposit) {
        accountNumber = accNum;
        customerName = name;
        balance = initialDeposit;
        addLog("Account opened with initialization fund: $" + to_string(initialDeposit));
    }

    string getAccNum() const { return accountNumber; }
    string getName() const { return customerName; }
    float getBalance() const { return balance; }

    void addLog(const string& note) {
        transactionHistory.push_back(note);
    }

    void deposit(float amount) {
        if (amount > 0) {
            balance += amount;
            addLog("Deposited: $" + to_string(amount) + " | Current Balance: $" + to_string(balance));
            cout << "Successfully deposited $" << amount << " into Account " << accountNumber << "\n";
        }
    }

    bool withdraw(float amount) {
        if (amount <= 0) return false;
        if (amount > balance) {
            cout << "Transaction Declined: Insufficient balance in Account " << accountNumber << "\n";
            return false;
        }
        balance -= amount;
        addLog("Withdrew: $" + to_string(amount) + " | Current Balance: $" + to_string(balance));
        cout << "Successfully withdrew $" << amount << " from Account " << accountNumber << "\n";
        return true;
    }

    void displayHistory() const {
        cout << "\n--- Transaction History for " << customerName << " (" << accountNumber << ") ---\n";
        for (const auto& log : transactionHistory) {
            cout << "  " << log << "\n";
        }
        cout << "\n";
    }
};

class Bank {
private:
    vector<Account> accounts;

    Account* findAccount(const string& accNum) {
        for (auto& acc : accounts) {
            if (acc.getAccNum() == accNum) return &acc;
        }
        return nullptr;
    }

public:
    void openAccount(string accNum, string name, float initialDeposit) {
        if (findAccount(accNum) != nullptr) {
            cout << "Error: Account number " << accNum << " already exists.\n";
            return;
        }
        accounts.push_back(Account(accNum, name, initialDeposit));
        cout << "Account registered successfully for " << name << ".\n";
    }

    void depositTo(string accNum, float amount) {
        Account* acc = findAccount(accNum);
        if (acc) acc->deposit(amount);
        else cout << "Account error: Not found.\n";
    }

    void withdrawFrom(string accNum, float amount) {
        Account* acc = findAccount(accNum);
        if (acc) acc->withdraw(amount);
        else cout << "Account error: Not found.\n";
    }

    void transferMoney(string srcAccNum, string destAccNum, float amount) {
        Account* source = findAccount(srcAccNum);
        Account* dest = findAccount(destAccNum);

        if (!source || !dest) {
            cout << "Transfer failed: One or both account parameters do not exist.\n";
            return;
        }

        if (source->withdraw(amount)) {
            dest->deposit(amount);
            source->addLog("Transferred $" + to_string(amount) + " to Account " + destAccNum);
            dest->addLog("Received $" + to_string(amount) + " from Account " + srcAccNum);
            cout << "Transfer complete: $" << amount << " moved safely.\n";
        }
    }

    void printHistoryOf(string accNum) {
        Account* acc = findAccount(accNum);
        if (acc) acc->displayHistory();
        else cout << "Account error: Not found.\n";
    }

    void findRichestCustomer() {
        if (accounts.empty()) {
            cout << "No existing accounts found.\n";
            return;
        }
        int richestIdx = 0;
        for (size_t i = 1; i < accounts.size(); i++) {
            if (accounts[i].getBalance() > accounts[richestIdx].getBalance()) {
                richestIdx = i;
            }
        }
        cout << "\n>>> RICHEST CUSTOMER FOUND <<<\n";
        cout << "Name:    " << accounts[richestIdx].getName() << "\n";
        cout << "Acc No:  " << accounts[richestIdx].getAccNum() << "\n";
        cout << "Balance: $" << fixed << setprecision(2) << accounts[richestIdx].getBalance() << "\n";
        cout << "\n";
    }
};

int main() {
    Bank apexBank;

    // Opening records
    apexBank.openAccount("ACC101", "Debi", 5000.00);
    apexBank.openAccount("ACC102", "Shuvra", 12000.50);
    apexBank.openAccount("ACC103", "Rita", 2500.25);

    cout << "\n--- Performing Operations ---\n";
    apexBank.depositTo("ACC101", 1500.00);
    apexBank.withdrawFrom("ACC103", 500.00);

    // Core Transfer Request
    cout << "\n--- Executing Funds Transfer ---\n";
    apexBank.transferMoney("ACC102", "ACC101", 3000.00);

    // Finding Top Capital Account Holder
    apexBank.findRichestCustomer();

    // Inspect Audit History Logs
    apexBank.printHistoryOf("ACC101");
    apexBank.printHistoryOf("ACC102");

    return 0;
}

