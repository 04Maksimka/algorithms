#include <vector>
#include <utility>
#include <iostream>

int FindMaxValues(std::vector<int>& vec) {
    // Ищем два самых больших элемента в массиве -- их произведение макс
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

    return small_max * big_max;
}

int main(){
    std::vector<int> vec = {1, 2, 2, 4, 8, 5, 7};
    int k = 3;
    int ans = -1;
    
    for (size_t i = 0; i != vec.size() - k; ++i){
        int current = FindMaxValues(vec(begin(vec), end(vec)));
    }
}