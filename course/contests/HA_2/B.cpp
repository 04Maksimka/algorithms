#include <vector>
#include <iostream>
#include <algorithm>

size_t FindInd(const std::vector<int>& vec, int target) {
    size_t left = 0;
    size_t right = vec.size();

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (vec[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left ;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i != n; ++i) {
        std::cin >> vec[i];
    }
    std::sort(vec.begin(), vec.end());

    int k;
    std::cin >> k;
    std::vector<std::pair<int, int>> requests(k);
    for (int i = 0; i != k; ++i) {
        int l;
        int r;
        std::cin >> l >> r;
        requests[i] = {l, r};
    }

    for (const auto& request : requests) {
        int l = request.first;
        int r = request.second;

        size_t left_ind = FindInd(vec, l);
        size_t right_ind = FindInd(vec, r + 1);

        std::cout << right_ind - left_ind << " ";
    }
    std::cout << std::endl;

}