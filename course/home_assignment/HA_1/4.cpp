#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 4, 5, 5, 3, 3, 2, 1, 1};
    int max_val = vec[0];

    size_t l = 0;
    size_t r = vec.size() - 1;

    while (l < r){
        size_t mid = (l + r) / 2;
        if (vec[mid + 1] > vec[mid]) {
            l = mid + 1;
        } else {
            r = mid;
        }
        if ((vec[mid] >= vec[mid - 1]) && (vec[mid] >= vec[mid + 1])) {
            max_val = vec[mid];
            break;
        }
    }
    std::cout << max_val << std::endl;
}