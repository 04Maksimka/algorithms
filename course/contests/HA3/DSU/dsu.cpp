#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
    private:
        vector<int> p;
        vector<int> s;
        int n;
    public:
        DSU(int max_n) : n(max_n) {
            p.resize(max_n);
            s.resize(max_n);
            for (int i = 0; i < max_n; ++i) {
                p[i] = i, s[i] = 1;
            }
        }

        void reset() {
            for (int i = 0; i < n; ++i) {
                p[i] = i, s[i] = 1;
            }
        }

        int leader(int v) {
            return (p[v] == v) ? v : p[v] = leader(p[v]);
        }

        bool unite(int a, int b) {
            a = leader(a), b = leader(b);
            if (a == b) return false;
            if (s[a] > s[b]) {
                swap(a, b);
            }
            s[b] += s[a];
            p[a] = b;
            return true;
        }
};

struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (auto& e : edges)
        cin >> e.u >> e.v >> e.w;

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
        return a.w < b.w;
    });

    if (n == 1) {
        cout << "YES\n0\n";
        return 0;
    }

    long long ans = LLONG_MAX;
    DSU dsu(n + 1); // +1 т.к. вершины нумеруются с 1

    for (int l = 0; l <= m - (n - 1); l++) {
        dsu.reset();
        int edgesUsed = 0;
        int lastWeight = 0;

        for (int i = l; i < m && edgesUsed < n - 1; i++) {
            if (dsu.unite(edges[i].u, edges[i].v)) {
                edgesUsed++;
                lastWeight = edges[i].w;
            }
        }

        if (edgesUsed == n - 1) {
            long long diff = (long long)lastWeight - edges[l].w;
            ans = min(ans, diff);
        }
    }

    if (ans == LLONG_MAX)
        cout << "NO\n";
    else
        cout << "YES\n" << ans << "\n";

    return 0;
}
