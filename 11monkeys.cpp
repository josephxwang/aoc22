// Modify and pass objects between 8 monkeys based on certain rules

#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <deque>
#include <vector>

using namespace std;

// Struct for monkey data, like a class but only data
struct monkey {
    deque<long> items;
    int mod;
    int tMonk;
    int fMonk;
    int inspects;
};

// Operate on 8 monkeys according to rules
int part1(vector<monkey> monkeys) {
    for (int round = 0; round < 20; round++) {
        // Do each monkey in a round
        for (int i = 0; i < monkeys.size(); i++) {
            int items = monkeys[i].items.size();

            // Do all items
            for (int j = 0; j < items; j++) {

                // Get first item
                long curr = monkeys[i].items.front();
                monkeys[i].items.pop_front();

                // Operate on item based on monkey
                switch (i) {
                    case 0:
                        curr *= 3;
                        break;
                    case 1:
                        curr += 8;
                        break;
                    case 2:
                        curr *= curr;
                        break;
                    case 3:
                        curr += 2;
                        break;
                    case 4:
                        curr += 3;
                        break;
                    case 5:
                        curr *= 17;
                        break;
                    case 6:
                        curr += 6;
                        break;
                    case 7:
                        curr += 1;
                        break;
                }

                curr /= 3;

                // Pass item based on condition
                if (curr % monkeys[i].mod == 0) {
                    monkeys[monkeys[i].tMonk].items.push_back(curr);
                }
                else {
                    monkeys[monkeys[i].fMonk].items.push_back(curr);
                }

                monkeys[i].inspects++;
            }
        }
    }

    // Find two monkeys with max inspects
    int max1 = 0;
    int max2 = 0;

    for (int i = 0; i < monkeys.size(); i++) {
        int curr = monkeys[i].inspects;

        if (curr >= max1) {
            max2 = max1;
            max1 = curr;
        }
        else if (curr >= max2) {
            max2 = curr;
        }
    }

    return max1 * max2;
}

int part2(vector<monkey> monkeys) {
    for (int round = 0; round < 10000; round++) {
        // Do each monkey in a round
        for (int i = 0; i < monkeys.size(); i++) {
            int items = monkeys[i].items.size();

            // Do all items
            for (int j = 0; j < items; j++) {

                // Get first item
                long curr = monkeys[i].items.front();
                monkeys[i].items.pop_front();

                // Operate on item based on monkey
                switch (i) {
                    case 0:
                        curr *= 3;
                        break;
                    case 1:
                        curr += 8;
                        break;
                    case 2:
                        curr *= curr;
                        break;
                    case 3:
                        curr += 2;
                        break;
                    case 4:
                        curr += 3;
                        break;
                    case 5:
                        curr *= 17;
                        break;
                    case 6:
                        curr += 6;
                        break;
                    case 7:
                        curr += 1;
                        break;
                }

                // Product of all divisible test numbers
                curr %= 9699690;

                // Pass item based on condition
                if (curr % monkeys[i].mod == 0) {
                    monkeys[monkeys[i].tMonk].items.push_back(curr);
                }
                else {
                    monkeys[monkeys[i].fMonk].items.push_back(curr);
                }

                monkeys[i].inspects++;
            }
        }
    }

    // Find two monkeys with max inspects
    int max1 = 0;
    int max2 = 0;

    for (int i = 0; i < monkeys.size(); i++) {
        int curr = monkeys[i].inspects;

        if (curr >= max1) {
            max2 = max1;
            max1 = curr;
        }
        else if (curr >= max2) {
            max2 = curr;
        }
    }

    // Output two max inspects (multiplying large numbers weird)
    cout << max1 << ' ' << max2 << endl;

    long long prod = max1 * max2;

    return prod;
}

int main() {
    ifstream infile("input.txt");
    string line;
    int numMonks = 8;

    vector<monkey> monkeys;

    // Get input
    for (int i = 0; i < numMonks; i++) {
        monkeys.push_back(monkey());

        int j;
        char c;

        getline(infile, line);

        // Get starting items
        getline(infile, line);
        j = line.find(':');
        line = line.substr(j+2);
        istringstream iss(line);
        long item;
        while (iss >> item >> c) {
            monkeys[i].items.push_back(item);
        }

        // Manually input operations later, skip for now
        getline(infile, line);

        // Get divisible number
        getline(infile, line);
        j = line.find('y');
        line = line.substr(j+2);
        monkeys[i].mod = stoi(line);

        // Get true and false monkeys
        getline(infile, line);
        j = line.find('y');
        line = line.substr(j+2);
        monkeys[i].tMonk = stoi(line);

        getline(infile, line);
        j = line.find('y');
        line = line.substr(j+2);
        monkeys[i].fMonk = stoi(line);
        
        getline(infile, line);

        monkeys[i].inspects = 0;
    }

    auto start = chrono::high_resolution_clock::now();
    // cout << part1(monkeys) << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Part 1: " << duration.count() << " us" << endl;

    start = chrono::high_resolution_clock::now();
    cout << part2(monkeys) << endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Part 2: " << duration.count() << " us" << endl;
}