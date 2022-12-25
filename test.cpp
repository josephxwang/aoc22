#include <iostream>
#include <vector>
#include <unordered_set>
#include <math.h>
#include <algorithm>

using namespace std;

int main() {
    vector<int> l1 = {1,2,3};

    auto l2 = l1;

    // l1 = {};

    cout << pow(5, 3) << endl;

    cout << *max_element(l1.begin(), l1.end()) << endl;
}
