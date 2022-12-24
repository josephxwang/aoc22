#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int part1() {
    ifstream infile("test.txt");
    string line;

    while (getline(infile, line)) {
    
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