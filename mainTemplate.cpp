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
#define what_is(x) cerr << #x << " = " << x << endl;

using namespace std;

#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,n) for(int i = n-1; i >= 0; i++)
#define ALL(x) x.begin(),x.end()
#define mp(x,y) make_pair(x,y)
#define sf(x,y) scanf("%" x,&y)
#define pf(x,y) printf("%" x,y)

typedef long long int64;
#define int int64

typedef unsigned long long uint64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pii64;
typedef vector<int> vint;
typedef vector<int64> vint64;
typedef long double float64;
template <typename T1, typename T2> istream& operator >> (istream& in, pair<T1, T2>& t) { return in >> t.first >> t.second; }
template <typename T1, typename T2> ostream& operator << (ostream& out, pair<T1, T2>& t) { return out << t.first << " " << t.second << endl; }
template <typename T> istream& operator >> (istream& in, vector<T>& t) { for (int i = 0; i < t.size(); i++) in >> t[i]; return in; }
template <typename T> ostream& operator << (ostream& out, vector<T>& t) { for (int i = 0; i < t.size(); i++) out << t[i] << " "; return out; }

signed main()
{
	int r = 1e5;
#ifdef _SANYA
	freopen("abc.txt", "r", stdin);
	r = 150;
#else
#define T "rings"
	//freopen(T ".in", "r", stdin);
	//freopen(T ".out", "w", stdout);
#endif
	return 0;
}
