/*
 * http://codeforces.com/contest/487/problem/B
 */
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
const int mod = inf + 7;
const double eps = 1e-9;
const double pi = acos(-1.0);

int n, s, l;
int a[100100];
pii t[4 * 100100];
int dp[4 * 100100];

pii merge(pii a, pii b) {
    return mp(max(a.f, b.f), min(a.s, b.s));
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = mp(a[tl], a[tl]);
    } else {
        int mid = (tl + tr) >> 1;
        build(2 * v, tl, mid);
        build(2 * v + 1, mid + 1, tr);
        t[v] = merge(t[2 * v], t[2 * v + 1]);
    }
}

pii get(int v, int tl, int tr, int l, int r) {
    // [tl, tr] [l, r]
    if (tl > r || tr < l) {
        return mp(-inf, inf);
    }
    if (l <= tl && tr <= r) {
        return t[v];
    }
    int mid = (tl + tr) >> 1;
    pii ans1 = get(2 * v, tl, mid, l, r);
    pii ans2 = get(2 * v + 1, mid + 1, tr, l, r);
    return merge(ans1, ans2);
}

void update_dp(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        dp[v] = val;
    } else {
        int mid = (tl + tr) >> 1;
        if (pos <= mid) update_dp(2 * v, tl, mid, pos, val);
        else update_dp(2 * v + 1, mid + 1, tr, pos, val);
        dp[v] = min(dp[2 * v], dp[2 * v + 1]);
    }
}

int get_dp(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) return inf;
    if (l <= tl && tr <= r) return dp[v];
    int mid = (tl + tr) >> 1;
    int ans1 = get_dp(2 * v, tl, mid, l, r);
    int ans2 = get_dp(2 * v + 1, mid + 1, tr, l, r);
    return min(ans1, ans2);
}

int main(){

    scanf("%d%d%d", &n, &s, &l);
    for (int i = 0; i < n; i++) scanf("%d", a + i);

    build(1, 0, n - 1);

    for (int i = 0; i < 4 * 100100; i++) dp[i] = inf;
    update_dp(1, 0, n, 0, 0);

    for (int i = 0; i < n; i++) {
        int jmax = i - l + 1;
        int jmin = -1;
        int L = 0, R = i;
        while (L <= R) {
            int mid = (L + R) >> 1;
            pii cur = get(1, 0, n - 1, mid, i);
            int diff = cur.f - cur.s;
            if (diff <= s) {
                jmin = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        // jmin, jmax
        if (jmin > jmax) {
            continue;
        }
        jmin++;
        jmax++;
        // [jmin-1, jmax-1]
        int val = get_dp(1, 0, n, jmin - 1, jmax - 1);
        update_dp(1, 0, n, i + 1, val + 1);
    }

    int ans = get_dp(1, 0, n, n, n);

    if (ans == inf) ans = -1;

    printf("%d\n", ans);

    return 0;
}
