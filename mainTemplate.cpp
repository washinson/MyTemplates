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
#define IO_OPTIMAZE ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,n) for(int i = n-1; i >= 0; i++)
#define ALL(x) x.begin(),x.end()
#define mp make_pair
#define sf(x,y) scanf("%" x,&y)
#define pf(x,y) printf("%" x,y)
#define sqr(x) (x)*(x)

typedef long long int64;
typedef long double ld;
#define int int64

typedef unsigned long long uint64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pii64;
typedef pair<double, double> pdd;
typedef vector<int> vint;
typedef vector<int64> vint64;
typedef vector<double> vd;
typedef vector<vint> vvint;
typedef vector<pii> vpii;

template <typename T1, typename T2> istream& operator >> (istream& in, pair<T1, T2>& t) { return in >> t.first >> t.second; }
template <typename T1, typename T2> ostream& operator << (ostream& out, pair<T1, T2>& t) { return out << t.first << " " << t.second; }
template <typename T> istream& operator >> (istream& in, vector<T>& t) { for (int i = 0; i < t.size(); i++) in >> t[i]; return in; }
template <typename T> ostream& operator << (ostream& out, vector<T>& t) { for (int i = 0; i < t.size(); i++) out << t[i] << " "; return out; }

signed main()
{
	IO_OPTIMAZE;
	int rrrr = 1e5;
#ifdef _SANYA
	freopen("abc.in", "r", stdin);
	freopen("abc.out", "w", stdout);
	rrrr = 150;
#else
#define T "rings"
	//freopen(T ".in", "r", stdin);
	//freopen(T ".out", "w", stdout);
#endif
	
	return 0;
}
