#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N;
vector<int> graph[100001];
int par[100001][20];
int d[100001];
bool visited[100001];

void init() {
	for (int i = 0; i < 100001; i++) {
		graph[i].clear();
	}
	memset(d, 0, sizeof(d));
	memset(visited, false, sizeof(visited));
};

int LCA(int x, int y, int cnt) {
	if (d[x] > d[y])
		swap(x, y);
	if (par[y][0] == x) {
		return 1;
	}
	for (int i = 19; i >= 0; i--) {
		if (d[y] - d[x] >= (1 << i)) {
			y = par[y][i];
			cnt += (1 << i);
		}
	}

	if (par[y][0] != par[x][0]) {
		for (int i = 19; i >= 0; i--) {
			if (par[x][i] != par[y][i]) {
				cnt += 2 * (1 << i);
				x = par[x][i];
				y = par[y][i];
			}
		}
	}
	
	if (par[x][0] == par[y][0]) {
		return cnt + 2;
	}
	return 0;
};

long long int bfs() {
	long long int result = 0;
	int pre, cur;
	queue<int> q;
	q.push(1);
	visited[1] = true;
	pre = 1;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < graph[x].size(); i++) {
			int y = graph[x][i];
			if (visited[y])
				continue;
			q.push(y);
			cur = y;
			visited[y] = true;
			result += LCA(pre, cur, 0);
			pre = cur;
		}
	}
	return result;
};

int main() {
	int tc, T;
    ifstream cin("codebattle10.txt", ios_base::in);    
	cin >> T;
	for (tc = 1; tc <= T; ++tc) {
		init();
		cin >> N;
		int k;
		par[1][0] = 0;
		d[1] = 0;
		for (int i = 2; i <= N; i++) {
			cin >> k;
			graph[k].push_back(i);
			par[i][0] = k;
			d[i] = d[k] + 1;
		}
		for (int y = 1; y < 20; y++) {
			for (int x = 1; x <= N; x++) {
				par[x][y] = par[par[x][y - 1]][y - 1];
			}
		}
		for (int x = 1; x <= N; x++) {
			for (int y = 0; y < 20; y++) {
				cout << par[x][y] << '\t';
			}
			cout << '\n';
		}
		cout << "#" << tc << " " << bfs() << "\n";
		break;
	}

	return 0;
}