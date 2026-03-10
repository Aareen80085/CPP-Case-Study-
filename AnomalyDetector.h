#pragma once
#include "CreditCard.h"
#include "Transaction.h"
#include <string>
using namespace std;

class AnomalyDetector {
public:
  // 4 individual rules
  bool checkHighAmount(Transaction &t, double avgSpend, string &reason);
  bool checkVelocity(vector<Transaction> &transactions, string &reason);
  bool checkLocationJump(Transaction &prev, Transaction &curr, string &reason);
  bool checkCreditLimit(double amount, double availableCredit, string &reason);

  // Master function — runs ALL 4 rules on a transaction
  bool analyze(Transaction &t, CreditCard &card);
};