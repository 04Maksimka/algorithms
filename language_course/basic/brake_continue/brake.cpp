#include <iostream>

int main(){
    int sum = 0;

    while (true) {
        int x;
        std::cin >> x;

        if (x == 0) {
            std::cout << "sum = " << sum;
            break;
        }

        sum += x;
    }
}