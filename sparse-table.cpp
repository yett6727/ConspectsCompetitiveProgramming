#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q; cin >> n >> q;
    int LOG = 21;
    
    int lg[n+1];
    lg[1] = 0;
    for (int i = 2; i <= n; i++){
        lg[i] = lg[i/2] + 1;
    }
    
    vector<vector<int>>ST(LOG, vector<int>(n, 0));
    for (int i = 0; i < n; i++){
        cin >> ST[0][i];
    }
    
    for (int j = 1; j < LOG; j++){
        for (int i = 0; i + (1<<j) <= n; i++){
            ST[j][i] = min(ST[j-1][i], ST[j-1][i+(1<<(j-1))]);
        }
    }
    
    while(q--){
        int l, r; cin >> l >> r;
        l--;
        
        int len = r - l;
        int j = lg[len];
        
        cout << min(ST[j][l], ST[j][r - (1<<j)]) << '\n';
    }
}