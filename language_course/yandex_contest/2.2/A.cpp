#include <iostream>


double CmToDuim(double& cm){
    return cm / 2.54;
}

int main(){
    double cm;
    std::cin >> cm;
    std::cout << CmToDuim(cm);

}
