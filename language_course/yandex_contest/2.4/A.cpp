#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::string password;
    std::cin >> password;

    size_t len = password.length();
    if (len < 8 || len > 14) {
        std::cout << "NO" << std::endl;
        return 0;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_other = false;

    for (char c : password) {
        if (static_cast<unsigned char>(c) < 33 || static_cast<unsigned char>(c) > 126) {
            std::cout << "NO" << std::endl;
            return 0;
        }
        if (std::isupper(static_cast<unsigned char>(c))) {
            has_upper = true;
        } else if (std::islower(static_cast<unsigned char>(c))) {
            has_lower = true;
        } else if (std::isdigit(static_cast<unsigned char>(c))) {
            has_digit = true;
        } else {
            has_other = true;
        }
    }

    int classes = 0;
    if (has_upper) ++classes;
    if (has_lower) ++classes;
    if (has_digit) ++classes;
    if (has_other) ++classes;

    if (classes >= 3) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
