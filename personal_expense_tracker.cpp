#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;

struct Expense {
    string description;
    string category;
    double amount;
    string date;

    Expense(string desc, string cat, double amt, string dt)
        : description(desc), category(cat), amount(amt), date(dt) {}
};

bool isValidDate(const string& date) {
    struct tm tm = {};
    stringstream ss(date);
    ss >> get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

class ExpenseTracker {
private:
    vector<Expense> expenses;

public:
    void addExpense(const string& description, const string& category, double amount, const string& date) {
        if (isValidDate(date)) {
            expenses.emplace_back(description, category, amount, date);
        } else {
            cout << "Invalid date format! Please use YYYY-MM-DD.\n";
        }
    }

    void viewExpenses() {
        if (expenses.empty()) {
            cout << "No expenses recorded.\n";
            return;
        }
        for (const auto& expense : expenses) {
            cout << "Description: " << expense.description
                 << ", Category: " << expense.category
                 << ", Amount: " << expense.amount
                 << ", Date: " << expense.date << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error opening file for saving!\n";
            return;
        }
        for (const auto& expense : expenses) {
            outFile << expense.description << "," << expense.category << "," << expense.amount << "," << expense.date << endl;
        }
        cout << "Data saved successfully!\n";
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error opening file for loading!\n";
            return;
        }
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string description, category, date;
            double amount;
            getline(ss, description, ',');
            getline(ss, category, ',');
            ss >> amount;
            ss.ignore();
            getline(ss, date);
            if (isValidDate(date)) {
                expenses.emplace_back(description, category, amount, date);
            }
        }
    }

    void sortByAmount() {
        sort(expenses.begin(), expenses.end(), [](const Expense& a, const Expense& b) {
            return a.amount < b.amount;
        });
    }

    void sortByDate() {
        sort(expenses.begin(), expenses.end(), [](const Expense& a, const Expense& b) {
            return a.date < b.date;
        });
    }

    void filterByCategory(const string& category) {
        for (const auto& expense : expenses) {
            if (expense.category == category) {
                cout << "Description: " << expense.description
                     << ", Amount: " << expense.amount
                     << ", Date: " << expense.date << endl;
            }
        }
    }

    void generateMonthlySummary() {
        map<string, double> monthlySummary;
        for (const auto& expense : expenses) {
            string month = expense.date.substr(0, 7);
            monthlySummary[month] += expense.amount;
        }
        for (const auto& entry : monthlySummary) {
            cout << "Month: " << entry.first << ", Total: " << entry.second << endl;
        }
    }
};

int main() {
    ExpenseTracker tracker;
    tracker.loadFromFile("expenses.csv");

    int choice;
    do {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n2. View Expenses\n3. Sort Expenses\n4. Filter Expenses\n5. Generate Reports\n6. Save and Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

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
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            tracker.addExpense(description, category, amount, date);
        } else if (choice == 2) {
            tracker.viewExpenses();
        } else if (choice == 3) {
            int sortChoice;
            cout << "Sort by:\n1. Amount\n2. Date\nEnter your choice: ";
            cin >> sortChoice;
            if (sortChoice == 1) tracker.sortByAmount();
            else if (sortChoice == 2) tracker.sortByDate();
            tracker.viewExpenses();
        } else if (choice == 4) {
            string category;
            cout << "Enter category to filter: ";
            cin.ignore();
            getline(cin, category);
            tracker.filterByCategory(category);
        } else if (choice == 5) {
            tracker.generateMonthlySummary();
        } else if (choice == 6) {
            tracker.saveToFile("expenses.csv");
        }
    } while (choice != 6);

    return 0;
}
