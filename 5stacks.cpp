// Move crates (chars) between stacks

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Move crates in reverse order (normal stack operations)
string part1(vector<vector<char>> v) {
    ifstream infile("input.txt");
    string line;
    char c, c1, c2, c3;

    while (getline(infile, line)) {
        istringstream iss(line);
        string s;
        int num, from, to;

        iss >> s >> num >> s >> from >> s >> to;
        from--;
        to--;

        // Move number of crates between those two stacks
        for (int i = 0; i < num; i++) {
            v[to].push_back(v[from].back());
            v[from].pop_back();
        }
    }

    string res = "";

    for (int i = 0; i < v.size(); i++) {
        res += v[i].back();
    }

    return res;
}

// Move crates in order
string part2(vector<vector<char>> v) {
    ifstream infile("input.txt");
    string line;
    char c, c1, c2, c3;

    while (getline(infile, line)) {
        istringstream iss(line);
        string s;
        int num, from, to;

        iss >> s >> num >> s >> from >> s >> to;
        from--;
        to--;

        // Use temporary stack so crates moved in order (all together)
        vector<int> temp;

        // Move number of crates between those two stacks
        for (int i = 0; i < num; i++) {
            temp.push_back(v[from].back());
            v[from].pop_back();
        }

        for (int i = 0; i < num; i++) {
            v[to].push_back(temp.back());
            temp.pop_back();
        }
    }

    string res = "";

    for (int i = 0; i < v.size(); i++) {
        res += v[i].back();
    }

    return res;
}

int main() {
    // vector<char> v1{'N', 'B', 'D', 'T', 'V', 'G', 'Z', 'J'};
    // vector<char> v2{'S', 'R', 'M', 'D', 'W', 'P', 'F'};
    // vector<char> v3{'V', 'C', 'R', 'S', 'Z'};

    // vector<vector<char>> v;
    // v.push_back(v1);
    // v.push_back(v2);
    // v.push_back(v3);

    // Pre-initialize all stacks as a vector of vectors (2D vector)
    vector<char> v1{'N', 'B', 'D', 'T', 'V', 'G', 'Z', 'J'};
    vector<char> v2{'S', 'R', 'M', 'D', 'W', 'P', 'F'};
    vector<char> v3{'V', 'C', 'R', 'S', 'Z'};
    vector<char> v4{'R', 'T', 'J', 'Z', 'P', 'H', 'G'};
    vector<char> v5{'T', 'C', 'J', 'N', 'D', 'Z', 'Q', 'F'};
    vector<char> v6{'N', 'V', 'P', 'W', 'G', 'S', 'F', 'M'};
    vector<char> v7{'G', 'C', 'V', 'B', 'P', 'Q'};
    vector<char> v8{'Z', 'B', 'P', 'N'};
    vector<char> v9{'W', 'P', 'J'};

    vector<vector<char>> v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);
    v.push_back(v8);
    v.push_back(v9);

    cout << part1(v) << endl;
    cout << part2(v) << endl;
}