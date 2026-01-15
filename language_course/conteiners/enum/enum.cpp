enum class Color {
    White,
    Black,
    Red,
    Green,
    Blue,
};

#include <iostream>

struct Point {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    Color color;  // пусть у нас будет цветная точка
};


int main() {
    Point point1;  // по умолчанию координаты будут нулевыми, а color никак не будет проинициализирован
    point1.color = Color::Blue;

    Point point2 = {1.4, -2.2, -3.98, Color::Red};
    // x = 1.4, y = -2.2, z = -3.98, color = Color::Red

    point2.z = 32;  // обращаться к полям можно через точку
    point2.x += 2;  // и вообще работать с ними как с обычными переменными
}
