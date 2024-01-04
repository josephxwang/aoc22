#include <iostream>
#include <vector>
#include <unordered_set>
#include <math.h>
#include <algorithm>
#include <functional>

using namespace std;

// template <typename T>
// void operator+=(vector<T> &a, vector<T> &b) {
//     transform(a.begin(), a.end(), b.begin(), a.begin(), plus<T>());
// }

// // Custom - operator for vectors for element-wise addition
// template <typename T>
// vector<T> operator-(vector<T> &a, vector<T> &b) {
//     vector<T> result(a.size(), 0);
//     transform(a.begin(), a.end(), b.begin(), result.begin(), minus<T>());
//     return result;
// }

int main() {
    vector<int> a = {1,0,1,0};
    vector<int> b = {};

    b = a;
    a = {};

    // a += b;

    // vector<int> c = b - a;

    for (int n : a) {
        cout << n << ' ';
    }

    cout << endl;

    for (int n : b) {
        cout << n << ' ';
    }
}
