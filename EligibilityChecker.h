#pragma once
#include "LoanApplicant.h"
#include <string>
using namespace std;

class EligibilityChecker {
private:
  double minIncome;
  int minAge;
  int maxAge;
  int minCreditScore;

public:
  EligibilityChecker();

  bool checkIncome(LoanApplicant &applicant, string &reason);
  bool checkAge(LoanApplicant &applicant, string &reason);
  bool checkCreditScore(LoanApplicant &applicant, string &reason);

  // Runs all checks — returns true only if ALL pass
  bool isEligible(LoanApplicant &applicant);
};