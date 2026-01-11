#include <iostream>
#include <vector>

int main() {
    std::vector<double> data = {1, 2, 4};

    for (double elem : data) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}