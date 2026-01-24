#include <bits/stdc++.h>
using namespace std;

#define pb push_back

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_map<string, vector<int>> hm;
    unordered_map<string, bool> vis;
    
    int n, k;
    cin >> n >> k;
    int c1, c2;
    string p1, p2;
    int unknown = n / 2;
    for (int i=0;i<k;i++) {
        cin >> c1 >> c2 >> p1 >> p2;
        if (hm.find(p1) == hm.end()) {
            hm[p1].pb(c1);
            unknown--;
        } else if (hm[p1].size() == 1 && hm[p1][0] != c1) {
            hm[p1].pb(c1);
        }
        
        if (hm.find(p2) == hm.end()) {
            hm[p2].pb(c2);
            unknown--;
        } else if (hm[p2].size() == 1 && hm[p2][0] != c2) {
            hm[p2].pb(c2);
        }
        
        if (p1 == p2) {
            vis[p1] = true;   
        }
    }
    
    int ans = 0;
    int onlyone = 0;
    for (auto& [key, values] : hm) {
        if (values.size() == 2 && vis.find(key) == vis.end()) {
            ans++;
        } else if (values.size() == 1) {
            onlyone++;
        }
    }
    
    if (unknown == 0) {
        ans += onlyone;
    } else if (unknown == 1 && onlyone == 0) {
        ans++;
    }
    
    cout << ans <<'\n';
}