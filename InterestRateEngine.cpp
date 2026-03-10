#include "InterestRateEngine.h"

double InterestRateEngine::getRate(int score) {
  if (score >= 800)
    return 7.5;
  else if (score >= 750)
    return 9.0;
  else if (score >= 700)
    return 11.0;
  else if (score >= 650)
    return 13.5;
  else
    return -1; // -1 means rejected
}

string InterestRateEngine::getRating(int score) {
  if (score >= 800)
    return "Excellent";
  else if (score >= 750)
    return "Very Good";
  else if (score >= 700)
    return "Good";
  else if (score >= 650)
    return "Fair";
  else
    return "Poor";
}