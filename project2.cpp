#include <iostream>
#include <string> 
#include <algorithm>

using std::string;
using std::to_string;  
using std::stoi; 
using std::stod; 
using std::erase; 
using std::remove; 

void deposit (double &balance, double amount_deposited) {
    balance += amount_deposited; 
}

bool withdraw (double &balance, double amount_withdrawn) {
    if (amount_withdrawn > balance) {
        return false; 
    }
    else {
        balance -= amount_withdrawn; 
        return true; 
    }
}

void overdraft (double &balance, double amount_withdrawn) {
    balance -= amount_withdrawn; 
    balance -= 35; 
}

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

void string_date_to_int_ptrs (string date, int *year, int *month, int *day) {
    string year_substring = date.substr(0,4);
    string month_substring = date.substr(5,7);
    string day_substring = date.substr(8, date.length() - 1);
    *year = stoi(year_substring);
    *month = stoi(month_substring);
    *day = stoi(day_substring);
}

void string_date_to_ints (string date, int &year, int &month, int &day) {
    string year_substring = date.substr(0,4);
    string month_substring = date.substr(5,7);
    string day_substring = date.substr(8, date.length() - 1);
    year = stoi(year_substring);
    month = stoi(month_substring);
    day = stoi(day_substring);
}

int number_of_first_of_months (string date_early, string date_late) {
    int year_early, month_early, day_early; 
    string_date_to_ints (date_early, year_early, month_early, day_early); 
    int year_late, month_late, day_late; 
    string_date_to_ints (date_late, year_late, month_late, day_late); 
    if (year_late == year_early) {
            if (month_late == month_early) {
                if (day_late == day_early) {
                    count = 0;  
                }
                else if (day_early == 1) {
                    count++;   
                }
                count = 0; 
            }
            else { 
                int difference = month_late - month_early; 
                count += difference;  
            }
        }
        else {
            int year_difference = (year_late - (year_early + 1)) * 12;
            count += year_difference; 
            if (month_late > month_early) {
                int month_difference = month_late - month_early; 
                count += month_difference; 
            }
            else {
                int month_difference = month_early - month_late;
                count += month_difference; 
            }
        }
    return count; 
}
 
double interest_earned ( double balance, double apr, string date_early, string date_late) {
    double interest = interest_for_month (balance, apr);
    int periods_passed = number_of_first_of_months (date_early, date_late);
    double interest_accured = interest * periods_passed; 
    return interest_accured;
}

int main() {
    //double balance = 1000.00;
    //double apr = 12.0;
    string date_early = "2015-11-03";
    string date_late = "2019-03-30";
    int result = number_of_first_of_months (date_early, date_late);
    std::cout << result << std::endl;
}
