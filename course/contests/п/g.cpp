#include <iostream>
#include <deque>

class GoblinQueue {
private:
    std::deque<int> left, right;

    void rebalance() {
        if (right.size() > left.size()) {
            // right большой — отдаём его голову в хвост left
            left.push_back(right.front());
            right.pop_front();
        } else if (left.size() > right.size() + 1) {
            // left большой — отдаём его хвост в голову right
            right.push_front(left.back());
            left.pop_back();
        }
    }

public:
    void push_back(int i) {
        right.push_back(i);
        rebalance();
    }

    void push_middle(int i) {
        right.push_front(i);
        rebalance();
    }

    int pop_front() {
        int val = left.front();
        left.pop_front();
        rebalance();
        return val;
    }

};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    GoblinQueue gq;

    for (int i = 0; i < n; i++) {
        char op;
        std::cin >> op;
        if (op == '+') {
            int x; std::cin >> x;
            gq.push_back(x);
        } else if (op == '*') {
            int x; std::cin >> x;
            gq.push_middle(x);
        } else {
            std::cout << gq.pop_front() << '\n';
        }
    }

    return 0;
}
