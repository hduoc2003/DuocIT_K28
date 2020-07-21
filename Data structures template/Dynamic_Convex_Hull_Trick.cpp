/// for more detail explanation: 932F Codeforces, Leafy_ submission
/// query min

bool type;

template <class unit>
class DynamicHull
{
private:
    unit inf = numeric_limits <unit> :: max();

    struct line
    {
        unit a,b;
        mutable double i;

        line() {}
        line(unit _a, unit _b, double _i = 0) {a = _a, b = _b, i = _i;}

        unit operator() (unit x) {return a*x + b;}
        double operator ^ (const line& other) const
        {
            return (double(other.b - b) / (a - other.a));
        }
        bool operator < (const line& other) const
        {
            return type ? i < other.i : a > other.a;
        }
    };

    multiset <line> s;

    bool bad(auto x, auto y) /// check if y is bad
    {
        double& xi = x->i;
        if (y == s.end()) {xi = inf; return false;}
        if (x->a == y->a)
            xi = (x->b < y->b ? inf : -inf);
        else
            xi = *x ^ *y;
        return xi >= y->i;
    }

public:
    void insert(unit a, unit b)
    {
        line d = line(a,b);
        auto cur = s.insert(d), nxt = cur, pre = cur;
        ++nxt;
        while (bad(cur, nxt))
            nxt = s.erase(nxt);
        if (pre != s.begin() && bad(--pre, cur))
            bad(pre, cur = s.erase(cur));
        while ((cur = pre) != s.begin() && bad(--pre, cur))
            bad(pre, s.erase(cur));
    }

    unit query(unit x)
    {
        type = true;
        auto it = *s.lower_bound(line(0,0,x));
        type = false;
        return it(x);
    }
};
