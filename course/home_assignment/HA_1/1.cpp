#include <vector>
#include <iostream>

int main(){
    std::vector<int> arr = {1, 3, 4, 4, 5, 6, 7, 9};
    int s = 9;

    size_t len = arr.size();
    size_t l = 0, r = len - 1; // (l - left pointer, r - right)

    bool existance_flag = false;

    while (l <= r){ // разрешаем i == j
        if (arr[l] + arr[r] > s){
            --r;
        }
        else if (arr[l] + arr[r] < s){
            ++l;
        }
        else{
            existance_flag = true;
            break;
        }
    }

    if (existance_flag) {
        std::cout << "YES";
    }
    else{
        std::cout << "NO";
    }

}