/*
 *
 * Q queries
 * 1 pos val - change value at index pos to val
 * 2 l r - find subarray of [l,r] with maximum sum
 *
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

struct Node {
    ll sum, ans, pref, suff;

    Node () {
        sum = 0;
        ans = -inf * 1ll * inf;
        pref = ans;
        suff = ans;
    }
    Node (ll _sum, ll _ans, ll _pref, ll _suff) {
        sum = _sum;
        ans = _ans;
        pref = _pref;
        suff = _suff;
    }
} t[4 * 100100];

int n, a[100100];

Node merge(Node a, Node b) {
    Node c = Node();
    c.sum = a.sum + b.sum;
    c.ans = max(a.ans, max(b.ans, a.suff + b.pref));
    c.pref = max(a.pref, a.sum + b.pref);
    c.suff = max(b.suff, a.suff + b.sum);
    return c;
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = Node(a[tl], a[tl], a[tl], a[tl]);
    } else {
        int mid = (tl + tr) >> 1;
        build(2 * v, tl, mid);
        build(2 * v + 1, mid + 1, tr);
        t[v] = merge(t[2 * v], t[2 * v + 1]);
    }
}

void update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        t[v] = Node(val, val, val, val);
    } else {
        int mid = (tl + tr) >> 1;
        if (pos <= mid) update(2 * v, tl, mid, pos, val);
        else update(2 * v+ 1, mid + 1, tr, pos, val);
        t[v] = merge(t[2 * v], t[2 * v + 1]);
    }
}

Node get(int v, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) return Node();
    if (l <= tl && tr <= r) return t[v];
    int mid = (tl + tr) >> 1;
    Node ans1 = get(2 * v, tl, mid, l, r);
    Node ans2 = get(2 * v + 1, mid + 1, tr, l, r);
    return merge(ans1, ans2);
}

int main(){

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }

    build(1, 0, n - 1);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int pos, val;
            scanf("%d%d", &pos, &val);
            pos--;
            update(1, 0, n - 1, pos, val);
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            l--; r--;
            Node cur = get(1, 0, n - 1, l, r);
            printf("%lld\n", cur.ans);
        }
    }

    return 0;
}

