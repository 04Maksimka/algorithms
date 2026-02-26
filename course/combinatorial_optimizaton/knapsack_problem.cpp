#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int n;
    int max_weight;

    std::cin >> n >> max_weight;

    std::vector<int> weights(n);
    std::vector<int> values(n);

    for (int i = 0; i != n; ++i) {
        std::cin >> weights[i] >> values[i];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(max_weight + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= max_weight; ++j) {
            if (j >= weights[i - 1]) {
                dp[i][j] = std::max(
                    dp[i - 1][j],
                    dp[i - 1][j - weights[i - 1]] + values[i - 1]
                );
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    std::vector<int> chosen;
    int j = max_weight;
    for (int i = n; i >= 1; --i) {      
        if (dp[i][j] != dp[i - 1][j]) { 
            chosen.push_back(i);    
            j -= weights[i - 1];        
        }
    }

    std::reverse(chosen.begin(), chosen.end());

    std::cout << chosen.size() << "\n";
    for (int idx : chosen) {
        std::cout << idx << " ";
    }
    std::cout << "\n";

    return 0;
}
