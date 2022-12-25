#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <deque>
#include <algorithm>

using namespace std;

struct visit {
    int dist;
    string parent;
};

void build_adj_mat(vector<vector<int>>& adj_mat) {

}

void rec_dfs(int total, int flow, int time_left, int curr, unordered_set<int> visited, vector<int>& totals, vector<vector<int>>& adj_mat, unordered_map<int, int>& flows) {
    // If visited
    if (visited.find(curr) != visited.end()) {
        return;
    }

    visited.insert(curr);

    // Open valve
    flow += flows[curr];

    // Add all neighbors to path
    for (int i = 0; i < adj_mat.size(); i++) {
        if (i == curr) {
            continue;
        }

        // If have time to open next valve
        if (time_left - adj_mat[curr][i] - 1 > 0) {
            rec_dfs(total + flow * (adj_mat[curr][i] + 1),
                flow, time_left - adj_mat[curr][i] - 1, i, visited, totals, adj_mat, flows);
        }
        // Otherwise run out of time
        else {
            totals.push_back(total + flow * time_left);
        }
    }
}

// DFS all paths from 2 starting points simultaneously
// I stopped it early and found the highest value so far (it was right)
void rec_dfs2(int total, int flow, int time_left, int curr, 
    int flow2, int time_left2, int curr2, unordered_set<int> visited,
    vector<int>& totals, vector<vector<int>>& adj_mat, unordered_map<int, int>& flows) {

    // If either visited
    // if (visited.find(curr) != visited.end() or visited.find(curr2) != visited.end()) {
    //     return;
    // }

    // visited.insert(curr);

    // Open valve
    // flow += flows[curr];

    // Progress path 1
    if (time_left > time_left2) {
        bool has_next = false;
        for (int i = 0; i < adj_mat.size(); i++) {
            // Skip if self
            if (i == curr) {
                continue;
            }

            // Skip if visited
            if (visited.find(i) != visited.end() or (i == 0 and time_left < 26)) {
                continue;
            }

            // If have time to open next valve
            if (adj_mat[curr][i] < 10 and time_left - adj_mat[curr][i] - 1 > 0) {
                visited.insert(i);
                has_next = true;
                // flow += flows[i];

                rec_dfs2(total + flow * (adj_mat[curr][i] + 1),
                    flow + flows[i], time_left - adj_mat[curr][i] - 1, i,
                    flow2, time_left2, curr2,
                    visited, totals, adj_mat, flows);
                
                visited.erase(i);
            }
            // // Otherwise run out of time
            // else {
            //     totals.push_back(total + flow * time_left + flow2 * time_left2);
            // }
        }

        // If out of nodes to visit
        if (not has_next) {
            int curr_total = total + flow * time_left + flow2 * time_left2;

            if (curr_total > 2300) {
                cout << curr_total << endl;
                totals.push_back(curr_total);
            }
        }
    }
    // Progress path 2
    else {
        bool has_next = false;
        for (int i = 0; i < adj_mat.size(); i++) {
            // Skip if self
            if (i == curr2) {
                continue;
            }

            // Skip if visited
            if (visited.find(i) != visited.end() or (i == 0 and time_left2 < 26)) {
                continue;
            }

            // If have time to open next valve
            if (adj_mat[curr2][i] < 10 and time_left2 - adj_mat[curr2][i] - 1 > 0) {
                visited.insert(i);
                has_next = true;
                // flow2 += flows[i];

                rec_dfs2(total + flow2 * (adj_mat[curr2][i] + 1),
                    flow, time_left, curr,
                    flow2 + flows[i], time_left2 - adj_mat[curr2][i] - 1, i,
                    visited, totals, adj_mat, flows);
                
                visited.erase(i);
            }
            // Otherwise run out of time
            // else {
            //     totals.push_back(total + flow * time_left + flow2 * time_left2);
            // }
        }

        // If out of nodes to visit
        if (not has_next) {
            int curr_total = total + flow * time_left + flow2 * time_left2;

            if (curr_total > 2300) {
                cout << curr_total << endl;
                totals.push_back(curr_total);
            }
        }
    }   
}

// Find weird optimal traversal of a weighted graph for maximum value 
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
    unordered_map<int, int> flows;

    int i = 1;

    while (getline(infile, line)) {
        // Get input
        istringstream iss(line);

        string u;
        int flow;

        iss >> u >> flow;

        if (flow > 0) {
            flows[i] = flow;
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

    // Check all paths (DFS)
    // vector<int> totals = {};

    // rec_dfs(0, 0, 30, 0, {}, totals, adj_mat, flows);

    // cout << *max_element(totals.begin(), totals.end()) << endl;

    
    // Part 2
    vector<int> totals2 = {};

    rec_dfs2(0, 0, 26, 0, 0, 26, 0, {}, totals2, adj_mat, flows);

    cout << *max_element(totals2.begin(), totals2.end()) << endl;


    // // Print out adjacency matrix
    // for (int r = 0; r < val_valves.size(); r++) {
    //     for (int c = 0; c < val_valves.size(); c++) {
    //         cout << adj_mat[r][c] << ",";
    //     }
    //     cout << endl;
    // }

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