#include <vector>
#include <iostream>

struct Request {
    int begin;
    int end;
    int target;
};

template <typename Iterator>
bool LinearSearch(Iterator begin, Iterator end, int target) {
    for (Iterator it = begin; it != end; ++it) {
        if (*it == target) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i != n; ++i) {
        std::cin >> vec[i];
    }

    int k;
    std::cin >> k;
    std::vector<Request> requests(k);
    for (int i = 0; i != k; ++i) {
        int l;
        int r;
        int t;
        std::cin >> l >> r >> t;
        requests[i] = {l, r, t};
    }

    std::string result = "";

    for (const auto& request : requests) {
        bool found = LinearSearch(
            vec.begin() + request.begin - 1, 
            vec.begin() + request.end, 
            request.target
        );

        result += (found ? '1' : '0');
    }

    std::cout << result << std::endl;

    return 0;
}