#include <iostream>
int main() {
    int a, b, x;
    // Инициализация переменных для предотвращения ошибок
    a = 0;
    b = 10;
    x = 5;

    if (a <= x && x <= b) {
        // точка x лежит на отрезке [a; b]
        std::cout << "x is within the range [" << a << "; " << b << "]\n";
    } else {
        // точка x лежит вне отрезка [a; b]
        std::cout << "x is outside the range [" << a << "; " << b << "]\n";
    }
}
