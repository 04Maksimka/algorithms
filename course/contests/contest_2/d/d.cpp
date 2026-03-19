#include <iostream>
#include <vector>
#include <string>

using ll = long long;

const ll MOD1 = 1'000'000'007;
const ll MOD2 = 1'000'000'009;
const ll BASE = 29;

ll safeMod(ll a, ll mod) {
    return (a % mod + mod) % mod;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string p, t;
    std::cin >> p >> t;

    int pLen = p.length();
    int tLen = t.length();

    if (pLen > tLen) {
        std::cout << 0 << "\n";
        return 0;
    }

    // Предвычисление степеней BASE
    std::vector<ll> pow1(pLen + 1), pow2(pLen + 1);
    pow1[0] = 1; pow2[0] = 1;
    
    for (int i = 1; i <= pLen; ++i) {
        pow1[i] = (pow1[i-1] * BASE) % MOD1;
        pow2[i] = (pow2[i-1] * BASE) % MOD2;
    }

    ll ph1 = 0, ph2 = 0;
    for (int i = 0; i < pLen; ++i) {
        ph1 = (ph1 * BASE + p[i]) % MOD1;
        ph2 = (ph2 * BASE + p[i]) % MOD2;
    }

    // Хеши для строки t
    std::vector<ll> h1(tLen + 1), h2(tLen + 1);
    h1[0] = 0; h2[0] = 0;
    for (int i = 0; i < tLen; ++i) {
        h1[i+1] = (h1[i] * BASE + t[i]) % MOD1;
        h2[i+1] = (h2[i] * BASE + t[i]) % MOD2;
    }

    std::vector<int> positions;

    for (int i = 0; i <= tLen - pLen; ++i) {
        ll hash1 = safeMod(h1[i+pLen] - h1[i] * pow1[pLen], MOD1);
        ll hash2 = safeMod(h2[i+pLen] - h2[i] * pow2[pLen], MOD2);

        if (hash1 == ph1 && hash2 == ph2) {
            positions.push_back(i + 1); // нумерация с 1
        }
    }

    std::cout << positions.size() << "\n";
    for (int i = 0; i < (int)positions.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << positions[i];
    }
    std::cout << "\n";

    return 0;
}