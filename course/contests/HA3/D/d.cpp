#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M, K, S;
    cin >> N >> M >> K >> S;
    S--;
    
    vector<tuple<int, int, long long>> edges(M);
    for (auto& [a, b, w] : edges) {
        cin >> a >> b >> w;
        a--; b--;
    }
    
    const long long INF = 1e18;
    // dp -- это "пути длиной ровно i", ndp -- "пути длиной ровно i+1"
    vector<long long> dp(N, INF), ndp(N, INF);
    dp[S] = 0;
    
    for (int i = 0; i < K; i++) {
        fill(ndp.begin(), ndp.end(), INF);

        for (auto& [a, b, w] : edges) {
            if (dp[a] != INF) {
                ndp[b] = min(ndp[b], dp[a] + w);
            }
        }
        dp = ndp;
    }
    
    for (int i = 0; i < N; i++) {
        cout << (dp[i] == INF ? -1 : dp[i]) << "\n";
    }
    
    return 0;
}
