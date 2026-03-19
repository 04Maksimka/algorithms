#include <iostream>
#include <deque>
#include <unordered_map>

class ConcertQueue {
private:
    std::deque<int> data;
    std::unordered_map<int,int> position;


public:
    void push_back(int id) {
        if (data.empty()) {
            position[id] = 1;
        }
        else {
            position[id] = position[data.back()] + 1;
        }
        data.push_back(id); 
    }

    void pop_front() {
        if (!data.empty()) {
            position.erase(data.front());
            data.pop_front();
        }
    }

    void pop_back() {
        if (!data.empty()) {
            position.erase(data.back());
            data.pop_back();
        }
    }

    bool empty() { return data.empty(); }
    int  front() { return data.front(); }

    int count_ahead(int q) {
        return position.at(q) - position.at(data.front());
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    ConcertQueue q;

    while (n--) {
        int type;
        std::cin >> type;

        switch (type) {
            case 1: {
                int id;
                std::cin >> id;
                q.push_back(id);
                break;
            }
            case 2:
                q.pop_front();
                break;
            case 3:
                q.pop_back();
                break;
            case 4: {
                int person;
                std::cin >> person;
                std::cout << q.count_ahead(person) << "\n";
                break;
            }
            case 5:
                std::cout << q.front() << "\n";
                break;
        }
    }

    return 0;
}