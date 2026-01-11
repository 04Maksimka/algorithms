#include <iostream>

int main(){
    int n;
    std::cout << "Write an integer: ";
    std::cin >> n;
    int i = 1;

    while (i < n) {
        std::cout << i << "\t" << i * i << "\n";
        ++i;
    }

    return 0;
}