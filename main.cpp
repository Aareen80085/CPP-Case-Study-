#include "CardManager.h"
#include "LoanManager.h"
#include <iostream>
using namespace std;

int main() {
  LoanManager loanManager;
  CardManager cardManager;

  // Load data on startup
  loanManager.loadLoans();
  cardManager.loadCards();

  int choice;
  do {
    cout << "\n=============================" << endl;
    cout << "   FINANCE MANAGEMENT SYSTEM   " << endl;
    cout << "=============================" << endl;
    cout << "1. Loan Management" << endl;
    cout << "2. Credit Card Management" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      loanManager.showMenu();
      break;
    case 2:
      cardManager.showMenu();
      break;
    case 3:
      // Save data on exit
      loanManager.saveLoans();
      cardManager.saveCards();
      cout << "Goodbye!" << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }
  } while (choice != 3);

  return 0;
}