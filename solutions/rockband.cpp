#include <bits/stdc++.h>
using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, s;
    cin >> m >> s;
    
    vector<vector<int>> q(m, vector<int>(s));
    
    for (int i=0;i<m;i++) {
        for (int j=0;j<s;j++) {
            cin >> q[i][j];
        }
    }
    
    vector<int> cnt(s + 1);
    int happy = 0;
    for (int j=0;j<s;j++) { // itr songs
        for (int i=0;i<m;i++) {
            cnt[q[i][j]]++;
            
            if (cnt[q[i][j]] == m) happy++;
            
            
        }
        if (happy == j + 1) break; // one loop one song
    }
    
    // take any member first happy songs
    cout << happy << '\n';
    vector<int> ans(happy);
    for (int i=0;i<happy;i++) {
        ans[i] = q[0][i];
    }
    sort(ans.begin(), ans.end());
    
    for (int i=0;i<happy;i++) {
        if (i != 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}