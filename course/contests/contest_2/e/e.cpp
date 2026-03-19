#include <iostream>
#include <queue>

int main() {
    int n;
    std::cin >> n;

    std::queue<int> first, second;

    for (int i = 0; i != n; ++i) {
        int elem;
        std::cin >> elem;
        if (i < n / 2) {
            first.push(elem);
        }
        else {
            second.push(elem);
        }
    }

    int count = 0;

    while (count < 2e5) {
        if (first.empty()) {
            std::cout << "second" << " " << count << std::endl;
            return 0;
        }
        if (second.empty()) {
            std::cout << "first" << " " << count << std::endl;
            return 0;
        }
        int curr1 = first.front(); int curr2 = second.front();
        first.pop(); second.pop();

        if (curr1 == 0 && curr2 == n - 1) {
            first.push(curr1); first.push(curr2);  
        }
        else if (curr2 == 0 && curr1 == n - 1) {
            second.push(curr1); second.push(curr2); 
        }
        else if (curr1 > curr2) {
            first.push(curr1); first.push(curr2); 
        }
        else {
            second.push(curr1); second.push(curr2);
        }
        ++count;
    }

    std::cout << "draw" << "\n";

    return 0;
}
