#pragma once
#include "Loan.h"

class EMISchedule {
public:
  void printFullSchedule(Loan &loan);
  void printReminder(Loan &loan, int currentMonth);
};