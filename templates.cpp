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