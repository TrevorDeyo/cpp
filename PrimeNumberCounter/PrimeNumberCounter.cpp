#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace chrono;

bool check_prime(int);

void update_progress(int current, int total);

int main() {

    int counter{};
    int totalNumbers{};
    char quit{};

    cout << "Enter the range you want to search for prime numbers (min 100): ";
    cin >> totalNumbers;

    auto start = high_resolution_clock::now();

        for (int i = 0; i < totalNumbers; i++) {
            if (check_prime(i)) {
                // cout << i << endl;
                counter++;
            }

            // Update progress bar every 1% of total numbers
            if (i % (totalNumbers / 100) == 0) {
                update_progress(i, totalNumbers);
            }
        }

    cout << "\nThere are " << counter << " prime numbers out of " << totalNumbers << endl;

    auto stop = high_resolution_clock::now();
    auto duration_ms = duration_cast<milliseconds>(stop - start);
    auto duration_s = duration_cast<seconds>(stop - start);

    cout << "Program took: " << duration_ms.count() << " milliseconds" << endl;
    cout << "Program took: " << duration_s.count() << " seconds" << endl;

    
    do {
        cout << "enter 'q' to quit..." << endl;
        cin >> quit;
    } while (quit != 'q');

    return 0;
}

bool check_prime(int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

void update_progress(int current, int total) {
    int progress = (static_cast<double>(current) / total) * 100;
    cout << "\rProgress: [" << setw(3) << progress << "%] " << flush;
}
