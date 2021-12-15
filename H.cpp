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

const double eps = 1e-9;
const double PI = acos(-1);

struct Point;
struct Circle;
struct Line;

struct Point
{
    double x,y;

    Point() {}
    Point(double _x, double _y): x(_x), y(_y) {}

    Point operator + (const Point& b) const
    {
        return Point(x+b.x, y+b.y);
    }

    double sdist(const Point& b) const
    {
        return (b.x-x)*(b.x-x) + (b.y-y)*(b.y-y);
    }

    double dist(const Point& b) const
    {
        return sqrt(sdist(b));
    }

};

istream& operator >> (istream& is, Point& P)
{
    is >> P.x >> P.y;
    return is;
}

struct Circle
{
    double r;
    Point O;

    Circle(Point _O, double _r): O(_O), r(_r) {}

    double area() {return r*r*PI;}

    double segment_area(double alpha)
    {
        return r*r*(alpha - sin(alpha)) / 2;
    }
};

struct Line
{
    double a,b,c;

    Line(Point A, Point B)
    {
        a = A.y - B.y;
        b = B.x - A.x;
        c = -(a*A.x + b*A.y);
    }

    vector <Point> intersection(Circle cir)
    {
        double C = c + a*cir.O.x + b*cir.O.y;
        double r = cir.r;
        double AB = a*a + b*b;
        vector <Point> res;
        if (r*r*AB < C*C)
            return res;
        double x0 = -a*C/AB, y0 = -b*C/AB;
        if (abs(r*r*AB - C*C) < eps)
        {
            res.eb(x0, y0);
            return res;
        }
        double d = r*r - C*C/AB;
        double m = sqrt(d / AB);
        Point I1 = Point(x0 + b*m, y0 - a*m);
        Point I2 = Point(x0 - b*m, y0 + a*m);
        res.eb(I1 + cir.O);
        res.eb(I2 + cir.O);
        return res;
    }

    double dist(Point P)
    {
        return abs((P.x*a + P.y*b + c)) / sqrt(a*a+b*b);
    }
};

Point A,B,C;
double R,p;

void enter()
{
    cin >> A >> B >> C >> R >> p;
}

void solve()
{
    Line AB(A, B);
    auto I = AB.intersection(Circle(C, R));
    if (I.size() < 2)
        return void(cout << "NO");
    auto E = I[0], F = I[1];
    double PI = acos(-1);
    double EF = E.sdist(F);
    double alpha = acos(1 - EF/(2*R*R));
    double per = Circle(C,R).segment_area(alpha) / Circle(C,R).area();
    p /= 100;
    cout << (p-0.05 <= per && per <= p+0.05 ? "YES" : "NO");
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
