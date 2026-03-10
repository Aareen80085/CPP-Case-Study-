#include "CreditCard.h"
#include <iomanip>
#include <iostream>
using namespace std;

CreditCard::CreditCard(string number, string name, int expMonth, int expYear,
                       string type, double limit) {
  cardNumber = number;
  maskedNumber = "**** **** **** " + number.substr(12, 4);
  cardHolderName = name;
  expiryMonth = expMonth;
  expiryYear = expYear;
  cardType = type;
  creditLimit = limit;
  availableCredit = limit;
  status = "Active";
  nextTransactionId = 1;
}
// Getters
string CreditCard::getCardNumber() { return cardNumber; }
string CreditCard::getMaskedNumber() { return maskedNumber; }
string CreditCard::getCardHolderName() { return cardHolderName; }

string CreditCard::getCardType() { return cardType; }
double CreditCard::getCreditLimit() { return creditLimit; }
double CreditCard::getAvailableCredit() { return availableCredit; }
string CreditCard::getStatus() { return status; }
int CreditCard::getNextTransactionId() { return nextTransactionId; }

vector<Transaction> &CreditCard::getTransactions() { return transactions; }

void CreditCard::blockCard() { status = "Blocked"; }
void CreditCard::unblockCard() { status = "Active"; }

void CreditCard::addTransaction(Transaction t, double amount) {
  availableCredit -= amount;
  transactions.push_back(t);
  nextTransactionId++;
}

double CreditCard::getAverageTransactionAmount() {
  if (transactions.size() == 0)
    return 0;

  double total = 0;
  for (int i = 0; i < transactions.size(); i++) {
    total += transactions[i].getAmount();
  }
  return total / transactions.size();
}

void CreditCard::displayDetails() {
  cout << fixed << setprecision(2);
  cout << "-----------------------------" << endl;
  cout << "Card Number     : " << maskedNumber << endl;
  cout << "Card Holder     : " << cardHolderName << endl;
  cout << "Card Type       : " << cardType << endl;
  cout << "Expiry          : " << expiryMonth << "/" << expiryYear << endl;
  cout << "Credit Limit    : Rs." << creditLimit << endl;
  cout << "Available Credit: Rs." << availableCredit << endl;
  cout << "Status          : " << status << endl;
  cout << "Transactions    : " << transactions.size() << endl;
  cout << "-----------------------------" << endl;
}

void CreditCard::viewAllTransactions() {
  if (transactions.size() == 0) {
    cout << "No transactions found!" << endl;
    return;
  }
  cout << "\n--- All Transactions ---" << endl;
  for (int i = 0; i < transactions.size(); i++) {
    transactions[i].displayDetails();
  }
}

void CreditCard::viewFlaggedTransactions() {
  bool found = false;
  cout << "\n--- Flagged Transactions ---" << endl;
  for (int i = 0; i < transactions.size(); i++) {
    if (transactions[i].getFlagStatus()) {
      transactions[i].displayDetails();
      found = true;
    }
  }
  if (!found) {
    cout << "No flagged transactions found!" << endl;
  }
}

void CreditCard::viewMonthlyStatement() {
  if (transactions.size() == 0) {
    cout << "No transactions found!" << endl;
    return;
  }

  double total = 0;
  cout << fixed << setprecision(2);
  cout << "\n=============================" << endl;
  cout << "       MONTHLY STATEMENT      " << endl;
  cout << "=============================" << endl;
  cout << "Card    : " << maskedNumber << endl;
  cout << "Holder  : " << cardHolderName << endl;
  cout << "-----------------------------" << endl;

  for (int i = 0; i < transactions.size(); i++) {
    cout << transactions[i].getTransactionId() << "  " << setw(15) << left
         << transactions[i].getMerchantName() << setw(10) << right
         << transactions[i].getAmount() << "  " << transactions[i].getStatus()
         << endl;
    total += transactions[i].getAmount();
  }

  cout << "-----------------------------" << endl;
  cout << "Total Spent     : Rs." << total << endl;
  cout << "Credit Limit    : Rs." << creditLimit << endl;
  cout << "Available Credit: Rs." << availableCredit << endl;
  cout << "=============================" << endl;
}