#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Employee {
private:
    string employeeID;
    string name;
    string designation;
    double baseSalary;

    // Computed Payroll Metrics
    double houseRent;
    double medicalAllowance;
    double tax;
    double netSalary;

    void processPayroll() {
        // Industry Standard Formulas:
        // House Rent = 40% of Base, Medical = 10% of Base
        houseRent = baseSalary * 0.40;
        medicalAllowance = baseSalary * 0.10;

        double grossSalary = baseSalary + houseRent + medicalAllowance;

        // Progressive Internal Tax Bracket Simulator
        if (grossSalary > 80000)      tax = grossSalary * 0.15; // 15% Tax Bracket
        else if (grossSalary > 50000) tax = grossSalary * 0.10; // 10% Tax Bracket
        else if (grossSalary > 30000) tax = grossSalary * 0.05; // 5% Tax Bracket
        else                          tax = 0.0;                // Tax Exempt

        netSalary = grossSalary - tax;
    }

public:
    Employee(string id, string n, string desig, double base)
        : employeeID(id), name(n), designation(desig), baseSalary(base) {
        processPayroll();
    }

    string getID() const { return employeeID; }
    string getName() const { return name; }
    string getDesignation() const { return designation; }
    double getNetSalary() const { return netSalary; }

    void displaySlipRow() const {
        cout << left << setw(10) << employeeID
             << setw(15) << name
             << setw(15) << designation
             << "$" << fixed << setprecision(2) << setw(12) << baseSalary
             << "$" << setw(10) << houseRent
             << "$" << setw(10) << medicalAllowance
             << "-$" << setw(9) << tax
             << "$" << setw(12) << netSalary << "\n";
    }
};

// Comparator to sort descending by Net Salary
bool compareByNetSalary(const Employee& a, const Employee& b) {
    return a.getNetSalary() > b.getNetSalary();
}

int main() {
    vector<Employee> roster;

    // Seeding sample organizational hierarchy data
    roster.push_back(Employee("EMP201", "Jonathan", "Lead Architect", 85000));
    roster.push_back(Employee("EMP202", "Sarah", "Data Analyst", 48000));
    roster.push_back(Employee("EMP203", "Marcus", "HR Director", 62000));
    roster.push_back(Employee("EMP204", "Elena", "Junior Dev", 32000));

    // Sort Roster by Net Income Output
    sort(roster.begin(), roster.end(), compareByNetSalary);

    // Render Master Payroll Grid Interface
    cout << "\n\n";
    cout << "                                  CORPORATE MASTER PAYROLL LEDGER                                   \n";
    cout << "\n";
    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Designation"
         << setw(13) << "Base"
         << setw(11) << "Rent (40%)"
         << setw(11) << "Med (10%)"
         << setw(11) << "Tax"
         << setw(12) << "Net Pay" << "\n";
    cout << "\n";

    for (const auto& emp : roster) {
        emp.displaySlipRow();
    }
    cout << "\n";

    return 0;
}
