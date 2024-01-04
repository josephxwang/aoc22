#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <unordered_set>
#include <numeric>

using namespace std;

// Custom * operator for vectors for element-wise multiplication
// template <typename T>
// void operator*(vector<T> &a, vector<T> &b) {
//     transform(a.begin(), a.end(), b.begin(), a.begin(), multiplies<T>());
// }

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

// Custom - operator for vectors for element-wise subtraction
template <typename T>
vector<T> operator-(vector<T> &a, vector<T> &b) {
    vector<T> result(a.size(), 0);
    transform(a.begin(), a.end(), b.begin(), result.begin(), minus<T>());
    return result;
}

// struct pair_hash {
//     inline size_t operator()(pair<vector<int>,vector<int>>& v) const {
//         vector<int> primes1 = {2, 3, 5, 7};
//         vector<int> primes2 = {11, 13, 17, 19};

//         vector<int> products1 = v.first * primes1;
//         vector<int> products2 = v.second * primes2;
//         return  + v.second * primes2;
//     }
// };

// Code for hashing a pair of vector<int>
struct pair_hash {
    size_t operator()(const pair<vector<int>, vector<int>>& p) const {
        size_t hash_val = 0;
        
        for (int i = 0; i < 4; ++i) {
            hash_val |= (p.first[i] << (i * 8));
            hash_val |= (p.second[i] << (i * 8 + 16));
        }
        
        return hash_val;
    }
};


int crack_geodes(int time, vector<vector<int>> &blueprint) {
    unordered_set<pair<vector<int>, vector<int>>, pair_hash> curr_q = {{{1,0,0,0},{0,0,0,0}}};
    unordered_set<pair<vector<int>, vector<int>>, pair_hash> next_q = {};

    int max_geode = 0;
    
    // vector<int> robots = {1,0,0,0};
    // vector<int> minerals = {0,0,0,0};

    // vector<int> new_robots = {0,0,0,0};

    // BFS each minute
    while (time > 0) {
        for (auto curr : curr_q) {
            vector<int> robots = curr.first;
            vector<int> minerals = curr.second;

            // Add minerals
            minerals += robots;

            // Check geode robot first
            vector<int> new_robots = {0,0,0,0};
            bool can_buy_geode = true;
            for (int min_i = 0; min_i < 4; min_i++) {
                if (minerals[min_i] - robots[min_i] < blueprint[3][min_i]) {
                    can_buy_geode = false;
                    break;
                }
            }

            // Buy geode robot
            if (can_buy_geode) {
                new_robots[3]++;

                // Add to queue, adding new robots and subtracting new robot mineral cost
                next_q.insert({robots + new_robots, minerals - blueprint[3]});
            }
            else {
                for (int rob_i = 1; rob_i < 4; rob_i++) {
                    new_robots = {0,0,0,0};

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

                        // Add to queue, adding new robots and subtracting new robot mineral cost
                        next_q.insert({robots + new_robots, minerals - blueprint[rob_i]});
                    }
                }
            }            

            // Do nothing
            next_q.insert({robots, minerals});
        }
        
        // cout << time << ' ' << next_q.size() << endl;;
        
        time--;
        curr_q = next_q;
        next_q = {};
    }

    // Find max geodes produced
    for (auto curr : curr_q) {
        if (curr.second[3] > max_geode) {
            max_geode = curr.second[3];
        }
    }

    return max_geode;
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
        int max_geode = crack_geodes(24, blueprints[j]);
        cout << max_geode << endl;
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