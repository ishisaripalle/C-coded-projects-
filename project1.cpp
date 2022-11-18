#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;
using std::boolalpha;
using std::transform;
using std::endl;

// function takes two characters and returns true if they are equal and false if
// not
bool CharCheck(char character_1, char character_2) {
  // returns true if the two characters are equal
  if (character_1 == character_2) {
    return true;
  }
  // returns true if the second character is % and the first characters is any
  // character
  else if (character_2 == '%') {
    return true;
  }
  // returns true if second character is # and first character is a single digit
  else if (character_2 == '#') {
    if (isdigit(character_1)) {
      return true;
    }
  }
  return false;
}

// function takes two strings and returns true if all the characters in the
// strings are the same
bool StringCheck(string string_1, string string_2) {
  if (string_1.length() != string_2.length()) {
    return false;
  }
  // for loop iterates through strings by calling the charcheck function and if
  // all the characters are the same then it will return true
  for (int i = 0; i < string_1.size(); i++) {
    if (CharCheck(string_1.at(i), string_2.at(i)) == true) {
      continue;
    }
    return false;
  }
  return true;
}

// function takes two strings and checks to see if the second string is in the
// first string
bool FindText(string text, string pattern) {
  // function automatically returns false if second string if larger than the
  // first
  if (pattern.length() > text.length()) {
    return false;
  }
  // for loop iterates through first string and finds an index that is equal to
  // the second strings first index and then creates a substring that contains
  // the length of characters as the second string
  for (int i = 0; i < text.size(); i++) {
    string text_substring;
    text_substring.append(text.begin() + i,
                          text.begin() + i + pattern.length());
    if (StringCheck(text_substring, pattern) == true) {
      // if the substring and pattern are the same then the function returns
      // true showing that the second string is contained in the first string
      return true;
    }
  }
  return false;
}

// https://www.youtube.com/watch?v=XUmZcK44lsc
// function takes string and makes all the characters uppercase
string UppercaseString(string text) {
  string uppercase_text;
  for (int i = 0; i < text.size(); i++) {
    uppercase_text += toupper(text.at(i));
  }
  return uppercase_text;
}

// function takes two strings and a bool and if the second string is in the
// first string it returns true
bool ImprovedContains(const string &text_to_search,
                      const string &pattern_to_search,
                      const bool *case_insensitive) {
  // if the bool is false it means that we don't have to account for uppercase
  // and lowercase differences in characters so i call the findtext function
  if (*case_insensitive == false) {
    if (FindText(text_to_search, pattern_to_search) == true) {
      return true;
    }
    return false;
  }
  // since the bool is true we need to call the uppercasestring function first
  // to account for uppercase and lowercase differences in characters and then
  // call the findtext function to see if the second string is contained in the
  // first string
  else {
    string text_to_search_uppercase = UppercaseString(text_to_search);
    string pattern_to_search_uppercase = UppercaseString(pattern_to_search);
    if (FindText(text_to_search_uppercase, pattern_to_search_uppercase) ==
        true) {
      return true;
    }
    return false;
  }
}

// function takes two strings and counts how many times the second string is in
// the first string
int CountPatternsInText(string text, string pattern) {
  int count;
  count = 0;
  // for loop iterates through first string and finds an index that is equal to
  // the second strings first index and then creates a substring that contains
  // the length of characters as the second string
  for (int i = 0; i < text.length(); i++) {
    string text_substring;
    text_substring.append(text.begin() + i,
                          text.begin() + i + pattern.length());
    if (StringCheck(text_substring, pattern) == true) {
      // adds one to the count everytime the second string shows up in the first
      count++;
    }
  }
  return count;
}

// function takes two strings and a bool and counts how many times the second
// string is in the first
int ImprovedMatches(const string &text_to_search,
                    const string &pattern_to_search,
                    const bool *case_insensitive) {
  // if the bool is false it means that we don't have to account for uppercase
  // and lowercase differences in characters so i call the countpatternsintext
  // function
  if (*case_insensitive == false) {
    return CountPatternsInText(text_to_search, pattern_to_search);
  }
  // since the bool is true we need to call the uppercasestring function first
  // to account for uppercase and lowercase differences in characters and then
  // call the countpatternsintext function to see how many times the second
  // string is in the first
  else {
    string text_to_search_uppercase = UppercaseString(text_to_search);
    string pattern_to_search_uppercase = UppercaseString(pattern_to_search);
    return CountPatternsInText(text_to_search_uppercase,
                               pattern_to_search_uppercase);
  }
}

// function takes two strings and returns the index where the second string is
// found in the first
int IndexFound(string text, string pattern) {
  // if the second string is larger then the first then the -1 is returned
  // because there is no index value
  if (pattern.length() > text.length()) {
    return -1;
  }
  // for loop iterates through first string and finds an index that is equal to
  // the second strings first index and then creates a substring that contains
  // the length of characters as the second string
  for (int i = 0; i < text.length(); i++) {
    string text_substring;
    text_substring.append(text.begin() + i,
                          text.begin() + i + pattern.length());
    if (StringCheck(text_substring, pattern) == true) {
      // if the two strings are equal the position of the index where they're
      // first character is equal is returned
      return i;
    }
  }
  return -1;
}

// function takes two strings and a bool and returns the index where the second
// string is found in the first
int ImprovedFindFirstOf(const string &text_to_search,
                        const string &pattern_to_search,
                        const bool *case_insensitive) {
  // if the bool is false it means that we don't have to account for uppercase
  // and lowercase differences in characters so i call the indexfound function
  if (*case_insensitive == false) {
    return IndexFound(text_to_search, pattern_to_search);
  } else {
    // since the bool is true we need to call the uppercasestring function first
    // to account for uppercase and lowercase differences in characters and then
    // call the indexfound function to see what index the second string is found
    // at in the first string
    string text_to_search_uppercase = UppercaseString(text_to_search);
    string pattern_to_search_uppercase = UppercaseString(pattern_to_search);
    return IndexFound(text_to_search_uppercase, pattern_to_search_uppercase);
  }
}

// function takes three strings and replaces the first instance of the second
// string in the first string with the third string
string ReplacePattern(string text, string pattern, string replace) {
  if (pattern.length() > text.length()) {
    return text;
  }
  // for loop iterates through first string and finds an index that is equal to
  // the second strings first index and then creates a substring that contains
  // the length of characters as the second string
  for (int i = 0; i < text.length(); i++) {
    string text_substring;
    text_substring.append(text.begin() + i,
                          text.begin() + i + pattern.length());
    if (StringCheck(text_substring, pattern) == true) {
      // if the substring and second string are equal then the first instance of
      // the second string is replaced with the third string
      text.replace(i, pattern.length(), replace);
      break;
    }
  }
  return text;
}

// function takes 5 strings because its a helper function for the improved
// replace function that modifies the original text instead of the uppercase
// text
string IndexFound2(string &text, string text2, string pattern, string pattern2,
                   string replace) {
  if (IndexFound(text2, pattern2) > -1) {
    text.replace(IndexFound(text2, pattern2), pattern.length(), replace);
    return text;
  }
  return text;
}

// function takes three strings and a bool and replaces the first instance of
// the second string in the first string with the third string
void ImprovedReplace(string &text_to_search, const string &pattern_to_search,
                     const string &replace_pattern,
                     const bool *case_insensitive) {
  // if the bool is false it means that we don't have to account for uppercase
  // and lowercase differences in characters so i call the replacepattern
  // function
  if (*case_insensitive == false) {
    text_to_search =
        ReplacePattern(text_to_search, pattern_to_search, replace_pattern);
  } else {
    // since the bool is true we need to call the uppercasestring function first
    // to account for uppercase and lowercase differences in characters and then
    // call the replace pattern fucntion to replace the first instance of the
    // second string in the first string with the replace word
    string text_to_search_uppercase = UppercaseString(text_to_search);
    string pattern_to_search_uppercase = UppercaseString(pattern_to_search);
    IndexFound2(text_to_search, text_to_search_uppercase, pattern_to_search,
                pattern_to_search_uppercase, replace_pattern);
  }
}

// function takes two same length strings and returns the amount of times a
// character at the same index is different
int DifferenceInStrings(string string1, string string2) {
  int count;
  count = 0;
  // for loop iterates thorugh strings using charcheck and if the characters at
  // the same index are different then one is added to the variable count
  for (int i = 0; i < string1.length(); i++) {
    if (CharCheck(string1.at(i), string2.at(i)) == false) {
      count++;
    }
  }
  // count is returned
  return count;
}

// function takes two strings and a bool and checks to see how many characters
// are different between the two strings
int ImprovedNumberOfDifferences(const string &string1, const string &string2,
                                const bool &case_insensitive) {
  // if the bool is false it means that we don't have to account for uppercase
  // and lowercase differences in characters so i call the differenceinstring
  // function
  if (case_insensitive == false) {
    return DifferenceInStrings(string1, string2);
  }
  // since the bool is true we need to call the uppercasestring function first
  // to account for uppercase and lowercase differences in characters and then
  // call the differenceinstring funciton to see how many characters are
  // different between the two strings
  else {
    string string1_uppercase = UppercaseString(string1);
    string string2_uppercase = UppercaseString(string2);
    return DifferenceInStrings(string1_uppercase, string2_uppercase);
  }
}

int main() {
  std::cout << "Hello, World!";
  return 0;
}
