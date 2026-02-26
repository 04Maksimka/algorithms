#include <iostream>
#include <vector>
#include <algorithm>


struct Item {
    long long weight;
    long long price;
    int original_index;
};

struct State {
    long long weight;
    long long price;
    int taken_mask; // кодируем 0 и 1 какие предметы взяты
};

int n;
long long W;
std::vector<Item> items;

std::vector<State> generateSubsets(int start_index, int count) {
    int num_subsets = 1 << count;
    std::vector<State> states(num_subsets);

    for (int mask = 0; mask < num_subsets; ++mask) {
        long long currentW = 0;
        long long currentP = 0;
        
        for (int i = 0; i < count; ++i) {
            if ((mask >> i) & 1) {
                currentW += items[start_index + i].weight;
                currentP += items[start_index + i].price;
            }
        }

        // Если вес не превышает
        if (currentW <= W) {
            states.push_back({currentW, currentP, mask});
        }
    }
    return states;
}

int main() {
    std::cin >> n >> W;
    items.resize(n);

    for (int i = 0; i != n; ++i) {
        std::cin >> items[i].weight >> items[i].price;
        items[i].original_index = i + 1;
    }

    int n1 = n / 2;
    int n2 = n - n1;

    std::vector<State> leftStates = generateSubsets(0, n1);
    std::vector<State> rightStates = generateSubsets(n1, n2);


    sort(leftStates.begin(), leftStates.end(), [](const State& a, const State& b) {
        return a.weight < b.weight;
    });

    // оставляем только те, где с ростом веса растет и стоимость
    std::vector<State> bestLeftStates;
    long long maxPriceCurr = -1;

    for (const auto& state : leftStates) {
        if (state.price > maxPriceCurr) {
            maxPriceCurr = state.price;
            bestLeftStates.push_back(state);
        }
    }

    long long finalMaxPrice = 0;
    int bestMaskLeft = 0;
    int bestMaskRight = 0;

    for (const auto& rightState : rightStates) {
        long long remainingWeight = W - rightState.weight;

        if (remainingWeight < 0) continue;

        State searchTarget = {remainingWeight, -1, 0};
        auto it = upper_bound(bestLeftStates.begin(), bestLeftStates.end(), searchTarget, 
            [](const State& val, const State& s) {
                return val.weight < s.weight;
            });


        if (it != bestLeftStates.begin()) {
            it--; // Теперь it указывает на лучший вариант из левой части, который влезает
            
            long long totalPrice = rightState.price + (*it).price;

            if (totalPrice > finalMaxPrice) {
                finalMaxPrice = totalPrice;
                bestMaskLeft = (*it).taken_mask;
                bestMaskRight = rightState.taken_mask;
            }
        }
    }

    std::vector<int> resultIndices;
    

    for (int i = 0; i < n1; ++i) {
        if ((bestMaskLeft >> i) & 1) {
            resultIndices.push_back(items[i].original_index);
        }
    }
    
    for (int i = 0; i < n2; ++i) {
        if ((bestMaskRight >> i) & 1) {
            resultIndices.push_back(items[n1 + i].original_index);
        }
    }


    std::cout << resultIndices.size() << "\n";
    for (size_t i = 0; i < resultIndices.size(); ++i) {
        std::cout << resultIndices[i];
    }
    std::cout << "\n";

    return 0;
}