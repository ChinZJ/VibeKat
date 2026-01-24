#include <bits/stdc++.h>
using namespace std;
#define pb push_back 
int main() {
    int n, m, c;
    cin >> n >> m;
    string s, s2;
    
    unordered_map<string, int> mapper(n+1);
    mapper["English"] = 0;
    for (int i=1;i<=n;i++) {
        cin >> s;
        mapper[s] = i;
    }
    
    vector<vector<pair<int, int>>> neigh(n+1);
    
    for (int i=0;i<m;i++) {
        cin >> s >> s2 >> c;
        neigh[mapper[s]].pb({c, mapper[s2]});
        neigh[mapper[s2]].pb({c, mapper[s]});
    }
    
    // First is always English
    if ((int)neigh[mapper["English"]].size() == 0) {
        cout << "Impossible\n";
        return 0;
    }
    
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
     // Pre seed
    for (auto [cc, ss] : neigh[mapper["English"]]) {
        pq.push({1, cc, ss});
    }
    
    int tot = 0;
    int ans = 0;
    vector<int> vis(n+1);
    while (!pq.empty()) {
        auto [ll, cc, ss] = pq.top();
        pq.pop();
        if (vis[ss] || ss == 0) continue;
        vis[ss] = 1;
        tot++;
        ans += cc;
        
        if (tot == n) break;
        
        ll++;
        if ((int)neigh[ss].size() > 0) {
            for (auto [aa, bb] : neigh[ss]) {
                pq.push({ll, aa, bb});
            }
        } 
    }
    
    if (tot == n) {
        cout << ans << '\n';
    } else {
        cout << "Impossible\n";
    }
    
    return 0;
}