#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    int narr[n];
    for (int i = 0; i < n; i++) {
        cin >> narr[i];
    }
    int m;
    cin >> m;
    int marr[m];
    for (int i=0;i<m;i++) {
        cin >> marr[i];
    }
    
    int cnt, costtmp;
    int mincost = INT_MAX;
    for (int i=0;i<n;i++) {
        cin >> cnt;
        for (int j=0;j<cnt;j++) {
            cin >> costtmp;
            mincost = min(mincost, narr[i] + marr[costtmp - 1]);
        }
    }
    int tot;
    cin >> tot;
    cout << max(0, tot / mincost - 1) <<'\n';
}