#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <utility>

using ll = long long;

const ll MOD1 = 1'000'000'007;
const ll MOD2 = 1'000'000'009;
const ll BASE = 29;

//чтобы избежать отрицательных чисел при вычислении хеша
ll safeMod(long long a, long long mod) {
    return (a % mod + mod) % mod;
}

// Функция проверки: существует ли общая подстрока длины len
std::pair<bool, std::pair<ll, ll>> check(
    int len,
    const std::vector<std::string>& strings, 
    const std::vector<ll>& pow1, // храним степени BASE
    const std::vector<ll>& pow2
) {
    if (len == 0) {
        return {true, {0, 0}};
    }

    // Множество хешей, которые встречались во всех обработанных строках
    std::set<std::pair<ll, ll>> common_hashes;

    // заполняем множество всеми хешами подстрок длины len для первой строки
    {
        const std::string& s = strings[0];
        int n = s.length();
        
        // заполняем массивы хешей для первой строки
        std::vector<ll> h1(n + 1), h2(n + 1);
        h1[0] = 0; h2[0] = 0;
        
        for (int i = 0; i < n; ++i) {
            h1[i+1] = (h1[i] * BASE + s[i]) % MOD1; 
            h2[i+1] = (h2[i] * BASE + s[i]) % MOD2;
        }

        for (int i = 0; i <= n - len; ++i) {
            ll hash1 = safeMod(h1[i+len] - h1[i] * pow1[len], MOD1);
            ll hash2 = safeMod(h2[i+len] - h2[i] * pow2[len], MOD2);
            common_hashes.insert({hash1, hash2});
        }
    }

    // Обработка остальных строк
    for (size_t k = 1; k < strings.size(); ++k) {
        if (common_hashes.empty()) {
            return {false, {0, 0}};
        }

        const std::string& s = strings[k];
        int n = s.length();
        
        std::vector<ll> h1(n + 1), h2(n + 1);
        h1[0] = 0; h2[0] = 0;
        
        for (int i = 0; i < n; ++i) {
            h1[i+1] = (h1[i] * BASE + s[i]) % MOD1;
            h2[i+1] = (h2[i] * BASE + s[i]) % MOD2;
        }

        // Множество хешей текущей строки, которые также есть в common_hashes
        std::set<std::pair<ll, ll>> next_common;
        
        for (int i = 0; i <= n - len; ++i) {
            ll hash1 = safeMod(h1[i+len] - h1[i] * pow1[len], MOD1);
            ll hash2 = safeMod(h2[i+len] - h2[i] * pow2[len], MOD2);
            
            std::pair<ll, ll> current_hash = {hash1, hash2};
            
            // Если такой хеш был в предыдущих строках, сохраняем его
            if (common_hashes.count(current_hash)) {
                next_common.insert(current_hash);
            }
        }
        
        common_hashes = next_common;
    }

    if (!common_hashes.empty()) {
        return {true, *common_hashes.begin()};
    }
    
    return {false, {0, 0}};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int k;
    std::cin >> k;

    std::vector<std::string> strings(k);
    int min_len = 10'001; // Больше максимальной длины строки

    for (int i = 0; i < k; ++i) {
        std::cin >> strings[i];
        if ((int)strings[i].length() < min_len) {
            min_len = strings[i].length();
        }
    }

    // Предвычисление степеней BASE
    // Нам нужны степени до min_len
    std::vector<ll> pow1(min_len + 1);
    std::vector<ll> pow2(min_len + 1);
    pow1[0] = 1; pow2[0] = 1;
    for (int i = 1; i <= min_len; ++i) {
        pow1[i] = (pow1[i-1] * BASE) % MOD1;
        pow2[i] = (pow2[i-1] * BASE) % MOD2;
    }

    // Бинарный поиск по длине ответа
    int low = 0;
    int high = min_len;
    std::pair<ll, ll> best_hash = {0, 0};
    int best_len = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        auto result = check(mid, strings, pow1, pow2);
        
        if (result.first) {
            best_len = mid;
            best_hash = result.second;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // Восстановление ответа
    if (best_len == 0) {
        std::cout << "" << std::endl;
    } else {
        // Ищем подстроку с хешем best_hash в первой строке
        const std::string& s = strings[0];
        int n = s.length();
        
        // заново посчитать хеши для первой строки
        std::vector<ll> h1(n + 1), h2(n + 1);
        h1[0] = 0; h2[0] = 0;
        for (int i = 0; i < n; ++i) {
            h1[i+1] = (h1[i] * BASE + s[i]) % MOD1;
            h2[i+1] = (h2[i] * BASE + s[i]) % MOD2;
        }
        
        for (int i = 0; i <= n - best_len; ++i) {
            ll hash1 = safeMod(h1[i+best_len] - h1[i] * pow1[best_len], MOD1);
            ll hash2 = safeMod(h2[i+best_len] - h2[i] * pow2[best_len], MOD2);
            
            if (hash1 == best_hash.first && hash2 == best_hash.second) {
                std::cout << s.substr(i, best_len) << std::endl;
                break;
            }
        }
    }

    return 0;
}