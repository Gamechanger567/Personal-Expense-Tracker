#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Expense {
public:
    string description;
    string category;
    double amount;
    string date;

    Expense(string desc, string cat, double amt, string dt) {
        description = desc;
        category = cat;
        amount = amt;
        date = dt;
    }
};

class ExpenseTracker {
private:
    vector<Expense> expenses;

public:
    // Add an expense
    void addExpense(string description, string category, double amount, string date) {
        expenses.push_back(Expense(description, category, amount, date));
    }

    // View all expenses
    void viewExpenses() {
        if (expenses.empty()) {
            cout << "No expenses recorded yet.\n";
            return;
        }
        cout << "\nAll Expenses:\n";
        for (int i = 0; i < expenses.size(); i++) {
            cout << i + 1 << ". " << expenses[i].description << " | "
                 << expenses[i].category << " | "
                 << expenses[i].amount << " | "
                 << expenses[i].date << "\n";
        }
    }

    // Save expenses to a file
    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& exp : expenses) {
                outFile << exp.description << "," << exp.category << ","
                        << exp.amount << "," << exp.date << "\n";
            }
            cout << "Expenses saved successfully!\n";
        } else {
            cout << "Unable to open file to save expenses.\n";
        }
    }

    // Load expenses from a file
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string description, category, date;
            double amount;
            while (getline(inFile, description, ',') && getline(inFile, category, ',') &&
                   inFile >> amount && inFile.ignore() &&
                   getline(inFile, date)) {
                expenses.push_back(Expense(description, category, amount, date));
            }
            cout << "Expenses loaded successfully!\n";
        } else {
            cout << "Unable to open file to load expenses.\n";
        }
    }
};

int main() {
    ExpenseTracker tracker;
    tracker.loadFromFile("expenses.csv");  // Load previous data if available

    int choice;
    do {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To clear the input buffer

        if (choice == 1) {
            string description, category, date;
            double amount;

            cout << "Enter description: ";
            getline(cin, description);
            cout << "Enter category: ";
            getline(cin, category);
            cout << "Enter amount: ";
            cin >> amount;
            cin.ignore();
            cout << "Enter date (yyyy-mm-dd): ";
            getline(cin, date);

            tracker.addExpense(description, category, amount, date);
        }
        else if (choice == 2) {
            tracker.viewExpenses();
        }
        else if (choice == 3) {
            tracker.saveToFile("expenses.csv");  // Save to file before exiting
            cout << "Data saved successfully!\n";
        }
    } while (choice != 3);

    return 0;
}
