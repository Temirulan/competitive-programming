#pragma comment(linker, "/STACK:64000000")
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


char s[100005];
int n, it, root;
// -4+(-3+2)*(5+2)

/*
1) -4
E, F, T
   F - tam ne *
E
  + -> F
  


*/

bool check(int pr, char ch) {
	if (pr == 1) return ch == '+' || ch == '-';
	return ch == '*';
}

void operate(int &x, int y, char op) {
	if (op == '+') x += y;
	else if (op == '-') x -= y;
	else x *= y;
}

int parse1(int pr) {
	if (pr == 3) {
		int cur;
		if (s[it] == '(') {
			it++; // (
			cur = parse1(1);
			it++; // )
		} else { // number
			cur = 0;
			int sign = +1;
			if (s[it] == '-') it++, sign = -1;
			while (it < n && '0' <= s[it] && s[it] <= '9') {
				cur = cur * 10 + s[it] - '0';
				it++;
			}
			cur *= sign;
		}
		return cur;
	}
	int cur = parse1(pr + 1);
	if (it < n && check(pr, s[it])) {
		char op = s[it++];
		int res = parse1(pr);
		operate(cur, res, op);
	}
	return cur;
}

int parseE();

int parseT() {
	int cur;
	if (s[it] == '(') {
		it++; // (
		cur = parseE();
		it++; // )
	} else { // number
		cur = 0;
		int sign = +1;
		if (s[it] == '-') it++, sign = -1;
		while (it < n && '0' <= s[it] && s[it] <= '9') {
			cur = cur * 10 + s[it] - '0';
			it++;
		}
		cur *= sign;
	}
	return cur;
}

int parseF() {
	int cur = parseT();
	if (it < n && (s[it] == '*')) {
		it++;
		int res = parseF();
		cur *= res;
	}
	return cur;
}
http://lightoj.com/volume_showproblem.php?problem=1309
int parseE() {
	int cur = parseF();
	if (it < n && (s[it] == '+' || s[it] == '-')) {
		char op = s[it];
		it++; // skip operation
		int res = parseE();
		if (op == '+') cur += res;
		else cur -= res;
	}
	return cur;
}

int main(){
	
	scanf("%s", s);
	n = strlen(s);
	
	int ans = parseE();
	printf("%d\n", ans);

    return 0;
}




