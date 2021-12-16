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

const int N = 105;

const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};

int m,n,t;
char a[N][N];

void enter()
{
    cin >> m >> n >> t;
    foru(i, 1, m)
        cin >> a[i] + 1;
}

int tran(int i, int j)
{
    return (i-1)*n + j - 1;
}

bool bound(int x, int y)
{
    return x > 0 && x <= m && y > 0 && y <= n && a[x][y] != '#';
}

void solve()
{
    foru(i, 1, m)
        foru(j, 1, n)
        {
            if (a[i][j] == 'U') a[i][j] = 0;
            if (a[i][j] == 'R') a[i][j] = 1;
            if (a[i][j] == 'D') a[i][j] = 2;
            if (a[i][j] == 'L') a[i][j] = 3;

        }
    Matrix <long long> F(m*n, m*n);
    foru(i, 1, m)
        foru(j, 1, n)
        {
            int u = tran(i,j);
            if (a[i][j] == '+')
            {
                for(int k = 0; k < 4; ++k)
                {
                    int x = i + di[k], y = j + dj[k];
                    if (bound(x,y))
                        F[u][tran(x,y)] = 1;
                }
            }
            else
                if (a[i][j] != '#')
                {
                    int x = i + di[a[i][j]], y = j + dj[a[i][j]];
                    if (bound(x,y))
                        F[u][tran(x,y)] = 1;
                }

        }
    Matrix <ll> res = F.bpow(t);
    long long ans = 0;
    foru(i, 0, m*n-1)
        foru(j, 0, m*n-1)
            ///cout << F[i][j] << " \n"[j==m*n-1];
            add(ans, res[i][j]);
    cout << ans;
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
