struct treap_key {
	struct Item {
		Item *l = 0, *r = 0;
		int x, y, cnt = 1;
		Item(int x, int y) : x(x), y(y) {}
	};

	Item* root = 0;

	void upd_cnt(Item*& it) {
		it->cnt = get_cnt(it->l) + get_cnt(it->r) + 1;
	}

	int get_cnt(Item*& it) {
		return it ? it->cnt : 0;
	}

	pair<Item*, Item*> split(Item*& it, int val) {
		if (it == 0) return { 0, 0 };
		if (get_cnt(it->l) >= val) {
			auto t = split(it->l, val);
			it->l = t.second;
			upd_cnt(it);
			return { t.first, it };
		}
		else {
			auto t = split(it->r, val - get_cnt(it->l) - 1);
			it->r = t.first;
			upd_cnt(it);
			return { it, t.second };
		}
	}

	Item* merge(Item*& l, Item*& r) {
		if (l == 0) return r;
		if (r == 0) return l;
		if (l->y > r->y) {
			l->r = merge(l->r, r);
			upd_cnt(l);
			return l;
		}
		else {
			r->l = merge(l, r->l);
			upd_cnt(r);
			return r;
		}
	}

	void insert(int i, int val) {
		auto p = split(root, i);
		Item* it = new Item(val, rand() * rand());
		p.first = merge(p.first, it);
		root = merge(p.first, p.second);
	}

	int get(int i) {
		auto p = split(root, i);
		auto p2 = split(p.second, 1);
		Item* t = merge(p2.first, p2.second);
		root = merge(p.first, t);
		return p2.first->x;
	}
};
