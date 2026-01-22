#include <vector>
#include <iostream>
#include <algorithm>

// Function to find the product of the two largest values in a vector
int FindMaxProduct(const std::vector<int>& vec) {
    int largest = std::max(vec[0], vec[1]);
    int second_largest = std::min(vec[0], vec[1]);

    for (size_t i = 2; i < vec.size(); ++i) {
        int current = vec[i];
        if (current > largest) {
            second_largest = largest;
            largest = current;
        } else if (current > second_largest) {
            second_largest = current;
        }
    }

    return largest * second_largest;
}

int main() {
    std::vector<int> vec = {1, 2, 2, 6};
    int k = 3;

    int max_product = -1;

    for (size_t i = 0; i <= vec.size() - k - 1; ++i) {
        std::vector<int> subarray(vec.begin() + i, vec.begin() + i + k + 1);
        int current_product = FindMaxProduct(subarray);
        max_product = std::max(max_product, current_product);
    }

    std::cout << max_product << std::endl;
}
