#include<bits/stdc++.h>
using namespace std;

vector<vector<long long>>dp;
vector<long long>pref;
vector<int>opt;
int n, k;

using ll = long long;

void build(int t, int l, int r, int optL, int optR){
    if (l > r) return;
    
    int m = l + (r - l) / 2;
    
    int st = max(optL, t-1);
    int fn = min(optR, m-1);
    int bestJ = optL;
    ll bestDp = LLONG_MAX;
    for (int j = st; j<=fn; j++){
        if (dp[t-1][j] == LLONG_MAX) continue;
        
        ll cur = dp[t-1][j] + (pref[m] - pref[j]) * (pref[m] - pref[j]);
        if (cur < bestDp){
            bestDp = cur;
            bestJ = j;
        }
    } 
    
    dp[t][m] = bestDp;
    build(t, l, m-1, optL, bestJ);
    build(t, m+1, r, bestJ, optR);
}

int main(){
    cin >> n >> k;
    pref.resize(n + 1);
    pref[0] = 0LL;
    for (int i = 1; i < n+1; i++){
        cin >> pref[i];
        pref[i] += pref[i-1];
    }
    
    dp.assign(k+1, vector<ll>(n+1, LLONG_MAX));
    for (int i = 1; i <= n; i++){
        dp[1][i] = pref[i] * pref[i];
    }
    
    for (int t = 2; t <= k; t++){
        build(t, t, n, t-1, n-1);
    }
    
    cout << dp[k][n];
}