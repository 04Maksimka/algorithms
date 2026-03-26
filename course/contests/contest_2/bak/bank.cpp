#include <iostream>
#include <map>
#include <string>

class Bank {
private:
    std::map<std::string, long long> accounts;
    std::map<std::string, bool> exists;

public:
    void deposit(const std::string& name, long long money) {
        accounts[name] += money;
        exists[name] = true;
    }

    void query(const std::string& name) {
        if (exists.find(name) == exists.end()) {
            std::cout << "ERROR" << "\n";
        } else {
            std::cout << accounts[name] << "\n";
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    Bank bank;

    for (int i = 0; i < n; i++) {
        int type;
        std::cin >> type;

        if (type == 1) {
            std::string name;
            long long money;
            std::cin >> name >> money;
            bank.deposit(name, money);
        } else {
            std::string name;
            std::cin >> name;
            bank.query(name);
        }
    }

    return 0;
}
