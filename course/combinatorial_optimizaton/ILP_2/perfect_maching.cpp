#include "glpk.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


int N, M;                   
std::vector<int> EA, EB, EW;


struct Dinic {
    struct Edge { int to, rev; double cap; };
    int n;
    std::vector<std::vector<Edge>> g;
    std::vector<int> level, iter;

    explicit Dinic(int n) : n(n), g(n) {}

    void add_edge(int u, int v, double c) {
        // Неориентированное ребро: оба направления c ёмкостью c.
        g[u].push_back({v, (int)g[v].size(), c});
        g[v].push_back({u, (int)g[u].size() - 1, c});
    }

    bool bfs(int s, int t) {
        level.assign(n, -1);
        level[s] = 0;
        std::queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u])
                if (level[e.to] < 0 && e.cap > 1e-12) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
        }
        return level[t] >= 0;
    }

    double dfs(int u, int t, double f) {
        if (u == t) return f;
        for (int &i = iter[u]; i < (int)g[u].size(); ++i) {
            auto &e = g[u][i];
            if (level[e.to] == level[u] + 1 && e.cap > 1e-12) {
                double d = dfs(e.to, t, std::min(f, e.cap));
                if (d > 1e-12) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    double max_flow(int s, int t) {
        double f = 0;
        while (bfs(s, t)) {
            iter.assign(n, 0);
            for (;;) {
                double d = dfs(s, t, 1e18);
                if (d < 1e-12) break;
                f += d;
            }
        }
        return f;
    }

    // Сторона min-cut, содержащая s (достижимые в остаточной сети).
    std::vector<char> side(int s) {
        std::vector<char> v(n, 0);
        v[s] = 1;
        std::queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u])
                if (!v[e.to] && e.cap > 1e-12) { v[e.to] = 1; q.push(e.to); }
        }
        return v;
    }
};

// ------ Сепарация blossom-неравенств через Gusfield -------------------------
// На каждой итерации i = 1..N-1 считаем min-cut между i и parent[i] в графе
// с ёмкостями x_e. Если |S| нечётно и величина разреза < 1, значит blossom для
// S нарушен — добавляем соответствующее неравенство как cut в GLPK.
static void separate(glp_tree *T) {
    glp_prob *P = glp_ios_get_prob(T);

    std::vector<double> x(M);
    for (int e = 0; e < M; ++e) x[e] = glp_get_col_prim(P, e + 1);

    std::vector<int> parent(N, 0);
    int added = 0;
    const int MAX_ADD = 200;

    for (int i = 1; i < N && added < MAX_ADD; ++i) {
        int t = parent[i];

        Dinic mf(N);
        for (int e = 0; e < M; ++e)
            if (x[e] > 1e-12) mf.add_edge(EA[e], EB[e], x[e]);

        double f = mf.max_flow(i, t);
        std::vector<char> S = mf.side(i);

        // Обновление parent'ов по Гузфилду (строим дерево Гомори-Ху).
        for (int j = i + 1; j < N; ++j)
            if (S[j] && parent[j] == t) parent[j] = i;

        int sz = 0;
        for (int v = 0; v < N; ++v) sz += S[v];

        // Условие нарушенного blossom: |S| нечётно (>=3) и разрез < 1.
        if (sz >= 3 && (sz & 1) && f < 1.0 - 1e-6) {
            // Если |S| > N/2 — удобнее взять дополнение V\S:
            // оба разреза дают одно и то же значение δ, parity совпадает
            // (N чётно), но constraint на меньшей стороне короче.
            std::vector<char> T_side = S;
            int use_sz = sz;
            if (sz > N - sz) {
                for (int v = 0; v < N; ++v) T_side[v] = !T_side[v];
                use_sz = N - sz;
            }

            std::vector<int> ind_v;
            for (int e = 0; e < M; ++e)
                if (T_side[EA[e]] && T_side[EB[e]])
                    ind_v.push_back(e + 1);

            int len = (int)ind_v.size();
            if (len == 0) continue;
            std::vector<int>    ind(len + 1);
            std::vector<double> val(len + 1, 1.0);
            for (int k = 0; k < len; ++k) ind[k + 1] = ind_v[k];

            glp_ios_add_row(T, nullptr, 0, 0, len,
                            ind.data(), val.data(),
                            GLP_UP, (double)(use_sz - 1) / 2.0);
            ++added;
        }
    }
}

static void cb(glp_tree *T, void *) {
    if (glp_ios_reason(T) == GLP_ICUTGEN) separate(T);
}

// ------ Основная программа --------------------------------------------------
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    glp_term_out(GLP_OFF);

    std::cin >> N >> M;
    EA.resize(M); EB.resize(M); EW.resize(M);
    for (int e = 0; e < M; ++e) std::cin >> EA[e] >> EB[e] >> EW[e];

    glp_prob *P = glp_create_prob();
    glp_set_obj_dir(P, GLP_MIN);

    // Переменные x_e ∈ {0,1}, целевая = w_e
    glp_add_cols(P, M);
    for (int e = 0; e < M; ++e) {
        glp_set_col_kind(P, e + 1, GLP_BV);
        glp_set_obj_coef(P, e + 1, EW[e]);
    }

    // Degree-ограничения: для каждой вершины v сумма x_e по инцидентным = 1
    glp_add_rows(P, N);
    for (int v = 0; v < N; ++v)
        glp_set_row_bnds(P, v + 1, GLP_FX, 1.0, 1.0);

    // Матрица: каждое ребро даёт +1 в двух строках (по концам).
    std::vector<int>    ia(2 * M + 1), ja(2 * M + 1);
    std::vector<double> ar(2 * M + 1);
    int k = 0;
    for (int e = 0; e < M; ++e) {
        ++k; ia[k] = EA[e] + 1; ja[k] = e + 1; ar[k] = 1.0;
        ++k; ia[k] = EB[e] + 1; ja[k] = e + 1; ar[k] = 1.0;
    }
    glp_load_matrix(P, 2 * M, ia.data(), ja.data(), ar.data());

    // Сначала решаем LP-релаксацию (callback требует presolve=OFF).
    glp_smcp smcp; glp_init_smcp(&smcp); smcp.msg_lev = GLP_MSG_OFF;
    glp_simplex(P, &smcp);

    glp_iocp iocp; glp_init_iocp(&iocp);
    iocp.msg_lev  = GLP_MSG_OFF;
    iocp.presolve = GLP_OFF;
    iocp.cb_func  = cb;
    iocp.br_tech  = GLP_BR_DTH;
    iocp.bt_tech  = GLP_BT_BLB;
    iocp.gmi_cuts = GLP_ON;
    iocp.mir_cuts = GLP_ON;
    iocp.cov_cuts = GLP_ON;
    iocp.clq_cuts = GLP_ON;

    glp_intopt(P, &iocp);

    // Вывод.
    long long total = 0;
    std::vector<int> chosen;
    for (int e = 0; e < M; ++e)
        if (glp_mip_col_val(P, e + 1) > 0.5) {
            chosen.push_back(e);
            total += EW[e];
        }

    std::cout << total << '\n';
    for (size_t i = 0; i < chosen.size(); ++i)
        std::cout << chosen[i] << (i + 1 == chosen.size() ? '\n' : ' ');

    glp_delete_prob(P);
    return 0;
}