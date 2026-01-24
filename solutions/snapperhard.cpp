#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    int n, k;
    int ct = 1;
    while (ct <= t) {
        cin >> n >> k;
        
        int mask = ((1 << n) - 1);
        int filt = k & ((1 << n) - 1);
        if (filt == mask) {
            cout << "Case #" << ct << ": " << "ON\n";
        } else {
            cout << "Case #" << ct << ": " << "OFF\n";
        }
        
        ct++;
    }
}