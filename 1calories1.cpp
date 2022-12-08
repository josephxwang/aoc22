#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int curr = 0;
    int max = 0;

    ifstream infile("input.txt");
    string line;

    while (getline(infile, line)) {
        // For empty line, compare to max
        if (line.empty()) {
            if (curr > max) {
                max = curr;
            }

            curr = 0;
        }
        // Otherwise add to curr
        else {
            curr += stoi(line);
        }
    }

    if (curr > max) {
        max = curr;
    }

    cout << max << endl;
}