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

        unit operator() (unit x) {return a*x + b;} /// get value at point x
        double operator ^ (const line& other) const /// get intersection with other line
        {
            return (double(other.b - b) / (a - other.a));
        }
        bool operator < (const line& other) const /// type = 1 -> to query
        {                                         /// type = 0 -> sort according slope  
            return type ? i < other.i : a > other.a;
        }
    };

    multiset <line> s;

    bool bad(auto y) /// check if y is bad
    {                /// x = l1, y = l2, z = l3
        auto z = next(y);
        if (y == s.begin())
        {
            if (z == s.end()) return false;
            return y->a == z->a && y->b >= z->b;
        }
        auto x = prev(y);
        if (z == s.end())
            return y->a == x->a && y->b >= x->b;
        return (*x ^ *z) <= (*x ^ *y);
    }

    void get_intersect(auto& x) /// get intersection with the next line
    {
        auto nxt = next(x);
        x->i = (nxt == s.end() ? inf : *x ^ *nxt);
    }

public:

    void insert(unit a, unit b)
    {
        line d = line(a,b);
        auto cur = s.insert(d);
        if (bad(cur)) {s.erase(cur); return;} /// if (cur) is bad then stop
        auto nxt = next(cur), pre = cur;
        while (nxt != s.end() && bad(nxt)) /// check if we can use (cur) to remove nxt
            nxt = s.erase(nxt);
        get_intersect(cur); /// update intersection
        while (cur != s.begin() && bad(pre = prev(cur))) /// check if we can use (cur) to remove pre
            s.erase(pre);
        if (cur != s.begin()) get_intersect(pre); /// update pre's intersection
    }

    unit query(unit p)
    {
        type = true;
        auto it = *s.lower_bound(line(0,0,p));
        type = false;
        return it(p);
    }
};
