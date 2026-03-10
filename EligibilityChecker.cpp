#include "EligibilityChecker.h"
#include <iostream>
using namespace std;

EligibilityChecker::EligibilityChecker() {
  minIncome = 25000;
  minAge = 21;
  maxAge = 60;
  minCreditScore = 650;
}

bool EligibilityChecker::checkIncome(LoanApplicant &applicant, string &reason) {
  if (applicant.getMonthlyIncome() < minIncome) {
    reason = "Monthly income below minimum threshold of Rs.25,000";
    return false;
  }
  return true;
}

bool EligibilityChecker::checkAge(LoanApplicant &applicant, string &reason) {
  if (applicant.getAge() < minAge || applicant.getAge() > maxAge) {
    reason = "Age must be between 21 and 60 years";
    return false;
  }
  return true;
}

bool EligibilityChecker::checkCreditScore(LoanApplicant &applicant,
                                          string &reason) {
  if (applicant.getCreditScore() < minCreditScore) {
    reason = "Credit score too low. Minimum required: 650";
    return false;
  }
  return true;
}

bool EligibilityChecker::isEligible(LoanApplicant &applicant) {
  string reason;
  bool eligible = true;

  cout << "\n--- Eligibility Check ---" << endl;

  if (!checkAge(applicant, reason)) {
    cout << " Age Check Failed    : " << reason << endl;
    eligible = false;
  } else {
    cout << " Age Check Passed" << endl;
  }

  if (!checkIncome(applicant, reason)) {
    cout << " Income Check Failed : " << reason << endl;
    eligible = false;
  } else {
    cout << " Income Check Passed" << endl;
  }

  if (!checkCreditScore(applicant, reason)) {
    cout << " Credit Score Failed : " << reason << endl;
    eligible = false;
  } else {
    cout << " Credit Score Passed" << endl;
  }

  return eligible;
}