/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Austin Kim
 * Version     : 1.0
 * Date        : 10/21/2019
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. - Austin Kim
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

/**
 * REMEMBER!!!
 * Next time, make sure each function returns correct data type.
 * Ex: don't return an int for the sorting methods.
 */


// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {           // slow iterative use of inversion counting using nested loops (doesn't use merge sort)
    long numberOfInversions = 0;
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] > array[j]) {
                numberOfInversions++;
            }
        }
    }
    return numberOfInversions;
}

/**
 * Using Borowski's pseudocode for Mergesort  https://sit.instructure.com/courses/32949/pages/pseudocode-for-mergesort?module_item_id=760191
 */
static long mergesort(int array[], int scratch[], int low, int high) {
    long numberOfInversions = 0;
    if (low < high) {
        int mid = low + (high - low) / 2;
        numberOfInversions += mergesort(array, scratch, low, mid);
        numberOfInversions += mergesort(array, scratch, mid + 1, high);
        int L = low;
        int H = mid + 1;
    	for (int k = low; k <= high; k++) {
    		if (L <= mid && (H > high || array[L] <= array[H])) {
    			scratch[k] = array[L];
    			L++;
    		} else {
                numberOfInversions += mid - L + 1;
    			scratch[k] = array[H];
    			H++;
    		}
    	}
    	for (int k = low; k <= high; k++) {
			array[k] = scratch[k];
    	}
    }
    return numberOfInversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {       // fast use of inversion counting
    int *values = new int[length];
    long numberOfInversions = mergesort(array, values, 0, length - 1);
    delete[] values;            // prevents memory leaks
    return numberOfInversions;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {                                                 // only "./inversioncounter" OR "./inversioncounter slow" is allowed.
        cout << "Usage: ./inversioncounter [slow]";                 // correct use of slow mode.
        return 1;                                                   // ERROR ENDS MAIN
    }

    bool slow = 0;                                                  // Set initial check for "slow" input arg as false.

    if(argv[1] != NULL) {                                           // Executes if there is something after first argument
        if (strcmp(argv[1], "slow") == 0) {                         // Executs if that something is the string "slow"
            slow = 1;
        }
        else {                                                      // Executes if that something is not the string "slow"
            cout << "Error: Unrecognized option '" << argv[1] << "'.";  // Error that "slow" isn't in correct form
            return 1;  
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output

    if (values.empty()) {
        cout << "Error: Sequence of integers not received.";
        return 1;
    }
    else {
        if (slow == 1) {    // "slow" input arg called.
            cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size());
        }
        else {              // "slow" input arg NOT called
            cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size());
        }
    }

    return 0;
}
