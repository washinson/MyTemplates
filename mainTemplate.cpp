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

using namespace std;

#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,n) for(int i = n-1; i >= 0; i++)
#define ALL(x) x.begin(),x.end()
#define mp(x,y) make_pair(x,y)
#define lson x*2, l, m
#define rson x*2+1, m+1, r

typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pii64;
typedef vector<int> vint;
typedef vector<int64> vint64;
typedef long double float64;
template <typename T> istream& operator >> (istream& in, vector<T>& t) { for (int i = 0; i < t.size(); i++) in >> t[i]; return in; }
template <typename T> ostream& operator << (ostream& out, vector<T>& t) { for (int i = 0; i < t.size(); i++) out << t[i] << " "; return out; }


int main()
{
#ifdef _SANYA
	freopen("abc.txt", "r", stdin);
#else
#define T "permutation"
	//freopen(T ".in", "r", stdin);
	//freopen(T ".out", "w", stdout);
#endif
	return 0;
}
