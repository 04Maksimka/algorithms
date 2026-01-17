#include <iostream>
#include <string>

void Print(int value) {
    std::cout << value << "\n";
}

void Print(const std::string& name, int value) {
    std::cout << name << ": " << value << "\n";  // печатаем название и саму величину
}

void Print(const std::string& str) {
    std::cout << str << "\n";
}

int main() {
    Print(42);  // версия 1
    Print("x", 42);  // версия 2
    Print("good bye");  // версия 3
}
