/**
 * author: Aufar Gilbran
 * date: 2019-03-21
 * license: CC0
 * type: algorithm
 * space: O(E+V)
 */

#ifdef DEBUG
#include <bits/stdc++.h>
#endif
namespace flow {
    using namespace std;
    using node_t = int;

    template<typename T>
    class network {
    public:
        struct edge
        {
            T c, w;
            node_t t;
            ssize_t r;
            edge(node_t _t, T _c, T _w, ssize_t _r):
                c(_c), w(_w), t(_t), r(_r) {}
        };

        /**
         * Construct network flow with _n number of node_ts, indexed from 0 to _n.
         */
        network(ssize_t n, bool _directed = true):
            g(n), directed(_directed) {}

        /**
         * Return all edges outgoing from node_t _v
         */
        vector<edge>& operator[](node_t v)
        {
            return g[v];
        }

        ssize_t size() const
        {
            return g.size();
        }

        /**
         * Add un/directed edge in the network from u to v, with capacity c,
         * and cost w (0 <= u, v < n)
         */
        void add_edge(node_t u, node_t v, T c, T w = 1)
        {
            edge a(v, c, w, sz(g[v])), b(u, directed ? 0 : c, -w, sz(g[u]));
            g[u].push_back(a);
            g[v].push_back(b);
        }

    private:
        vector<vector<edge>> g;
        bool directed;
    };
}
