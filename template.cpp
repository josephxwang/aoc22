#include <iostream>
#include <chrono>

using namespace std;

int part1() {
    while (getline(cin, line) && line.size() > 0) {
        
    }

    return 0;
}

int part2() {
    while (getline(cin, line) && line.size() > 0) {
        
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