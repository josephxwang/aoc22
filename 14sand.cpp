#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <vector>

using namespace std;

int part1() {
    string line;

    // int minX = 1000;
    // int minY = 1000;
    // int maxX = 0;
    // int maxY = 0;

    // // Find max bounds of input
    // while (getline(cin, line) && line.size() > 0) {
    //     int x, y;
    //     char c;
    //     string s;

    //     istringstream iss(line);

    //     while (iss >> x >> c >> y >> s) {
    //         if (x > maxX) {
    //             maxX = x;
    //         }

    //         if (y > maxY) {
    //             maxY = y;
    //         }

    //         if (x < minX) {
    //             minX = x;
    //         }

    //         if (y < minY) {
    //             minY = y;
    //         }
    //     }
    // }

    // cout << maxX << endl;
    // cout << maxY << endl;
    // cout << minX << endl;
    // cout << minY << endl;


    // Initialize grid as all air '.'
    vector<vector<char>> grid;
    int rows = 180;
    int cols = 90;

    // Range of y: 12-178
    for (int r = 0; r < rows; r++) {
        grid.push_back({});

        // Range of x: 465-536, remap to 15-86 (minus 450)
        for (int c = 0; c < cols; c++) {
            grid[r].push_back('.');
        }
    }

    // Fill grid with rocks (in lines)
    while (getline(cin, line) && line.size() > 0) {
        int c1, r1, c2, r2;
        char c;
        string s;

        istringstream iss(line);

        // Get first point
        iss >> c1 >> c >> r1 >> s;

        c1 -= 450;

        // Get next point
        while (iss >> c2 >> c >> r2 >> s) {
            c2 -= 450;

            // If horizontal line
            if (r1 == r2) {
                int minC = min(c1, c2);
                int maxC = max(c1, c2);
                for (int dc = 0; dc <= maxC - minC; dc++) {
                    grid[r1][minC+dc] = '#';
                }
            }

            // If vertical line
            else if (c1 == c2) {
                int minR = min(r1, r2);
                int maxR = max(r1, r2);
                for (int dr = 0; dr <= maxR - minR; dr++) {
                    grid[minR+dr][c1] = '#';
                }
            }

            c1 = c2;
            r1 = r2;
        }
    }

    // Drop in sand from 500,0 (50, 0) until runs off edge
    int sandC = 50;
    int sandR = 0;
    while (sandR >= 0 && sandR < rows-1 && sandC >= 0 && sandC < cols-1) {
        // Try to fall down
        if (grid[sandR+1][sandC] == '.') {
            sandR++; 
        }
        // Try to fall down and to the left
        else if (grid[sandR+1][sandC-1] == '.') {
            sandC--;
            sandR++; 
        }
        // Try to fall down and to the right
        else if (grid[sandR+1][sandC+1] == '.') {
            sandC++;
            sandR++; 
        }
        // Otherwise sand comes to rest
        else {
            cout << sandR << ' ' << sandC << endl;
            grid[sandR][sandC] = 'o';

            // Start new sand
            sandC = 50;
            sandR = 0;
        }
    }

    // Count amount of sand in grid
    int units = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'o') {
                units++;
            }
        }
    }

    return units;
}

int part2() {
    string line;

    // Initialize grid as all air '.'
    vector<vector<char>> grid;
    int rows = 183;
    int cols = 500;

    // Range of y: 12-178
    for (int r = 0; r < rows; r++) {
        grid.push_back({});

        // Range of x: 465-536, remap to 215-286 (minus 250)
        for (int c = 0; c < cols; c++) {
            grid[r].push_back('.');
        }
    }

    // Set bottom row equal to '#'
    for (int c = 0; c < cols; c++) {
        grid[180][c] = '#';
    }

    // Fill grid with rocks (in lines)
    while (getline(cin, line) && line.size() > 0) {
        int c1, r1, c2, r2;
        char c;
        string s;

        istringstream iss(line);

        // Get first point
        iss >> c1 >> c >> r1 >> s;

        c1 -= 250;

        // Get next point
        while (iss >> c2 >> c >> r2 >> s) {
            c2 -= 250;

            // If horizontal line
            if (r1 == r2) {
                int minC = min(c1, c2);
                int maxC = max(c1, c2);
                for (int dc = 0; dc <= maxC - minC; dc++) {
                    grid[r1][minC+dc] = '#';
                }
            }

            // If vertical line
            else if (c1 == c2) {
                int minR = min(r1, r2);
                int maxR = max(r1, r2);
                for (int dr = 0; dr <= maxR - minR; dr++) {
                    grid[minR+dr][c1] = '#';
                }
            }

            c1 = c2;
            r1 = r2;
        }
    }

    // Drop in sand from 500,0 (250, 0) until runs off edge
    int sandC = 250;
    int sandR = 0;
    while (sandR >= 0 && sandR < rows-1 && sandC >= 0 && sandC < cols-1) {
        // If starting location filled
        if (grid[0][250] == 'o') {
            break;
        }

        // Try to fall down
        if (grid[sandR+1][sandC] == '.') {
            sandR++; 
        }
        // Try to fall down and to the left
        else if (grid[sandR+1][sandC-1] == '.') {
            sandC--;
            sandR++; 
        }
        // Try to fall down and to the right
        else if (grid[sandR+1][sandC+1] == '.') {
            sandC++;
            sandR++; 
        }
        // Otherwise sand comes to rest
        else {
            grid[sandR][sandC] = 'o';

            // Start new sand
            sandC = 250;
            sandR = 0;
        }
    }

    // Count amount of sand in grid
    int units = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'o') {
                units++;
            }
        }
    }

    return units;
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