// Count total surface area (internal and external) of a volume

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <deque>

using namespace std;

// Count total surface area of a volume
int part1() {
    ifstream infile("input.txt");
    string line;

    // int min_x = 10;
    // int max_x = 0;
    // int min_y = 10;
    // int max_y = 0;
    // int min_z = 10;
    // int max_z = 0;

    // Make 3D cube
    // x: 1-21
    // y: 0-21
    // z: 1-21
    vector<vector<vector<int>>> cube;
    int range = 24;

    for (int layer = 0; layer < range; layer++) {
        cube.push_back({});

        for (int r = 0; r < range; r++) {
            cube[layer].push_back({});

            for (int c = 0; c < range; c++) {
                cube[layer][r].push_back(0);
            }
        }
    }

    while (getline(infile, line)) {
        char ch;
        int layer, r, c;

        istringstream iss(line);

        iss >> layer >> ch >> r >> ch >> c;

        cube[layer+1][r+1][c+1] = 1;

        // if (x < min_x) {
        //     min_x = x;
        // }
        // if (x > max_x) {
        //     max_x = x;
        // }

        // if (y < min_y) {
        //     min_y = y;
        // }
        // if (y > max_y) {
        //     max_y = y;
        // }

        // if (z < min_z) {
        //     min_z = z;
        // }
        // if (z > max_z) {
        //     max_z = z;
        // }        
    }

    // Step through cube and check 6 adjacent sides
    int total = 0;

    int dirs[6][3] = {
        {0,0,1},
        {0,0,-1},
        {0,1,0},
        {0,-1,0},
        {1,0,0},
        {-1,0,0}
    };

    for (int layer = 1; layer < range-1; layer++) {
        for (int r = 1; r < range-1; r++) {
            for (int c = 1; c < range-1; c++) {
                if (cube[layer][r][c] == 1) {
                    int area = 6;

                    for (auto dir : dirs) {
                        int d_layer = dir[0];
                        int dr = dir[1];
                        int dc = dir[2];

                        // If adjacent cube is occupied, reduce surface area by 1
                        if (cube[layer+d_layer][r+dr][c+dc] == 1) {
                            area--;
                        }
                    }

                    total += area;
                }
            }
        }
    }

    // cout << min_x << " " << max_x << endl;
    // cout << min_y << " " << max_y << endl;
    // cout << min_z << " " << max_z << endl;

    return total;
}

// Count total external surface area of a volume
int part2() {
    ifstream infile("input.txt");
    string line;

    // Make 3D cube
    // x: 1-21
    // y: 0-21
    // z: 1-21
    vector<vector<vector<int>>> cube;
    int range = 24;

    for (int layer = 0; layer < range; layer++) {
        cube.push_back({});

        for (int r = 0; r < range; r++) {
            cube[layer].push_back({});

            for (int c = 0; c < range; c++) {
                cube[layer][r].push_back(0);
            }
        }
    }

    while (getline(infile, line)) {
        char ch;
        int layer, r, c;

        istringstream iss(line);

        iss >> layer >> ch >> r >> ch >> c;

        // Mark actual cubes with 1
        cube[layer+1][r+1][c+1] = 1;
    }

    // BFS to fill outside space with -1
    deque<vector<int>> q;
    q.push_back({0,0,0});

    int dirs[6][3] = {
        {0,0,1},
        {0,0,-1},
        {0,1,0},
        {0,-1,0},
        {1,0,0},
        {-1,0,0}
    };

    while (!q.empty()) {
        vector<int> curr = q.front();
        q.pop_front();

        int layer = curr[0];
        int r = curr[1];
        int c = curr[2];

        // If visited
        if (cube[layer][r][c] == 1 or cube[layer][r][c] == -1) {
            continue;
        }

        // Mark visited
        cube[layer][r][c] = -1;

        // Check 6 neighbors
        for (auto dir : dirs) {
            int d_layer = dir[0];
            int dr = dir[1];
            int dc = dir[2];

            // If within range
            if (layer+d_layer >= 0 and layer+d_layer < range 
                and r+dr >= 0 and r+dr < range
                and c+dc >= 0 and c+dc < range) {
                
                q.push_back({layer+d_layer, r+dr, c+dc});
            }
        }
    }

    // Step through cube and fill empty space (if 0) with 1
    for (int layer = 0; layer < range; layer++) {
        for (int r = 0; r < range; r++) {
            for (int c = 0; c < range; c++) {
                if (cube[layer][r][c] == 0) {
                    cube[layer][r][c] = 1;
                }
            }
        }
    }

    // Step through cube and check 6 adjacent sides
    int total = 0;

    for (int layer = 1; layer < range-1; layer++) {
        for (int r = 1; r < range-1; r++) {
            for (int c = 1; c < range-1; c++) {
                if (cube[layer][r][c] == 1) {
                    int area = 6;

                    for (auto dir : dirs) {
                        int d_layer = dir[0];
                        int dr = dir[1];
                        int dc = dir[2];

                        // If adjacent cube is occupied, reduce surface area by 1
                        if (cube[layer+d_layer][r+dr][c+dc] == 1) {
                            area--;
                        }
                    }

                    total += area;
                }
            }
        }
    }

    return total;
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