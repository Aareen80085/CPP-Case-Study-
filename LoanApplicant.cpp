#include "LoanApplicant.h"
#include <iomanip>
#include <iostream>
using namespace std;

LoanApplicant::LoanApplicant(string n, int a, double income, double loanAmount,
                             int tenure) {
  name = n;
  age = a;
  monthlyIncome = income;
  loanAmountRequested = loanAmount;
  tenureRequested = tenure;
  creditScore = 0; // will be set by CreditScoreCalculator
}

string LoanApplicant::getName() { return name; }
int LoanApplicant::getAge() { return age; }
double LoanApplicant::getMonthlyIncome() { return monthlyIncome; }
int LoanApplicant::getCreditScore() { return creditScore; }
double LoanApplicant::getLoanAmountRequested() { return loanAmountRequested; }
int LoanApplicant::getTenureRequested() { return tenureRequested; }

void LoanApplicant::setCreditScore(int score) { creditScore = score; }

void LoanApplicant::displayDetails() {
  cout << fixed << setprecision(2);
  cout << "-----------------------------" << endl;
  cout << "Name          : " << name << endl;
  cout << "Age           : " << age << endl;
  cout << "Monthly Income: " << monthlyIncome << endl;
  cout << "Credit Score  : " << creditScore << endl;
  cout << "Loan Requested: " << loanAmountRequested << endl;
  cout << "Tenure        : " << tenureRequested << " months" << endl;
  cout << "-----------------------------" << endl;
}