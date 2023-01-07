#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// // Tristate enum
// enum tristate {
//     null = -1,
//     false,
//     true
// };

// Check if s[i] is a number
bool isNum(int i, string s) {
    if (s[i] != ',' and s[i] != '[' and s[i] != ']') {
        return true;
    }
    else {
        return false;
    }
}

// Find the next number or '[', where the recursive function should start
int findNextStart(int i, string s) {
    while (s[i] == ',' or s[i] == ']') {
        // If reached end of string
        if (i+1 == s.size()) {
            return -1;
        }
        i++;
    }
    return i;
}

// Check if pair is legitimate given indices
bool recPair(int& i, int& j, string p1, string p2) {
    // If both are lists
    if (p1[i] == '[' && p2[j] == '[') {
        i++;
        j++;
        
        return recPair(i, j, p1, p2);
    }
    // If p1 is a list and p2 isn't
    else if (p1[i] == '[' && p2[j] != '[') {
        // Convert the other value and compare
        i++;

        return recPair(i, j, p1, p2);
    }
    else if ((p1[i] != '[' && p2[j] == '[')) {) {
        j++;

        return recPair(i, j, p1, p2);
    }
    // Otherwise compare two integers
    else {
        // Parse both integers
        int n1, n2;

        if (!isNum(i+1, p1)) {
            n1 = stoi(p1[i]);
            i = findNextStart(i+1, p1);
        }
        // If int takes two positions
        else if (!isNum(i+1, p1)) {
            n1 = stoi(p1.substr(i, 2));
            i = findNextStart(i+2, p1);
        }

        if (!isNum(j+1, p2)) {
            n2 = stoi(p2[j]);
            j = findNextStart(j+1, p2);
        }
        // If int takes two positions
        else if (!isNum(j+2, p2)) {
            n2 = stoi(p2.substr(j, 2));
            j = findNextStart(j+2, p2);
        }

        // Compare two integers
        if (n1 < n2) {
            return true;
        }
        else if (n1 > n2) {
            return false;
        }

        // If same, continue
        // If reached end of p1
        if (i == -1) {
            return true;
        }
        // If reached end of p2
        else if (j == -1) {
            return false;
        }
        
        return recPair(i, j, p1, p2);
    }
}

int part1() {
    ifstream infile("test.txt");
    int sum = 0;
    int pair = 1;

    string line;
    string p1, p2;

    while (getline(infile, p1)) {
        getline(infile, p2);

        // Consume empty line
        getline(infile, line);

        if (recPair(0, 0, p1, p2)) {
            sum += pair;
        }

        // Increment pair count
        pair++;
    }

    return sum;
}

int part2() {
    ifstream infile("test.txt");
    
    return 0;
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    cout << part1() << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Part 1: " << duration.count() << " us" << endl;

    start = chrono::high_resolution_clock::now();
    cout << part2() << endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Part 2: " << duration.count() << " us" << endl;
}