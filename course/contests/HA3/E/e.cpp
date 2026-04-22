#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <array>
#include <algorithm>

using namespace std;

bool hasZero(int n) {
    while (n > 0) {
        if (n % 10 == 0) return true;
        n /= 10;
    }
    return false;
}

vector<int> neighbors(int n) {
    std::array<int, 4> d;

    d[0] = n / 1000;
    d[1] = (n / 100) % 10;
    d[2] = (n / 10) % 10;
    d[3] = n % 10;

    vector<int> res;

    // 1. Увеличить первую цифру на 1
    if (d[0] != 9)
        res.push_back((d[0]+1)*1000 + d[1]*100 + d[2]*10 + d[3]);

    // 2. Уменьшить последнюю цифру на 1
    if (d[3] != 1)
        res.push_back(d[0]*1000 + d[1]*100 + d[2]*10 + (d[3]-1));

    // 3. Циклический сдвиг вправо: ABCD -> DABC
    res.push_back(d[3]*1000 + d[0]*100 + d[1]*10 + d[2]);

    // 4. Циклический сдвиг влево: ABCD -> BCDA
    res.push_back(d[1]*1000 + d[2]*100 + d[3]*10 + d[0]);

    // Убираем числа с нулями
    vector<int> filtered;
    for (int x : res)
        if (!hasZero(x))
            filtered.push_back(x);

    return filtered;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int start, end;
    cin >> start >> end;

    unordered_map<int, int> prev;
    prev[start] = -1;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front(); q.pop();

        if (cur == end) break;

        for (int nb : neighbors(cur)) {
            if (prev.find(nb) == prev.end()) {
                prev[nb] = cur;
                q.push(nb);
            }
        }
    }

    // Восстанавливаем путь
    vector<int> path;
    int cur = end;

    while (cur != -1) {
        path.push_back(cur);
        cur = prev[cur];
    }

    reverse(path.begin(), path.end());

    for (int num : path)
        cout << num << "\n";

    return 0;
}