#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <vector>

using namespace std;

// Traverse an asymmetric 2D grid with wrap around rules
int part1() {
    ifstream infile("input.txt");
    string line;

    // Get instructions
    // R is -1, L is -2
    getline(infile, line);
    istringstream iss(line);
    vector<int> insts;
    int inst;
    while (iss >> inst) {
        insts.push_back(inst);
    }

    getline(infile, line);

    // One large grid
    // . empty, # obstacle, o out of bounds
    vector<vector<char>> grid;

    int r = 0;
    int c;

    int row = 0;
    int col = 0;
    bool found_col = false;
    while (getline(infile, line)) {
        grid.push_back({});
        istringstream iss(line);

        char ch;

        while (iss >> ch) {
            grid[row].push_back(ch);

            // Find starting position, top left corner
            if (row == 0 and not found_col) {
                if (ch != 'o') {
                    c = col;
                    found_col = true;
                }

                col++;
            }
        }
        row++;
    }
    
    // Four directions, in clockwise rotation
    int dirs[4][2] = {
        {0,1},
        {1,0},
        {0,-1},
        {-1,0}
    };
    
    int dir_i = 0;

    for (int inst : insts) {
        switch (inst) {
            case -1:
                dir_i++;
                dir_i %= 4;
                break;
            case -2:
                dir_i--;
                dir_i = (dir_i+4) % 4;
                break;
            // If normal number
            default:
                for (int step = 0; step < inst; step++) {
                    int dr = dirs[dir_i][0];
                    int dc = dirs[dir_i][1];

                    // If within bounds
                    if (r+dr >= 0 && r+dr < grid.size() 
                        && c+dc >= 0 && c+dc < grid[r+dr].size()
                        && grid[r+dr][c+dc] != 'o') {
                        // Stop if obstacle
                        if (grid[r+dr][c+dc] == '#') {
                            break;
                        }

                        // Move one step
                        r += dr;
                        c += dc;
                    }
                    // Otherwise wrap around
                    else {
                        // Look backward
                        int orig_r = r;
                        int orig_c = c;

                        dr = -dr;
                        dc = -dc;

                        while (true) {
                            // Stop if hit opposite edge
                            if (r+dr < 0 or r+dr >= grid.size() 
                                or c+dc < 0 or c+dc >= grid[r+dr].size()
                                or grid[r+dr][c+dc] == 'o') {
                                
                                // If obstacle, don't wrap around
                                if (grid[r][c] == '#') {
                                    r = orig_r;
                                    c = orig_c;
                                }

                                break;
                            }

                            r += dr;
                            c += dc; 
                        }
                    }
                }
        }
    }

    cout << r << " " << c << endl;
    cout << dir_i << endl;

    return (r+1)*1000 + (c+1)*4 + dir_i;
}


// Traverse the surface of a 3D cube given by a 2D unfolded pattern
int part2() {
    ifstream infile("input.txt");
    string line;

    // Get instructions
    // R is -1, L is -2
    getline(infile, line);
    istringstream iss(line);
    vector<int> insts;
    int inst;
    while (iss >> inst) {
        insts.push_back(inst);
    }

    getline(infile, line);

    // One large grid
    // . empty, # obstacle, o out of bounds
    vector<vector<char>> grid;

    int r = 0;
    int c;

    int row = 0;
    int col = 0;
    bool found_col = false;
    while (getline(infile, line)) {
        grid.push_back({});
        istringstream iss(line);

        char ch;

        while (iss >> ch) {
            grid[row].push_back(ch);

            // Find starting position, top left corner
            if (row == 0 and not found_col) {
                if (ch != 'o') {
                    c = col;
                    found_col = true;
                }

                col++;
            }
        }
        row++;
    }
    
    // Four directions, in clockwise rotation
    int dirs[4][2] = {
        {0,1},
        {1,0},
        {0,-1},
        {-1,0}
    };
    
    int dir_i = 0;

    for (int inst : insts) {
        switch (inst) {
            case -1:
                dir_i++;
                dir_i %= 4;
                break;
            case -2:
                dir_i--;
                dir_i = (dir_i+4) % 4;
                break;
            // If normal number
            default:
                for (int step = 0; step < inst; step++) {
                    int dr = dirs[dir_i][0];
                    int dc = dirs[dir_i][1];

                    // If within bounds
                    if (r+dr >= 0 && r+dr < grid.size() 
                        && c+dc >= 0 && c+dc < grid[r+dr].size()
                        && grid[r+dr][c+dc] != 'o') {
                        // Stop if obstacle
                        if (grid[r+dr][c+dc] == '#') {
                            break;
                        }

                        // Move one step
                        r += dr;
                        c += dc;
                    }
                    // Otherwise wrap around according to cube rules
                    else {
                        int orig_r = r;
                        int orig_c = c;
                        int orig_dir_i = dir_i;

                        // Side 8
                        if (r == 0 and c >= 50 and c <= 50+49 and dir_i == 3) {
                            // cout << dir_i << endl;
                            c = 0;
                            r = 150 + (orig_c - 50);
                            dir_i = 0;
                        }
                        else if (c == 0 and r >= 150 and r <= 150+49 and dir_i == 2) {
                            r = 0;
                            c = 50 + (orig_r - 150);
                            dir_i = 1;
                        }

                        // Side 3
                        // Need to flip!
                        else if (c == 50 and r >= 0 and r <= 0+49 and dir_i == 2) {
                            c = 0;
                            // r = 100 + (orig_r - 0);
                            r = 149 + (0 - orig_r);
                            dir_i = 0;
                        }
                        else if (c == 0 and r >= 100 and r <= 100+49 and dir_i == 2) {
                            c = 50;
                            // r = 0 + (orig_r - 100);
                            r = 49 + (100 - orig_r);
                            dir_i = 0;
                        }

                        // Side 4
                        else if (c == 50 and r >= 50 and r <= 50+49 and dir_i == 2) {
                            r = 100;
                            c = 0 + (orig_r - 50);
                            dir_i = 1;
                        }
                        else if (r == 100 and c >= 0 and c <= 0+49 and dir_i == 3) {
                            c = 50;
                            r = 50 + (orig_c - 0);
                            dir_i = 0;
                        }

                        // Side 12
                        else if (r == 199 and c >= 0 and c <= 0+49 and dir_i == 1) {
                            r = 0;
                            c = 100 + (orig_c - 0);
                            dir_i = 1;
                        }
                        else if (r == 0 and c >= 100 and c <= 100+49 and dir_i == 3) {
                            r = 199;
                            c = 0 + (orig_c - 100);
                            dir_i = 3;
                        }

                        // Side 5
                        else if (c == 49 and r >= 150 and r <= 150+49 and dir_i == 0) {
                            r = 149;
                            c = 50 + (orig_r - 150);
                            dir_i = 3;
                        }
                        else if (r == 149 and c >= 50 and c <= 50+49 and dir_i == 1) {
                            c = 49;
                            r = 150 + (orig_c - 50);
                            dir_i = 2;
                        }

                        // Side 11
                        // Need to flip!
                        else if (c == 99 and r >= 100 and r <= 100+49 and dir_i == 0) {
                            c = 149;
                            // r = 0 + (orig_r - 100);
                            r = 49 + (100 - orig_r);
                            dir_i = 2;
                        }
                        else if (c == 149 and r >= 0 and r <= 0+49 and dir_i == 0) {
                            c = 99;
                            // r = 100 + (orig_r - 0);
                            r = 149 + (0 - orig_r);
                            dir_i = 2;
                        }

                        // Side 10
                        else if (c == 99 and r >= 50 and r <= 50+49 and dir_i == 0) {
                            r = 49;
                            c = 100 + (orig_r - 50);
                            dir_i = 3;
                        }
                        else if (r == 49 and c >= 100 and c <= 100+49 and dir_i == 1) {
                            c = 99;
                            r = 50 + (orig_c - 100);
                            dir_i = 2;
                        }

                        // If obstacle, don't wrap around, revert
                        if (grid[r][c] == '#') {
                            r = orig_r;
                            c = orig_c;
                            dir_i = orig_dir_i;
                            break;
                        }
                    }
                }
        }
    }

    cout << r << " " << c << endl;
    cout << dir_i << endl;

    return (r+1)*1000 + (c+1)*4 + dir_i;
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