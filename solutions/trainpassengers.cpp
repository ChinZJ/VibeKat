#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll c;
    int n;
    cin >> c >> n;
    
    ll cur = 0;
    
    ll inin, inen, inst;
    
    for (int i=0;i<n;i++) {
        cin >> inin >> inen >> inst;
        if (i == 0) { // No one in the train at the start
            if (inin != (ll) 0) {
                cout << "impossible\n";
                return 0;
            }
        }
        else if (i == n - 1) { // No one waiting or entering
            if (inen != 0 || inst != 0 || cur != inin) {
                cout << "impossible\n";
                return 0;
            }
        }
        
        // Invalid inputs
        if (inin < 0 || inen < 0 || inst < 0) {
            cout << "impossible\n";
            return 0;
        }
        
        // Current leave is valid
        if (cur < inin) {
            cout << "impossible\n";
            return 0;
        }
        
        // Exceed cap
        if (cur - inin + inen > c) {
            cout << "impossible\n";
            return 0;
        }
        
        // Got space but waited in vain
        if (inst > 0 && cur -inin + inen < c) {
            cout << "impossible\n";
            return 0;
        }
        
        cur = cur - inin + inen;
    }
    cout << "possible\n";
}