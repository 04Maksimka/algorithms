#include <iostream>

int main() {
    int sum = 0;
    long long num;

    std::cin >> num;

    while (num != 0){
        sum += num % 10;
        num /= 10;
    }
    std::cout << sum;
}