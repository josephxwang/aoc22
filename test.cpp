#include <iostream>

using namespace std;

int main() {
    string s1, s2;
    s1 = "Hello";

    s2 = s1;

    s1 = "Hi";

    cout << s1 << endl;
    cout << s2 << endl;
}