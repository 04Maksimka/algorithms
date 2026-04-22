#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge {
    int u, v, w;
};


struct DSU {
    vector<int> parent, rank_;
    int components;
    
    DSU(int n) : parent(n+1), rank_(n+1, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank_[x] < rank_[y]) swap(x, y);
        parent[y] = x;
        if (rank_[x] == rank_[y]) rank_[x]++;
        components--;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (auto& e : edges)
        cin >> e.u >> e.v >> e.w;
    
    // Сортируем по весу
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
        return a.w < b.w;
    });
    
    // Граф из одной вершины — дерево тривиально
    if (n == 1) {
        cout << "YES\n0\n";
        return 0;
    }
    
    long long ans = LLONG_MAX;
    
    // Перебираем левую границу
    for (int l = 0; l <= m - (n - 1); l++) {
        DSU dsu(n);
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
    
    if (ans == LLONG_MAX) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << ans << "\n";
    }
    
    return 0;
}
