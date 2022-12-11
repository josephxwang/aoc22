// Analyze grid of numbers to see which are visible

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int part1(vector<vector<int>> grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Create matching 2D array of bools (initialize false) to track if visible
    bool is_vis[rows][cols];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            is_vis[r][c] = false;
        }
    }

    // @@ CAN REFACTOR WITH DIRECTIONS, ANOTHER FOR LOOP

    // Look at grid from left side
    for (int r = 0; r < rows; r++) {

        // Track max row by row to see which are visible
        int curr_max = grid[r][0];
        is_vis[r][0] = true;

        // Ignore edges on each side (always visible)
        for (int c = 1; c < cols-1; c++) {
            int curr = grid[r][c];

            // Track if greater
            if (curr > curr_max) {
                is_vis[r][c] = true;
                curr_max = curr;
            }
        }  
    }

    // Look at grid from right side
    for (int r = 0; r < rows; r++) {
        int curr_max = grid[r][cols-1];
        is_vis[r][cols-1] = true;

        for (int c = cols-2; c > 0; c--) {
            int curr = grid[r][c];

            if (curr > curr_max) {
                is_vis[r][c] = true;
                curr_max = curr;
            }
        }  
    }

    // Look at grid from top side
    for (int c = 0; c < cols; c++) {
        int curr_max = grid[0][c];
        is_vis[0][c] = true;

        for (int r = 1; r < rows-1; r++) {
            int curr = grid[r][c];

            if (curr > curr_max) {
                is_vis[r][c] = true;
                curr_max = curr;
            }
        }  
    }

    // Look at grid from bottom side
    for (int c = 0; c < cols; c++) {
        int curr_max = grid[rows-1][c];
        is_vis[rows-1][c] = true;

        for (int r = rows-2; r > 0; r--) {
            int curr = grid[r][c];

            if (curr > curr_max) {
                is_vis[r][c] = true;
                curr_max = curr;
            }
        }  
    }
    
    // Count number of trues
    int count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (is_vis[r][c]) {
                count++;
            }
        }
    }

    return count;
}

int part2(vector<vector<int>> grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Check all locations
    // Four directions
    int dirs[4][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    int maxScore = 0;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int score = 1;
            int curr = grid[row][col];

            // Check all four directions
            for (int i = 0; i < 4; i++) {
                int dr = dirs[i][0];
                int dc = dirs[i][1];

                int r = row;
                int c = col;
                int count = 0;

                // Stay within edges
                while (r+dr >= 0 && r+dr < rows && c+dc >= 0 && c+dc < cols) {
                    r += dr;
                    c += dc;
                    
                    // Stop at first tree same height or taller than curr
                    if (grid[r][c] >= curr) {
                        count++;
                        break;
                    }
                    
                    count++;
                }

                score *= count;
            }

            if (score > maxScore) {
                maxScore = score;
            }
        }
    }

    return maxScore;
}

int main() {
    ifstream infile("input.txt");
    vector<vector<int>> grid;
    string line;

    // Get input as 2D array of ints
    while (getline(infile, line)) {
        vector<int> row;
        for (int i = 0; i < line.length(); i++) {
            row.push_back(line[i] - '0');
        }

        grid.push_back(row);
    }

    cout << part1(grid) << endl;
    cout << part2(grid) << endl;
}