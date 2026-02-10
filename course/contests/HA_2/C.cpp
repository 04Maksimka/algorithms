#include <iostream>
#include <algorithm>

int main() {
    long long w, h, n;
    std::cin >> w >> h >> n;
    
    long long left = 1, right = 1;

    while ((right / w) * (right / h) < n) {
    right *= 2;
}
    
    long long answer = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        long long count = (mid / w) * (mid / h);
        
        if (count >= n) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    std::cout << answer << std::endl;
    
    return 0;
}