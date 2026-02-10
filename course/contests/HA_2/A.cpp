#include <vector>
#include <iostream>

std::vector<int> Merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    size_t i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            ++i;
        } else {
            result.push_back(right[j]);
            ++j;
        }
    }
    // append the remaining
    while (i < left.size()) {
        result.push_back(left[i]);
        ++i;
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        ++j;
    }

    return result;
}

std::vector<int> MergeSort(const std::vector<int>& vec) {
    if (vec.size() <= 1) {
        return vec;
    }

    size_t mid = vec.size() / 2;
    std::vector<int> left(vec.begin(), vec.begin() + mid);
    std::vector<int> right(vec.begin() + mid, vec.end());

    return Merge(MergeSort(left), MergeSort(right));
}

int main() {
    int N;
    std::cin >> N;
    std::vector<int> vec(N); // we allocate space for the vector

    for (int i = 0; i != N; ++i) {
        std::cin >> vec[i];
    }

    std::vector<int> sorted_vec = MergeSort(vec);

    for (const int& num : sorted_vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
