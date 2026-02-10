#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// линейный поиск за O(n)
bool CanPlaceCows(const vector<int>& stalls, int k, int dist) {
    int count = 1; // Первую корову ставим в первое стойло
    int lastPosition = stalls[0];
    
    for (int i = 1; i < stalls.size(); i++) {
        if (stalls[i] - lastPosition >= dist) {
            count++;
            lastPosition = stalls[i];
            
            if (count == k) {
                return true;
            }
        }
    }
    
    return false;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> stalls(n);
    for (int i = 0; i < n; i++) {
        cin >> stalls[i];
    }
    
    sort(stalls.begin(), stalls.end());
    
    int left = 1;
    int right = stalls[n - 1] - stalls[0];
    int answer = 0;
    // стандартный бинпоиск O(n)
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (CanPlaceCows(stalls, k, mid)) {
            answer = mid;
            left = mid + 1; // Пробуем найти больше
        } else {
            right = mid - 1; // Уменьшаем расстояние
        }
    }
    
    cout << answer << endl;
    
    return 0;
}