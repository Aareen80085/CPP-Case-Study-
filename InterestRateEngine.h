#pragma once
#include <string>
using namespace std;

class InterestRateEngine {
public:
  double getRate(int creditScore);
  string getRating(int creditScore);
};