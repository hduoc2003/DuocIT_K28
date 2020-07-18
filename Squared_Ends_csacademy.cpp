#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <numeric>
#include <chrono>
#include <functional>
#include <tuple>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <array>
#include <bitset>
#include <unordered_map>

#define foru(i, a, b) for(int i = a, _b = (b)+1; i < _b; ++i)
#define ford(i, a, b) for(int i = a, _b = (b)-1; i > _b; --i)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define fr freopen
#define eb emplace_back
#define ep emplace

using namespace std;

template <class X>
bool mini(X& a, const X& b)
{
    if (a > b) { a = b; return true; } return false;
}

template <class X>
bool maxi(X& a, const X& b)
{
    if (a < b) { a = b; return true; } return false;
}

typedef const int& ci;
typedef long long ll;
typedef pair <int, int> pii;

const int N = 1e4+1, A = 1e6;
const ll inf = 1e19, add = 1e16;

template <class unit>
class LichaoTree
{
private:
    struct line
    {
        unit a,b;

        line() {}
        line(unit _a, unit _b): a(_a), b(_b) {}

        unit operator() (unit x)
        {
            return a*x + b;
        }
    };

    struct node
    {
        node *l, *r;
        line d;

        node() {l = nullptr, r = nullptr;}
        node(line _d) {d = _d; l = nullptr; r = nullptr;}
    };

    node *root;
    int n;

    void insert(line d, int l, int r, node*& cur)
    {
        if (!cur) {cur = new node(d); return;}
        bool cl = d(l) < cur->d(l);
        bool cr = d(r) < cur->d(r);
        if (cl && cr) {cur->d = d; return;}
        if (!cl && !cr) return;
        if (cl) swap(cur->d, d); /// d.a > cur->d.a
        int mid = (l + r) >> 1;
        if (d(mid) < cur->d(mid))
        {
            swap(d, cur->d);
            insert(d, l, mid, cur->l);
        }
        else insert(d, mid+1, r, cur->r);
    }

    unit get(unit p, int l, int r, node*& cur)
    {
        if (!cur) return numeric_limits <unit> :: max();
        if (l == r) return cur->d(p);
        int mid = (l + r) >> 1;
        if (mid < p)
            return min(cur->d(p), get(p, mid+1, r, cur->r));
        return min(cur->d(p), get(p, l, mid, cur->l));
    }

public:
    void resize(int sz)
    {
        n = sz, root = nullptr;
    }

    void insert(unit a, unit b)
    {
        insert(line(a,b), 1, n, root);
    }

    unit get(unit p)
    {
        return get(p, 1, n, root);
    }
};

int n,k;
ll a[N];
ll dp[N];
LichaoTree <long long> t;

void enter()
{
    cin >> n >> k;
    foru(i, 1, n)
        cin >> a[i];
}

void solve()
{
    t.resize(A);
    foru(i, 2, n)
        dp[i] = (a[i] - a[1])*(a[i] - a[1]);
    foru(j, 2, k)
    {
        vector <ll> tmp(dp, dp+n+1);
        foru(r, j, n)
        {
            t.insert(-2*a[r], a[r]*a[r] + tmp[r-1] - (j-1)*add);
            dp[r] = t.get(a[r]) + a[r]*a[r] + add*(j-1);
        }
    }
    cout << dp[n];
}

int main()
{
    #define haid ""

    ios_base :: sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    fr(haid".inp", "r", stdin);

#endif
    enter();
    solve();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms";
}
