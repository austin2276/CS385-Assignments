/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Austin Kim
 * Date        : September 29, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

/* TODO: Return a vector of vectors of ints representing
 * the different combinations of ways to climb num_stairs
 * stairs, moving up either 1, 2, or 3 stairs at a time.
 */
vector< vector<int> > get_ways(int num_stairs) {
    vector< vector<int> >       vectorOfVectors;                            // Vector of Vectors of Ints.
    vector<int>                 vectorOfInts;                               // Vectors of Ints.

    if (num_stairs <= 0) {                                                  // From python code reference line #9
        vectorOfVectors.push_back(vectorOfInts);                            // From python code reference line #10
    }
    else {
        for (int i=1; i < 4; i++) {                                         // From python code reference line #12
            if (num_stairs >= i) {                                          // From python code reference line #13
                vector< vector<int> > result = get_ways(num_stairs - i);    // From python code reference line #14
                for (unsigned int j=0; j < result.size(); j++) {            // From python code reference line #15
                    result.at(j).push_back(i);                              // From python code reference line #16
                }
                vectorOfVectors.insert(vectorOfVectors.end(), result.begin(), result.end());    // From python code reference line #17
            }
        }
    }
    return vectorOfVectors;             // From python code reference line #18
}

// Simple Function to determine # of digits in integer.
int numberOfDigits(int number) {
    int length = 1;
    while (number /= 10) {
        length++;
    }
    return length;
}

/* TODO: Display the ways to climb stairs by iterating over
 * the vector of vectors and printing each combination.
 */
void display_ways(const vector< vector<int> > &ways) {
	for (unsigned int i=0; i < ways.size(); i++) {
		if (ways.size() > 9) {
			cout << setw(numberOfDigits(ways.size()));
		}
		cout << i + 1 << "." << " [";                                   // Prints the number of the next variation of steps taken.
		for (unsigned int j = ways[i].size() - 1; j > 0; j--) {
			cout << ways[i][j] << ", ";                                 // Prints step
		}
		cout << ways[i][0];                                             // Prints step
		cout << "]" << endl;                                            // Prints last closed bracket.
	}
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {                        // Executes if there are no input args or too many input args.
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;       // Error - Ends main function before printing output.
    }
    else {
        istringstream iss;      // Reads input
        iss.str(argv[1]);       // Gets inputted # of stair(s) 
        int numStairs;               // int var for checking/calculating

        if (!(iss >> numStairs) || !(numStairs > 0)) {  // Executes if argv[1] is not int or if argv[1] is not positive.
            cout << "Error: Number of stairs must be a positive integer." << endl;
            return 1;   // Error - Ends main function before printing output.
        }

        // Code for Adding "s" to "way_ to climb" stairs.
        int numWays = get_ways(numStairs).size();
        if (numWays == 1) {
            cout << numWays << " way to climb " << numStairs << " stair." << endl;      // singular way
        }
        else {
            cout << numWays << " ways to climb " << numStairs << " stairs." << endl;    // plural ways
        }

        display_ways(get_ways(numStairs));      // prints output string
        return 0;                               // ends main function
    }   
}
