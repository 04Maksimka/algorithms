#include <vector>
#include <utility>
#include <iostream>
#include <deque>
#include <algorithm>

std::pair<int, int> FindMaxValues(std::vector<int>& vec) {
    // Ищем два самых больших элемента в массиве
    int big_max = vec[0];
    int small_max = vec[1];
    if (small_max > big_max){
        big_max = vec[1];
        small_max = vec[0];
    }

    for (size_t i = 2; i != vec.size(); ++i){
        int current = vec[i];
        if (current > small_max){
            if (current > big_max){
                small_max = big_max;
                big_max = current;
            }
            else{
                small_max = current;
            }
        }
    }

    return {small_max, big_max};
}

int main(){
    int n, k;
    std::cin >> n >> k;
    std::deque<int> window;
    long long ans = 0;

    for(int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if(!window.empty()) {
            std::vector<int> temp(window.begin(), window.end());
            int max_prev;
            if(temp.size() == 1) {
                max_prev = temp[0];
            } else {
                auto p = FindMaxValues(temp);
                max_prev = p.second;
            }
            long long prod = (long long) x * max_prev;
            ans = std::max(ans, prod);
        }
        window.push_back(x);
        if(window.size() > k) {
            window.pop_front();
        }
    }
    std::cout << ans << std::endl;
    return 0;
}