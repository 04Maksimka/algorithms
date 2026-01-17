#include <iostream>
#include <cmath>

int main() {
    int n;
    std::cin >> n;
    
    double sum = 0.0;

    for (int k = 1; k <= n; ++k) {
        double sign = std::pow(-1.0, k + 1);
        sum += sign / k;
    }
    
    std::cout << sum;
}