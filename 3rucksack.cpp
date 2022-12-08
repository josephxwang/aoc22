#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int part1() {
    ifstream infile("input.txt");
    string s;
    int sum = 0;

    while (infile >> s) {
        unordered_set<char> chars;

        int n = s.length();

        // Add first half of characters to set
        for (int i = 0; i < n / 2; i++) {
            chars.insert(s[i]);
        }

        for (int i = n / 2; i < n; i++) {
            // If found duplicate item
            if (chars.find(s[i]) != chars.end()) {
                int pri = (int)s[i];

                // If capital letter
                if (pri >= 65 && pri <= 90) {
                    sum += (pri - 38);
                }
                // If lowercase letter
                else if (pri >= 97 && pri <= 122) {
                    sum += (pri - 96);
                }

                break;
            }
        }
    }

    return sum;
}

int part2() {
    ifstream infile("input.txt");
    string s;
    int sum = 0;
    int line = 0;

    unordered_set<char> chars1;
    unordered_set<char> chars2;

    while (infile >> s) {
        // Add first line to set chars1
        if (line % 3 == 0) {
            chars1 = {};
            for (int i = 0; i < s.length(); i++) {
                chars1.insert(s[i]);
            }
        }
        // Add overlap of first and second line to set chars2
        else if (line % 3 == 1) {
            chars2 = {};
            for (int i = 0; i < s.length(); i++) {
                if (chars1.find(s[i]) != chars1.end()) {
                    chars2.insert(s[i]);
                }
            }
        }
        // Add value of overlap of third with second and first line to sum
        else if (line % 3 == 2) {
            for (int i = 0; i < s.length(); i++) {
                if (chars2.find(s[i]) != chars2.end()) {
                    int pri = (int)s[i];

                    // If capital letter
                    if (pri >= 65 && pri <= 90) {
                        sum += (pri - 38);
                    }
                    // If lowercase letter
                    else if (pri >= 97 && pri <= 122) {
                        sum += (pri - 96);
                    }

                    break;
                }
            }
        }

        line++;
    }

    return sum;
}

int main() {
    cout << part1() << endl;
    cout << part2() << endl;
}