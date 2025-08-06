#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
private:
    long long accountNumber;
    string name;
    double balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nName: " << name;
        cout << "\nBalance: ₹" << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Amount deposited successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance)
            cout << "Insufficient Balance!\n";
        else {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        }
    }

    long long getAccountNumber() {
        return accountNumber;
    }

    void writeToFile(ofstream &out) {
        out << accountNumber << endl;
        out << name << endl;
        out << balance << endl;
    }

    void readFromFile(ifstream &in) {
        in >> accountNumber;
        in.ignore();
        getline(in, name);
        in >> balance;
        in.ignore();
    }
};

// ✅ 1. Create and Save New Account
void createAndSaveAccount() {
    BankAccount acc;
    acc.createAccount();

    ofstream fout("accounts.txt", ios::app);
    if (!fout) {
        cout << "File open failed!\n";
        return;
    }

    acc.writeToFile(fout);
    fout.close();

    cout << "Account created and saved successfully.\n";
}

// ✅ 2. Display All Accounts
void displayAllAccounts() {
    BankAccount acc;
    ifstream fin("accounts.txt");

    cout << "\n--- All Bank Accounts ---\n";
    while (fin.peek() != EOF) {
        acc.readFromFile(fin);
        if (fin) acc.showAccount();
    }

    fin.close();
}

// ✅ 3. Deposit
void depositToAccount() {
    long long roll;
    double amount;
    cout << "Enter Account Number: ";
    cin >> roll;

    BankAccount acc;
    bool found = false;

    ifstream fin("accounts.txt");
    ofstream fout("temp.txt");

    while (fin.peek() != EOF) {
        acc.readFromFile(fin);
        if (acc.getAccountNumber() == roll) {
            cout << "Account found:\n";
            acc.showAccount();
            cout << "Enter amount to deposit: ";
            cin >> amount;
            acc.deposit(amount);
            found = true;
        }
        acc.writeToFile(fout);
    }

    fin.close();
    fout.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) cout << "Account not found!\n";
}

// ✅ 4. Withdraw
void withdrawFromAccount() {
    long long roll;
    double amount;
    cout << "Enter Account Number: ";
    cin >> roll;

    BankAccount acc;
    bool found = false;

    ifstream fin("accounts.txt");
    ofstream fout("temp.txt");

    while (fin.peek() != EOF) {
        acc.readFromFile(fin);
        if (acc.getAccountNumber() == roll) {
            cout << "Account found:\n";
            acc.showAccount();
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            acc.withdraw(amount);
            found = true;
        }
        acc.writeToFile(fout);
    }

    fin.close();
    fout.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) cout << "Account not found!\n";
}

// ✅ 5. Delete Account
void deleteAccount() {
    long long roll;
    cout << "Enter Account Number to delete: ";
    cin >> roll;

    BankAccount acc;
    bool found = false;

    ifstream fin("accounts.txt");
    ofstream fout("temp.txt");

    while (fin.peek() != EOF) {
        acc.readFromFile(fin);
        if (acc.getAccountNumber() == roll) {
            cout << "Account found and deleted.\n";
            found = true;
            continue; // delete => skip writing
        }
        acc.writeToFile(fout);
    }

    fin.close();
    fout.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) cout << "Account not found!\n";
}

// ✅ 6. Main Menu
int main() {
    int choice;

    do {
        cout << "\n======== Bank Management Menu ========\n";
        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Delete Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: createAndSaveAccount(); break;
            case 2: displayAllAccounts(); break;
            case 3: depositToAccount(); break;
            case 4: withdrawFromAccount(); break;
            case 5: deleteAccount(); break;
            case 6: cout << "Exiting program. Thank you!\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
