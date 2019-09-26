/**
 * author: Aufar Gilbran
 * date: 2019-03-21
 * license: CC0
 * type: algorithm
 * status: tested (https://codeforces.com/contest/1139/submission/51652898)
 * time: O(V^3)
 * space: O(E+V)
 * usage: 
 */

#ifdef DEBUG
#include <bits/stdc++.h>
#endif
#include "flow_network.cpp"
namespace flow {
    template<typename T>
    T max_flow(network<T> &g, node_t s, node_t t) {
        using edge = typename network<T>::edge;
        const T infinite = numeric_limits<T>::max();

        vector<T> dist(g.size());
        auto bfs = [&g, &dist](node_t _f, node_t _t) {
            int from = _f, to = _t;
            fill(dist.begin(), dist.end(), -1);
            dist[from] = 0;
            queue<node_t> q;
            q.push(from);
            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (auto &e: g[v]) {
                    int u = e.t;
                    if (dist[u] < 0 && e.c > 0) {
                        dist[u] = dist[v] + 1;
                        q.push(u);
                    }
                }
            }
            return dist[to] >= 0;
        };

        vector<ssize_t> work(g.size());
        auto dfs = [&g, &work, &dist](auto&& self, node_t v, node_t end, T f) {
            if (v == end) return f;
            for (ssize_t &i = work[v]; i < sz(g[v]); i++) {
                edge &e = g[v][i], &r = g[e.t][e.r];
                if (e.c == 0) continue;
                node_t u = e.t;
                if (dist[v] < dist[u]) {
                    T df = self(self, u, end, min(f, e.c));
                    if (df > 0) {
                        e.c -= df; r.c += df;
                        return df;
                    }
                }
            }
            return static_cast<T>(0);
        };

        T mf = 0;
        while (bfs(s, t)) {
            fill(work.begin(), work.end(), 0);
            while (T flow = dfs(dfs, s, t, infinite))
                mf += flow;
        }
        return mf;
    }
}
