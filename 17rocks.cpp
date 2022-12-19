// Play Tetris according to pattern and determine final height

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

int part1() {
    ifstream infile("input.txt");
    string line;

    // Drop 2022 rocks
    int rock_count = 2022;

    // Convert jet pattern to vector of bools
    vector<bool> is_rights;

    while (getline(infile, line)) {
        for (auto c : line) {
            if (c == '>') {
                is_rights.push_back(true);
            }
            else {
                is_rights.push_back(false);
            }
        }  
    }

    // Create grid upside down
    vector<vector<char>> grid;
    int height = 0;

    // Floor
    grid.push_back({'#','#','#','#','#','#','#',});

    // Add empty rows, 3 above floor, max rock is 4 tall
    for (int i = 0; i < height+3+4; i++) {
        grid.push_back({'.','.','.','.','.','.','.',});
    }


    // Five types of rocks (flipped upside down)

    // ####

    // .#.
    // ###
    // .#.

    // ###
    // ..#
    // ..#

    // #
    // #
    // #
    // #

    // ##
    // ##

    // List of coordinates in each rock relative to left top (originally bottom) corner
    vector<vector<pair<int, int>>> rocks;

    rocks.push_back({{0,0},{0,1},{0,2},{0,3},});
    rocks.push_back({{0,1},{1,0},{1,1},{1,2},{2,1},});
    rocks.push_back({{0,0},{0,1},{0,2},{1,2},{2,2},});
    rocks.push_back({{0,0},{1,0},{2,0},{3,0},});
    rocks.push_back({{0,0},{0,1},{1,0},{1,1},});

    // Heights of rocks relative to left top corner (originally bottom)
    int heights[5] = {0, 2, 2, 3, 1};

    int i = 0;

    for (int rock_i = 0; rock_i < rock_count; rock_i++) {
        int rock_l = 2;

        // Index of the top of the rock (since upside down, originally bottom)
        int rock_t = height + 4;

        // Get current rock
        vector<pair<int, int>> rock = rocks[rock_i % rocks.size()];
        int rock_height = heights[rock_i % 5];

        while (true) {
            // Try to move rock left or right according to jet pattern
            // Use mod to wrap around, repeating jet pattern if needed
            bool is_right = is_rights[i % is_rights.size()];

            bool has_collision = false;
            if (is_right) {
                // Check each coordinate in the rock
                for (auto coord : rock) {
                    int r = rock_t + coord.first;
                    int c = rock_l + coord.second;
                    
                    // If out of bounds or collision
                    if (c+1 >= 7 or grid[r][c+1] == '#') {
                        has_collision = true;
                        break;
                    }
                }

                // Move right if no collision
                if (not has_collision) {
                    rock_l++;
                }
            }
            else {
                // Check each coordinate in the rock
                for (auto coord : rock) {
                    int r = rock_t + coord.first;
                    int c = rock_l + coord.second;
                    
                    // If out of bounds or collision
                    if (c-1 < 0 or grid[r][c-1] == '#') {
                        has_collision = true;
                        break;
                    }
                }

                // Move left if no collision
                if (not has_collision) {
                    rock_l--;
                }
            }

            i++;

            // Try to move rock up (originally down)
            has_collision = false;
            for (auto coord : rock) {
                int r = rock_t + coord.first;
                int c = rock_l + coord.second;
                
                // If out of bounds or collision
                if (grid[r-1][c] == '#') {
                    has_collision = true;
                    break;
                }
            }

            // Move down if no collision
            if (not has_collision) {
                rock_t--;
            }
            // Otherwise land rock
            else {
                for (auto coord : rock) {
                    int r = rock_t + coord.first;
                    int c = rock_l + coord.second;
                    
                    grid[r][c] = '#';
                }

                // Save new max height if needed
                if (rock_t + rock_height > height) {
                    height = rock_t + rock_height;

                    // Add empty rows, 3 above floor, max rock is 4 tall
                    for (int j = grid.size(); j < height+3+4+1; j++) {
                        grid.push_back({'.','.','.','.','.','.','.',});
                    }
                }

                break;
            }

        }
    }

    return height;
}

// Deal with massive input
// I hand-sleuthed through the data to find where it repeated, then use mod math to simplify
int part2() {
    ifstream infile("input.txt");
    string line;

    // For test.txt, rocks seem to repeat on a 35 rock pattern starting from about rock 92
    // For input.txt, rocks seem to repeat on a 1700 rock pattern starting from rock 3406
    int rock_count = 3406 + 194;

    // Convert jet pattern to vector of bools
    vector<bool> is_rights;

    while (getline(infile, line)) {
        for (auto c : line) {
            if (c == '>') {
                is_rights.push_back(true);
            }
            else {
                is_rights.push_back(false);
            }
        }  
    }

    // Create grid upside down
    vector<vector<char>> grid;
    int height = 0;

    // Floor
    grid.push_back({'#','#','#','#','#','#','#',});

    // Add empty rows, 3 above floor, max rock is 4 tall
    for (int i = 0; i < height+3+4; i++) {
        grid.push_back({'.','.','.','.','.','.','.',});
    }


    // Five types of rocks (flipped upside down)

    // ####

    // .#.
    // ###
    // .#.

    // ###
    // ..#
    // ..#

    // #
    // #
    // #
    // #

    // ##
    // ##

    // List of coordinates in each rock relative to left top (originally bottom) corner
    vector<vector<pair<int, int>>> rocks;

    rocks.push_back({{0,0},{0,1},{0,2},{0,3},});
    rocks.push_back({{0,1},{1,0},{1,1},{1,2},{2,1},});
    rocks.push_back({{0,0},{0,1},{0,2},{1,2},{2,2},});
    rocks.push_back({{0,0},{1,0},{2,0},{3,0},});
    rocks.push_back({{0,0},{0,1},{1,0},{1,1},});

    // Heights of rocks relative to left top corner (originally bottom)
    int heights[5] = {0, 2, 2, 3, 1};

    int i = 0;

    int prev_height = 0;

    for (int rock_i = 0; rock_i < rock_count; rock_i++) {
        int rock_l = 2;

        // Index of the top of the rock (since upside down, originally bottom)
        int rock_t = height + 4;

        // Get current rock
        vector<pair<int, int>> rock = rocks[rock_i % rocks.size()];
        int rock_height = heights[rock_i % 5];

        while (true) {
            // Try to move rock left or right according to jet pattern
            // Use mod to wrap around, repeating jet pattern if needed
            bool is_right = is_rights[i % is_rights.size()];

            bool has_collision = false;
            if (is_right) {
                // Check each coordinate in the rock
                for (auto coord : rock) {
                    int r = rock_t + coord.first;
                    int c = rock_l + coord.second;
                    
                    // If out of bounds or collision
                    if (c+1 >= 7 or grid[r][c+1] == '#') {
                        has_collision = true;
                        break;
                    }
                }

                // Move right if no collision
                if (not has_collision) {
                    rock_l++;
                }
            }
            else {
                // Check each coordinate in the rock
                for (auto coord : rock) {
                    int r = rock_t + coord.first;
                    int c = rock_l + coord.second;
                    
                    // If out of bounds or collision
                    if (c-1 < 0 or grid[r][c-1] == '#') {
                        has_collision = true;
                        break;
                    }
                }

                // Move left if no collision
                if (not has_collision) {
                    rock_l--;
                }
            }

            i++;

            // If circled through jet pattern
            // if (i % is_rights.size() == 0) {
            //     // Print current rock and current height
            //     cout << rock_i << " " << rock_i % rocks.size() << " " << height << endl;
            // }

            // Try to move rock up (originally down)
            has_collision = false;
            for (auto coord : rock) {
                int r = rock_t + coord.first;
                int c = rock_l + coord.second;
                
                // If out of bounds or collision
                if (grid[r-1][c] == '#') {
                    has_collision = true;
                    break;
                }
            }

            // Move down if no collision
            if (not has_collision) {
                rock_t--;
            }
            // Otherwise land rock
            else {
                for (auto coord : rock) {
                    int r = rock_t + coord.first;
                    int c = rock_l + coord.second;
                    
                    grid[r][c] = '#';
                }

                // Save new max height if needed
                if (rock_t + rock_height > height) {
                    height = rock_t + rock_height;

                    // Add empty rows, 3 above floor, max rock is 4 tall
                    for (int j = grid.size(); j < height+3+4+1; j++) {
                        grid.push_back({'.','.','.','.','.','.','.',});
                    }
                }

                break;
            }

        }
    }


    return height;
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