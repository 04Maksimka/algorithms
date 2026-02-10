#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> sizes(n);
    for (int i = 0; i < n; i++) {
        std::cin >> sizes[i];
    }
    
    std::sort(sizes.begin(), sizes.end());
    

    int passengerEnd = n / 2 - 1; // we cannot have more passengers than carriers
    int carrierStart = n / 2;
    
    int passenger = 0;
    int carrier = carrierStart;
    int paired = 0;
    
    while (passenger <= passengerEnd && carrier < n) {
        if (sizes[carrier] >= 2 * sizes[passenger]) {
            paired++;
            passenger++;
            carrier++;
        } else {
            carrier++;
        }
    }
    std::cout << n - paired << std::endl;
    
    return 0;
}