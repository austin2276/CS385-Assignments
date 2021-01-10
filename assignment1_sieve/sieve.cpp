/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Austin Kim
 * Date        : September 11, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    // Constructor
    PrimesSieve(int limit);

    // The "~" is a deconstructor which frees memory on the heap.
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    // Getter
    int num_primes() const {
        return num_primes_;
    }

    // Public Method (Implemented Below)
    void display_primes() const;


private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    int maxPrimeGetter() const;
    void sieve();
    static int num_digits(int num);

    

};

// Notation: "ClassName::MethodName"
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
    num_primes_ = count_num_primes();
    max_prime_ = maxPrimeGetter();
    
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);
    int itemsInRow = 0;

    if (num_primes_ > primes_per_row) {
        for(int i = 2; i <= limit_; i++) {
        	if(itemsInRow < primes_per_row - 1) {
                if (is_prime_[i] == true) {
                    if (i < max_prime_) {
                        cout  << setw(max_prime_width) << i << " ";
        				itemsInRow++;
                    }
                    else {
                        cout << setw(max_prime_width) << i;
        				itemsInRow++;
                    }
                }
        	}
            else if(itemsInRow == primes_per_row - 1) {
                if (is_prime_[i] == true) {
                    if (i < max_prime_) {
                        cout  << setw(max_prime_width) << i;
        				itemsInRow++;
                    }
                    else {
                        cout << setw(max_prime_width) << i;
        				itemsInRow++;
                    }
                }
        	}
        	else {
        		itemsInRow = 0;
        		cout << endl;
        	}
        }
        cout << endl;
    }
    else {
        for(int i = 2; i <= limit_; i++) {
        	if (is_prime_[i] == true) {
        		cout << i;
        	}
        	int itemsInRow = 0;
        	if(is_prime_[i+1] == true) {
        		cout << " ";
        		itemsInRow++;
        	}
        	else {
        		itemsInRow = 0;
        	}
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int count = 0;
    for (int i=2; i<=limit_; i++) {
        if (is_prime_[i] == true) {
            count++;
        }
    }
    return count;
}

int PrimesSieve::maxPrimeGetter() const {
    int maxPrime = 0;
    for (int i=2; i<=limit_; i++) {
        if (is_prime_[i] == true) {
            maxPrime = i;
        }
    }
    return maxPrime;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm

    for (int i = 0; i <= limit_; i++) {
        is_prime_[i] = true;
    }

    is_prime_[0] = false;
    is_prime_[1] = false;

    for (int i=2; i<=sqrt(limit_); i++) {
        if (is_prime_[i] == true) {
            for (int j=i*i; j<=limit_; j+=i) {
                is_prime_[j] = false;
            }
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int numberOfDigits = 1;
    while (num/10 != 0) {
        num = num/10;
        numberOfDigits++;
    }
    return numberOfDigits;
}

int main() {
    
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieve(limit);
    cout << endl;
    cout << "Number of primes found: " << sieve.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    sieve.display_primes();

    return 0;
}
