#pragma once
#include <string>
using namespace std;

class Loan {
private:
  int loanId;
  string borrowerName;
  double principal;
  double interestRate;
  int tenureMonths;
  double emiAmount;
  double amountPaid;
  string status;

public:
  Loan(int id, string name, double principal, double rate, int tenure);

  void setEMI(double emi);
  void makePayment(double amount);

  int getLoanId();
  string getBorrowerName();
  double getPrincipal();
  double getInterestRate();
  int getTenureMonths();
  double getEMI();
  double getAmountPaid();
  double getOutstandingBalance();
  string getStatus();

  void displayDetails();
};