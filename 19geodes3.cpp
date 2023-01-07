#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

// @@ MEMOIZE?
void rec_geodes(int& count, int time, vector<int> robots, vector<int> minerals, vector<vector<int>>& blueprint, int& max_geode) {
    // Recursion limit
    if (count > 100000000) {
        return;
    }
    
    if (time == 0) {
        int curr_geode = minerals[3];

        if (curr_geode > max_geode) {
            max_geode = curr_geode;
            // cout << max_geode << endl;
        }

        return;
    }

    // Add minerals
    for (int i = 0; i < robots.size(); i++) {
        minerals[i] += robots[i];
    }

    // Recursively try all options

    // Try to buy each robot, starting from geode robot to obsidian robot (already bought ore robots)
    for (int rob_i = robots.size()-1; rob_i >= 1; rob_i--) {
        // Check each mineral requirement
        bool can_buy = true;
        for (int min_i = 0; min_i < blueprint[rob_i].size(); min_i++) {
            if (minerals[min_i] - robots[min_i] < blueprint[rob_i][min_i]) {
                can_buy = false;
                break;
            }
        }

        // Buy robot
        if (can_buy) {
            robots[rob_i]++;
            for (int min_i = 0; min_i < blueprint[rob_i].size(); min_i++) {
                minerals[min_i] -= blueprint[rob_i][min_i];
            }
            
            count++;
            rec_geodes(count, time-1, robots, minerals, blueprint, max_geode);

            // Reset values
            robots[rob_i]--;
            for (int min_i = 0; min_i < blueprint[rob_i].size(); min_i++) {
                minerals[min_i] += blueprint[rob_i][min_i];
            }
        }
    }

    // Don't do anything
    count++;
    rec_geodes(count, time-1, robots, minerals, blueprint, max_geode);
}

int part1() {
    ifstream infile("19test2.txt");
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

    vector<int> max_geodes;

    for (auto blueprint : blueprints) {
        
        // cout << endl << "NEW ROBOT" << endl; 
        
        // int ore_rob = 3;

        vector<int> current_geodes = {};
        
        // Simulate starting with different numbers of ore robots
        // Max ore robots needed is 4 to maintain production, max ore cost is 4
        for (int ore_robs = 1; ore_robs <= 4; ore_robs++) {
            int max_geode = 0;
            int count = 0;

            vector<int> robots = {1,0,0,0};
            vector<int> minerals = {0,0,0,0};
            int time = 24;

            // Buy ore robots first
            while (robots[0] < ore_robs) {
                // Add ore
                minerals[0] += robots[0];

                // If can buy ore robot
                if (minerals[0] - robots[0] >= blueprint[0][0]) {
                    robots[0]++;
                    minerals[0] -= blueprint[0][0];
                }

                time--;
            }

            cout << "Starting ore robots: " << robots[0] << endl;
            rec_geodes(count, time, robots, minerals, blueprint, max_geode);
            cout << max_geode << endl;
            current_geodes.push_back(max_geode);
        }

        int curr_max = *max_element(current_geodes.begin(), current_geodes.end());

        cout << curr_max << endl;

        max_geodes.push_back(curr_max);
    }

    int quality = 0;
    for (int i = 0; i < max_geodes.size(); i++) {
        quality += (i+1) * max_geodes[i];
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