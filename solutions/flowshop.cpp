#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    int tmp;
    vector<vector<int>> arr(n, vector<int>(m+1, 0));
    for (int i=0;i<n;i++) {
        for (int j=1;j<=m;j++) {
            cin >> tmp;
            if (i == 0) {
                arr[i][j] = tmp + arr[i][j-1];
            } else {
                arr[i][j] = tmp + max(arr[i-1][j], arr[i][j-1]);
            }
        }
    }
    cout << arr[0][m];
    for (int i=1;i<n;i++) {
        cout << ' ' << arr[i][m];
    }
    cout << '\n';
    return 0;
}