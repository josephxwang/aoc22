// Track sizes of directories and subdirectories (recursive tree)

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

// Pass address of total and alias to infile
int recLs(int* total, ifstream& infile) {
    string line;
    int dir = 0;
    int dirs = 0;

    while(getline(infile, line)) {
        // If cd command
        if (line[0] == '$') {
            // Consume next cd and ls lines until data
            while (infile.peek() == '$') {
                getline(infile, line);
            }
            break;
        }
        // Count number of subdirectories (for recursion count)
        else if (line[0] == 'd') {
            dirs += 1;
        }
        // Otherwise add up file values
        else {
            istringstream iss(line);
            int num;
            string s;

            iss >> num >> s;

            dir += num;
        }
    }

    // Add up subdirectories
    for (int i = 0; i < dirs; i++){
        dir += recLs(total, infile);
    }

    // Add up size of directory if under 100000
    if (dir <= 100000) {
        *total += dir;
    }
        
    return dir;
}

// Pass address of currMax and alias to infile
int recLs2(int neededSpace, int* currMax, ifstream& infile) {
    string line;
    int dir = 0;
    int dirs = 0;

    while(getline(infile, line)) {
        // If cd command
        if (line[0] == '$') {
            // Consume next cd and ls lines until data
            while (infile.peek() == '$') {
                getline(infile, line);
            }
            break;
        }
        // Count number of subdirectories (for recursion count)
        else if (line[0] == 'd') {
            dirs += 1;
        }
        // Otherwise add up file values
        else {
            istringstream iss(line);
            int num;
            string s;

            iss >> num >> s;

            dir += num;
        }
    }

    // Add up subdirectories
    for (int i = 0; i < dirs; i++){
        dir += recLs2(neededSpace, currMax, infile);
    }

    // Save smallest directory greater than needed space
    if (dir < *currMax && dir > neededSpace) {
        *currMax = dir;
    }
        
    return dir;
}

int part1() {
    ifstream infile("input.txt");
    string line;
    int dir = 0;
    int total = 0;

    while(getline(infile, line)) {
        // If command
        if (line[0] == '$') {
            // For ls command
            if (line[2] == 'l') {
                dir = recLs(&total, infile);

                // Add up size of directory if under 100000
                if (dir <= 100000) {
                    total += dir;
                }
            }
        }
    }

    return total;
}

int part2() {
    ifstream infile("input.txt");
    string line;
    int currSpace = 0;
    int total = 0;

    // Find the current amount of space used
    while(getline(infile, line)) {
        // If command
        if (line[0] == '$') {
            // For ls command
            if (line[2] == 'l') {
                currSpace = recLs(&total, infile);
            }
        }
    }

    // Calculate the space needed
    int freeSpace = (70000000 - currSpace);
    int neededSpace = 30000000 - freeSpace;
    int currMax = numeric_limits<int>::max();

    // Traverse again and find smallest directory less than needed space
    ifstream infile2("input.txt");
    while(getline(infile2, line)) {
        // If command
        if (line[0] == '$') {
            // For ls command
            if (line[2] == 'l') {
                currSpace = recLs2(neededSpace, &currMax, infile2);
            }
        }
    }
    
    return currMax;
}

int main() {
    cout << part1() << endl;
    cout << part2() << endl;
}