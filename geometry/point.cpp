/**
 * author: Aufar Gilbran
 * date: 2019-05-13
 * license: CC0
 * type: data structure
 * status: untested
 */

#ifdef DEBUG
#include <bits/stdc++.h>
#endif
namespace geometry {
    using namespace std;
    template<typename T>
    class point {
        public:
        T x, y;
        point(): x(reinterpret_cast<T>(0)), y(reinterpret_cast<T>(0)) {}
        point(const T& _x, const T& _y): x(_x), y(_y) {}
    };
}
