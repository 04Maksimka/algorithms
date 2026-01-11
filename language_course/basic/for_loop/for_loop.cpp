/*
for loop:
for (initialization, condition; action) {
body of the function
}
*/
#include <iostream>

using namespace std;

int main() {
    for (int i = 1; i <= 10; ++i) {
        cout << i << "\t" << i * i << "\n";
    }
}