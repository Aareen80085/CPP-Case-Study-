#include "AnomalyDetector.h"
#include <iostream>
using namespace std;

// Rule 1 — High Amount
bool AnomalyDetector::checkHighAmount(Transaction &t, double avgSpend,
                                      string &reason) {
  if (avgSpend == 0)
    return false; // no previous transactions to compare

  if (t.getAmount() > 3 * avgSpend) {
    reason = "Amount Rs." + to_string(t.getAmount()) +
             " is 3x above average spend of Rs." + to_string(avgSpend);
    return true;
  }
  return false;
}

// Rule 2 — Velocity Check
bool AnomalyDetector::checkVelocity(vector<Transaction> &transactions,
                                    string &reason) {
  int size = transactions.size();
  if (size < 3)
    return false; // need at least 3 previous transactions

  // Look at last 3 transactions
  int count = 0;
  Transaction &latest = transactions[size - 1];

  for (int i = size - 2; i >= 0 && i >= size - 4; i--) {
    int latestMins = latest.getHour() * 60 + latest.getMinute();
    int prevMins = transactions[i].getHour() * 60 + transactions[i].getMinute();
    int diff = latestMins - prevMins;

    if (diff >= 0 && diff <= 10) {
      count++;
    }
  }

  if (count >= 3) {
    reason = "4 transactions detected within 10 minutes — possible card theft";
    return true;
  }
  return false;
}

// Rule 3 — Location Jump
bool AnomalyDetector::checkLocationJump(Transaction &prev, Transaction &curr,
                                        string &reason) {
  // Same city — no problem
  if (prev.getCity() == curr.getCity())
    return false;

  // Calculate time difference in minutes
  int prevMins = prev.getHour() * 60 + prev.getMinute();
  int currMins = curr.getHour() * 60 + curr.getMinute();
  int diff = currMins - prevMins;

  if (diff >= 0 && diff <= 60) {
    reason = "Transaction in " + curr.getCity() + " only " + to_string(diff) +
             " mins after transaction in " + prev.getCity() +
             " — impossible location change";
    return true;
  }
  return false;
}

// Rule 4 — Credit Limit
bool AnomalyDetector::checkCreditLimit(double amount, double availableCredit,
                                       string &reason) {
  if (amount > availableCredit * 0.90) {
    reason = "Transaction amount exceeds 90% of available credit limit";
    return true;
  }
  return false;
}

// Master function — runs ALL rules
bool AnomalyDetector::analyze(Transaction &t, CreditCard &card) {
  string reason;
  bool flagged = false;

  cout << "\n--- Running Security Checks ---" << endl;

  // Rule 1
  double avg = card.getAverageTransactionAmount();
  if (checkHighAmount(t, avg, reason)) {
    cout << "⚠️  Rule 1 TRIGGERED: " << reason << endl;
    t.flagTransaction(reason);
    flagged = true;
  } else {
    cout << "✅ Rule 1 Passed: Normal amount" << endl;
  }

  // Rule 2
  vector<Transaction> &allTransactions = card.getTransactions();
  if (checkVelocity(allTransactions, reason)) {
    cout << "⚠️  Rule 2 TRIGGERED: " << reason << endl;
    t.flagTransaction(reason);
    flagged = true;
  } else {
    cout << "✅ Rule 2 Passed: Normal velocity" << endl;
  }

  // Rule 3
  int size = allTransactions.size();
  if (size > 0) {
    Transaction &prev = allTransactions[size - 1];
    if (checkLocationJump(prev, t, reason)) {
      cout << "⚠️  Rule 3 TRIGGERED: " << reason << endl;
      t.flagTransaction(reason);
      flagged = true;
    } else {
      cout << "✅ Rule 3 Passed: Normal location" << endl;
    }
  }

  // Rule 4
  if (checkCreditLimit(t.getAmount(), card.getAvailableCredit(), reason)) {
    cout << "⚠️  Rule 4 TRIGGERED: " << reason << endl;
    t.flagTransaction(reason);
    flagged = true;
  } else {
    cout << "✅ Rule 4 Passed: Within credit limit" << endl;
  }

  return flagged;
}