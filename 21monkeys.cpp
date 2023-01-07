#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <unordered_map>

using namespace std;

struct monkey {
    bool is_num;
    long long num;
    pair<string, string> deps;
    char op;
};

bool is_num(string s) {
    return (atoll(s.c_str())); 
}

long long rec_calc_monkey(string name, unordered_map<string, monkey>& monkeys) {
    // Return number if number monkey
    if (monkeys[name].is_num) {
        return monkeys[name].num;
    }
    // Recurse if monkey with deps
    else {
        // Depending on operator
        switch (monkeys[name].op) {
            case '+':
                return rec_calc_monkey(monkeys[name].deps.first, monkeys) + rec_calc_monkey(monkeys[name].deps.second, monkeys);
            case '-':
                return rec_calc_monkey(monkeys[name].deps.first, monkeys) - rec_calc_monkey(monkeys[name].deps.second, monkeys);
            case '*':
                return rec_calc_monkey(monkeys[name].deps.first, monkeys) * rec_calc_monkey(monkeys[name].deps.second, monkeys);
            case '/':
                return rec_calc_monkey(monkeys[name].deps.first, monkeys) / rec_calc_monkey(monkeys[name].deps.second, monkeys);
        }
    }
}

string rec_calc_monkey2(string name, unordered_map<string, monkey>& monkeys) {
    if (name == "humn") {
        return "x";
    }
    // Return number if number monkey
    else if (monkeys[name].is_num) {
        return to_string(monkeys[name].num);
    }
    // Recurse if monkey with deps
    else {
        string part1 = rec_calc_monkey2(monkeys[name].deps.first, monkeys);
        string part2 = rec_calc_monkey2(monkeys[name].deps.second, monkeys);

        return "(" + part1 + monkeys[name].op + part2 + ")";

        // Depending on operator
        // switch (monkeys[name].op) {
        //     case '+':
        //         return rec_calc_monkey2(monkeys[name].deps.first, monkeys) + rec_calc_monkey(monkeys[name].deps.second, monkeys);
        //     case '-':
        //         return rec_calc_monkey2(monkeys[name].deps.first, monkeys) - rec_calc_monkey(monkeys[name].deps.second, monkeys);
        //     case '*':
        //         return rec_calc_monkey2(monkeys[name].deps.first, monkeys) * rec_calc_monkey(monkeys[name].deps.second, monkeys);
        //     case '/':
        //         return rec_calc_monkey2(monkeys[name].deps.first, monkeys) / rec_calc_monkey(monkeys[name].deps.second, monkeys);
        // }
    }
}

// Run recursive math operations
long long part1() {
    ifstream infile("input.txt");
    string line;

    // Map of names to monkey structs
    unordered_map<string, monkey> monkeys;

    while (getline(infile, line)) {
        istringstream iss(line);

        string name;
        iss >> name;

        string next;
        iss >> next;

        // If is number monkey
        if (is_num(next)) {
            monkeys[name] = monkey({true, stoll(next), {"", ""}, ' '});
        }
        // Else is monkey with deps
        else {
            char op;
            string last;
            iss >> op >> last;
            monkeys[name] = monkey({false, 0, {next, last}, op});
        }
    }

    // monkeys["humn"].is_num = true;
    // monkeys["humn"].num = 3469704905530;

    // 3469704905530 too high?? For humn
    // Nvm it's 3469704905529
    cout << rec_calc_monkey("wvvv", monkeys) << endl;
    cout << rec_calc_monkey("whqc", monkeys) << endl;

    // cout << rec_calc_monkey("pppw", monkeys) << endl;
    // cout << rec_calc_monkey("sjmn", monkeys) << endl;

    return rec_calc_monkey("root", monkeys);
}

// Find number needed to give a specific value for recursive math operations
long long part2() {
    ifstream infile("test.txt");
    string line;

    // Map of names to monkey structs
    unordered_map<string, monkey> monkeys;

    while (getline(infile, line)) {
        istringstream iss(line);

        string name;
        iss >> name;

        string next;
        iss >> next;

        // If is number monkey
        if (is_num(next)) {
            monkeys[name] = monkey({true, stoll(next), {"", ""}, ' '});
        }
        // Else is monkey with deps
        else {
            char op;
            string last;
            iss >> op >> last;
            monkeys[name] = monkey({false, 0, {next, last}, op});
        }
    }

    // monkeys["humn"].is_num = true;
    // monkeys["humn"].num = 3469704905530;

    // 3469704905530 too high?? For humn
    // cout << rec_calc_monkey2("wvvv", monkeys) << endl;
    // cout << rec_calc_monkey("whqc", monkeys) << endl;

    cout << rec_calc_monkey2("pppw", monkeys) << endl;
    cout << rec_calc_monkey("sjmn", monkeys) << endl;

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