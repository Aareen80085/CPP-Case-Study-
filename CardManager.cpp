#include "CardManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

CardManager::CardManager() { nextCardId = 1; }

// Helper — find card by card number
int CardManager::findCardIndex(string cardNumber) {
  for (int i = 0; i < cards.size(); i++) {
    if (cards[i].getCardNumber() == cardNumber) {
      return i;
    }
  }
  return -1;
}

// Helper — show all cards for a name, returns index chosen by admin
int CardManager::selectCardByName() {
  string name;
  cout << "Enter Customer Name: ";
  cin >> name;

  // collect matching indices
  vector<int> matches;
  for (int i = 0; i < cards.size(); i++) {
    if (cards[i].getCardHolderName() == name) {
      matches.push_back(i);
    }
  }

  if (matches.size() == 0) {
    cout << "No cards found for: " << name << endl;
    return -1;
  }

  // Show matching cards
  cout << "\nCards found for " << name << ":" << endl;
  for (int i = 0; i < matches.size(); i++) {
    cout << i + 1 << ". " << cards[matches[i]].getMaskedNumber() << " ("
         << cards[matches[i]].getCardType() << ")"
         << " | Limit: Rs." << fixed << setprecision(2)
         << cards[matches[i]].getCreditLimit()
         << " | Status: " << cards[matches[i]].getStatus() << endl;
  }

  // Admin picks one
  int pick;
  cout << "Select card (1-" << matches.size() << "): ";
  cin >> pick;

  if (pick < 1 || pick > matches.size()) {
    cout << "Invalid selection!" << endl;
    return -1;
  }

  return matches[pick - 1];
}

void CardManager::createCard() {
  string name, type;
  double limit;
  int expMonth, expYear;

  cout << "\n--- Create New Credit Card ---" << endl;
  cout << "Card Holder Name  : ";
  cin >> name;

  cout << "Card Type         : " << endl;
  cout << "  1. Visa" << endl;
  cout << "  2. Mastercard" << endl;
  cout << "  3. Rupay" << endl;
  cout << "Choose: ";
  int typeChoice;
  cin >> typeChoice;

  if (typeChoice == 1)
    type = "Visa";
  else if (typeChoice == 2)
    type = "Mastercard";
  else
    type = "Rupay";

  cout << "Credit Limit      : ";
  cin >> limit;
  cout << "Expiry Month(1-12): ";
  cin >> expMonth;
  cout << "Expiry Year       : ";
  cin >> expYear;

  // Generate card number based on type prefix
  string prefix;
  if (type == "Visa")
    prefix = "4";
  else if (type == "Mastercard")
    prefix = "5";
  else
    prefix = "6";

  string cardNumber = prefix + "000000000000";
  cardNumber += to_string(1000 + nextCardId);
  cardNumber = cardNumber.substr(0, 16);

  // Create card without CVV
  CreditCard newCard(cardNumber, name, expMonth, expYear, type, limit);
  cards.push_back(newCard);

  cout << "\n✅ Card Created Successfully!" << endl;
  cout << "-----------------------------" << endl;
  cout << "Card Holder : " << name << endl;
  cout << "Card Number : **** **** **** " << cardNumber.substr(12, 4) << endl;
  cout << "Card Type   : " << type << endl;
  cout << "Expiry      : " << expMonth << "/" << expYear << endl;
  cout << "Limit       : Rs." << fixed << setprecision(2) << limit << endl;
  cout << "-----------------------------" << endl;

  nextCardId++;
}

void CardManager::viewAllCards() {
  if (cards.size() == 0) {
    cout << "\nNo cards found!" << endl;
    return;
  }

  cout << "\n--- All Cards ---" << endl;
  for (int i = 0; i < cards.size(); i++) {
    cards[i].displayDetails();
  }
}

void CardManager::blockUnblockCard() {
  if (cards.size() == 0) {
    cout << "\nNo cards found!" << endl;
    return;
  }

  int index = selectCardByName();
  if (index == -1)
    return;

  cout << "Current Status: " << cards[index].getStatus() << endl;
  cout << "1. Block Card" << endl;
  cout << "2. Unblock Card" << endl;
  cout << "Choose: ";
  int choice;
  cin >> choice;

  if (choice == 1) {
    cards[index].blockCard();
    cout << "✅ Card blocked successfully!" << endl;
  } else {
    cards[index].unblockCard();
    cout << "✅ Card unblocked successfully!" << endl;
  }
}

void CardManager::searchByName() {
  if (cards.size() == 0) {
    cout << "\nNo cards found!" << endl;
    return;
  }

  string name;
  cout << "\nEnter Card Holder Name: ";
  cin >> name;

  bool found = false;
  for (int i = 0; i < cards.size(); i++) {
    if (cards[i].getCardHolderName() == name) {
      cards[i].displayDetails();
      found = true;
    }
  }

  if (!found) {
    cout << "No cards found for: " << name << endl;
  }
}

void CardManager::addTransaction() {
  if (cards.size() == 0) {
    cout << "\nNo cards found!" << endl;
    return;
  }

  cout << "\n--- New Transaction ---" << endl;

  int index = selectCardByName();
  if (index == -1)
    return;

  if (cards[index].getStatus() == "Blocked") {
    cout << "❌ Card is blocked! Transaction declined." << endl;
    return;
  }

  cout << "✅ Card selected — " << cards[index].getCardHolderName() << endl;

  // Transaction details
  string merchant, city;
  double amount;
  int hour, minute, catChoice;

  cout << "\nEnter Merchant Name      : ";
  cin >> merchant;
  cout << "Enter Amount             : ";
  cin >> amount;

  cout << "Enter Category           : " << endl;
  cout << "  1. Food & Dining" << endl;
  cout << "  2. Shopping" << endl;
  cout << "  3. Travel" << endl;
  cout << "  4. Fuel" << endl;
  cout << "  5. Entertainment" << endl;
  cout << "  6. Healthcare" << endl;
  cout << "  7. Utilities" << endl;
  cout << "  8. Other" << endl;
  cout << "Choose: ";
  cin >> catChoice;

  string category;
  switch (catChoice) {
  case 1:
    category = "Food & Dining";
    break;
  case 2:
    category = "Shopping";
    break;
  case 3:
    category = "Travel";
    break;
  case 4:
    category = "Fuel";
    break;
  case 5:
    category = "Entertainment";
    break;
  case 6:
    category = "Healthcare";
    break;
  case 7:
    category = "Utilities";
    break;
  default:
    category = "Other";
  }

  cout << "Enter City               : ";
  cin >> city;
  cout << "Enter Hour (0-23)        : ";
  cin >> hour;
  cout << "Enter Minute (0-59)      : ";
  cin >> minute;

  // Check credit limit
  if (amount > cards[index].getAvailableCredit()) {
    cout << "❌ Insufficient credit limit! Transaction declined." << endl;
    cout << "Available Credit: Rs." << fixed << setprecision(2)
         << cards[index].getAvailableCredit() << endl;
    return;
  }

  // Create transaction
  int txnId = cards[index].getNextTransactionId();
  string lastFour = cards[index].getCardNumber().substr(12, 4);

  Transaction newTxn(txnId, lastFour, merchant, category, amount, city, hour,
                     minute);

  // Run anomaly detection BEFORE adding
  bool flagged = detector.analyze(newTxn, cards[index]);

  // Add to card
  cards[index].addTransaction(newTxn, amount);

  // Print receipt
  newTxn.printReceipt();

  if (flagged) {
    cout << "\n⚠️  Transaction flagged for review!" << endl;
  }

  cout << "Available Credit: Rs." << fixed << setprecision(2)
       << cards[index].getAvailableCredit() << endl;
}

void CardManager::viewTransactions() {
  if (cards.size() == 0) {
    cout << "\nNo cards found!" << endl;
    return;
  }

  int index = selectCardByName();
  if (index == -1)
    return;

  cards[index].viewAllTransactions();
}

void CardManager::viewMonthlyStatement() {
  if (cards.size() == 0) {
    cout << "\nNo cards found!" << endl;
    return;
  }

  int index = selectCardByName();
  if (index == -1)
    return;

  cards[index].viewMonthlyStatement();
}

void CardManager::viewAllFlaggedTransactions() {
  if (cards.size() == 0) {
    cout << "\nNo cards found!" << endl;
    return;
  }

  bool anyFound = false;
  cout << "\n--- All Flagged Transactions ---" << endl;

  for (int i = 0; i < cards.size(); i++) {
    vector<Transaction> &txns = cards[i].getTransactions();
    for (int j = 0; j < txns.size(); j++) {
      if (txns[j].getFlagStatus()) {
        cout << "Card: " << cards[i].getMaskedNumber()
             << " | Holder: " << cards[i].getCardHolderName() << endl;
        txns[j].displayDetails();
        anyFound = true;
      }
    }
  }

  if (!anyFound) {
    cout << "No flagged transactions found!" << endl;
  }
}

void CardManager::markTransactionSafe() {
  if (cards.size() == 0) {
    cout << "\nNo cards found!" << endl;
    return;
  }

  string txnId;
  cout << "\nEnter Transaction ID (e.g TXN1001): ";
  cin >> txnId;

  for (int i = 0; i < cards.size(); i++) {
    vector<Transaction> &txns = cards[i].getTransactions();
    for (int j = 0; j < txns.size(); j++) {
      if (txns[j].getTransactionId() == txnId) {
        txns[j].setStatus("Approved");
        cout << "✅ Transaction " << txnId << " marked as safe!" << endl;
        return;
      }
    }
  }
  cout << "Transaction not found!" << endl;
}

void CardManager::saveCards() {
  ofstream file("cards.csv");
  if (!file) {
    cout << "Error saving cards!" << endl;
    return;
  }

  for (int i = 0; i < cards.size(); i++) {
    // Save card details — prefix with "CARD"
    file << "CARD," << cards[i].getCardNumber() << ","
         << cards[i].getCardHolderName() << "," << cards[i].getCardType() << ","
         << cards[i].getCreditLimit() << "," << cards[i].getAvailableCredit()
         << "," << cards[i].getStatus() << "\n";

    // Save each transaction — prefix with "TXN"
    vector<Transaction> &txns = cards[i].getTransactions();
    for (int j = 0; j < txns.size(); j++) {
      file << "TXN," << cards[i].getCardNumber() << ","
           << txns[j].getTransactionId() << "," << txns[j].getMerchantName()
           << "," << txns[j].getCategory() << "," << txns[j].getAmount() << ","
           << txns[j].getCity() << "," << txns[j].getHour() << ","
           << txns[j].getMinute() << "," << txns[j].getStatus() << ","
           << txns[j].getFlagStatus() << "\n";
    }
  }

  file.close();
  cout << "✅ Cards saved successfully!" << endl;
}

void CardManager::loadCards() {
  ifstream file("cards.csv");
  if (!file)
    return;

  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue;

    stringstream ss(line);
    string token, type;

    getline(ss, token, ',');
    type = token;

    if (type == "CARD") {
      string number, name, cardType, status;
      double limit, available;

      getline(ss, token, ',');
      number = token;
      getline(ss, token, ',');
      name = token;
      getline(ss, token, ',');
      cardType = token;
      getline(ss, token, ',');
      limit = stod(token);
      getline(ss, token, ',');
      available = stod(token);
      getline(ss, token, ',');
      status = token;

      // Extract expiry from card number — use defaults
      CreditCard card(number, name, 1, 2030, cardType, limit);

      // Restore available credit
      double spent = limit - available;
      if (spent > 0)
        card.addTransaction(Transaction(0, number.substr(12, 4), "Restored",
                                        "Other", spent, "N/A", 0, 0),
                            spent);

      if (status == "Blocked")
        card.blockCard();

      cards.push_back(card);
      if (nextCardId <= cards.size())
        nextCardId = cards.size() + 1;
    }

    else if (type == "TXN") {
      string cardNumber, txnId, merchant, category, city, status;
      double amount;
      int hour, minute;
      bool flagged;

      getline(ss, token, ',');
      cardNumber = token;
      getline(ss, token, ',');
      txnId = token;
      getline(ss, token, ',');
      merchant = token;
      getline(ss, token, ',');
      category = token;
      getline(ss, token, ',');
      amount = stod(token);
      getline(ss, token, ',');
      city = token;
      getline(ss, token, ',');
      hour = stoi(token);
      getline(ss, token, ',');
      minute = stoi(token);
      getline(ss, token, ',');
      status = token;
      getline(ss, token, ',');
      flagged = (token == "1");

      // Find the card and add transaction
      int index = findCardIndex(cardNumber);
      if (index != -1) {
        string lastFour = cardNumber.substr(12, 4);
        int id = cards[index].getNextTransactionId();
        Transaction t(id, lastFour, merchant, category, amount, city, hour,
                      minute);
        if (flagged)
          t.flagTransaction("Loaded from file");
        t.setStatus(status);
        cards[index].getTransactions().push_back(t);
      }
    }
  }
  file.close();
}

void CardManager::showMenu() {
  int choice;
  do {
    cout << "\n--- Credit Card Management ---" << endl;
    cout << "1. Card Operations" << endl;
    cout << "2. Transaction Operations" << endl;
    cout << "3. Anomaly & Fraud Report" << endl;
    cout << "4. Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
      int subChoice;
      do {
        cout << "\n--- Card Operations ---" << endl;
        cout << "1. Create New Card" << endl;
        cout << "2. View All Cards" << endl;
        cout << "3. Block / Unblock Card" << endl;
        cout << "4. Search by Name" << endl;
        cout << "5. Back" << endl;
        cout << "Enter choice: ";
        cin >> subChoice;

        switch (subChoice) {
        case 1:
          createCard();
          break;
        case 2:
          viewAllCards();
          break;
        case 3:
          blockUnblockCard();
          break;
        case 4:
          searchByName();
          break;
        case 5:
          break;
        default:
          cout << "Invalid choice!" << endl;
        }
      } while (subChoice != 5);
    }

    else if (choice == 2) {
      int subChoice;
      do {
        cout << "\n--- Transaction Operations ---" << endl;
        cout << "1. Add New Transaction" << endl;
        cout << "2. View All Transactions" << endl;
        cout << "3. View Monthly Statement" << endl;
        cout << "4. Back" << endl;
        cout << "Enter choice: ";
        cin >> subChoice;

        switch (subChoice) {
        case 1:
          addTransaction();
          break;
        case 2:
          viewTransactions();
          break;
        case 3:
          viewMonthlyStatement();
          break;
        case 4:
          break;
        default:
          cout << "Invalid choice!" << endl;
        }
      } while (subChoice != 4);
    }

    else if (choice == 3) {
      int subChoice;
      do {
        cout << "\n--- Anomaly & Fraud Report ---" << endl;
        cout << "1. View All Flagged Transactions" << endl;
        cout << "2. Mark Transaction as Safe" << endl;
        cout << "3. Back" << endl;
        cout << "Enter choice: ";
        cin >> subChoice;

        switch (subChoice) {
        case 1:
          viewAllFlaggedTransactions();
          break;
        case 2:
          markTransactionSafe();
          break;
        case 3:
          break;
        default:
          cout << "Invalid choice!" << endl;
        }
      } while (subChoice != 3);
    }

  } while (choice != 4);
}