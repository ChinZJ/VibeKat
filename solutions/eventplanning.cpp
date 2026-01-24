#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, B, H, W, p, q;
    int bed[W];
    cin >> N >> B >> H >> W;
    
    int ans = INT_MAX;
    bool isUp = false;
    for (int i=0;i<H;i++) {
        cin >> p;
        for (int j=0;j<W;j++) {
            cin >> q;
            if (q >= N) {
                ans = min(p * N, ans);
                isUp = true;
            }
        }
            
    }
    if (isUp && ans <= B) {
        cout << ans << '\n';
    } else {
        cout << "stay home\n";
    }
}