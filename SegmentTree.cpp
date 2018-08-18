//Not tested yet
struct ST {
	struct Item {
		int val = 0;
		int set = -1;
		int add = 0;
	};

	vector<Item> g;

	ST() {}
	ST(int n) { g.resize(4 * n); }
	ST(vint &ve) { g.resize(4 * ve.size()); build(1, 0, ve.size() - 1, ve); }

#define lson v * 2, l, m
#define rson v * 2 + 1, m + 1, r

	void build(int v, int l, int r, vint &ve) {
		if (l == r) {
			g[v].val = ve[l]; return;
		}
		int m = (l + r) / 2;
		build(lson, ve);
		build(rson, ve);
		g[v].val = g[v * 2].val + g[v * 2 + 1].val;
	}

	void push(int v, int l, int r) {
		if (g[v].set == -1 && g[v].add == 0) return;
		if (g[v].set != -1) g[v].val = g[v].set * (r - l + 1);
		g[v].val += g[v].add * (r - l + 1);
		if (v * 2 + 1 < g.size()) {
			g[v * 2 + 1].add = g[v * 2].add = g[v].add;
			g[v * 2 + 1].set = g[v * 2].set = g[v].set;
		}
		g[v].add = 0;
		g[v].set = -1;
	}

	void set(int v, int l, int r, int a, int b, int val) {
		push(v, l, r);
		if (r < a || l > b) return;
		if (a <= l && b >= r) {
			g[v].add = 0; g[v].set = val; push(v, l, r); return;
		}
		int m = (l + r) / 2;
		set(lson, a, b, val);
		set(rson, a, b, val);
		g[v].val = g[v * 2].val + g[v * 2 + 1].val;
	}

	void add(int v, int l, int r, int a, int b, int val) {
		push(v, l, r);
		if (r < a || l > b) return;
		if (a <= l && b >= r) {
			g[v].add = val; push(v, l, r); return;
		}
		int m = (l + r) / 2;
		add(lson, a, b, val);
		add(rson, a, b, val);
		g[v].val = g[v * 2].val + g[v * 2 + 1].val;
	}

	int sum(int v, int l, int r, int a, int b) {
		push(v, l, r);
		if (r < a || l > b) return 0;
		if (a <= l && b >= r) {
			return g[v].val;
		}
		int m = (l + r) / 2;
		int s1 = sum(lson, a, b);
		int s2 = sum(rson, a, b);
		return s1 + s2;
	}
};
