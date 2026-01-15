#include <iostream>
#include <algorithm>

int main(){
    int x, y, z;
    int a, b, c;
    std::cin >> a >> b >> c;

    x = std::min({a, b, c});
    z = std::max({a, b, c});
    y = a + b + c - x - z;

    if (x + y < z){
        std::cout << "UNDEFINED";
    }
    else if (x * x + y * y == z * z){
        std::cout << "YES";
    }
    else{
        std::cout << "NO";
    }
}