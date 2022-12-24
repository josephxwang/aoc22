#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <deque>

using namespace std;

struct visit {
    int dist;
    string parent;
};

int part1() {
    ifstream infile("16input.txt");
    string line;

    // Add all valves to graph
    unordered_map<string, vector<string>> graph;

    // List of value valves
    unordered_map<string, int> val_valves;
    unordered_set<string> val_valves_set;
    val_valves["AA"] = 0;

    // Map of value valves to their flow rates
    unordered_map<string, int> flows;

    int i = 1;

    while (getline(infile, line)) {
        // Get input
        istringstream iss(line);

        string u;
        int flow;

        iss >> u >> flow;

        if (flow > 0) {
            flows[u] = flow;
            graph[u] = {};
            val_valves[u] = i;

            val_valves_set.insert(u);

            i++;
        }

        // vector<string> v_vect;
        string dest;

        while (iss >> dest) {
            graph[u].push_back(dest);
        } 
    }

    // Initialize adjacency matrix
    vector<vector<int>> adj_mat;

    for (int r = 0; r < val_valves.size(); r++) {
        adj_mat.push_back({});
        for (int c = 0; c < val_valves.size(); c++) {
            adj_mat[r].push_back(0);
        }
    }

    vector<vector<string>> adj_mat_parent;

    for (int r = 0; r < val_valves.size(); r++) {
        adj_mat_parent.push_back({});
        for (int c = 0; c < val_valves.size(); c++) {
            adj_mat_parent[r].push_back("");
        }
    }
    
    // BFS from all value valves to all other value valves
    for (auto u : val_valves) {
        deque<string> q;
        q.push_back(u.first);

        // Track valves visited and distance
        unordered_map<string, visit> visited;

        for (auto node : graph) {
            visited[node.first].dist = -1;
            visited[node.first].parent = "";
        }

        visited[u.first].dist = 0;
        visited[u.first].parent = u.first;

        while (!q.empty()) {
            string curr = q.front();
            q.pop_front();

            for (string nbr : graph[curr]) {
                // If not visited
                if (visited[nbr].dist == -1) {
                    visited[nbr].dist = visited[curr].dist + 1;

                    // If a value valve
                    if (val_valves.find(nbr) != val_valves.end()) {
                        adj_mat[val_valves[u.first]][val_valves[nbr]] = visited[nbr].dist;
                        adj_mat[val_valves[nbr]][val_valves[u.first]] = visited[nbr].dist;
                    }

                    q.push_back(nbr);
                }
            }
        }
    }

    // Print out adjacency matrix
    for (int r = 0; r < val_valves.size(); r++) {
        for (int c = 0; c < val_valves.size(); c++) {
            cout << adj_mat[r][c] << ",";
        }
        cout << endl;
    }

    // @@ NEED TO TRACK LAST VALUE VALVE

    // @@ TEST ON LARGER SAMPLE, SEE IF CORRECT
    // @@ THEN BUILD ADJACENCY MATRIX AND SEE IF CAN MAKE PROGRESS BY INSPECTION 

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