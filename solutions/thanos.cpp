#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        long long p, r, f;
        cin >> p >> r >> f;
        
        if (p > f) {
            cout << "0\n";
            continue;
        }
        
        int years = 0;
        while (p <= f) {
            if (p > f / r) {
                years++;
                break;
            }
            p *= r;
            years++;
        }
        cout << years << "\n";
    }
}