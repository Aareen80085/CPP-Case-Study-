#pragma once
#include <string>
using namespace std;

class LoanApplicant {
private:
  string name;
  int age;
  double monthlyIncome;
  int creditScore;
  double loanAmountRequested;
  int tenureRequested;

public:
  LoanApplicant(string name, int age, double income, double loanAmount,
                int tenure);

  // Getters
  string getName();
  int getAge();
  double getMonthlyIncome();
  int getCreditScore();
  double getLoanAmountRequested();
  int getTenureRequested();

  // Setter for credit score (CreditScoreCalculator will call this)
  void setCreditScore(int score);

  void displayDetails();
};