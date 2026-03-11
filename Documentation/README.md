# Finance Management System
A terminal-based C++ application that simulates a real-world banking system with two core modules — Loan Management and Credit Card Transaction Monitoring.

---

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [How to Compile & Run](#how-to-compile--run)
- [System Walkthrough](#system-walkthrough)
- [Anomaly Detection Rules](#anomaly-detection-rules)
- [File Handling](#file-handling)
- [Concepts Used](#concepts-used)

---

## Overview

This system is designed from an **Admin / Bank Officer** perspective. The admin can manage loans, credit cards, and monitor transactions for suspicious activity — all from the terminal.

---

## Features

### Loan Management
- **Loan Application** — Applicant submits name, age, income, loan amount and tenure
- **Eligibility Check** — Validates age (21–60), income (min ₹25,000/month) and credit score (min 650)
- **Credit Score Calculation** — Automatically calculated based on monthly income
- **Interest Rate Assignment** — Rate assigned based on credit score tier
- **EMI Calculation** — Uses the standard reducing balance formula
- **Loan Approval Flow** — Loan ID generated, account created, EMI schedule printed
- **Full Amortization Schedule** — Month-by-month breakdown of every payment
- **EMI Reminders** — Shows outstanding balance and months remaining
- **Make Payments** — Tracks payments, automatically marks loan as Closed when fully paid
- **Search by Borrower Name**

### Credit Card Management
- **Create Cards** — Supports Visa, Mastercard and Rupay with auto-generated card numbers
- **Block / Unblock Cards**
- **Add Transactions** — Admin selects customer by name, picks card, enters transaction details
- **Merchant Categories** — Food & Dining, Shopping, Travel, Fuel, Entertainment, Healthcare, Utilities, Other
- **Transaction Receipt** — Printed after every transaction with approval code
- **Monthly Statement** — Full spending summary with total and available credit
- **Anomaly Detection** — Runs automatically on every new transaction
- **Flagged Transaction Review** — View and mark suspicious transactions as safe

---

## Project Structure

```
C++ Case Study/
│
├── main.cpp
│
├── Loan.h / Loan.cpp                       — Core loan entity
├── EMICalculator.h / EMICalculator.cpp     — EMI formula
├── LoanApplicant.h / LoanApplicant.cpp     — Applicant data
├── CreditScoreCalculator.h / .cpp          — Score from income
├── EligibilityChecker.h / .cpp             — Age, income, score checks
├── InterestRateEngine.h / .cpp             — Rate from credit score
├── EMISchedule.h / EMISchedule.cpp         — Amortization + reminders
├── LoanManager.h / LoanManager.cpp         — Manages all loans
│
├── Transaction.h / Transaction.cpp         — Single card transaction
├── CreditCard.h / CreditCard.cpp           — Card + transaction history
├── AnomalyDetector.h / AnomalyDetector.cpp — Fraud detection rules
├── CardManager.h / CardManager.cpp         — Manages all cards
│
├── loans.csv                               — Persisted loan data
└── cards.csv                               — Persisted card + transaction data
```

---

## How to Compile & Run

### Requirements
- macOS / Linux with `clang++` or `g++`
- C++17 or later

### Compile
```bash
clang++ -std=c++17 main.cpp Loan.cpp EMICalculator.cpp LoanManager.cpp \
LoanApplicant.cpp CreditScoreCal.cpp EligibilityChecker.cpp \
InterestRateEngine.cpp EMISchedule.cpp Transaction.cpp CreditCard.cpp \
AnomalyDetector.cpp CardManager.cpp -o main
```

### Run
```bash
./main
```

---

## System Walkthrough

### Main Menu
```
=============================
   FINANCE MANAGEMENT SYSTEM
=============================
1. Loan Management
2. Credit Card Management
3. Exit
```

### Loan Application Flow
```
Enter applicant details
        ↓
Credit score calculated from income
        ↓
Eligibility checked (age, income, score)
        ↓
Interest rate assigned from score tier
        ↓
EMI calculated using reducing balance formula
        ↓
Loan account created → Full EMI schedule printed
```

### Credit Score & Interest Rate Tiers

| Monthly Income     | Credit Score | Interest Rate |
|--------------------|-------------|---------------|
| Below ₹25,000      | 300–500     | Rejected      |
| ₹25,000–₹50,000    | 500–650     | Rejected      |
| ₹50,000–₹75,000    | 650–750     | 13.5%         |
| ₹75,000–₹1,00,000  | 750–800     | 11.0% – 9.0%  |
| Above ₹1,00,000    | 800–900     | 7.5%          |

### EMI Formula
```
EMI =  P × r × (1 + r)^n
       ─────────────────
          (1 + r)^n - 1

P = Principal
r = Monthly interest rate = (Annual Rate / 100) / 12
n = Tenure in months
```

---

## Anomaly Detection Rules

Every transaction is automatically scanned by 4 rules:

### Rule 1 — High Amount
```
If transaction amount > 3x the average spend on that card → FLAG
```

### Rule 2 — Velocity Check
```
If more than 3 transactions occur within 10 minutes → FLAG
Indicates possible card theft
```

### Rule 3 — Location Jump
```
If two transactions happen in different cities within 60 minutes → FLAG
Physically impossible travel detected
```

### Rule 4 — Credit Limit Breach
```
If transaction amount > 90% of available credit limit → FLAG
```

A transaction can be flagged by one or multiple rules simultaneously. Flagged transactions appear in the **Anomaly & Fraud Report** and can be reviewed and marked safe by the admin.

---

## File Handling

Data is automatically saved and loaded using CSV files:

- **loans.csv** — Stores all loan records
- **cards.csv** — Stores all card details and transaction history

```
On program start  → data loaded from CSV files
On program exit   → data saved to CSV files
```

This ensures no data is lost between sessions.

---

## Concepts Used

| Concept | Where Used |
|---|---|
| Classes & OOP | Every module |
| Constructors & Destructors | All classes |
| Getters & Setters | All classes |
| Vectors | Storing loans, cards, transactions |
| File Handling (fstream) | Save & load CSV data |
| Stringstream | Parsing CSV lines |
| cmath / pow() | EMI calculation |
| Nested loops | Anomaly detection, transaction search |
| References (&) | Passing objects efficiently |
| Header Guards (#pragma once) | All .h files |

---

## Author
Built as a C++ Case Study project covering OOP, file handling, and system design fundamentals.
