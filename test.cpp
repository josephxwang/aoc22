#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<pair<int, int>> intervals;

    intervals.push_back({-2, 2});
    intervals.push_back({3, 11});
    intervals.push_back({12, 12});
    intervals.push_back({13, 20});

    vector<pair<int, int>> merged;
    pair<int, int> curr = intervals[0];
    int i = 1;
    pair<int, int> next = intervals[i];
    
    while (i < intervals.size()-1) {
        
        // While two intervals overlap
        while (curr.second >= next.first-1) {
            if (i > intervals.size()-2) {
                break;
            }

            // Merge
            curr.second = max(curr.second, next.second);
            i++;

            next = intervals[i];
        }

        if (i > intervals.size()-2) {
            break;
        }
        
        merged.push_back(curr);
        curr = next;
        i++;
        next = intervals[i];
    }

    // Check last 2 intervals
    // If overlap
    if (curr.second >= next.first-1) {
        curr.second = max(curr.second, next.second);
        merged.push_back(curr);
    }
    else {
        merged.push_back(curr);
        merged.push_back(next);
    }

    for (int i = 0; i < merged.size(); i++) {
        cout << merged[i].first << ' ' << merged[i].second << endl;
    }
    cout << endl;
}