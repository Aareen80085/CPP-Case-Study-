#pragma once
#include <string>
using namespace std;

class Transaction {
private:
  string transactionId;    // auto generated e.g TXN1001
  string maskedCardNumber; // **** **** **** 1234
  string merchantName;
  string category; // Food, Shopping, Travel etc
  double amount;
  string city;
  int hour;
  int minute;
  string status;        // Approved / Declined / Flagged
  string approvalCode;  // auto generated e.g AUTH482910
  string declineReason; // if declined, why
  bool isFlagged;

public:
  // Constructor
  Transaction(int id, string cardLastFour, string merchant, string category,
              double amount, string city, int hour, int minute);

  // Getters
  string getTransactionId();
  string getMaskedCardNumber();
  string getMerchantName();
  string getCategory();
  double getAmount();
  string getCity();
  int getHour();
  int getMinute();
  string getStatus();
  string getApprovalCode();
  bool getFlagStatus();

  // Setters
  void setStatus(string status);
  void setDeclineReason(string reason);
  void flagTransaction(string reason);

  void displayDetails();
  void printReceipt();
};