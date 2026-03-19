#include <iostream>
#include <queue>
#include <vector>
#include <string>

class DualHeap {
    std::priority_queue<long long> maxHeap;
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> minHeap;

public:
    void insert(long long val) {
        maxHeap.push(val);
        minHeap.push(val);
    }

    long long getMin() {
        long long val = minHeap.top();
        minHeap.pop();
        removeFromMax(val);
        return val;
    }

    long long getMax() {
        long long val = maxHeap.top();
        maxHeap.pop();
        removeFromMin(val);
        return val;
    }

private:
    void removeFromMax(long long val) {
        std::vector<long long> tmp;
        while (!maxHeap.empty()) {
            long long top = maxHeap.top();
            maxHeap.pop();
            if (top == val) break;
            tmp.push_back(top);
        }
        for (long long x : tmp) maxHeap.push(x);
    }

    void removeFromMin(long long val) {
        std::vector<long long> tmp;
        while (!minHeap.empty()) {
            long long top = minHeap.top();
            minHeap.pop();
            if (top == val) break;
            tmp.push_back(top);
        }
        for (long long x : tmp) minHeap.push(x);
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