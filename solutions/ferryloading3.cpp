#include <bits/stdc++.h>
using namespace std;

struct P{
    int arr, idx;
    
    P(int a, int i) : arr(a), idx(i) {};
    
    bool operator>(const P& o) const {
        if (arr != o.arr) return arr > o.arr;
        return idx > o.idx;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<queue<P>> bank(2);
    int c;
    cin >> c;
    while (c--) {
        int n, t, m, arr;
        cin >> n >> t >> m;
        string str;
        
        // Load sides
        for (int i=0;i<m;i++) {
            cin >> arr >> str;
            if (str[0] == 'l') {
                bank[0].push({arr, i});
            } else {
                bank[1].push({arr, i});
            }
        }
        
        int tott = 0, side = 0;
        vector<int> ans(m);
        while (!bank[0].empty() || !bank[1].empty()) {
            if (!bank[side].empty()) {
                if (tott >= bank[side].front().arr) {
                    int consec = 0;
                    int st = max(tott, bank[side].front().arr);
                    tott += t;
                    while (consec < n && !bank[side].empty() && st >= bank[side].front().arr) {
                        consec++;
                        ans[bank[side].front().idx] = tott;
                        bank[side].pop();
                    }
                    side = (side + 1) % 2;
                } else if (!bank[(side+1)%2].empty() && bank[(side+1)%2].front().arr < bank[side].front().arr) {
                    if (tott < bank[(side+1)%2].front().arr) tott = bank[(side+1)%2].front().arr;
                    tott += t;
                    side = (side + 1) % 2;
                } else {
                    tott = bank[side].front().arr;
                }
            } else if (!bank[(side+1)%2].empty()) {
                if (tott < bank[(side+1)%2].front().arr) tott = bank[(side+1)%2].front().arr;
                side = (side + 1) % 2;
                tott += t;
            }
        }
        
        for (int i=0;i<m;i++) {
            cout << ans[i] << '\n';
        }
        cout << '\n';
    }
    
    return 0;
}