#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    vector<ll> s, temp;
    s.reserve(1000001);
    temp.reserve(1000001);
    
    while (t--) {
        ll n, a, b, c, x, y;
        cin >> n >> a >> b >> c >> x >> y;
        x %= y;
        
        s.resize(n);
        s[0] = a;
        for (ll i = 1; i < n; i++) {
            s[i] = (s[i-1] * b + a) % c;
        }
        
        // Radix sort (base 256, 4 passes for 32-bit values)
        temp.resize(n);
        for (int shift = 0; shift < 32; shift += 8) {
            int cnt[256] = {};
            for (ll i = 0; i < n; i++) cnt[(s[i] >> shift) & 255]++;
            
            for (int i = 1; i < 256; i++) cnt[i] += cnt[i-1];
            
            for (ll i = n - 1; i >= 0; i--) {
                temp[--cnt[(s[i] >> shift) & 255]] = s[i];
            }
            swap(s, temp);
        }
        
        ll V = 0;
        for (ll i = 0; i < n; i++) {
            V = (V * x + s[i]) % y;
        }
        cout << V << '\n';
        
        s.clear();
        temp.clear();
    }
}