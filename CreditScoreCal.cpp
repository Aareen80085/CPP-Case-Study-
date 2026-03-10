#include "CreditScoreCal.h"

int CreditScoreCal::calculate(double income) {
  if (income >= 100000)
    return 850;
  else if (income >= 75000)
    return 780;
  else if (income >= 50000)
    return 700;
  else if (income >= 25000)
    return 620;
  else
    return 450;
}

void CreditScoreCal::assignScore(LoanApplicant &applicant) {
  int score = calculate(applicant.getMonthlyIncome());
  applicant.setCreditScore(score);
}