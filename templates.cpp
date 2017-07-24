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

//SqrtDec
struct SqrtDec
{
	const static int size = 100;
	pii64 getBlock(int x)
	{
		return mp(x / size, x%size);
	}
	struct Block
	{
		deque<int64> w;
		int64 sum = 0;

		Block() { }

		void Insert(int n, int64 val)
		{
			add_sum(val);
			w.insert(w.begin() + n, val);
		}
		void Erase(int n)
		{
			dec_sum(w[n]);
			w.erase(w.begin() + n);
		}

		void push_back(int64 val)
		{
			add_sum(val);
			w.push_back(val);
		}
		void push_front(int64 val)
		{
			add_sum(val);
			w.push_front(val);
		}
		int64 pop_back()
		{
			int64 t = w.back();
			dec_sum(t);
			w.pop_back();
			return t;
		}
		int64 pop_front()
		{
			int64 t = w.front();
			dec_sum(t);
			w.pop_front();
			return t;
		}

		int64 Sum()
		{
			return sum;
		}

		int64 Sum(int l, int r)
		{
			int64 res = 0;
			for (int i = l;i <= r;i++)
			{
				res += w[i];
			}
			return res;
		}

		void dec_sum(int64 val)
		{
			sum -= val;
		}

		void add_sum(int64 val)
		{
			sum += val;
		}
	};
	vector<Block> t;
	SqrtDec() {}
	SqrtDec(int n)
	{
		init(n);
	}
	void init(int n)
	{
		t.assign(n / size + 1, Block());
	}

	void Insert(int n, int64 val)
	{
		auto blk = getBlock(n);
		t[blk.first].Insert(blk.second, val);
		for (int i = blk.first;i + 1 < t.size() && t[i].w.size() > size;i++)
		{
			t[i + 1].push_front(t[i].pop_back());
		}
	}
	void Erase(int n)
	{
		auto blk = getBlock(n);
		t[blk.first].Erase(blk.second);
		for (int i = blk.first;i + 1 < t.size() && t[i].w.size() < size;i++)
		{
			t[i].push_back(t[i + 1].pop_front());
		}
	}
	int64 Sum(int l, int r)
	{
		auto bl1 = getBlock(l);
		auto bl2 = getBlock(r);
		if (bl1.first == bl2.first) return t[bl1.first].Sum(bl1.second, bl2.second);

		int64 res = t[bl1.first].Sum(bl1.second, size - 1) + t[bl2.first].Sum(0, bl2.second);

		for (int i = bl1.first + 1;i<bl2.second;i++)
		{
			res += t[i].Sum();
		}
		return res;
	}
};

