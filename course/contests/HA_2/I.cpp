#include <vector>
#include <iostream>
#include <cmath>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> array1(n);
    for (size_t i = 0; i != n; ++i) {
        std::cin >> array1[i];
    }

    std::vector<int> array2(m);
    for (size_t i = 0; i != m; ++i) {
        std::cin >> array2[i];
    }

    size_t i = 0;
    size_t j = 0;
    int min_diff = std::abs(array1[0] - array2[0]);

    while (i != array1.size() && j != array2.size()) {
        int curr_diff = array1[i] - array2[j];
        if (std::abs(curr_diff) < min_diff) {
            min_diff = std::abs(curr_diff);
        }
        if (curr_diff > 0) {
            ++j;
        }
        else {
            ++i;
        }
    }

    // Check the rest 
    while (j != array2.size()) {
        int curr_diff = array1[i - 1] - array2[j];
        if (std::abs(curr_diff) < min_diff) {
            min_diff = std::abs(curr_diff);
        }
        ++j;
    }
    
    while (i != array1.size()) {
        int curr_diff = array1[i] - array2[j - 1];
        if (std::abs(curr_diff) < min_diff) {
            min_diff = std::abs(curr_diff);
        }
        ++i;
    }

    std::cout << min_diff << std::endl;
}