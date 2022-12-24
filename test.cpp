#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> l1 = {1,2,3};

    auto l2 = l1;

    l1 = {};

    cout << l2.size();
}
