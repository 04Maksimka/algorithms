// chess
#include <iostream>
#include <cmath>

int main(){
    int x_1, y_1, x_2, y_2;
    std::cin >> x_1 >> y_1 >> x_2 >> y_2;

    if ((x_1 == x_2) || (y_1 == y_2) || (abs(x_1 - x_2) == abs(y_1 - y_2))){
        std::cout << "YES";
    }
    else{
        std::cout << "NO";
    }

}
