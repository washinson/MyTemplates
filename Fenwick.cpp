struct Fenwick {
	vint t;

	Fenwick() {}
	Fenwick(int n) { t.resize(n); }

	void add(int i, int val) {
		for (int j = i; j < t.size(); j = j | (j + 1)) {
			t[j] += val;
		}
	}

	void set(int i, int val) {
		add(i, val - sum(i, i));
	}

	int sum(int r) {
		int res = 0;
		for (int i = r; i >= 0; i = ((i + 1) & i) - 1) {
			res += t[i];
		}
		return res;
	}

	int sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};
