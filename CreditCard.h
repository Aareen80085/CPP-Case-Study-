#pragma once
#include "Transaction.h"
#include <vector>
using namespace std;

class CreditCard {
private:
  string cardNumber;
  string maskedNumber;
  string cardHolderName;
  int expiryMonth;
  int expiryYear;
  string cardType;
  double creditLimit;
  double availableCredit;
  string status;
  vector<Transaction> transactions;
  int nextTransactionId;

public:
  // Constructor
  CreditCard(string number, string name, int expMonth, int expYear, string type,
             double limit);

  // Getters
  string getCardNumber();
  string getMaskedNumber();
  string getCardHolderName();
  string getCardType();
  double getCreditLimit();
  double getAvailableCredit();
  string getStatus();
  int getNextTransactionId();
  vector<Transaction> &getTransactions();

  // Actions
  void addTransaction(Transaction t, double amount);
  void blockCard();
  void unblockCard();
  double getAverageTransactionAmount();

  // Display
  void displayDetails();
  void viewAllTransactions();
  void viewFlaggedTransactions();
  void viewMonthlyStatement();
};