/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Austin Kim
 * Date        : 9/20/2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
using namespace std;

/* 
 * TODO: returns true if all characters in string
 * are lowercase letters in the English alphabet; 
 * false otherwise. 
 */
bool is_all_lowercase(const string &s) {
    for (unsigned int i = 0; i < s.length(); i++) {     // Iterates through string s.
        if (!islower(s[i])) {                           // Executes if s[i] is NOT lowercase.
            return false;                               // Returns false because uppercase found.
        }
    }
    return true;    // Returns true after finishing for loop since no uppercase was found.
}

/*
 * TODO: returns true if all letters in string are unique,
 * that is no duplicates are found; false otherwise.
 * You may use only a single int for storage and
 * work with bitwise and bitshifting operators.
 * 
 * No credit will be given for other solutions.
 */
bool all_unique_letters(const string &s) {
    unsigned int temp = 0;
    for (unsigned int i = 0; i < s.length(); i++) {      // Iterates through string s.
        int letter = s[i] - 97;                          // ASCII Characters (a-z) = (97 - 122).
        if ( ((temp >> letter) & 1) == 1) {              // Bitshift temp to right by position, pairwise AND resutl with 1, check if equal to 1.
            return false;                                // Executes if duplicate letter/(1) found
        }
        temp |= 1 << letter;                             // Bitwise OR operator on temp | (1 << letter).
    }
    return true;                                         // Executes after entire for loop finds no duplicate
}

/* 
 * TODO: reads and parses command line arguments.
 * Calls other functions to produce correct output.
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {                                            // Executes if incorrect command line input.
        cout << "Usage: ./unique <string>" << endl;
    }
    else {
        if (is_all_lowercase(string(argv[1])) == false) {       // Executes if string is NOT all lowercase.
            cout << "Error: String must contain only lowercase letters." << endl;
        }
        else {
            if (all_unique_letters(string(argv[1])) == false) { // Executes if string is NOT all lowercase
                cout << "Duplicate letters found." << endl;
            }
            else {                                              // Executes if string is ALL lowercase.
                cout << "All letters are unique." << endl;      // Executes if successful.
            }
        }
    }
}
