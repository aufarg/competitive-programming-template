#include <bits/stdc++.h>
using namespace std;
#define all(c) (c).begin(), (c).end()
#define sz(c) (int)(c).size()
#define endl "\\n"
#ifdef DEBUG
#define dump(v) cerr << "["#v << ":" << (v) << "]" << endl;
#else
#define dump(v)
#endif
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vector<int>> vii;
typedef vector<ll> vl;
const ll MOD = (1e9+7);
const ll INF = (1e9+123456789);
const ll INFL = (INF*INF);
inline ll addm(ll a, ll b, ll m = MOD) {return ((a+b)%m);}
inline ll subm(ll a, ll b, ll m = MOD) {return (((a-b)%m+m)%m);}
inline ll mulm(ll a, ll b, ll m = MOD) {return ((a*b)%m);}
ll powm(ll a, ll b, ll m = MOD) {ll ret=(!b)?1:powm(a, b/2, m);return (!b)?1:mulm(mulm(ret,ret,m),b%2?a:1,m);}
ll inv(ll x, ll m = MOD) {return powm(x,m-2,m);}

struct ${ClassName}
{
    ${Method.ReturnType} ${Method.Name}(${Method.Params})
    {
        return ${Method.ReturnType;zeroval};
    }
};

${CutBegin}
${<TestCode}
${CutEnd}
