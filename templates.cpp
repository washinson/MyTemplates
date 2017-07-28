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
	const int size = 1000;

	struct Block
	{
		deque<int64> w; int64 sum = 0;

		int64 find_element(int64 val)
		{
			return lower_bound(ALL(w), val) - w.begin();
		}

		void Insert_Val(int64 val)
		{
			auto it = lower_bound(ALL(w), val); if (it != w.end() && *it == val) return; w.insert(it, val); push_operation(val);
		}

		void Insert_Index(int to, int64 val)
		{
			push_operation(val); w.insert(w.begin() + to, val);
		}

		void Erase_Val(int64 val)
		{
			auto it = lower_bound(ALL(w), val); if (it != w.end() && *it == val) return; w.erase(it); pop_operation(val);
		}

		void Erase_Index(int to)
		{
			pop_operation(w[to]); w.erase(w.begin() + to);
		}

		void push_back(int64 val)
		{
			w.push_back(val); push_operation(val);
		}

		void push_front(int64 val)
		{
			w.push_front(val); push_operation(val);
		}

		int64 pop_back()
		{
			int64 t = w.back(); pop_operation(t); w.pop_back(); return t;
		}

		int64 pop_front()
		{
			int64 t = w.front(); pop_operation(t); w.pop_front(); return t;
		}

		int64 Sum_Index(int64 l, int64 r)
		{
			int64 sum = 0;
			for (;l < w.size() && l <= r;l++)
			{
				sum += w[l];
			}
			return sum;
		}

		int64 Sum_Val(int64 l,int64 r)
		{
			int64 sum = 0;
			for (int i = 0 ;i < w.size();i++)
			{
				if (w[i] >= l&&w[i] <= r)sum += w[i];
			}
			return sum;
		}

		void push_operation(int64 val)
		{
			sum += val;
		}

		void pop_operation(int64 val)
		{
			sum -= val;
		}
	};

	vector<Block> t;

	void init(int n)
	{
		t.assign(n / size + 5, Block());
	}

	pii64 getBlock_Val(int64 val)
	{
		for (int i = 0;;i++)
		{
			int ind = t[i].find_element(val);
			if (ind >= size) continue;
			return mp(i, ind);
		}
	}

	pii64 getBlock_Index(int64 val)
	{
		return mp(val / size, val%size);
	}

	void Insert_Val(int64 val)
	{
		pii64 bl = getBlock_Val(val);
		t[bl.first].Insert_Val(val);
		for (int i = bl.first;t[i].w.size() > size;i++)
		{
			t[i+1].push_front(t[i].pop_back());
		}
	}

	void Insert_Index(int64 val)
	{
		pii64 bl = getBlock_Index(val);
		t[bl.first].Insert_Index(bl.second, val);
		for (int i = bl.first;t[i].w.size() > size;i++)
		{
			t[i + 1].push_front(t[i].pop_back());
		}
	}

	void Erase_Val(int64 val)
	{
		pii64 bl = getBlock_Val(val);
		t[bl.first].Erase_Val(val);
		for (int i = bl.first;!t[i + 1].w.empty() && t[i].w.size() < size;i++)
		{
			t[i].push_back(t[i + 1].pop_front());
		}
	}

	void Erase_Index(int64 val)
	{
		pii64 bl = getBlock_Index(val);
		t[bl.first].Erase_Index(bl.second);
		for (int i = bl.first;!t[i + 1].w.empty() && t[i].w.size() < size;i++)
		{
			t[i].push_back(t[i + 1].pop_front());
		}
	}

	int64 Sum_Index(int64 l, int64 r)
	{
		auto itl = getBlock_Index(l);
		auto itr = getBlock_Index(r);

		if (itl.first == itr.first) return t[itl.first].Sum_Index(l, r);

		int64 res = t[itl.first].Sum_Index(itl.second, size - 1) + t[itr.first].Sum_Index(0, itr.second);

		for (int i = itl.first + 1;i < itr.first;i++)
		{
			res += t[i].sum;
		}
		return res;
	}

	int64 Sum_Val(int64 l,int64 r)
	{
		auto itl = getBlock_Val(l);
		auto itr = getBlock_Val(r);

		if (itl.first == itr.first) return t[itl.first].Sum_Val(l,r);

		int64 res = t[itl.first].Sum_Val(l, r) + t[itr.first].Sum_Val(l, r);

		for (int i = itl.first+1;i < itr.first;i++)
		{
			res += t[i].sum;
		}
		return res;
	}
};


