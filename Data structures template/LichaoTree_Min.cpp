template <class unit>
class LichaoTree
{
private:
    struct line
    {
        unit a,b;

        line() {}
        line(unit _a, unit _b) {a = _a, b = _b;}

        unit operator() (unit x) {return a*x + b;}
    };

    struct node
    {
        node *l,*r;
        line d;

        node() {l = nullptr; r = nullptr;}
        node(unit _a, unit _b) {l = nullptr; r = nullptr; d = line(_a, _b);}
        node(line _d) {l = nullptr; r = nullptr; d = _d;}
    };

    node *root;

    void insert(line d, int l, int r, node*& cur)
    {
        if (l > r) return;
        if (!cur) {cur = new node(d); return;}
        line& old = cur->d;
        bool cl = d(l) < old(l);
        bool cr = d(r) < old(r);
        if (cl && cr) {old = d; return;}
        if (!cl && !cr) return;
        if (cl) swap(old, d); /// == d.a > old.a
        int mid = (l + r) >> 1;
        if (d(mid) < old(mid)) {swap(d, old); insert(d, l, mid, cur->l);}
        else insert(d, mid+1, r, cur->r);
    }

    unit query(unit p, int l, int r, node*& cur)
    {
        if (!cur) return numeric_limits <unit> :: max();
        if (l == r) return cur->d(p);
        int mid = (l + r) >> 1;
        if (p > mid) return min(cur->d(p), query(p, mid+1, r, cur->r));
        return min(cur->d(p), query(p, l, mid, cur->l));
    }

public:
    int l,r; /// query range

    void resize(int _l, int _r) {l = _l, r = _r, root = nullptr;}

    void insert(unit a, unit b)
    {
        insert(line(a, b), l, r, root);
    }

    unit query(unit p)
    {
        return query(p, l, r, root);
    }
};
