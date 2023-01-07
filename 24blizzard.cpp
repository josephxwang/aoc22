#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

int part1() {
    ifstream infile("test.txt");
    string line;

    while (getline(infile, line)) {
    
    }

    // Directions, also option to stay put
    int dirs[5][2] = {
        {0,1},
        {1,0},
        {0,0},
        {0,-1},
        {-1,0}
    };

    // Try a DFS first
    vector<int> stack = {};

    while (!stack.empty()) {


        // Check neighbors
        for (int i = 0; i < 5; i++) {
            int dr = dirs[i][0];
            int dc = dirs[i][1];

            // Also if an open spot
            if (r+dr >= 0 && r+dr < rows && c+dc >= 0 && c+dc < cols) {
            

            }
        }
    }

    return 0;
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