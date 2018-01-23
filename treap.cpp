struct treap
{
	struct Item
	{
		int y, x;
		int sum, val;
		Item *l, *r;
		Item(int y, int val) : y(y), l(0), r(0), sum(val*val), val(val), x(1) {}
	};

	int get(Item*& v)
	{
		return v ? v->x : 0;
	}

	int getSum(Item*& v)
	{
		return v ? v->sum : 0;
	}

	void upd(Item*& v)
	{
		if (v == 0) return;
		v->x = get(v->l) + get(v->r) + 1;
		v->sum = getSum(v->l) + getSum(v->r) + v->val*v->val;
	}

	Item* root = 0;
	typedef pair<Item*, Item*> pII;

	Item* merge(Item*& l, Item*& r)
	{
		if (l == 0) return r;
		if (r == 0) return l;

		if (l->y > r->y)
		{
			Item* p = merge(l->r, r);
			l->r = p;
			upd(l);
			return l;
		}
		else
		{
			Item* p = merge(l, r->l);
			r->l = p;
			upd(r);
			return r;
		}
	}

	pII split(Item*& v, int i)
	{
		if (v == 0)
			return pII(0, 0);
		else if (get(v->l) >= i)
		{
			pII p = split(v->l, i);
			v->l = p.second;
			upd(v);
			return pII(p.first, v);
		}
		else
		{
			pII p = split(v->r, i - get(v->l) - 1);
			v->r = p.first;
			upd(v);
			return pII(v, p.second);
		}
	}

	void insert(Item*& v, int i, Item* it)
	{
		pII p = split(v, i);
		p.first = merge(p.first, it);
		root = merge(p.first, p.second);
	}

	void erase(Item*& v, int i)
	{
		pII p = split(v, i);
		pII p2 = split(p.second, 1);
		root = merge(p.first, p2.second);
	}

	int get(Item*& v, int i)
	{
		pII p = split(v, i);
		pII p2 = split(p.second, 1);
		int t = p2.first->val;
		Item* w = merge(p2.first, p2.second);
		root = merge(p.first, w);
		return t;
	}

	void add(Item*& v, int i, int a)
	{
		pII p = split(v, i);
		pII p2 = split(p.second, 1);
		p2.first->val += a;
		upd(p2.first);
		Item* w = merge(p2.first, p2.second);
		root = merge(p.first, w);
	}
};

struct Treap
{
	struct Item
	{
		int x, y, cnt;
		Item *l, *r;
		Item(int x, int y) : x(x), y(y), l(0), r(0), cnt(0) {}
	};

	Item* root = 0;
	typedef pair<Item*, Item*> pII;

	int cnt(Item* v)
	{
		return v ? v->cnt : 0;
	}

	void upd_cnt(Item*& v)
	{
		if (!v) return;
		v->cnt = cnt(v->l) + cnt(v->r) + 1;
	}

	pII split(Item*& v, int x)
	{
		if (v == 0) return pII(0, 0);
		else if (v->x < x)
		{
			pII p = split(v->r, x);
			v->r = p.first;
			upd_cnt(v);
			return pII(v, p.second);
		}
		else
		{
			pII p = split(v->l, x);
			v->l = p.second;
			upd_cnt(v);
			return pII(p.first, v);
		}
	}

	Item* merge(Item*& l, Item*& r)
	{
		if (l == 0) return r;
		if (r == 0) return l;
		if (l->y > r->y)
		{
			l->r = merge(l->r, r);
			upd_cnt(l); 
			return l;
		}
		else
		{
			r->l = merge(l, r->l);
			upd_cnt(r);
			return r;
		}
	}

	void insert(Item*& v, Item* k)
	{
		if (v == 0) { v = k; }
		else if (v->y < k->y)
		{
			pII p = split(v, k->x);
			k->l = p.first; k->r = p.second;
			v = k;
		}
		else
		{
			insert(v->x < k->x ? v->r : v->l, k);
		}
		upd_cnt(v);
	}

	void erase(Item*& v, int k)
	{
		if (v == 0) return;
		if (v->x == k)
		{
			v = merge(v->l, v->r);
		}
		else
		{
			erase(v->x < k ? v->r : v->l, k);
		}
		upd_cnt(v);
	}
};

typedef Treap::Item Item;

set<int> tt;
int getY()
{
	while (1)
	{
		int ch = rand() * rand();
		if (tt.find(ch) == tt.end()) return tt.insert(ch), ch;
	}
}
