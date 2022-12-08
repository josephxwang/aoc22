#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int part1() {
    int score = 0;
    string s1, s2;

    // Scores of each combination
    unordered_map<string, int> scores = {
        {"AX", 4},
        {"AY", 8},
        {"AZ", 3},
        {"BX", 1},
        {"BY", 5},
        {"BZ", 9},
        {"CX", 7},
        {"CY", 2},
        {"CZ", 6},
    };

    ifstream infile("input.txt");

    while (infile >> s1 >> s2) {
        string s = s1 + s2;

        score += scores[s];
    }

    return score;
}

int part2() {
    int score = 0;
    string s1, s2;

    // Scores of each combination
    unordered_map<string, int> scores = {
        {"AX", 3},
        {"AY", 4},
        {"AZ", 8},
        {"BX", 1},
        {"BY", 5},
        {"BZ", 9},
        {"CX", 2},
        {"CY", 6},
        {"CZ", 7},
    };

    ifstream infile("input.txt");

    while (infile >> s1 >> s2) {
        string s = s1 + s2;

        score += scores[s];
    }

    return score;
}

int main() {
    cout << part1() << endl;
    cout << part2() << endl;
}