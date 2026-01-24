#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll fastexp(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    ll n;
    cin >> n;
    
    ll sz = fastexp(2, n);
    ll uniq = (fastexp(4, n) - 1) / 3;
    
    vector<vector<int>> grid(sz, vector<int>(sz));
    vector<int> vis(uniq);
    
    for (int i=0;i<sz;i++) {
        for (int j=0;j<sz;j++) {
            cin >> grid[i][j];
        }
    }
    
    
    for (int i=0;i<sz;i++) {
        for (int j=0;j<sz;j++) {
            if (grid[i][j] == -1) continue;
            
            int curr = grid[i][j];
            grid[i][j] = -1;
            vis[curr]++;
            
            // bot left
            // check extra condition, that there must exist one bot
            if (j > 0 && i + 1 < sz && grid[i+1][j-1] == curr) {
                if (grid[i+1][j] == curr) {
                    vis[curr]++;
                    grid[i+1][j-1] = -1;
                } else {
                    cout << 0 << '\n';
                    return 0;
                }
            }
            
            // bot
            if (i+1 < sz && grid[i+1][j] == curr) {
                vis[curr]++;
                grid[i+1][j] = -1;
            }
            // right
            if (j + 1 < sz && grid[i][j + 1] == curr) {
                vis[curr]++;
                grid[i][j+1] = -1;
            }
            // diag right
            if (i + 1 < sz && j + 1 < sz && grid[i+1][j+1] == curr) {
                vis[curr]++;
                grid[i+1][j+1] = -1;
            } 
            
            if ((curr != 0 && vis[curr] != 3) || (curr == 0 && vis[curr] != 1)) {
                cout << 0 << '\n';
                return 0;
            }
        }
    }
    cout << 1 << '\n';
}