#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>

using namespace std;

// Execute two instructions and track register and cycle count
int part1() {
    ifstream infile("input.txt");
    string line;

    int X = 1;

    int cycles = 0;
    int signalCycle = 20;

    int total = 0;

    while(getline(infile, line)) {
        // noop instruction
        if (line[0] == 'n') {
            cycles++;

            // If hit signal cycle
            if (cycles + 1 == signalCycle) {
                total += X * signalCycle;
                signalCycle += 40;
            }
        }
        // addx instruction
        else {
            istringstream iss(line);
            string s;
            int V;

            iss >> s >> V;

            // If going to hit signal cycle exactly
            if (cycles + 3 == signalCycle) {
                X += V;
                cycles += 2;

                total += X * signalCycle;
                signalCycle += 40;
            }
            // If going to pass signal cycle
            else if (cycles + 2 >= signalCycle) {
                total += X * signalCycle;
                signalCycle += 40;

                X += V;
                cycles += 2;
            }
            else {
                X += V;
                cycles += 2;
            }
        }
    }

    return total;
}

void drawPixels(int X, int& cycles, int& row, string& res) {
    // Start new row
    if (cycles / 40 > row) {
        row++;
        res += '\n';
    }

    int i = cycles % 40;

    // If sprite positioned where drawing
    if (abs(X - i) <= 1) {
        res += '#';
    }
    else {
        res += '.';
    }
    
    cycles++;
}

string part2() {
    ifstream infile("input.txt");
    string line;

    int X = 1;
    int cycles = 0;

    int row = 0;
    string res = "";

    while(getline(infile, line)) {
        // noop instruction
        if (line[0] == 'n') {
            // Draw one pixel
            drawPixels(X, cycles, row, res);
        }
        // addx instruction
        else {
            istringstream iss(line);
            string s;
            int V;

            iss >> s >> V;

            // Draw 2 pixels
            drawPixels(X, cycles, row, res);
            drawPixels(X, cycles, row, res);

            X += V;
        }

        
    }

    return res;
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