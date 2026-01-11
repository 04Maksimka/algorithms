#include <iostream>
#include <vector>

int main() {
    int x;
    std::vector<int> data;
    while (std::cin >> x) {  // читаем числа, пока не закончится ввод
        data.push_back(x);  // добавляем очередное число в вектор
    }

    while (!data.empty() && data.back() == 0) {
        // Пока вектор не пуст и последний элемент равен нулю
        data.pop_back();  // удаляем этот нулевой элемент
    }

    for (size_t i = 0; i != data.size(); ++i) {
    std::cout << data[i] << " ";
}

}
