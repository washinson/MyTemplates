struct ST {
	ST() {}
	vector<vint> t;
	vector<vint> res;
	ST(vector<int>& v) {
		t.assign(v.size(), vint(40, 1e9));
		res.assign(v.size(), vint(40, -1));
		for (int i = 0; i<v.size(); i++) {
			t[i][0] = v[i];
		}
	}

	int get2(int l, int st) {
		int &cur = t[l][st];
		if (cur != 1e9) return cur;
		return cur = min(get2(l, st - 1), get2(l + (1 << (st - 1)), st - 1));
	}

	int get2ID(int l, int st) {
		int &cur = res[l][st];
		if (st == 0) return l;
		if (cur != -1) return cur;
		int a = get2(l, st - 1);
		int b = get2(l + (1 << (st - 1)), st - 1);
		if (a < b) return cur = get2ID(l, st - 1);
		return cur = get2ID(l + (1 << (st - 1)), st - 1);
	}

	int get(int l, int r) {
		int len = (r - l + 1);
		int st = 0; while (len >= (1 << st)) st++; st--;
		return min(get2(l, st), get2(r - (1 << st) + 1, st));
	}

	int getID(int l, int r) {
		int len = (r - l + 1);
		int st = 0; while (len >= (1 << st)) st++; st--;
		int a = get2ID(l, st); int b = get2ID(r - (1 << st) + 1, st);
		if (t[a][0] < t[b][0]) return a;
		return b;
	}
};
