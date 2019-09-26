// template {{{
#include <bits/stdc++.h>

using namespace std;

#define all(c) (c).begin(), (c).end()
#define sz(c) (static_cast<int>(c.size()))
#define endl "\n"

using ld = long double;
using ll = long long;

inline ll addm(ll __a, ll __b, ll __m);
inline ll subm(ll __a, ll __b, ll __m);
inline ll mulm(ll __a, ll __b, ll __m);
ll powm(ll __a, ll __b, ll __m);
ll inv(ll __x, ll __m);
// }}}

const ll INFL = numeric_limits<ll>::max() / 2;
const ll INF = numeric_limits<int>::max() / 2;
const ll MOD = 1e9+7;

void solve()
{
}

// main {{{
int main()
{
    cin.sync_with_stdio(0); cin.tie(NULL);
    solve();
    return 0;
}

inline ll addm(ll __a, ll __b, ll __m = MOD) {
    return ((__a+__b)%__m);
}
inline ll subm(ll __a, ll __b, ll __m = MOD) {
    return (((__a-__b)%__m+__m)%__m);
}
inline ll mulm(ll __a, ll __b, ll __m = MOD) {
    return ((__a*__b)%__m);
}
ll powm(ll __a, ll __b, ll __m = MOD) {
    ll ret = (!__b) ? 1 : powm(__a, __b/2, __m);
    return (!__b) ? 1 : mulm(mulm(ret, ret, __m), (__b%2) ? __a : 1, __m);
}
ll inv(ll __x, ll __m = MOD) {
    return powm(__x, __m-2, __m);
}
// }}}
