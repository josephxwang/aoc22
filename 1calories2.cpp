#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    int curr = 0;
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;

    ifstream infile("input.txt");
    string s;

    while (getline(infile, s)) {
        // For empty line, compare to top 3 maxes
        if (s.empty()) {
            if (curr >= max3) {
                max1 = max2;
                max2 = max3;
                max3 = curr;
            }
            else if (curr >= max2) {
                max1 = max2;
                max2 = curr;
            }
            else if (curr >= max1) {
                max1 = curr;
            }

            curr = 0;
        }
        // Otherwise add to curr
        else {
            curr += stoi(s);
        }
    }

    if (curr >= max3) {
        max1 = max2;
        max2 = max3;
        max3 = curr;
    }
    else if (curr >= max2) {
        max1 = max2;
        max2 = curr;
    }
    else if (curr >= max1) {
        max1 = curr;
    }

    cout << max1 + max2 + max3 << endl;
}