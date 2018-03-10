#pragma comment(linker, "/STACK:268435456")
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <iomanip>
#include <stack>
#include <string>
#include <set>
#include <queue>
#include <functional>
#include <deque>
#include <cmath>
#include <sstream>
#include <bitset>
#include <unordered_map>
#define what_is(x) cerr << #x << " = " << x << endl;
#define db(x) cerr << x << endl;

using namespace std;

#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,n) for(int i = n-1; i >= 0; i++)
#define ALL(x) x.begin(),x.end()
#define mp(x,y) make_pair(x,y)
#define sf(x,y) scanf("%" x,&y)
#define pf(x,y) printf("%" x,y)

typedef long long int64;
typedef unsigned long long uint64;
#define int int64


typedef pair<int, int> pii;
typedef pair<int64, int64> pii64;
typedef vector<int> vint;
typedef vector<int64> vint64;
typedef long double float64;
template <typename T1, typename T2> istream& operator >> (istream& in, pair<T1, T2>& t) { return in >> t.first >> t.second; }
template <typename T1, typename T2> ostream& operator << (ostream& out, pair<T1, T2>& t) { return out << t.first << " " << t.second << endl; }
template <typename T> istream& operator >> (istream& in, vector<T>& t) { for (int i = 0; i < t.size(); i++) in >> t[i]; return in; }
template <typename T> ostream& operator << (ostream& out, vector<T>& t) { for (int i = 0; i < t.size(); i++) out << t[i] << " "; return out; }

vector<vector<string> > g(5);
vector<vector<int> > dp(5);
vector<vector<pii> > rev(5);

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

vector<ST> st(5);

int dd(string& a, string& b) {
	for (int i = 0; i < 10; i++) {
		if (a[i] != b[i]) return 10 - i;
	}
}

signed main()
{
	int rrrr = 1e9;
#ifdef _SANYA
	freopen("abc.txt", "r", stdin);
	cout.rdbuf(cerr.rdbuf());
	//rrrr = 15;
#else
#define T "rings"
	//freopen(T ".in", "r", stdin);
	//freopen(T ".out", "w", stdout);
#endif
	string sf; cin >> sf;
	g[0].push_back(sf);
	string ss; cin >> ss;
	g[4].push_back(ss);
	for (int i = 0; i<5; i++) {
		int n; cin >> n;
		dp[i].assign(n, 1e9);
		g[i].reserve(n);
		rev[i].resize(n);
		for (int j = 0; j<n; j++) {
			string s; cin >> s;
			if (i == 0 || i == 4) continue;
			g[i].push_back(s);
		}
	}
	for (int i = 0; i<5; i++) {
		sort(ALL(g[i]));
	}

	dp[0][0] = 0;
	st[0] = ST(dp[0]);
	for (int i = 1; i<5; i++) {
		for (int j = 0; j<g[i].size(); j++) {
			string str = g[i][j];
			for (int k = 1; k <= 10; k++) {
				str.pop_back();
				int tl = lower_bound(ALL(g[i - 1]), str + string(k, '0')) - g[i - 1].begin();
				int tr = upper_bound(ALL(g[i - 1]), str + string(k, '9')) - g[i - 1].begin();
				tr--;
				if (tr < tl) continue;
				int add = k;
				int solv = st[i - 1].get(tl, tr) + add;
				if (dp[i][j] > solv) {
					dp[i][j] = solv;
					rev[i][j] = { tl,tr };
				}
			}
		}
		st[i] = ST(dp[i]);
	}
	vector<string> ans;
	int pos = 0;
	for (int i = 4; i>0; --i) {
		ans.push_back(g[i][pos]);
		pos = st[i - 1].getID(rev[i][pos].first, rev[i][pos].second);
	}
	ans.push_back(g[0][0]);
	reverse(ALL(ans));
	cout << dp[4][0] << " " << ans.size() << endl;
	for (string s : ans) cout << s << endl;
	return 0;
}