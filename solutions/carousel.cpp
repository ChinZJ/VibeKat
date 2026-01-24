#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    long long a, b, hia, hib;
    bool change;
    while (cin >> n >> m) {
        change = false;
        if (n == 0 && m == 0) break;
        
        for (int i=0; i<n;i++) {
            cin >> a >> b;
            if (a > m) continue;
            if (!change) {
                hia = a;
                hib = b;
                change = true;
            }
            if (b * hia < hib * a) {
                hia = a;
                hib = b;
            } else if ((b * hia == hib * a) && (a > hia)) {
                hia = a;
                hib = b;
            }
        }
        
        if (change) {
            cout << "Buy " << hia << " tickets for $" << hib <<'\n';
        } else {
            cout << "No suitable tickets offered\n";
        }
            
    }
}