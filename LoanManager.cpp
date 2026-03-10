#include "LoanManager.h"
#include "CreditScoreCal.h"
#include "EMISchedule.h"
#include "EligibilityChecker.h"
#include "InterestRateEngine.h"
#include "LoanApplicant.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

LoanManager::LoanManager() { nextLoanId = 1; }

void LoanManager::addLoan() {
  string name;
  int age, tenure;
  double income, loanAmount;

  cout << "\n--- Loan Application ---" << endl;
  cout << "Applicant Name    : ";
  cin >> name;
  cout << "Age               : ";
  cin >> age;
  cout << "Monthly Income    : ";
  cin >> income;
  cout << "Loan Amount       : ";
  cin >> loanAmount;
  cout << "Tenure (months)   : ";
  cin >> tenure;

  // Step 1 — Create applicant
  LoanApplicant applicant(name, age, income, loanAmount, tenure);

  // Step 2 — Calculate credit score
  CreditScoreCal scoreCalc;
  scoreCalc.assignScore(applicant);

  cout << "\nCredit Score      : " << applicant.getCreditScore() << endl;

  // Step 3 — Check eligibility
  EligibilityChecker checker;
  if (!checker.isEligible(applicant)) {
    cout << "\n Loan Application REJECTED!" << endl;
    return;
  }

  // Step 4 — Assign interest rate
  InterestRateEngine rateEngine;
  double rate = rateEngine.getRate(applicant.getCreditScore());
  string rating = rateEngine.getRating(applicant.getCreditScore());

  cout << "\n--- Loan Approval ---" << endl;
  cout << " Loan ID Generated  : " << nextLoanId << endl;
  cout << " Credit Rating      : " << rating << endl;
  cout << " Interest Rate      : " << rate << "%" << endl;

  // Step 5 — Calculate EMI
  double emi = calc.calculate(loanAmount, rate, tenure);
  cout << " EMI Calculated     : " << fixed << setprecision(2) << emi << endl;

  // Step 6 — Create loan account
  Loan newLoan(nextLoanId, name, loanAmount, rate, tenure);
  newLoan.setEMI(emi);
  loans.push_back(newLoan);

  cout << " Loan Account Created!" << endl;
  cout << "\n--- Application Complete ---" << endl;
  newLoan.displayDetails();

  // Step 7 — Print full EMI schedule
  char choice;
  cout << "View full EMI schedule? (y/n): ";
  cin >> choice;
  if (choice == 'y' || choice == 'Y') {
    EMISchedule schedule;
    schedule.printFullSchedule(newLoan);
  }

  nextLoanId++;
}

void LoanManager::viewAllLoans() {
  if (loans.size() == 0) {
    cout << "\nNo loans found!" << endl;
    return;
  }

  cout << "\n--- All Loans ---" << endl;
  for (int i = 0; i < loans.size(); i++) {
    loans[i].displayDetails();
  }
}

void LoanManager::makePayment() {
  if (loans.size() == 0) {
    cout << "\nNo loans found!" << endl;
    return;
  }

  int id;
  cout << "\nEnter Loan ID: ";
  cin >> id;

  for (int i = 0; i < loans.size(); i++) {
    if (loans[i].getLoanId() == id) {
      if (loans[i].getStatus() == "Closed") {
        cout << "This loan is already closed!" << endl;
        return;
      }

      cout << "Outstanding Balance: " << loans[i].getOutstandingBalance()
           << endl;
      cout << "EMI Amount        : " << loans[i].getEMI() << endl;

      double amount;
      cout << "Enter payment amount: ";
      cin >> amount;

      loans[i].makePayment(amount);

      cout << "Payment successful!" << endl;
      cout << "New Outstanding   : " << loans[i].getOutstandingBalance()
           << endl;
      cout << "Status            : " << loans[i].getStatus() << endl;
      return;
    }
  }

  cout << "Loan ID not found!" << endl;
}

void LoanManager::searchByName() {
  if (loans.size() == 0) {
    cout << "\nNo loans found!" << endl;
    return;
  }

  string name;
  cout << "\nEnter borrower name: ";
  cin >> name;

  bool found = false;
  for (int i = 0; i < loans.size(); i++) {
    if (loans[i].getBorrowerName() == name) {
      loans[i].displayDetails();
      found = true;
    }
  }

  if (!found) {
    cout << "No loans found for: " << name << endl;
  }
}
void LoanManager::saveLoans() {
  ofstream file("loans.csv");
  if (!file) {
    cout << "Error saving loans!" << endl;
    return;
  }

  for (int i = 0; i < loans.size(); i++) {
    file << loans[i].getLoanId() << "," << loans[i].getBorrowerName() << ","
         << loans[i].getPrincipal() << "," << loans[i].getInterestRate() << ","
         << loans[i].getTenureMonths() << "," << loans[i].getEMI() << ","
         << loans[i].getAmountPaid() << "," << loans[i].getStatus() << "\n";
  }

  file.close();
  cout << "✅ Loans saved successfully!" << endl;
}

void LoanManager::loadLoans() {
  ifstream file("loans.csv");
  if (!file)
    return; // no file yet, that's fine

  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue;

    // Split line by comma
    stringstream ss(line);
    string token;

    int id, tenure;
    string name, status;
    double principal, rate, emi, amountPaid;

    getline(ss, token, ',');
    id = stoi(token);
    getline(ss, token, ',');
    name = token;
    getline(ss, token, ',');
    principal = stod(token);
    getline(ss, token, ',');
    rate = stod(token);
    getline(ss, token, ',');
    tenure = stoi(token);
    getline(ss, token, ',');
    emi = stod(token);
    getline(ss, token, ',');
    amountPaid = stod(token);
    getline(ss, token, ',');
    status = token;

    // Recreate loan
    Loan loan(id, name, principal, rate, tenure);
    loan.setEMI(emi);

    // Restore amount paid
    if (amountPaid > 0) {
      loan.makePayment(amountPaid);
    }

    loans.push_back(loan);

    // Keep nextLoanId ahead of loaded IDs
    if (id >= nextLoanId)
      nextLoanId = id + 1;
  }

  file.close();
}
void LoanManager::showMenu() {
  int choice;

  do {
    cout << "\n--- Loan Management ---" << endl;
    cout << "1. Apply for Loan" << endl;
    cout << "2. View All Loans" << endl;
    cout << "3. Make EMI Payment" << endl;
    cout << "4. Search by Name" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    // If user typed a letter or invalid input, cin goes into fail state
    if (cin.fail()) {
      cin.clear();            // reset the fail state
      cin.ignore(1000, '\n'); // discard the bad input
      cout << "Invalid input! Please enter a number." << endl;
      continue; // skip to next loop iteration
    }

    switch (choice) {
    case 1:
      addLoan();
      break;
    case 2:
      viewAllLoans();
      break;
    case 3:
      makePayment();
      break;
    case 4:
      searchByName();
      break;
    case 5:
      cout << "Goodbye!" << endl;
      break;
    default:
      cout << "Invalid choice! Please enter 1-5." << endl;
    }

  } while (choice != 5);
}