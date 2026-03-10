#include "Transaction.h"
#include <iomanip>
#include <iostream>
using namespace std;

Transaction::Transaction(int id, string cardLastFour, string merchant,
                         string cat, double amt, string cty, int hr, int min) {

  // Generate transaction ID e.g TXN1001
  transactionId = "TXN" + to_string(1000 + id);

  // Mask card number → **** **** **** 1234
  maskedCardNumber = "**** **** **** " + cardLastFour;

  merchantName = merchant;
  category = cat;
  amount = amt;
  city = cty;
  hour = hr;
  minute = min;
  status = "Approved";
  isFlagged = false;
  declineReason = "";

  // Generate approval code e.g AUTH482910
  approvalCode = "AUTH" + to_string(100000 + (id * 7 + 482910) % 900000);
}

// Getters
string Transaction::getTransactionId() { return transactionId; }
string Transaction::getMaskedCardNumber() { return maskedCardNumber; }
string Transaction::getMerchantName() { return merchantName; }
string Transaction::getCategory() { return category; }
double Transaction::getAmount() { return amount; }
string Transaction::getCity() { return city; }
int Transaction::getHour() { return hour; }
int Transaction::getMinute() { return minute; }
string Transaction::getStatus() { return status; }
string Transaction::getApprovalCode() { return approvalCode; }
bool Transaction::getFlagStatus() { return isFlagged; }

// Setters
void Transaction::setStatus(string s) { status = s; }
void Transaction::setDeclineReason(string r) { declineReason = r; }

void Transaction::flagTransaction(string reason) {
  isFlagged = true;
  status = "Flagged";
  declineReason = reason;
}

void Transaction::displayDetails() {
  cout << fixed << setprecision(2);
  cout << "-----------------------------" << endl;
  cout << "Transaction ID  : " << transactionId << endl;
  cout << "Card            : " << maskedCardNumber << endl;
  cout << "Merchant        : " << merchantName << endl;
  cout << "Category        : " << category << endl;
  cout << "Amount          : Rs." << amount << endl;
  cout << "City            : " << city << endl;
  cout << "Time            : " << hour << ":" << setw(2) << setfill('0')
       << minute << setfill(' ') << endl;
  cout << "Status          : " << status << endl;
  if (isFlagged) {
    cout << "Flag Reason     : " << declineReason << endl;
  }
  cout << "-----------------------------" << endl;
}

void Transaction::printReceipt() {
  cout << fixed << setprecision(2);
  cout << "\n=============================" << endl;
  cout << "       TRANSACTION RECEIPT    " << endl;
  cout << "=============================" << endl;
  cout << "Transaction ID  : " << transactionId << endl;
  cout << "Approval Code   : " << approvalCode << endl;
  cout << "Card            : " << maskedCardNumber << endl;
  cout << "Merchant        : " << merchantName << endl;
  cout << "Category        : " << category << endl;
  cout << "Amount          : Rs." << amount << endl;
  cout << "City            : " << city << endl;
  cout << "Time            : " << hour << ":" << setw(2) << setfill('0')
       << minute << setfill(' ') << endl;
  cout << "Status          : " << status << endl;
  if (isFlagged) {
    cout << "⚠️  FLAGGED       : " << declineReason << endl;
  }
  cout << "=============================" << endl;
}