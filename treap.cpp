struct Item
{
	Item *l, *r;
	int x, y;
	Item(int _x, int _y) : x(_x), y(_y), l(0), r(0) {}
};

struct treap
{
	Item* root = 0;

	pair<Item*,Item*> split(Item* v, int x)
	{
		if (v == 0)
		{
			return pair<Item*, Item*>(0, 0);
		}
		else if (x > v->x)
		{
			pair<Item*, Item*> p = split(v->r, x);
			v->r = p.first;
			return pair<Item*, Item*>(v, p.second);
		}
		else
		{
			pair<Item*, Item*> p = split(v->l, x);
			v->l = p.second;
			return pair<Item*, Item*>(p.first, v);
		}
	}

	Item* merge(Item* l,Item* r)
	{
		if (l == 0)
		{
			return r;
		}
		else if (r == 0)
		{
			return l;
		}
		else if (l->y > r->y)
		{
			l->r = merge(l->r, r);
			return l;
		}
		else
		{
			r->l = merge(l, r->l);
			return r;
		}
	}

	void insert(Item*& v, Item* k)
	{
		if (v == 0)
		{
			v = k;
			return;
		}
		else if (k->y > v->y)
		{
			pair<Item*, Item*> p = split(v, k->x);
			k->l = p.first; k->r = p.second;
			v = k;
		}
		else
		{
			insert(v->x < k->x ? v->r : v->l, k);
		}
	}

	void erase(Item*& v, int x)
	{
		Item* n = v->x < x ? v->r : v->l;
		if (n->x == x)
		{
			Item* p = merge(n->l, n->r);
			v->x < x ? v->r = p : v->l = p;
			delete n;
			return;
		}
		erase(n, x);
		return;
	}

	int findBR(Item*& v, int x)
	{
		if (v == 0) return -1;
		if (v->x >= x)
		{
			int f = find(v->l, x);
			if (f != -1) return f;
			return v->x;
		}
		else
		{
			int f = find(v->r, x);
			if (f == -1) return f;
			return f;
		}
	}
};
