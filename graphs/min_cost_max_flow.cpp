/**
 * author: Aufar Gilbran
 * date: 2019-03-21
 * license: CC0
 * type: algorithm
 * time: O(V^3E) / O(V^2E^2) (non-negative / negative edge)
 * space: O(V+E)
 */

#ifdef DEBUG
#include <bits/stdc++.h>
#endif
#include "flow_network.cpp"
namespace flow {
    using namespace std;
    /**
     * Find maximum flow with lowest cost from s to t.
     * Enable neg flag for network with negative gs.
     */
    template<typename T>
    pair<T, T> min_cost_max_flow(network<T> &g, node_t s, node_t t)
    {
        using edge = typename network<T>::edge;

        const T infinite = numeric_limits<T>::max() >> 2;

        vector<T> pot(g.size());

        /**
         * Initialize potential values.
         *
         * Use Bellman-Ford to initialize node potential in case there is
         * a negative cycle
         */
        bool negative = false;
        for (node_t v = 0; v < g.size(); v++) {
            for (auto &e: g[v]) if (e.c > 0 && e.w < 0)
                negative = true;
        }
        if (negative) {
            fill(pot.begin(), pot.end(), infinite);
            pot[s] = 0;
            int cnt = static_cast<int>(g.size()); bool ch = true;
            while (ch && cnt--) {
                ch = false;
                for (node_t v = 0; v < g.size(); v++) if (pot[v] != infinite)
                    for (auto &e: g[v]) if (e.c > 0)
                        if (pot[v] + e.w < pot[e.t]) {
                            pot[e.t] = pot[v] + e.w;
                            ch = true;
                        }
            }
            assert(cnt >= 0);
        }

        /**
         * Find augmenting path from s to t with minimum total weight.
         */
        auto find_path = [&](node_t _from, node_t _to) {
            node_t from = _from, to = _to;
            vector<T> dist(g.size(), infinite);
            vector<ssize_t> prv(g.size());
            vector<bool> seen(g.size());
            priority_queue<pair<T, node_t>> pq;

            pq.push({0, from}); dist[from] = 0;
            while (!pq.empty()) {
                node_t v = pq.top().second; pq.pop();
                if (seen[v]) continue;
                seen[v] = true;
                for (auto &e: g[v]) if (e.c > 0) {
                    node_t u = e.t;
                    T ndist = dist[v] + e.w + pot[v] - pot[u];
                    if (ndist < dist[u]) {
                        dist[u] = ndist;
                        prv[u] = e.r;
                        pq.push({-ndist, u});
                    }
                }
            }

            for (node_t i = 0; i < g.size(); i++)
                pot[i] = min(pot[i] + dist[i], infinite);

            unique_ptr<vector<reference_wrapper<edge>>> path;
            if (seen[to]) {
                path = make_unique<vector<reference_wrapper<edge>>>();
                node_t v = to;
                while (v != from) {
                    edge &r = g[v][prv[v]], &e = g[r.t][r.r];
                    path->push_back(e);
                    v = r.t;
                }
            }

            return path;
        };

        T mf = 0, mc = 0;
        while (auto path = find_path(s, t)) {
            T flow = infinite;
            for (edge& e: *path) flow = min(flow, e.c);
            for (edge& e: *path) {
                edge &r = g[e.t][e.r];
                e.c -= flow; r.c += flow;
                mc += e.w * flow;
            };
            mf += flow;
        }
        return {mf, mc};
    }
}
