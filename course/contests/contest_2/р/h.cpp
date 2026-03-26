#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>

class DualHeap {
    std::priority_queue<long long> maxHeap;
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> minHeap;
    std::unordered_map<long long, int> deleted; // val → сколько раз помечен удалённым

    void cleanMax() {
        while (!maxHeap.empty()) {
            long long top = maxHeap.top();
            if (deleted.count(top) && deleted[top] > 0) {
                deleted[top]--;
                if (deleted[top] == 0) deleted.erase(top);
                maxHeap.pop();
            } else {
                break;
            }
        }
    }

    void cleanMin() {
        while (!minHeap.empty()) {
            long long top = minHeap.top();
            if (deleted.count(top) && deleted[top] > 0) {
                deleted[top]--;
                if (deleted[top] == 0) deleted.erase(top);
                minHeap.pop();
            } else {
                break;
            }
        }
    }

public:
    void insert(long long val) {
        maxHeap.push(val);
        minHeap.push(val);
    }

    long long getMin() {
        cleanMin();
        long long val = minHeap.top();
        minHeap.pop();
        deleted[val]++;  // пометить как удалённый в maxHeap
        return val;
    }

    long long getMax() {
        cleanMax();
        long long val = maxHeap.top();
        maxHeap.pop();
        deleted[val]++;  // пометить как удалённый в minHeap
        return val;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    DualHeap dh;

    while (n--) {
        std::string op;
        std::cin >> op;

        if (op == "GetMin") {
            std::cout << dh.getMin() << "\n";
        } else if (op == "GetMax") {
            std::cout << dh.getMax() << "\n";
        } else {
            long long val = std::stoll(op.substr(7, op.size() - 8));
            dh.insert(val);
        }
    }

    return 0;
}