// Insertion sorting algorithm implementation in C++

#include <vector>
#include <iostream>

#include <vector>
#include <iostream>

void InsertionSort(std::vector<int>& data) {
    int n = (int)data.size();
    
    for (int j = 1; j != n; ++j) {
        int current = data[j];
        int i;
        
        for (i = j; i > 0 && data[i - 1] > current; --i) {
            data[i] = data[i - 1];
        }
        data[i] = current;
    }
}


int main() {
    std::vector<int> data = {12, 2, 4, 4, 8, 1, 29};

    InsertionSort(data);

    for (auto elem : data) {
        std::cout << elem << " ";
    }
}
