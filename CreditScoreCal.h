#pragma once
#include "LoanApplicant.h"

class CreditScoreCal {
public:
  int calculate(double monthlyIncome);
  void assignScore(LoanApplicant &applicant); // directly updates applicant
};