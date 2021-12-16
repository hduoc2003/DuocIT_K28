#include <bits/stdc++.h>

#define foru(i, a, b) for(int i = a, _b = (b)+1; i < _b; ++i)
#define ford(i, a, b) for(int i = a, _b = (b)-1; i > _b; --i)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define fr freopen
#define eb emplace_back
#define ep emplace

using namespace std;

void show() {}
template <typename T, typename... V> void show(T t, V... v)
{cerr << t; if (sizeof...(v)) cerr << ", "; show(v...);}

#define debug(...) cerr << '[' << #__VA_ARGS__ << "]   =   [", show(__VA_ARGS__), cerr << "]\n"

template <class X>
bool mini(X& a, const X& b)
{
    if (a > b) {a = b; return true;} return false;
}

template <class X>
bool maxi(X& a, const X& b)
{
    if (a < b) {a = b; return true;} return false;
}

typedef const int& ci;
typedef long long ll;
typedef pair <int, int> pii;

const int mod = 1e9+7;

void add(ll&x, ll y)
{
    x += y;
    if (x >= mod) x -= mod;
}

template <class T>
class Matrix
{
public:

    Matrix() {}
    Matrix(int m, int n): a(m, vector <T>(n, 0)) {}
    Matrix(const vector<vector<T>>& _a): a(_a) {}

    Matrix operator * (Matrix b)
    {
        int m = a.size(), n = a[0].size();
        int p = b[0].size();
        Matrix res(m, p);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < p; ++j)
                for(int k = 0; k < n; ++k)
                    add(res[i][j], a[i][k] * b[k][j] % mod);
        return res;
    }

    Matrix bpow(int k)
    {
        Matrix <ll> res(a);
        Matrix <ll> tmp(a);
        for(--k; k > 0; k >>= 1, tmp = tmp * tmp)
            if (k & 1)
                res = res * tmp;
        return res;
    }

    vector <T>& operator [] (int i)
    {
        return a[i];
    }

private:
    vector <vector<T>> a;
};
