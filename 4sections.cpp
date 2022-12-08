// Check for complete and partial overlap between pairs of intervals

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Check how many pairs of intervals overlap completely (one contains the other)
int part1() {
    ifstream infile("input.txt");
    int a1, a2, b1, b2;
    string s;
    char c;
    int count = 0;

    while (infile >> s) {
        istringstream iss(s);

        iss >> a1 >> c >> a2 >> c >> b1 >> c >> b2;

        // If one interval contains the other
        if ((a1 >= b1 && a2 <= b2) || (a1 <= b1 && a2 >= b2)) {
            count++;
        }
    }
    
    return count;
}

// Check how many pairs of intervals overlap at all
int part2() {
    ifstream infile("input.txt");
    int a1, a2, b1, b2;
    string s;
    char c;
    int count = 0;
    int total = 0;

    while (infile >> s) {
        istringstream iss(s);

        iss >> a1 >> c >> a2 >> c >> b1 >> c >> b2;

        // If intervals don't overlap at all
        if (a1 > b2 || a2 < b1) {
            count++;
        }

        total++;
    }
    
    return total - count;
}

int main() {
    cout << part1() << endl;
    cout << part2() << endl;
}