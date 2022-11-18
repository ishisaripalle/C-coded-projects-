#pragma once 
#include <string> 
using std::string;

void deposit (double &balance, double amount_deposited);

bool withdraw (double &balance, double amount_withdrawn);

void overdraft (double &balance, double amount_withdrawn);

double interest_for_month (double balance, double apr);

void string_date_to_int_ptrs (string date, int *year, int *month, int *day);

void string_date_to_ints (string date, int &year, int &month, int &day);

int number_of_first_of_months (string date_early, string date_late);

double interest_earned (double balance, double apr, string date_early, string date_late);

string process_command (string line, string &previous_date, double &balance, double apr); 

string process_commands (string input, double apr); 
