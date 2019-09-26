/**
 * Author: Aufar Gilbran
 * Date: 2019-03-21
 * License: CC0
 * Status: Tested on problems:
 * - https://codeforces.com/contest/949/submission/51609862
 * Time: O(V+E)
 * Space: O(V)
 * Usage: 
 */

#ifdef DEBUG
#include <bits/stdc++.h>
#endif
namespace scc
{
    using namespace std;
    using node_t = int;

    struct S {
        S(int n):
            low(n, 0), comp(n, -1),
            time(0), ncomp(0) {}
        vector<int> low, comp;
        int time, ncomp;
        stack<int> pool;
    };

    template<class Graph>
    int dfs(const Graph &g, S &s, size_t v)
    {

        int entry = s.low[v] = ++s.time;
        s.pool.push(v);
        for (auto &u: g[v]) if (s.comp[u] == -1)
            s.low[v] = min(s.low[v], (s.low[u]) ? s.low[u] : dfs(g, s, u));

        node_t u;
        if (entry == s.low[v]) {
            do {
                u = s.pool.top(); s.pool.pop();
                s.comp[u] = s.ncomp;
            } while (v != u);
            s.ncomp++;
        }
        return s.low[v];
    }

    template<class Graph>
    vector<int> scc(const Graph &g) {
        size_t n = g.size();
        S s = S(n);
        for (size_t i = 0; i < n; i++) if (!s.low[i])
            dfs(g, s, i);
        return s.comp;
    }
}
