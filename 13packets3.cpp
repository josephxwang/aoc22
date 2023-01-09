#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

vector<vector<vector<vector<vector<int>>>>> stolist(string s) {
    vector<vector<vector<vector<vector<int>>>>> l;
    for (char c : s) {
        if (c == '[') {
            l.push_back({});
        }
        else if (c == ']') {
            depth--;
        }
    }
}

// Try recursive list approach instead of string approach
int part1() {
    ifstream infile("input.txt");
    
    int sum = 0;
    int pair_i = 1;

    int max_depth = 0;

    string line;
    string p1, p2;

    while (getline(infile, p1)) {
        getline(infile, p2);

        // Consume empty line
        getline(infile, line);

        int depth = 0;
        for (char c : p1) {
            if (c == '[') {
                depth++;
            }
            else if (c == ']') {
                depth--;
            }

            if (depth > max_depth) {
                max_depth = depth;
            }
        }

        depth = 0;
        for (char c : p2) {
            if (c == '[') {
                depth++;
            }
            else if (c == ']') {
                depth--;
            }

            if (depth > max_depth) {
                max_depth = depth;
            }
        }

        // if (recPair(0, 0, p1, p2)) {
        //     sum += pair_i;
        // }

        // Increment pair count
        pair_i++;
    }

    cout << max_depth << endl;


    return 0;
}

int part2() {
    ifstream infile("test.txt");
    string line;

    while (getline(infile, line)) {
    
    }

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