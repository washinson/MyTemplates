//Union
struct Union
{
	struct Node
	{
		int p, r;
	};

	vector<Node> t;

	void init(int n)
	{
		t.resize(n);
		for (int i = 0;i < t.size();i++)
		{
			t[i].p = i;
			t[i].r = 0;
		}
	}

	int get(int a)
	{
		return a == t[a].p ? a : t[a].p = get(t[a].p);
	}

	void unite(int f, int s)
	{
		int a = get(f);
		int b = get(s);
		if (a == b) return;
		if (t[a].r < t[b].r) swap(a, b);
		t[b].p = a;
		if (t[a].r == t[b].r) t[a].r++;
	}
};

//SegmentTree
struct SegmentTree
{
	struct Node
	{
		int64 val = 0;
		int64 sum = 0;
	};
	
	vector<Node> t;
	static int n;

	void init(int nn)
	{
		t.assign(4 * n, Node());
		n = nn;
	}

	void Push(int x, int l, int r)
	{
		if (t[x].sum == 0) return;
		t[x].val += t[x].sum * (r - l + 1);
		if (l <= r)
		{
			t[x * 2].sum = t[x].sum;
			t[x * 2 + 1].sum = t[x].sum;
		}
		t[x].sum = 0;
	}

	void Add(int a, int b, int64 v, int x = 1, int l = 0, int r = n - 1)
	{
		Push(x, l, r);
		if (a > r || b < l) return;
		if (a >= l&&b <= r)
		{
			t[x].sum += v;
			Push(x, l, r);
			return;
		}
		Add(a, b, v, x * 2, l, (l + r) / 2);
		Add(a, b, v, x * 2 + 1, (l + r) / 2 + 1, r);
		t[x].val = t[x * 2].val + t[x * 2 + 1].val;
	}

	int64 Sum(int a, int b, int x = 1, int l = 0, int r = n - 1)
	{
		Push(x, l, r);
		if (a > r || b < l) return 0;
		if (a >= l&&b <= r)
		{
			return t[x].val;
		}
		int64 s1 = Sum(a, b, x * 2, l, (l + r) / 2);
		int64 s2 = Sum(a, b, x * 2 + 1, (l + r) / 2 + 1, r);
		return s1 + s2;
	}
};

