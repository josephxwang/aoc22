#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Code for hashing a pair
struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first*31 + v.second;
    }
};

int part1() {
    ifstream infile("input.txt");
    string line;
    
    // Use bit operations for faster
    vector<vector<bool>> grid;

    // Locations of elves
    unordered_set<pair<int, int>, pair_hash> starts;

    int size = 74 + 10 + 10;
    // int size = 7 + 10 + 10;
    // int size = 5 + 10 + 10;

    // Pad grid with 10 empty rows
    int row = 0;
    for (int i = 0; i < 10; i++) {
        grid.push_back({});
        for (int j = 0; j < size; j++) {
            grid[row].push_back(false);
        }

        row++;
    }

    // Parse input
    while (getline(infile, line)) {
        int col = 0;
        grid.push_back({});

        // Pad grid with 10 empty columns on each side
        for (int i = 0; i < 10; i++) {
            grid[row].push_back(false);
            col++;
        }

        istringstream iss(line);
        char ch;

        while (iss >> ch) {
            if (ch == '.') {
                grid[row].push_back(false);
            }
            else {
                grid[row].push_back(true);

                starts.insert({row, col});
            }

            col++;
        }

        for (int i = 0; i < 10; i++) {
            grid[row].push_back(false);
        }
        
        row++;
    }

    for (int i = 0; i < 10; i++) {
        grid.push_back({});
        for (int j = 0; j < size; j++) {
            grid[row].push_back(false);
        }

        row++;
    }

    // Four directions to check for movement
    vector<vector<pair<int, int>>> dirs = {
        {{-1,-1},{-1,0},{-1,1}}, // north
        {{1,-1},{1,0},{1,1}}, // south
        {{-1,-1},{0,-1},{1,-1}}, // west
        {{-1,1},{0,1},{1,1}}, // east
    };

    // Four direction offsets for movement if valid
    int d_dirs[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    // All 8 directions
    vector<pair<int, int>> all_dirs = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,1},
        {1,-1},{1,0},{1,1},
    };

    int dir_i = 0;

    for (int round = 0; round < 10; round++) {
        // Map of proposed locations to proposing elves
        // Essentially a map of ends to starts
        unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> ends_to_starts = {};

        // Set of where elves will end
        unordered_set<pair<int, int>, pair_hash> ends = {};        

        // Move all elves
        for (pair<int, int> start : starts) {
            // Check if has any neighbor
            bool has_nbr = false;

            for (pair<int, int> dir : all_dirs) {
                if (grid[start.first + dir.first][start.second + dir.second]) {
                    has_nbr = true;
                    break;
                }
            }

            // Propose move if has neighbor
            if (has_nbr) {
                // Check four directions
                bool is_valid = true;
                for (int d_dir_i = 0; d_dir_i < 4; d_dir_i++) {
                    is_valid = true;

                    for (pair<int, int> dir : dirs[(dir_i + d_dir_i) % 4]) {
                        if (grid[start.first + dir.first][start.second + dir.second]) {
                            is_valid = false;
                            break;
                        }
                    }

                    if (is_valid) {
                        pair<int, int> end = {start.first + d_dirs[(dir_i + d_dir_i) % 4][0], start.second + d_dirs[(dir_i + d_dir_i) % 4][1]};
                        
                        // Check if duplicate (conflict)
                        if (ends_to_starts.find(end) != ends_to_starts.end()) {
                            ends_to_starts[end].push_back(start);

                            ends.erase(end);

                            // Insert starts of duplicate ends into the ends vector
                            for (pair<int, int> dup_start : ends_to_starts[end]) {
                                ends.insert(dup_start);
                            }
                        }
                        else {
                            ends_to_starts[end].push_back(start);
                            ends.insert(end);
                        }
                        
                        break;
                    }
                }
                if (not is_valid) {
                    ends.insert(start);
                }
            }
            // Otherwise stay put if no neighbors
            else {
                ends.insert(start);
            }
        }

        // Remove all starts
        for (pair<int, int> start : starts) {
            grid[start.first][start.second] = false;
        }

        // Fill all ends
        for (pair<int, int> end : ends) {
            grid[end.first][end.second] = true;
        }

        starts = ends;

        // Rotate directions to check
        dir_i++;
    }

    // Find bounds of grid
    int min_r = 1000;
    int min_c = 1000;
    int max_r = 0;
    int max_c = 0;

    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            if (grid[r][c]) {
                if (r < min_r) {
                    min_r = r;
                }
                if (r > max_r) {
                    max_r = r;
                }
                if (c < min_c) {
                    min_c = c;
                }
                if (c > max_c) {
                    max_c = c;
                }
            }
        }
    }

    // Count empty spaces
    int total = 0;
    for (int r = min_r; r <= max_r; r++) {
        for (int c = min_c; c <= max_c; c++) {
            if (not grid[r][c]) {
                total++;
            }
        }
    }
    
    return total;
}

int part2() {
    ifstream infile("input.txt");
    string line;
    
    // Use bit operations for faster
    vector<vector<bool>> grid;

    // Locations of elves
    unordered_set<pair<int, int>, pair_hash> starts;

    int pad_size = 200;

    int size = 74 + pad_size * 2;
    // int size = 7 + pad_size * 2;
    // int size = 5 + pad_size * 2;

    int last_round;
    

    // Pad grid with 10 empty rows
    int row = 0;
    for (int i = 0; i < pad_size; i++) {
        grid.push_back({});
        for (int j = 0; j < size; j++) {
            grid[row].push_back(false);
        }

        row++;
    }

    // Parse input
    while (getline(infile, line)) {
        int col = 0;
        grid.push_back({});

        // Pad grid with 10 empty columns on each side
        for (int i = 0; i < pad_size; i++) {
            grid[row].push_back(false);
            col++;
        }

        istringstream iss(line);
        char ch;

        while (iss >> ch) {
            if (ch == '.') {
                grid[row].push_back(false);
            }
            else {
                grid[row].push_back(true);

                starts.insert({row, col});
            }

            col++;
        }

        for (int i = 0; i < pad_size; i++) {
            grid[row].push_back(false);
        }
        
        row++;
    }

    for (int i = 0; i < pad_size; i++) {
        grid.push_back({});
        for (int j = 0; j < size; j++) {
            grid[row].push_back(false);
        }

        row++;
    }

    // Four directions to check for movement
    vector<vector<pair<int, int>>> dirs = {
        {{-1,-1},{-1,0},{-1,1}}, // north
        {{1,-1},{1,0},{1,1}}, // south
        {{-1,-1},{0,-1},{1,-1}}, // west
        {{-1,1},{0,1},{1,1}}, // east
    };

    // Four direction offsets for movement if valid
    int d_dirs[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    // All 8 directions
    vector<pair<int, int>> all_dirs = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,1},
        {1,-1},{1,0},{1,1},
    };

    int dir_i = 0;

    for (int round = 0; round < 10000; round++) {
        // Map of proposed locations to proposing elves
        // Essentially a map of ends to starts
        unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> ends_to_starts = {};

        // Set of where elves will end
        unordered_set<pair<int, int>, pair_hash> ends = {};

        bool any_has_nbr = false;

        // Move all elves
        for (pair<int, int> start : starts) {
            // Check if has any neighbor
            bool has_nbr = false;

            for (pair<int, int> dir : all_dirs) {
                if (grid[start.first + dir.first][start.second + dir.second]) {
                    has_nbr = true;
                    any_has_nbr = true;
                    break;
                }
            }

            // Propose move if has neighbor
            if (has_nbr) {
                // Check four directions
                bool is_valid = true;
                for (int d_dir_i = 0; d_dir_i < 4; d_dir_i++) {
                    is_valid = true;

                    for (pair<int, int> dir : dirs[(dir_i + d_dir_i) % 4]) {
                        if (grid[start.first + dir.first][start.second + dir.second]) {
                            is_valid = false;
                            break;
                        }
                    }

                    if (is_valid) {
                        pair<int, int> end = {start.first + d_dirs[(dir_i + d_dir_i) % 4][0], start.second + d_dirs[(dir_i + d_dir_i) % 4][1]};
                        
                        // Check if duplicate (conflict)
                        if (ends_to_starts.find(end) != ends_to_starts.end()) {
                            ends_to_starts[end].push_back(start);

                            ends.erase(end);

                            // Insert starts of duplicate ends into the ends vector
                            for (pair<int, int> dup_start : ends_to_starts[end]) {
                                ends.insert(dup_start);
                            }
                        }
                        else {
                            ends_to_starts[end].push_back(start);
                            ends.insert(end);
                        }
                        
                        break;
                    }
                }
                if (not is_valid) {
                    ends.insert(start);
                }
            }
            // Otherwise stay put if no neighbors
            else {
                ends.insert(start);
            }
        }

        // Remove all starts
        for (pair<int, int> start : starts) {
            grid[start.first][start.second] = false;
        }

        // Fill all ends
        for (pair<int, int> end : ends) {
            grid[end.first][end.second] = true;
        }

        starts = ends;

        // Rotate directions to check
        dir_i++;

        // Print round every 50 rounds
        if (round % 50 == 0) {
            cout << round << endl;
        }

        // If all elves have no neighbors (no move)
        if (not any_has_nbr) {
            last_round = round + 1;
            break;
        }
    }
    
    return last_round;
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