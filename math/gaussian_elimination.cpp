#ifdef DEBUG
#include <bits/stdc++.h>
#endif
using namespace std;
template<typename T>
void gaussian_elimination(vector<vector<T>> &a) {
    if (a.empty()) return;
    size_t r = a.size(), c = a[0].size();
    size_t lr = 0;
    for (size_t i = 0; i < r; i++) {
        size_t p = lr;
        while (p < r) {
            if (a[p][i]) break;
            p++;
        }
        if (p == r) continue;
        for (size_t j = 0; j < c; j++) swap(a[lr][j], a[p][j]);
        T d = 1 / a[lr][i];
        for (size_t j = 0; j < c; j++) a[lr][j] / d;
        for (size_t k = 0; k < r; k++) {
            if (k == lr) continue;
            if (a[k][i]) {
                T q = a[k][i] / a[lr][i];
                for (size_t j = 0; j < c; j++) {
                    a[k][j] -= q * a[lr][j];
                }
            }
        }
        lr++;
    }
}
