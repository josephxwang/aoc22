// Find length of shortest path in grid graph

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <deque>

using namespace std;

// Find length of shortest path from start to end in a grid
int part1(int rows, int cols, pair<int, int> start, pair<int, int> end, vector<vector<char>> grid, vector<vector<int>> visited) {
    // Four directions to visit
    int dirs[4][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    // Do BFS of graph, starting from start, ending at end
    deque<pair<int, int>> q;
    q.push_back(start);

    visited[start.first][start.second] = 0;

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop_front();

        int r = curr.first;
        int c = curr.second;
        int steps = visited[r][c];

        // If reached end
        if (r == end.first and c == end.second) {
            return visited[r][c];
        }

        // Check neighbors in four directions
        for (int i = 0; i < 4; i++) {
            int dr = dirs[i][0];
            int dc = dirs[i][1];

            // If within bounds
            if (r+dr >= 0 && r+dr < rows && c+dc >= 0 && c+dc < cols) {
                // If new location at most 1 higher
                if (grid[r+dr][c+dc] - grid[r][c] <= 1) {
                    // If not visited yet
                    if (visited[r+dr][c+dc] == -1) {
                        visited[r+dr][c+dc] = steps + 1;
                        q.push_back({r+dr, c+dc});
                    }
                }
            }
        }
    }

    return 0;
}

// Find length of shortest path from end to any 'a'
int part2(int rows, int cols, pair<int, int> start, pair<int, int> end, vector<vector<char>> grid, vector<vector<int>> visited) {
    // Four directions to visit
    int dirs[4][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };
    
    // Do BFS of graph, starting from end, ending at first 'a'
    deque<pair<int, int>> q;
    q.push_back(end);

    visited[end.first][end.second] = 0;

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop_front();

        int r = curr.first;
        int c = curr.second;
        int steps = visited[r][c];

        // If reached end
        if (grid[r][c] == 'a') {
            return visited[r][c];
        }

        // Check neighbors in four directions
        for (int i = 0; i < 4; i++) {
            int dr = dirs[i][0];
            int dc = dirs[i][1];

            // If within bounds
            if (r+dr >= 0 && r+dr < rows && c+dc >= 0 && c+dc < cols) {
                // If new location at most 1 lower
                if (grid[r+dr][c+dc] - grid[r][c] >= -1) {
                    // If not visited yet
                    if (visited[r+dr][c+dc] == -1) {
                        visited[r+dr][c+dc] = steps + 1;
                        q.push_back({r+dr, c+dc});
                    }
                }
            }
        }
    }

    return 0;
}

int main() {
    ifstream infile("input.txt");
    string line;

    int rows, cols;
    vector<vector<char>> grid;

    // Get input
    int r = 0;
    pair<int, int> startLoc, end;
    while (getline(infile, line)) {
        grid.push_back({});
        for (int c = 0; c < line.size(); c++) {
            // Save start and end locations
            if (line[c] == 'S') {
                startLoc = {r, c};
                grid[r].push_back('a');
            }
            else if (line[c] == 'E') {
                end = {r, c};
                grid[r].push_back('z');
            }
            else {
                grid[r].push_back(line[c]);
            }
        }

        r++;
        
        cols = line.size();
    }

    rows = r;

    // Initialize visited array to -1
    vector<vector<int>> visited;
    for (int r = 0; r < rows; r++) {
        visited.push_back({});
        for (int c = 0; c < cols; c++) {
            visited[r].push_back(-1);
        }
    }

    auto start = chrono::high_resolution_clock::now();
    cout << part1(rows, cols, startLoc, end, grid, visited) << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Part 1: " << duration.count() << " us" << endl;

    start = chrono::high_resolution_clock::now();
    cout << part2(rows, cols, startLoc, end, grid, visited) << endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Part 2: " << duration.count() << " us" << endl;
}