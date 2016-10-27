/*
	Implementation of suffix automaton based on Temurlan's last lecture
*/

#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = (int)1e4 + 256;

struct node {
	int nxt[27];
	int lnk, len;
} t[MAXN * 2];

int sz, lst;
char s[MAXN];
int len;

void add(char c) {
	c -= 'a';
	int cur = ++sz;
	
	t[cur].len = t[lst].len + 1;
	int p = lst;
	while (p != -1 && !t[p].nxt[c]) {
		t[p].nxt[c] = cur;
		p = t[p].lnk;
	}
	if (p == -1) {
		t[cur].lnk = 0;
	} else {
		int q = t[p].nxt[c];
		if (t[q].len - 1 == t[p].len) {
			t[cur].lnk = q;
		} else {
			int qq = ++sz;
			for (int i = 0; i < 26; ++i)
				t[qq].nxt[i] = t[q].nxt[i];
			t[qq].len = t[p].len + 1;
			t[cur].lnk = t[q].lnk = qq;
			while (p != -1 && t[p].nxt[c] == q) {
				t[p].nxt[c] = qq;
				p = t[p].lnk;
			}
		}
	}
	lst = cur;
}

bool search(string s) {
	int v = 0;
	for (auto it : s) {
		it -= 'a';
		if (!t[v].nxt[it])
			return false;
		v = t[v].nxt[it];
	}
	return true;
}

int main() {
	t[lst].lnk = -1;
	++sz;
	
	string s = "temirulanabacabasuffixrubacubaakaliibizibierumarusabo";
	for (auto it : s)
		add(it);
	vector <string> v = {"aba", "ha", "erumaru", "sabo", "akali", "temirulan", "run", "array"};
	for (auto it : v)
		cout << boolalpha << it << " " << search(it) << endl;
	return 0;
}
