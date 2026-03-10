#include "EMISchedule.h"
#include <iomanip>
#include <iostream>
using namespace std;

void EMISchedule::printFullSchedule(Loan &loan) {
  double balance = loan.getPrincipal();
  double monthlyRate = (loan.getInterestRate() / 100.0) / 12.0;
  double emi = loan.getEMI();

  cout << "\n--- Full EMI Schedule ---" << endl;
  cout << fixed << setprecision(2);
  cout << setw(6) << "Month" << setw(15) << "Opening Bal" << setw(10) << "EMI"
       << setw(12) << "Principal" << setw(12) << "Interest" << setw(15)
       << "Closing Bal" << endl;
  cout << string(70, '-') << endl;

  for (int month = 1; month <= loan.getTenureMonths(); month++) {
    double interest = balance * monthlyRate;
    double principalPart = emi - interest;
    double closingBal = balance - principalPart;

    if (closingBal < 0)
      closingBal = 0;

    cout << setw(6) << month << setw(15) << balance << setw(10) << emi
         << setw(12) << principalPart << setw(12) << interest << setw(15)
         << closingBal << endl;

    balance = closingBal;
  }
}

void EMISchedule::printReminder(Loan &loan, int currentMonth) {
  if (loan.getStatus() == "Closed") {
    cout << "Loan is already closed. No EMI due." << endl;
    return;
  }

  int remaining = loan.getTenureMonths() - currentMonth + 1;

  cout << "\n--- EMI Reminder ---" << endl;
  cout << "Loan ID         : " << loan.getLoanId() << endl;
  cout << "Borrower        : " << loan.getBorrowerName() << endl;
  cout << "EMI Due         : " << loan.getEMI() << endl;
  cout << "Current Month   : " << currentMonth << endl;
  cout << "Months Remaining: " << remaining << endl;
  cout << "Outstanding Bal : " << loan.getOutstandingBalance() << endl;
  cout << "Please pay your EMI on time to avoid penalties!" << endl;
}