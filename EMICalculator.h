#pragma once
#include <string>
using namespace std;

class EMICalculator {
public:
  double calculate(double principal, double annualRate, int months);
  double getTotalPayable(double emi, int months);
  double getTotalInterest(double principal, double emi, int months);
};