#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> events;
    
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        
        int left = min(a, b);
        int right = max(a, b);
        
        // Event: +1 at left endpoint (segment opens)
        events.push_back({left, 1});
        // Event: -1 at right+1 (segment closes after right)
        events.push_back({right + 1, -1});
    }
    
    // Sort events by a_i
    sort(events.begin(), events.end());
    
    vector<pair<int, int>> prefix;
    int current_count = 0;
    
    for (auto& event : events) {
        current_count += event.second;
        prefix.push_back({event.first, current_count});
    }
    
    vector<int> ans_arr(m);

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        
        // Binary search
        int left = 0, right = prefix.size() - 1;
        int answer = 0;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (prefix[mid].first <= x) {
                answer = prefix[mid].second;
                ans_arr[i] = answer;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    for (int ans : ans_arr) {
        cout << ans << " ";
    }
    
    return 0;
}