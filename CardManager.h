#pragma once
#include "AnomalyDetector.h"
#include "CreditCard.h"
#include <vector>
using namespace std;

class CardManager {
private:
private:
  vector<CreditCard> cards;
  AnomalyDetector detector;
  int nextCardId;

  int findCardIndex(string cardNumber); // ← add this

  // Helper — finds card by name, returns index chosen by admin
  int selectCardByName();

public:
  CardManager();

  // Card Operations
  void createCard();
  void viewAllCards();
  void blockUnblockCard();
  void searchByName();

  // Transaction Operations
  void addTransaction();
  void viewTransactions();
  void viewMonthlyStatement();

  // Anomaly Operations
  void viewAllFlaggedTransactions();
  void markTransactionSafe();

  // File Handling
  void saveCards();
  void loadCards();

  void showMenu();
};