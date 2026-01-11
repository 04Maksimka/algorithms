#include <cstdint>
#include <iostream>

int main() {
    int64_t a, b;
    char operation;
    std::cin >> a >> operation >> b;

    int64_t result;
    switch (operation) {
        case '+':
            result = a + b;
            break;  // если не написать этот break, программа просто пойдёт дальше в код следующего блока case
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = 1.0 * a / b;
            break;
        case '%':
            result = a % b;
            break;
        default:  // здесь обрабатывается случай, когда ни один case не сработал.
            result = 0;
    }

    std::cout << result << "\n";
}
