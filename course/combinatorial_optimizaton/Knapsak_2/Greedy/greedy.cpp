#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    long long W;
    std::cin >> N >> W;

    std::vector<long long> values(N), weights(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> values[i] >> weights[i];
    }

    std::vector<int> order(N);
    for (int i = 0; i < N; ++i) order[i] = i;
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        return values[a] * weights[b] > values[b] * weights[a];
    });

    long long totalValue  = 0;
    long long totalWeight = 0;
    std::vector<bool> taken(N, false);

    for (int i = 0; i < N; ++i) {
        int idx = order[i];
        if (totalWeight + weights[idx] <= W) {
            taken[idx]    = true;
            totalValue   += values[idx];
            totalWeight  += weights[idx];
        }
    }


    for (int i = 0; i < N; ++i) {
        int out_idx = order[i];
        if (!taken[out_idx]) continue;

        for (int j = 0; j < N; ++j) {
            int in_idx = order[j];
            if (taken[in_idx]) continue;

            long long newWeight = totalWeight - weights[out_idx] + weights[in_idx];
            long long newValue  = totalValue  - values[out_idx]  + values[in_idx];

            if (newWeight <= W && newValue > totalValue) {
                taken[out_idx] = false;
                taken[in_idx]  = true;
                totalWeight    = newWeight;
                totalValue     = newValue;
                break;
            }
        }
    }

    std::cout << totalValue << '\n';
    bool first = true;
    for (int i = 0; i < N; ++i) {
        if (taken[i]) {
            if (!first) std::cout << ' ';
            std::cout << (i + 1);
            first = false;
        }
    }
    std::cout << '\n';

    return 0;
}
