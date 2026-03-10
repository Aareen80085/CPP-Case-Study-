#include "Loan.h"
#include <iomanip>
#include <iostream>
using namespace std;

Loan::Loan(int id, string name, double p, double rate, int tenure) {
  loanId = id;
  borrowerName = name;
  principal = p;
  interestRate = rate;
  tenureMonths = tenure;
  emiAmount = 0;
  amountPaid = 0;
  status = "Active";
}

void Loan::setEMI(double emi) { emiAmount = emi; }

void Loan::makePayment(double amount) {
  amountPaid += amount;
  if (amountPaid >= principal) {
    status = "Closed";
  }
}

int Loan::getLoanId() { return loanId; }
string Loan::getBorrowerName() { return borrowerName; }
double Loan::getPrincipal() { return principal; }
double Loan::getInterestRate() { return interestRate; }
int Loan::getTenureMonths() { return tenureMonths; }
double Loan::getEMI() { return emiAmount; }
double Loan::getAmountPaid() { return amountPaid; }
string Loan::getStatus() { return status; }

double Loan::getOutstandingBalance() {
  double balance = principal - amountPaid;
  if (balance < 0)
    return 0;
  return balance;
}

void Loan::displayDetails() {
  cout << fixed << setprecision(2);
  cout << "-----------------------------" << endl;
  cout << "Loan ID          : " << loanId << endl;
  cout << "Borrower         : " << borrowerName << endl;
  cout << "Principal        : " << principal << endl;
  cout << "Interest Rate    : " << interestRate << "%" << endl;
  cout << "Tenure           : " << tenureMonths << " months" << endl;
  cout << "EMI              : " << emiAmount << endl;
  cout << "Amount Paid      : " << amountPaid << endl;
  cout << "Outstanding      : " << getOutstandingBalance() << endl;
  cout << "Status           : " << status << endl;
  cout << "-----------------------------" << endl;
}