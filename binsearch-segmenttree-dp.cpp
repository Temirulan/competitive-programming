//http://codeforces.com/gym/100801
//problem J
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

#define f first
#define s second
#define pb push_back
#define mp make_pair
#define ll long long
#define pii pair < int, int >
#define pll pair < long long, long long>
#define ull unsigned long long
#define y1 stupid_cmath
#define left stupid_left
#define right stupid_right
#define vi vector <int>
#define sz(a) (int)a.size()
#define forit(it, s) for(__typeof(s.begin()) it = s.begin(); it != s.end(); it++)
#define all(a) a.begin(), a.end()
#define sqr(x) ((x) * (x))

const int inf = (int)1e9;
const ll INF = (ll)1e18;
const int mod = inf + 7;
const double eps = 1e-9;
const double pi = acos(-1.0);

int n, T;
int p[100100], d[100100];
ll dp[100100], t[4 * 50500];

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = dp[tl];
    } else {
        int mid = (tl + tr) / 2;
        build(2 * v, tl, mid);
        build(2 * v + 1, mid + 1, tr);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
}

void update(int v, int tl, int tr, int pos, ll val) {
    if (tl == tr) {
        t[v] = val;
    } else {
        int mid = (tl + tr) >> 1;
        if (pos <= mid) update(2 * v, tl, mid, pos, val);
        else update(2 * v + 1, mid + 1, tr, pos, val);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
}

ll getmin(int v, int tl, int tr, int l, int r) {
    if (tr < l || tl > r) {
        return INF;
    }
    if (l <= tl && tr <= r) {
        return t[v];
    }
    int mid = (tl + tr) / 2;
    ll ans1 = getmin(2 * v, tl, mid, l, r);
    ll ans2 = getmin(2 * v + 1, mid + 1, tr, l, r);
    return min(ans1, ans2);
}

bool can(int r) {
    dp[0] = 0;
    for (int i = 1; i < n; i++) dp[i] = INF;
    build(1, 0, n - 1);
    for (int i = 1; i < n; i++) {
        // L = i - r, R = i - 1
        int L = i - r, R = i - 1;
        L = max(L, 0);
        ll val = getmin(1, 0, n - 1, L, R);
        val += d[i];
        dp[i] = val;
        update(1, 0, n - 1, i, val);
    }
    return dp[n - 1] <= T;
}

int main(){

    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);

    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n - 1; i++) scanf("%d", p + i);
    for (int i = 1; i < n - 1; i++) scanf("%d", d + i);
    d[n - 1] = 0;

    T -= n - 1;

    int L = 1, R = n - 1;
    int rmin = n - 1;

    while (L <= R) {
        int mid = (L + R) / 2;
        if (can(mid)) {
            rmin = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }

    // rmin

    int ans = inf;

    for (int i = rmin; i <= n - 1; i++) {
        ans = min(ans, p[i]);
    }

    printf("%d\n", ans);

    return 0;
}

