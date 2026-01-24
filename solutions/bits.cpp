#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int cnt;
        int ans = 0;
        int val, tmp;
        cin >> val;
        while (val > 0) {
            tmp = val;
            cnt = 0;
            while (tmp) {
                if (tmp & 1) {
                    cnt++;
                } 
                tmp >>= 1;
            }
            ans = max(ans, cnt);
            
            val /= 10;
        }
        cout << ans << '\n';
    }
}