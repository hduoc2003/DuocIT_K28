/// query min: insert descending according to the slope
/// query max: insert ascending according to the slope
/// unit: unit of coordinate

template <class unit>
class CHTrick
{
private:
    struct line
    {
        unit a,b;
        double i; /// x-coordinate of the intersection with previous line

        line() {}
        line(unit _a, unit _b) {a = _a; b = _b;}
        line(unit _a, unit _b, double _i) {a = _a, b = _b, i = _i;}

        unit operator() (unit x) {return a*x + b;} /// get the value at point x
        double operator ^ (const line& other) const& /// get the intersection with other line
        {
            return (double(other.b-b) / (a-other.a));
        }
    };

    vector <line> v;

public:
    bool concave(line& l1, line& l2, line& l3) /// check if l2 is bad
    {
        return (l3 ^ l1) < (l2 ^ l1);
    }

    void insert(unit a, unit b)
    {
        line d = line(a, b);
        while (v.size() > 1 && concave(*(v.end()-2), v.back(), d))
            v.pop_back();
        d.i = v.size() ? d ^ v.back() : -1e18;
        v.push_back(d);
    }

    unit query(unit x)
    {
        /// find the line which give the best value
        auto it = *--upper_bound(all(v), line(0,0,x), [&](line a, line b) -> bool
        {
            return a.i < b.i;
        });
        return it(x);
    }
};
