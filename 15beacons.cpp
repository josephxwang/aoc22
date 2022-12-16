// Given a couple of diamonds, figure out how they intersect a target row
// And which square they don't cover

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

struct sensor {
    int r;
    int c;
    int rad;
};

// Merge intervals
vector<pair<int, int>> merge_intervals(vector<pair<int, int>> intervals) {
    vector<pair<int, int>> merged;
    pair<int, int> curr = intervals[0];
    int i = 1;
    pair<int, int> next = intervals[i];
    
    while (i < intervals.size()-1) {
        
        // While two intervals overlap
        while (curr.second >= next.first-1) {
            if (i > intervals.size()-2) {
                break;
            }

            // Merge
            curr.second = max(curr.second, next.second);
            i++;

            next = intervals[i];
        }

        if (i > intervals.size()-2) {
            break;
        }
        
        merged.push_back(curr);
        curr = next;
        i++;
        next = intervals[i];
    }

    // Check last 2 intervals
    // If overlap
    if (curr.second >= next.first-1) {
        curr.second = max(curr.second, next.second);
        merged.push_back(curr);
    }
    else {
        merged.push_back(curr);
        merged.push_back(next);
    }

    return merged;
}

// Check how a couple of diamonds intersect with a target row
int part1() {
    ifstream infile("input.txt");
    string line;
    int cs, rs, cb, rb;

    int target_row = 2000000;

    vector<pair<int, int>> intervals;

    while (getline(infile, line)) {
        istringstream iss(line);

        iss >> cs >> rs >> cb >> rb;

        // Find radius of sensor (Manhattan distance)
        int rad = abs(cs - cb) + abs(rs - rb);

        // If can reach target row
        if (rad >= abs(target_row - rs)) {
            int range = rad - abs(target_row - rs);

            intervals.push_back({cs - range, cs + range});
        }
    }

    // Sort intervals
    sort(intervals.begin(), intervals.end());

    // Merge intervals (eliminate overlap)
    vector<pair<int, int>> merged = merge_intervals(intervals);

    // Count intervals
    int count = 0;
    for (int i = 0; i < merged.size(); i++) {
        count += merged[i].second - merged[i].first;
    }

    // for (int i = 0; i < merged.size(); i++) {
    //     cout << merged[i].first << ' ' << merged[i].second << endl;
    // }
    // cout << endl;

    return count;
}

// Check which one square is not covered by some diamonds
int part2() {
    ifstream infile("input.txt");
    string line;

    int bound = 4000000;
    int cs, rs, cb, rb;

    // Vector of all sensors
    vector<sensor> sensors;
    int i = 0;

    // Get all sensors
    while (getline(infile, line)) {
        istringstream iss(line);

        iss >> cs >> rs >> cb >> rb;

        // Find radius of sensor (Manhattan distance)
        int rad = abs(cs - cb) + abs(rs - rb);

        sensors.push_back(sensor());
        sensors[i].r = rs;
        sensors[i].c = cs;
        sensors[i].rad = rad;

        i++;
    }

    int x;
    int y;
     
    // Check all rows
    for (int r = 0; r < bound; r++) {
        vector<pair<int, int>> intervals;

        // Check all sensors
        for (auto curr : sensors) {
            // If can reach target row
            if (curr.rad >= abs(r - curr.r)) {
                int range = curr.rad - abs(r - curr.r);

                intervals.push_back({curr.c - range, curr.c + range});
            }
        }

        // Sort intervals
        sort(intervals.begin(), intervals.end());

        // Merge intervals (eliminate overlap)
        vector<pair<int, int>> merged = merge_intervals(intervals);

        // Check if merged intervals span area
        bool doesSpan = false;
        for (auto curr : merged) {
            // If an interval spans the bound
            if (curr.second >= bound and curr.first <= 0) {
                doesSpan = true;
                break;
            }
        }

        // Print out row that isn't spanned
        if (not doesSpan) {
            y = r;
            cout << "r: " << r << endl;
        }
    }

    // Check all columns
    for (int c = 0; c < bound; c++) {
        vector<pair<int, int>> intervals;

        // Check all sensors
        for (auto curr : sensors) {
            // If can reach target row
            if (curr.rad >= abs(c - curr.c)) {
                int range = curr.rad - abs(c - curr.c);

                intervals.push_back({curr.r - range, curr.r + range});
            }
        }

        // Sort intervals
        sort(intervals.begin(), intervals.end());

        // Merge intervals (eliminate overlap)
        vector<pair<int, int>> merged = merge_intervals(intervals);

        // Check if merged intervals span area
        bool doesSpan = false;
        for (auto curr : merged) {
            // If an interval spans the bound
            if (curr.second >= bound and curr.first <= 0) {
                doesSpan = true;
                break;
            }
        }

        // Print out column that isn't spanned
        if (not doesSpan) {
            x = c;
            cout << "c: " << c << endl;
        }
    }

    cout << x << ' ' << y << endl;
        
    return x * 4000000 + y;
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