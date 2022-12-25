#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <math.h>

using namespace std;

long long part1() {
    ifstream infile("input.txt");
    string line;

    long long total = 0;
    while (getline(infile, line)) {
        long long value = 0;
        for (int digit = 0; digit < line.size(); digit++) {
            char c = line[digit];

            // Powers of 5
            long long place = pow(5, line.size() - digit - 1);

            switch (c) {
                case '2':
                    value += 2 * place;
                    break;
                case '1':
                    value += 1 * place;
                    break;
                case '-':
                    value += -1 * place;
                    break;
                case '=':
                    value += -2 * place;
                    break;
            }
        }

        total += value;
    }

    cout << total << endl;

    return total;
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