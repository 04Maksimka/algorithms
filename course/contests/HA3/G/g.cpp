#include <iostream>
#include <vector>
#include <tuple>
#include <queue>


using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // edges: {from, to, weight}
    vector<tuple<int,int,int>> edges(M);
    // adjacency list forward and backward
    vector<vector<pair<int,int>>> adj(N + 1), radj(N + 1);

    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        radj[v].push_back({u, w});
    }

    // BFS from 1 (forward)
    vector<bool> from1(N + 1, false);
    {
        queue<int> q;
        q.push(1);
        from1[1] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, w] : adj[u]) {
                if (!from1[v]) {
                    from1[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // BFS from N (backward)
    vector<bool> toN(N + 1, false);
    {
        queue<int> q;
        q.push(N);
        toN[N] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, w] : radj[u]) {
                if (!toN[v]) {
                    toN[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // If N is not reachable from 1
    if (!from1[N]) {
        cout << ":()" << endl;
        return 0;
    }

    const long long NEG_INF = LLONG_MIN / 2;

    vector<long long> dist(N + 1, NEG_INF);
    dist[1] = 0;

    // Bellman-Ford: N-1 iterations (maximize)
    for (int iter = 0; iter < N - 1; iter++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == NEG_INF) continue;
            if (!from1[u]) continue;  // u is not reachable from 1
            if (dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    if (dist[N] == NEG_INF) {
        cout << ":(" << endl;
        return 0;
    }

    // N more iterations to detect positive cycles affecting path to N
    bool inf_cycle = false;
    for (int iter = 0; iter < N; iter++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == NEG_INF) continue;

            if (!from1[u]) continue;

            if (dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
                if (toN[v]) {
                    inf_cycle = true;
                }
            }
        }
    }

    if (inf_cycle) {
        cout << ":)" << endl;
    } else {
        cout << dist[N] << endl;
    }

    return 0;
}
