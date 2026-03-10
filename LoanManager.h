#pragma once
#include "EMICalculator.h"
#include "Loan.h"
#include <vector>
using namespace std;

class LoanManager {
private:
  vector<Loan> loans;
  int nextLoanId;
  EMICalculator calc;

public:
  LoanManager();
  void addLoan();
  void saveLoans();
  void loadLoans();
  void viewAllLoans();
  void makePayment();
  void searchByName();
  void showMenu();
};