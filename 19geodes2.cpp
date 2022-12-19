#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>

using namespace std;

int part1() {
    ifstream infile("input.txt");
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

    vector<int> geodes;

    for (auto blueprint : blueprints) {
        vector<int> current_geodes;

        // For different amounts of ore robots
        for (int ore_rob_count = 1; ore_rob_count < 5; ore_rob_count++) {
            vector<int> robots = {1,0,0,0};
            vector<int> minerals = {0,0,0,0};
            
            // For 24 minutes
            for (int i = 0; i < 24; i++) {
                vector<int> new_robots = {0,0,0,0};

                // Buy ore robots first until hit limit
                if (robots[0] < ore_rob_count) {
                    if (minerals[0] >= blueprint[0][0]) {
                        robots[0]++;
                        new_robots[0]++;
                        minerals[0] -= blueprint[0][0];
                    }
                }
                else {
                    // If can buy geode robot
                    if (minerals[0] >= blueprint[3][0] and minerals[2] >= blueprint[3][2]) {
                        robots[3]++;
                        new_robots[3]++;
                        minerals[0] -= blueprint[3][0];
                        minerals[2] -= blueprint[3][2];
                    }

                    // Check if need to save ore for future geode robots
                    // If within 2 turns of having enough obsidian and don't have enough ore
                    if (blueprint[3][2] > minerals[2] 
                        and blueprint[3][2] - minerals[2] <= robots[2] * 2 
                        and blueprint[3][0] > (minerals[0] - blueprint[2][0] + robots[0])) {
                        
                    }
                    // Or if past minute 21 (only buy before or at minute 21)
                    else if (i > 20) {

                    }
                    // Otherwise buy obsidian robots
                    else {
                        if (minerals[0] >= blueprint[2][0] and minerals[1] >= blueprint[2][1]) {
                            robots[2]++;
                            new_robots[2]++;
                            minerals[0] -= blueprint[2][0];
                            minerals[1] -= blueprint[2][1];
                        }
                    }

                    // Check if need to save ore for future obsidian robots
                    if (blueprint[2][1] > minerals[1] 
                        and blueprint[2][1] - minerals[1] <= robots[1] * 2 
                        and blueprint[2][0] > (minerals[0] - blueprint[1][0] + robots[0])) {

                    }
                    // Or if past minute 17 (only buy before or at minute 17), this is a guess
                    else if (i > 16) {

                    }
                    // Otherwise buy clay robots
                    else {
                        if (minerals[0] >= blueprint[1][0]) {
                            robots[1]++;
                            new_robots[1]++;
                            minerals[0] -= blueprint[1][0];
                        }
                    }
                }

                // Add minerals
                for (int j = 0; j < robots.size(); j++) {
                    minerals[j] += (robots[j] - new_robots[j]);
                }
            }

            current_geodes.push_back(minerals[3]);
        }
        

        // Find max geodes possible with different number of ore robots
        int max_geodes = 0;

        for (int geode : current_geodes) {
            if (geode > max_geodes) {
                max_geodes = geode;
            }
        }
        
        geodes.push_back(max_geodes);
    }

    int quality = 0;
    for (int i = 0; i < geodes.size(); i++) {
        quality += (i+1) * geodes[i];
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