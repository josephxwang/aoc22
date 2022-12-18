#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

// struct edge {
//     string dest;
//     int weight;
// };

int part1() {
    ifstream infile("test.txt");
    string line;

    // Map of valves with flow to their flow rates
    unordered_map<string, int> flows;

    // Graph of valves with flow rates
    unordered_map<string, unordered_map<string, int>> graph;

    // Graph of valves with no flow rate
    unordered_map<string, unordered_map<string, int>> zeros_graph;

    while (getline(infile, line)) {
        // Get input
        istringstream iss(line);

        string u;
        int flow;

        iss >> u >> flow;

        vector<string> v_vect;
        string dest;

        while (iss >> dest) {
            v_vect.push_back(dest);
        }
        
        
        // If has flow rate
        if (flow != 0 or u == "AA") {
            // Save flow rate
            flows[u] = flow;

            graph[u] = {};

            // Check all destination nodes
            for (auto v : v_vect) {
                // If v is a zero node
                if (zeros_graph.find(v) != zeros_graph.end()) {
                    // Find edges to resolve
                    for (auto e : zeros_graph[v]) {
                        // Skip if resolving to self
                        if (u == e.first) {
                            continue;
                        }

                        // Resolve proper edge (non-zero node)
                        graph[u][e.first] = e.second + 1;
                    }
                }
                // Otherwise add node to graph
                else {
                    graph[u][v] = 1;
                }
            }
        }
        // If zero node (no flow rate)
        else {
            zeros_graph[u] = {};
            vector<string> nodes_to_resolve;
            vector<string> zero_nodes_to_resolve;

            // Check all destination nodes v
            for (auto v : v_vect) {
                // If v is a zero node
                if (zeros_graph.find(v) != zeros_graph.end()) {
                    // Find edges to resolve
                    for (auto e : zeros_graph[v]) {
                        // Skip if resolving to self
                        if (u == e.first) {
                            zero_nodes_to_resolve.push_back(v);
                            continue;
                        }

                        // Resolve proper edge (non-zero node)
                        zeros_graph[u][e.first] = e.second + 1;
                    }
                }
                // Otherwise add v to graph
                else {
                    zeros_graph[u][v] = 1;
                    nodes_to_resolve.push_back(v);
                }
            }

            // Resolve where u appears in other node edge lists if needed
            // u is zero node
            // v is value node (normal node)
            for (auto v : nodes_to_resolve) {
                // If v already exists
                if (graph.find(v) != graph.end()) {
                    // Find edge that contains u to resolve it
                    int old_weight = graph[v][u];

                    // Find edge to resolve to (1 of 2)
                    for (auto e : zeros_graph[u]) {
                        if (v == e.first) {
                            continue;
                        }

                        // Resolve proper edge (non-zero node)
                        graph[v][e.first] = e.second + 1;

                        // Remove old edge
                        graph[v].erase(u);                        
                    }
                }
            }

            // Resolve where u appears in other zero node edge lists if needed
            // u is zero node
            // v is zero node too
            for (auto v : zero_nodes_to_resolve) {
                // If v already exists
                if (zeros_graph.find(v) != zeros_graph.end()) {
                    // Find edge to resolve to (1 of 2)
                    for (auto e : zeros_graph[u]) {
                        // Check if unique edge
                        bool has_same_edge = false;
                        string common_node;

                        for (auto f : zeros_graph[v]) {
                            if (e.first == f.first) {
                                has_same_edge = true;
                                common_node = e.first;
                            }
                        }

                        // Change old zero node to new zero node in common node
                        if (has_same_edge) {
                            // Add new zero node
                            for (auto g : zeros_graph[u]) {
                                if (common_node == g.first) {
                                    continue;
                                }

                                // Resolve proper edge (non-zero node)
                                graph[common_node][g.first] = graph[common_node][u] + 1;
                            }
                            
                            // Remove old zero node
                            graph[common_node].erase(u);
                        }

                        // Resolve proper edge (zero node)
                        zeros_graph[v][e.first] = e.second + 1;

                        // Remove old edge
                        zeros_graph[v].erase(u);
                    }
                }
            }
        }    
    }

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