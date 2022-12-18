#include <iostream>

using namespace std;

struct edge {
    string dest;
    int weight;
};

int main() {
    cout << edge("test", 12).dest << endl;
    cout << edge({"test", 12}).weight << endl;
}