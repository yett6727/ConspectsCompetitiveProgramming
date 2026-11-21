#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<unordered_map>

using namespace std;

const int INF = 2e9;
const int N = 200000;
const int LOGN = 18;

vector<int> graph[N];
vector<bool> used;
int sz[N];
int p[N];
int levels[N];
int dists[LOGN][N];
int ans[N];
int component_size = 0;

int calc_size(int v, int p) {
    if (used[v]) return 0;
    sz[v] = 1;
    component_size++;
    for (auto u : graph[v]) {
        if (u == p) continue;
        sz[v] += calc_size(u, v);
    }
    return sz[v];
}

int find_centroid(int v, int p) {
    for (auto& u : graph[v]) {
        if (u == p) continue;
        if (used[u]) continue;
        if (sz[u] * 2 > component_size) {
            return find_centroid(u, v);
        }
    }
    return v;
}

vector<pair<int, int>> dists_cur;

void find_dists(int v, int level, int p) {
    for (auto u : graph[v]) {
        if (u == p) continue;
        if (used[u]) continue;
        dists[level][u] = dists[level][v] + 1;
        dists_cur.push_back({u, dists[level][u]});
        find_dists(u, level, v);
    }
}

int build_decomp(int v, int level = 0) {
    component_size = 0;
    calc_size(v, -1);
    v = find_centroid(v, -1);
    dists_cur.clear();
    dists_cur.push_back({v, 0});
    dists[level][v] = 0;
    levels[v] = level;
    find_dists(v, level, -1);
    sort(dists_cur.begin(), dists_cur.end());
    vector<int> dists_min(dists_cur.size());
    dists_min.back() = dists_cur.back().second;
    for (int i = (int)dists_cur.size() - 2; i >= 0; i--) {
        dists_min[i] = min(dists_min[i + 1], dists_cur[i].second);
    }
    for (int i = 0; i < (int)dists_cur.size() - 1; i++) {
        int cur = dists_cur[i].first;
        ans[cur] = min(ans[cur], dists[level][cur] +
                                 dists_min[i + 1]);
    }
    used[v] = 1;
    for (auto u : graph[v]) {
        if (used[u]) continue;
        p[build_decomp(u, level + 1)] = v;
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        p[i] = -1;
        ans[i] = INF;
    }
    build_decomp(0);
    for (int i = 0; i < n - 1; i++) {
        cout << ans[i] << '\n';
    }
}
