// Modify pairs of numbers, one tracking another

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <chrono>

using namespace std;

// Code for hashing a pair
struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first*31 + v.second;
    }
};

// Modify head position
void move_head(char dir, pair<int, int>& head) {
    if (dir == 'L') {
        head.second -= 1;
    }
    else if (dir == 'R') {
        head.second += 1;
    }
    else if (dir == 'U') {
        head.first -= 1;
    }
    else if (dir == 'D') {
        head.first += 1;
    }
}

// Modify one knot based on previous knot
void move_knot(pair<int, int>& knot1, pair<int, int>& knot2) {
    // If either position difference by 2 or more
    if (abs(knot1.first - knot2.first) >= 2 or abs(knot1.second - knot2.second) >= 2) {
        // If same row, change knot2 column
        if (knot1.first == knot2.first) {
            if (knot1.second > knot2.second) {
                knot2.second += 1;
            }
            else {
                knot2.second -= 1;
            }
        }
        // If same column, change knot2 row
        else if (knot1.second == knot2.second) {
            if (knot1.first > knot2.first) {
                knot2.first += 1;
            }
            else {
                knot2.first -= 1;
            }
        }

        // Otherwise move knot2 diagonally (change row and column)
        else {
            if (knot1.first > knot2.first and knot1.second > knot2.second) {
                knot2.first += 1;
                knot2.second += 1;
            }
            else if (knot1.first < knot2.first and knot1.second > knot2.second) {
                knot2.first -= 1;
                knot2.second += 1;
            }
            else if (knot1.first > knot2.first and knot1.second < knot2.second) {
                knot2.first += 1;
                knot2.second -= 1;
            }
            else if (knot1.first < knot2.first and knot1.second < knot2.second) {
                knot2.first -= 1;
                knot2.second -= 1;
            }
        }
    }
}

// Modify 2 tracking knots
int part1() {
    ifstream infile("input.txt");
    char dir;
    int steps;

    // Head and tail starting position
    pair<int, int> head (0, 0);
    pair<int, int> tail (0, 0);

    // Track coordinates that the tail goes to
    unordered_set<pair<int, int>, pair_hash> coords;
    coords.insert(make_pair(0, 0));

    while (infile >> dir >> steps) {
        for (int i = 0; i < steps; i++) {
            move_head(dir, head);

            move_knot(head, tail);

            // Track coordinates that the tail goes to
            coords.insert(tail);
        }
    }

    return coords.size();
}

// Modify 10 tracking knots
int part2() {
    ifstream infile("input.txt");
    char dir;
    int steps;

    // Vector of 10 knots
    vector<pair<int, int>> knots;
    for (int i = 0; i < 10; i++) {
        knots.push_back(make_pair(0, 0));
    }

    // Track coordinates that the tail goes to
    unordered_set<pair<int, int>, pair_hash> coords;
    coords.insert(make_pair(0, 0));

    while (infile >> dir >> steps) {
        for (int i = 0; i < steps; i++) {
            // Move head then next 9 knots
            move_head(dir, knots[0]);

            for (int i = 0; i < 9; i++) {
                move_knot(knots[i], knots[i+1]);
            }
            
            // Track coordinates that the tail goes to
            coords.insert(knots[9]);
        }
    }

    return coords.size();
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