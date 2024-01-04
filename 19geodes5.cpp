#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

// Custom += operator for vectors for element-wise addition
template <typename T>
void operator+=(vector<T> &a, vector<T> &b) {
    transform(a.begin(), a.end(), b.begin(), a.begin(), plus<T>());
}

// Custom + operator for vectors for element-wise addition
template <typename T>
vector<T> operator+(vector<T> &a, vector<T> &b) {
    vector<T> result(a.size(), 0);
    transform(a.begin(), a.end(), b.begin(), result.begin(), plus<T>());
    return result;
}

// Custom - operator for vectors for element-wise addition
template <typename T>
vector<T> operator-(vector<T> &a, vector<T> &b) {
    vector<T> result(a.size(), 0);
    transform(a.begin(), a.end(), b.begin(), result.begin(), minus<T>());
    return result;
}


void rec_crack_geodes(int time, vector<int> robots, vector<int> minerals, vector<vector<int>> &blueprint, int &max_geode) {
    // If out of time, check geodes
    if (time == 0) {
        int curr_geode = minerals[3];

        if (curr_geode > max_geode) {
            max_geode = curr_geode;

            cout << max_geode << endl;
        }

        return;
    }

    // Add minerals
    minerals += robots;

    // Try to buy each robot
    for (int rob_i = 0; rob_i < 4; rob_i++) {
        vector<int> new_robots = {0,0,0,0};

        // Check each mineral requirement
        bool can_buy = true;
        for (int min_i = 0; min_i < 4; min_i++) {
            if (minerals[min_i] - robots[min_i] < blueprint[rob_i][min_i]) {
                can_buy = false;
                break;
            }
        }

        // Buy robot
        if (can_buy) {
            new_robots[rob_i]++;

            // Do recursive call, adding new robots and subtracting new robot mineral cost
            rec_crack_geodes(time-1, robots + new_robots, minerals - blueprint[rob_i], blueprint, max_geode);
        }
    }

    // Do nothing
    rec_crack_geodes(time-1, robots, minerals, blueprint, max_geode);
}

int part1() {
    ifstream infile("19test.txt");
    string line;

    // Save robot costs
    vector<vector<vector<int>>> blueprints;

    int i = 0;

    while (getline(infile, line)) {
        blueprints.push_back({});

        istringstream iss(line);
        char c;
        int n1, n2;

        iss >> n1 >> c;

        // Ore robot
        iss >> n1 >> c;
        blueprints[i].push_back({n1,0,0,0});

        // Clay robot
        iss >> n1 >> c;
        blueprints[i].push_back({n1,0,0,0});

        // Obsidian robot
        iss >> n1 >> n2 >> c;
        blueprints[i].push_back({n1,n2,0,0});

        // Geode robot
        iss >> n1 >> n2 >> c;
        blueprints[i].push_back({n1,0,n2,0});

        i++;
    }

    // Run each blueprint
    int quality = 0;
    for (int j = 0; j < blueprints.size(); j++) {
        int max_geode = 0;
        rec_crack_geodes(32, {1,0,0,0}, {0,0,0,0}, blueprints[j], max_geode);
        quality += (j+1) * max_geode;
    }

    return quality;
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