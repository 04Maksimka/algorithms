#include <vector>
#include <utility>
#include <iostream>

std::pair<size_t, size_t> MatrixArgMax(const std::vector<std::vector<int>>& matrix) {
    // Handle empty matrix (or empty rows) gracefully
    if (matrix.empty() || matrix[0].empty()) {
        return {0, 0};  // or throw an exception if preferred
    }

    size_t max_row_ind = 0;
    size_t max_col_ind = 0;

    for (size_t row = 0; row < matrix.size(); ++row) {
        for (size_t col = 0; col < matrix[row].size(); ++col) {
            if (matrix[row][col] > matrix[max_row_ind][max_col_ind]) {
                max_row_ind = row;
                max_col_ind = col;
            }
        }
    }

    return {max_row_ind, max_col_ind};
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 10, 0},
    };

    auto max_pos = MatrixArgMax(matrix);

    std::cout << "Maximum element found at row " << max_pos.first
              << ", column " << max_pos.second << std::endl;
    // Output: Maximum element found at row 1, column 1

    return 0;
}