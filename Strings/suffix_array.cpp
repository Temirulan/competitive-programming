/*
 *
 * Created by Temirulan Mussayev (8 October 2016)
 *
 * Suffix array algorithm, building complexity O(n*log(n))
 * 
 * suff[i]: i-th lexographically suffix
 * lcp[i]: longest common prefix of suffix suff[i] and suff[i + 1]
 *
 * getlcp(i, j): longest common prefix of s[i..n-1] and s[j..n-1], O(1)
 * is_equal(l1, r1, l2, r2): equality of two substrings s[l1..r1] and s[l2..r2], O(1)
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
const int MAX_LVL = 19;
const int MAX_LEN = 200200;

int n;
char s[MAX_LEN];
int dp[MAX_LVL][MAX_LEN], two[MAX_LEN];
int suff[MAX_LEN], nsuff[MAX_LEN];
int col[MAX_LEN], ncol[MAX_LEN], cn = 0;
int head[MAX_LEN], lcp[MAX_LEN], p[MAX_LEN];

bool cmp(int i, int j) {
    return s[i] < s[j];
}

void suffix_array() {
    s[n++] = '$';
    for (int i = 0; i < n; i++) {
        suff[i] = i;
    }
    stable_sort(suff, suff + n, cmp);
    cn = 0;
    for (int i = 0; i < n; i++) {
        if (i && s[suff[i]] == s[suff[i - 1]]) {
            col[suff[i]] = col[suff[i - 1]];
        } else {
            col[suff[i]] = cn;
            head[cn] = i;
            cn++;
        }
    }
    for (int len = 1; len <= n; len += len) {
        for (int i = 0; i < n; i++) {
            int j = suff[i] - len;
            if (j < 0) j += n;
            nsuff[head[col[j]]++] = j;
        }
        cn = 0;
        for (int i = 0; i < n; i++) {
            suff[i] = nsuff[i];
        }
        for (int i = 0; i < n; i++) {
            if (i && col[suff[i]] == col[suff[i - 1]]
                  && col[(suff[i] + len) % n] == col[(suff[i - 1] + len) % n]) {
                ncol[suff[i]] = ncol[suff[i - 1]];
            } else {
                ncol[suff[i]] = cn;
                head[cn] = i;
                cn++;
            }
        }
        for (int i = 0; i < n; i++) {
            col[i] = ncol[i];
        }
    }
}

void precalcLCP() {
    for (int i = 0; i < n; i++) {
        p[suff[i]] = i;
    }
    int m = 0;
    for (int i = 0; i < n; i++) {
        int j = p[i];
        if (j == n - 1) {
            lcp[j] = 0;
            m = 0;
            continue;
        }
        while (suff[j] + m < n
               && suff[j + 1] + m < n
               && s[suff[j] + m] == s[suff[j + 1] + m]) m++;
        lcp[j] = m;
        m = max(m - 1, 0);
    }

    two[0] = -1;
    for (int i = 1; i < MAX_LEN; i++) {
        two[i] = 1 + two[i / 2];
    }
    for (int i = 0; i < n; i++) {
        dp[0][i] = lcp[i];
    }
    for (int lvl = 1; (1 << lvl) <= n; lvl++) {
        for (int i = 0; i + (1 << lvl) <= n; i++) {
            dp[lvl][i] = min(dp[lvl - 1][i],
                             dp[lvl - 1][i + (1 << (lvl - 1))]);
        }
    }
}

int getmin(int l, int r) {
    if (l > r) assert(false);
    int lvl = two[r - l + 1];
    int ans1 = dp[lvl][l];
    int ans2 = dp[lvl][r - (1 << lvl) + 1];
    return min(ans1, ans2);
}

void print() {
    for (int i = 0; i < n; i++) {
        cout << lcp[i] << ": ";
        for (int j = suff[i]; j < n; j++) printf("%c", s[j]);
        printf("\n");
    }
}

int getlcp(int i, int j) {
    int ii = p[i];
    int jj = p[j];
    if (ii > jj) swap(ii, jj);
    if (i == j) return n - i;
    return getmin(ii, jj - 1);
}

bool is_equal(int l1, int r1, int l2, int r2) {
    assert(l1 <= r1);
    assert(l2 <= r2);
    int len1 = r1 - l1 + 1;
    int len2 = r2 - l2 + 1;
    if (len1 != len2) return false;
    return getlcp(l1, l2) >= len1;
}

bool is_smaller(int l1, int r1, int l2, int r2) {
    assert(l1 <= r1);
    assert(l2 <= r2);
    int len1 = r1 - l1 + 1;
    int len2 = r2 - l2 + 1;
    int len = getlcp(l1, l2);
    if (len >= len1 && len >= len2) {
        return len1 < len2;
    }
    if (len >= len1 && len < len2) {
        return true;
    }
    if (len < len1 && len >= len2) {
        return false;
    }
    return s[l1 + len] < s[l2 + len];
}

bool cmp2(pii a, pii b) {
    return is_smaller(a.f, a.s, b.f, b.s);
}

ll number_of_different_substrings() {
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans += n - 1 - suff[i] - lcp[i - 1];
    }
    return ans;
}

void print_substrings_lexographically() {
    printf("All different substrings lexographically:\n");
    for (int i = 1; i < n; i++) {
        for (int j = lcp[i - 1] + 1; j <= n - 1 - suff[i]; j++) {
            for (int t = suff[i]; t < suff[i] + j; t++) {
                printf("%c", s[t]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

int main(){

    scanf("%s", s);
    n = strlen(s);

    suffix_array();
    precalcLCP();

    print();

    print_substrings_lexographically();

    printf("Number of different substrings: %lld\n", number_of_different_substrings());

    return 0;
}
