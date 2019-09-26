/**
 * author: Aufar Gilbran
 * date: 2019-05-14
 * license: CC0
 * type: data structure
 * status: untested
 */

#ifdef DEBUG
#include <bits/stdc++.h>
#endif
#include "point.cpp"
namespace geometry {
    using namespace std;
    template<typename T>
    class line {
        public:
        T a, b, c;
        line(const point<T>& p, const point<T>& q) {
            a = p.x - q.x;
            b = p.y - q.y;
            c = p.x * q.y - q.x * p.y;
            T g = gcd(gcd(a, b), c);
            a /= g; b /= g; c /= g;
            if (a < 0 || (a == 0 && b < 0))
                a *= -1, b *= -1, c *= -1;
        }

        pair<T, T> slope() { return {b, a}; }
    };
}
