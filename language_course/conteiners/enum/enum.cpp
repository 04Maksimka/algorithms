enum class Color {
    White,
    Black,
    Red,
    Green,
};

#include <iostream>

// Overload the << operator for the Color enum class
std::ostream& operator<<(std::ostream& os, Color color) {
    switch (color) {
        case Color::White: os << "White"; break;
        case Color::Black: os << "Black"; break;
        case Color::Red: os << "Red"; break;
        case Color::Green: os << "Green"; break;
    }
    return os;
}

int main(){
    Color color_1 = Color::Red;
    Color color_2 = Color::Green;

    std::cout << color_1 << "\n";
}