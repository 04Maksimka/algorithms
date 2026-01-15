#include <algorithm>
#include <iostream>
#include <vector>

struct Date {
    int year = 1970;
    int month = 1;
    int day = 1;
};

int main() {
    std::vector<Date> dates = {
        {2020, 3, 15},
        {2019, 1, 21},
        {2021, 1, 30},
    };

    // напечатаем содержимое:
    for (const auto& [year, month, day] : dates) {
        std::cout << year << "." << month << "." << day << "\n";
    }
}
