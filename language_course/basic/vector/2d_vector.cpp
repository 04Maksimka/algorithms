#include <iostream>
#include <vector>

int main() {
    size_t m, n;
    std::cin >> m >> n;  // число строк и столбцов

    // создаём матрицу matrix из m строк, каждая из которых — вектор из n нулей
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));

    for (size_t i = 0; i != m; ++i) {
        for (size_t j = 0; j != n; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    // напечатаем матрицу, выводя элементы через табуляцию
    for (size_t i = 0; i != m; ++i) {
        for (size_t j = 0; j != n; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}
