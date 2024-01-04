#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
// #include <unordered_map>

using namespace std;

int part1() {
    ifstream infile("test.txt");
    string line;

    // One vector has actual numbers in original order
    // Other vector has indices of numbers in mixed order 
    // Has duplicate numbers
    vector<int> num_origs;
    vector<int> i_news;

    // Save index of 0 in original list
    int zero_i;

    // vector<int> mixed;

    // Map of indices to number
    // unordered_map<int, int> nums;

    int i = 0;
    while (getline(infile, line)) {
        num_origs.push_back(stoi(line));
        // mixed.push_back(stoi(line));

        if (stoi(line) == 0) {
            zero_i = i;
        }

        i_news.push_back(i);
        i++;
    }

    int n = num_origs.size();

    // Mix each number
    for (int i = 0; i < n; i++) {
        int curr = num_origs[i];
        
        // Numbers wrap around on n-1, not n, because of weird insertion logic
        curr %= (n-1);

        // Find where number occurs in mixed list (find by index)
        int start_i = find(i_news.begin(), i_news.end(), i) - i_news.begin();

        // Find new index, using mod to wrap around to positive indices
        int new_i = (start_i + curr) % n;

        // If goes off front side of list
        if (new_i == 0) {
            new_i = n-1;
        }

        // If wrapping around from the front (negative index)
        if (new_i < 0) {
            new_i = (new_i + n) % n - 1;

            i_news.erase(i_news.begin() + start_i);
            i_news.insert(i_news.begin()+new_i, i);
        }
        else {
            // First delete old number
            i_news.erase(i_news.begin() + start_i);

            // If number moved forward in list by wrapping back
            if (new_i < start_i and curr > 0) {
                i_news.insert(i_news.begin()+new_i+1, i);
            }
            // If moved back in list
            else {
                i_news.insert(i_news.begin()+new_i, i);
            }  
        }

        
    }

    for (int i : i_news) {
        cout << num_origs[i] << endl;
    }
    cout << endl;

    int sum = 0;

    // Find where 0 is in new list
    int zero_new_i = find(i_news.begin(), i_news.end(), zero_i) - i_news.begin();

    for (int i = 1000; i < 4000; i += 1000) {
        int index = (zero_new_i + i) % i_news.size();
        sum += num_origs[i_news[index]];
    }
    // sum += num_origs[i_news[(zero_new_i+1000) % i_news.size()]];
    // sum += num_origs[i_news[(zero_new_i+2000) % i_news.size()]];
    // sum += num_origs[i_news[(zero_new_i+3000) % i_news.size()]];

    return sum;
}

long long part2() {
    ifstream infile("test.txt");
    string line;

    // One vector has actual numbers in original order
    // Other vector has indices of numbers in mixed order 
    // Has duplicate numbers
    // vector<long> num_origs_origs;
    vector<long long> num_origs;
    vector<int> i_news;

    // Save index of 0 in original list
    int zero_i;

    // int key = 811589153 % 4999;

    int i = 0;
    while (getline(infile, line)) {
        // num_origs_origs.push_back(stoi(line));
        num_origs.push_back(stoll(line) * 811589153);
        // mixed.push_back(stoi(line));

        if (stoi(line) == 0) {
            zero_i = i;
        }

        i_news.push_back(i);
        i++;
    }

    int n = num_origs.size();

    // Mix each number
    for (int j = 0; j < 10; j++) {
        for (long long i : i_news) {
            cout << num_origs[i] << endl;
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            long long curr = num_origs[i];
            
            // Numbers wrap around on n-1, not n, because of weird insertion logic
            curr %= (n-1);

            // Find where number occurs in mixed list (find by index)
            int start_i = find(i_news.begin(), i_news.end(), i) - i_news.begin();

            // Find new index, using mod to wrap around to positive indices
            int new_i = (start_i + curr) % n;

            // If goes off front side of list
            if (new_i == 0) {
                new_i = n-1;
            }

            // // Correct negative index
            // new_i = (new_i + n) % n;

            // First delete old number
            i_news.erase(i_news.begin() + start_i);

            // // If before self
            // if (new_i <= start_i) {
            //     i_news.insert(i_news.begin()+new_i, i);
            // }
            // // If after self
            // else if (new_i > start_i) {
            //     i_news.insert(i_news.begin()+new_i-1, i);
            // }

            // If wrapping around from the front (negative index)
            if (new_i < 0) {
                new_i = (new_i + n) % n - 1;

                i_news.insert(i_news.begin()+new_i, i);
            }
            else {
                // If number moved forward in list by wrapping back
                if (new_i < start_i and curr > 0) {
                    i_news.insert(i_news.begin()+new_i+1, i);
                }
                // If moved back in list
                else {
                    i_news.insert(i_news.begin()+new_i, i);
                }  
            }
        }
    }

    long long sum = 0;

    // Find where 0 is in new list
    int zero_new_i = find(i_news.begin(), i_news.end(), zero_i) - i_news.begin();

    for (int i = 1000; i < 4000; i += 1000) {
        int index = (zero_new_i + i) % i_news.size();
        long long num = num_origs[i_news[index]];

        // num = num / 1503 * 811589153;

        cout << num << endl;
        sum += num;
    }
    // sum = sum / 5 * 811589153;

    return sum;
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