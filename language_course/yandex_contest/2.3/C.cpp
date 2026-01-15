#include <iostream>

int main(){
    int year;
    std::cin >> year;

    if (year % 4 == 0){
        if (year % 100 == 0){
            if (year % 400 == 0){
                std::cout << "YES";
            }
            else{
                std::cout << "NO";
            }
        }
        else{
            std::cout << "YES";
        }
    }
    else{
        std::cout << "NO";
    }
}