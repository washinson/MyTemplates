vpii unite(vpii &a, vpii &b) {
	vpii res; res.reserve(a.size() + b.size());
	for (int i = 0, j = 0; i < a.size() || j < b.size(); ) {
		if (i != a.size() && (j == b.size() || a[i].first < b[j].first)) res.push_back(a[i++]);
		else res.push_back(b[j++]);
	}
	return res;
}

struct DOM {
#define lson v * 2, l, m
#define rson v * 2 + 1, m + 1, r
	struct Item {
		vpii mas;
	};

	vector<Item> g;

	DOM() {}
	DOM(vint &base) { g.resize(4 * base.size()); build(1, 0, base.size() - 1, base); }

	void build(int v, int l, int r, vint &base) {
		if (l == r) {
			g[v].mas = { { base[l], l } };
			return;
		}
		int m = (l + r) / 2;
		build(lson, base);
		build(rson, base);
		g[v].mas = unite(g[v * 2].mas, g[v * 2 + 1].mas);
	}

	vpii get(int v, int l, int r, int a, int b) {
		if (r < a || l > b) return vpii();
		if (a <= l && b >= r) return g[v].mas;
		int m = (l + r) / 2;

		vpii aa = get(lson, a, b);
		vpii bb = get(rson, a, b);

		return unite(aa, bb);
	}
};
