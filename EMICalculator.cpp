#include "EMICalculator.h"
#include <cmath> // for pow()

double EMICalculator::calculate(double principal, double annualRate,
                                int months) {
  double r = (annualRate / 100.0) / 12.0; // convert to monthly rate
  double emi = (principal * r * pow(1 + r, months)) / (pow(1 + r, months) - 1);
  return emi;
}

double EMICalculator::getTotalPayable(double emi, int months) {
  return emi * months;
}

double EMICalculator::getTotalInterest(double principal, double emi,
                                       int months) {
  return getTotalPayable(emi, months) - principal;
}