/**
 * Author: Aufar Gilbran
 * Date: 2019-03-21
 * License: CC0
 * Status: Tested on problems:
 * - https://community.topcoder.com/stat?c=problem_statement&pm=15257&rd=17422
 * Time: O(V+E)
 * Space: O(V+E)
 * Usage: 
 */

#ifdef DEBUG
#include <bits/stdc++.h>
#endif
namespace biconnected_component
{
    using namespace std;
    using node_t = int;

    struct S {
        vector<int> entry, low;
        int time;
        vector<size_t> bridge, cut;
        S(size_t n):
            entry(n, 0), low(n, 0),
            time(0) {}
    };

    template<class Graph>
    int dfs(Graph &g, S &s, node_t v, node_t p = -1)
    {
        s.entry[v] = s.low[v] = ++s.time;
        size_t c = 0;
        bool cut = false;
        for (auto &e: g[v]) if (e.first != p) {
            node_t u; size_t id; tie(u, id) = e;
            if (s.entry[u]) s.low[v] = min(s.low[v], s.entry[u]);
            else {
                dfs(g, s, u, v);
                s.low[v] = min(s.low[v], s.low[u]);
                if (s.low[u] > s.entry[v])
                    s.bridge.emplace_back(id);
                if (!cut && s.low[u] >= s.entry[v] && p != -1) {
                    cut = 1;
                    s.cut.emplace_back(v);
                }
                c++;
            }
        }
        if (p == -1 && c > 1)
            s.cut.emplace_back(v);

        return s.low[v];
    }

    template<class Edgelist>
    vector<size_t> bridge(size_t n, const Edgelist &edge) {
        vector<vector<pair<int,size_t>>> g(n);
        for (size_t i = 0; i < edge.size(); i++) {
            node_t u, v; tie(u, v) = edge[i];
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
        }
        S s = S(n);
        for (size_t i = 0; i < n; i++) if (!s.entry[i])
            dfs(g, s, i);

        return s.bridge;
    }

    template<class Graph>
    vector<size_t> cut(Graph &g) {
        size_t n = g.size();
        S s = S(n);
        for (size_t i = 0; i < n; i++) if (!s.entry[i])
            dfs(g, s, i);
        return s.cut;
    }
}
