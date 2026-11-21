#include<bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>>adj;
vector<int>sz;
vector<int>parent;
int centroid;

int dfs(int v, int p){
    sz[v] = 1;
    parent[v] = p;
    
    for (auto u : adj[v]){
        if (u == p) continue;
        sz[v] += dfs(u, v);
    }
    
    return sz[v];
}

int find_C(int v, int p){
    for (auto u : adj[v]){
        if (u != p && 2*sz[u] > n){
            return find_C(u, v);
        }
    }
    
    return v;
}

int main(){
    cin >> n;
    adj.resize(n);
    sz.resize(n);
    parent.resize(n);
    for (int i = 0; i < n-1; i++){
        int u, v; cin >> u >> v;
        u--; v--;
        
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    
    dfs(0, -1);
    centroid = find_C(0, -1);
    
    for (auto u : adj[centroid]){
        if (u == parent[centroid]) continue;
        if (2*sz[u] == n){
            cout << "2\n" << centroid + 1 << ' ' << u + 1;
            return 0;
        }
    }
    
    cout << "1\n" << centroid + 1;
}