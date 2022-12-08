#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

// Check for first 4 unique consecutive characters in string
int part1() {
    ifstream infile("input.txt");

    string s;
    unordered_set<char> chars;

    infile >> s;

    for (int i = 3; i < s.length(); i++) {
        unordered_set<char> chars;

        // Add past 4 characters to set
        chars.insert(s[i-3]);
        chars.insert(s[i-2]);
        chars.insert(s[i-1]);
        chars.insert(s[i]);

        if (chars.size() == 4) {
            return i+1;
        }
    }
    
    return 0;
}

// Check for first 14 unique consecutive characters in string
int part2() {
    ifstream infile("input.txt");

    string s;
    unordered_set<char> chars;

    infile >> s;

    for (int i = 13; i < s.length(); i++) {
        unordered_set<char> chars;

        // Add past 14 characters to set
        for (int j = 0; j < 14; j++){
            chars.insert(s[i-j]);
        }
        
        if (chars.size() == 14) {
            return i+1;
        }
    }
        
    return 0;
}

int main() {
    cout << part1() << endl;
    cout << part2() << endl;
}