#include <iostream>
#include <sstream> 
#include <string> 
#include <algorithm>
#include <iomanip>
#include <gtest/gtest.h>
#include "bank_account.hpp"

using std::string;
using std::to_string;  
using std::stoi; 
using std::stod; 
using std::stringstream; 
using std::fixed; 
using std::setprecision; 

//void function that updates balance by adding amount depositied to it
void deposit (double &balance, double amount_deposited) {
  balance += amount_deposited; 
}

//if the amount withdraw is greater than the balance false is returned and if not the balance is updated and true is returned 
bool withdraw (double &balance, double amount_withdrawn) {
  if (amount_withdrawn > balance) {
      return false; 
  }
  else {
      balance -= amount_withdrawn; 
      return true; 
  }
}

//balance is updating by subtracting amount withdrawn and a fee of $35 for an overdraft charge
void overdraft (double &balance, double amount_withdrawn) {
  balance -= amount_withdrawn; 
  balance -= 35; 
  
}

//apr is divided by 100 and then 12 to get monthly interest rate and then for loop removes anything after two decimal points and interest for month is returned as double 
double interest_for_month (double balance, double apr) {
  apr /= 100; 
  double interest = balance * apr;
  interest /= 12; 
  string interest_string = to_string(interest);
  for (int i = 0; i < interest_string.length(); i++) {
    if (interest_string.at(i) == '.') {
      interest_string.erase(i+3, interest_string.length() - 1);
    }
  }
  double interest2 = stod(interest_string); 
  return interest2; 
}

//date is split into three substrings for year, month, and day and then converted into ints with ptrs
void string_date_to_int_ptrs (string date, int *year, int *month, int *day) {
  string year_substring = date.substr(0,4);
  string month_substring = date.substr(5,7);
  string day_substring = date.substr(8, date.length() - 1);
  *year = stoi(year_substring);
  *month = stoi(month_substring);
  *day = stoi(day_substring);
}

//same as last but with references 
void string_date_to_ints (string date, int &year, int &month, int &day) {
  string year_substring = date.substr(0,4);
  string month_substring = date.substr(5,7);
  string day_substring = date.substr(8, date.length() - 1);
  year = stoi(year_substring);
  month = stoi(month_substring);
  day = stoi(day_substring);
}

//takes two dates as strings and counts the number of first days in the the month that pass
int number_of_first_of_months (string date_early, string date_late) {
  int year_early, month_early, day_early; 
  string_date_to_ints (date_early, year_early, month_early, day_early); 
  int year_late, month_late, day_late; 
  string_date_to_ints (date_late, year_late, month_late, day_late); 
  int count = 0; 
  if (date_early != date_late) {
    if (day_early == 1) {
      count++; 
    }
    int year_difference = (year_late - year_early) * 12;
    int month_difference = (month_late - month_early) * 1; 
    count += year_difference; 
    count += month_difference; 
  }
  else {
    count = 0; 
  }
  return count; 
}

//returns final interest by using two prior functions to find the interest accrued per month and constantly updating the balance with that value through a for loop 
double interest_earned (double balance, double apr, string date_early, string date_late) { 
  double balance_copy = balance; 
  int periods_passed = number_of_first_of_months (date_early, date_late); 
  for (int i = 1; i <= periods_passed; i++) {
    balance += interest_for_month(balance, apr);  
  }
  double final_interest = balance - balance_copy; 
  return final_interest; 
}

//function utilizes many of the functions from before to perform deposits, withdraw, and overdraft operations to constanatly update the balance, the funciton utilizes stringstreams
string process_command (string line, string &previous_date, double &balance, double apr) {
  string date, action, amount;
  stringstream ss; 
  ss << line; 
  ss >> date; 
  ss >> action; 
  ss >> amount; 
  if (previous_date == "") {
    previous_date += date; 
  }
  string amount_copy = amount;
  amount.erase(amount.begin());
  double amount_as_int = stod(amount); 
  int periods_passed = number_of_first_of_months(previous_date, date);
  double interest_accrued = interest_earned( balance, apr, previous_date, date);
  if (interest_accrued < 0) {
    interest_accrued = 0; 
  }
  //if action is deposit and no firsts of the month have passed between date and previous_date 
  if (action == "Deposit" && periods_passed == 0) {
    deposit(balance, amount_as_int);
    stringstream ns; 
    ns << "On " << date << ": Instructed to perform \"" <<  action << ' ' << amount_copy << "\"" << "\nBalance: " << fixed << setprecision(2) << 
    balance << "\n";
    previous_date = date;
    return ns.str();
  }
  //if action is deposit and at least firsts of the month has passed between date and previous_date 
  if (action == "Deposit" && periods_passed >= 1) {
    deposit(balance, amount_as_int);
    balance += interest_accrued; 
    stringstream os; 
    os << "On " << date << ": Instructed to perform \"" <<  action << ' ' << amount_copy << "\"" << "\nSince " << previous_date << ", " << 
    "interest has accrued " << periods_passed << " times." << "\n$" << fixed << setprecision(2) << interest_accrued << " interest has been earned." << "\nBalance: " << fixed << 
    setprecision(2) << balance << "\n";
    previous_date = date;
    return os.str();
  }
  //if action is deposit and at least firsts of the month has passed between date and previous_date and the balance is negative so no interest accrued even though many firsts of the month have passed 
  if (action == "Deposit" && periods_passed >= 1 && interest_accrued == 0) {
    deposit(balance, amount_as_int);
    balance += interest_accrued; 
    stringstream nss; 
    nss << "On " << date << ": Instructed to perform \"" <<  action << ' ' << amount_copy << "\"" << "\nSince " << previous_date << ", " << 
    "interest has accrued " << periods_passed << " times." << "\n$" << fixed << setprecision(2) << interest_accrued << " interest has been earned." << "\nBalance: " << fixed << setprecision(2) << balance << "\n";  
    previous_date = date;
    return nss.str();
  } 
  //if action is withdraw and no firsts of the month have passed between date and previous_date 
  if (action == "Withdraw"  && periods_passed == 0) {
    bool value = withdraw(balance, amount_as_int);
    if (value == true) {
      stringstream oss; 
      oss << "On " << date << ": Instructed to perform \"" <<  action << ' ' << amount_copy << "\"" << "\nBalance: " << fixed << setprecision(2) 
      << balance << "\n";
      previous_date = date;
      return oss.str();
    }
    if (value == false) {
      overdraft(balance, amount_as_int);
      stringstream ms;
      ms << "On " << date << ": Instructed to perform \"" <<  action << ' ' << amount_copy << "\"" << "\nOverdraft!\nBalance: " <<
      fixed << setprecision(2) << balance << "\n";
      previous_date = date;
      return ms.str();
    }
  }
  //if action is deposit and at least firsts of the month has passed between date and previous_date
  if (action == "Withdraw"  && periods_passed >= 1) {
    bool value = withdraw(balance, amount_as_int);
    if (value == true) {
      balance += interest_accrued;
      stringstream oss; 
      oss << "On " << date << ": Instructed to perform \"" <<  action << ' ' << amount_copy << "\"" << "\nSince " << previous_date << ", " << "interest has accrued " << periods_passed << " times." << "\n$" << fixed << setprecision(2) << interest_accrued << " interest has been earned." << "\nBalance: " << fixed << setprecision(2) << balance << "\n";  
    previous_date = date;
      previous_date = date;
      return oss.str();
    }
    if (value == false) {
      overdraft(balance, amount_as_int);
      balance += interest_accrued;
      stringstream ms;
      ms << "On " << date << ": Instructed to perform \"" <<  action << ' ' << amount_copy << "\"" << "\nSince " << previous_date << ", " << "interest has accrued " << periods_passed << " times." << "\n$" << fixed << setprecision(2) << interest_accrued << " interest has been earned." << "\nOverdraft!\nBalance: " << fixed << setprecision(2) << balance << "\n";
      previous_date = date;
      return ms.str();
    }
  }
  return 0; 
}

//completely reliant on process_command function as its only operation is to use getline to extract strings from a multiline input and then call process_command to utilize it on each line extracted from the multiline input 
string process_commands (string input, double apr) {
  stringstream ss(input);
  string line; 
  string previous_date = "";
  double balance = 0;
  stringstream os; 
  while (std::getline(ss, line, '\n')) {
    string output = process_command (line, previous_date, balance, apr); 
    os << output;  
  } 
  return os.str(); 
}

//main i used to test my functions 
int main () {
  string input =  
  "2016-09-02 Deposit $600\n"
  "2016-09-02 Withdraw $23.54\n"
  "2016-09-04 Withdraw $58\n"
  "2016-11-02 Deposit $200\n"
  "2017-03-02 Withdraw $1200\n"
  "2019-11-02 Deposit $1500\n"
  "2020-03-02 Withdraw $100\n"
  "2021-03-02 Deposit $100\n";
  double apr = 7;
  string result = process_commands (input, apr); 
  std::cout << result << std::endl; 
}
