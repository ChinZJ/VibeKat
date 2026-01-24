#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double C, X, M;
    cin >> C >> X >> M;
    
    int ans = -1;
    int tx;
    double ty;
    for (int i=0;i<6;i++) {
        cin >> tx >> ty;
        double f1 = M / ty;
        double f2 = M / tx;
        double req = f1 + (f2 * X);
        
        if ((C / 2.0) - req >= 1e-6) {
            ans = tx;
        }
    }
    
    if (ans != -1) {
        cout << "YES " << ans << '\n';
    } else {
        cout << "NO\n";
    }
}