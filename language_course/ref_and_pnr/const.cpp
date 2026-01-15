#include <iostream>
#include <vector>

void bubble_sort(int* a, int n) {
    for (int k = 0; k != n; ++k)
        for (int i = 0; i != n - 1; ++i)
            // сравниваем элемент со следующим
            if (a[i] > a[i + 1])
                // меняем местами, если следующий меньше
                std::swap(a[i], a[i + 1]);
}

int main() {
    int a[5] = {5, 2, 1, 3, 1};

    bubble_sort(a, 5);

    for (int i = 0; i != 5; ++i)
        std::cout << a[i] << " ";
}
