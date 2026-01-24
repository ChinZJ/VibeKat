#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return 0;
    }
    
    int idx = 0, start = 1, mul = 1, cum = 0, dbt;
    int d[n];
    int ans = 1;
    
    for (int i=0;i<n;i++) {
        cin >> d[i];
    }
    
    while (start < n) {
        int dbt = ((d[start] - d[start - 1]) * mul) + cum;
        if (dbt < 20) {
            mul++;
            cum = dbt;
        } else {
            ans++;
            mul = 1;
            cum = 0;
        }
        start++;
    }
    cout << ans << '\n';
}