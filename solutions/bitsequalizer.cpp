#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int tr;
    cin >> tr;
    int t = 1;
    while (t <= tr) {
        string a, b;
        cin >> a >> b;
        int n = a.length();
        int za = 0, oa = 0, qa = 0, zb = 0, ob = 0;
        
        for (auto& c : a) {
            if (c == '0') {
                za++;
            } else if (c == '1') {
                oa++;
            } else {
                qa++;
            }
        }
        
        for (auto& c : b) {
            if (c == '0') {
                zb++;
            } else {
                ob++;
            }
        }
        
        if (qa + za < zb) {
            cout << "Case " << t << ": " << -1 << '\n';
            t++; 
            continue;
        }
        
        int zm = 0, om = 0;
        for (int i=0;i<n;i++) {
            if (a.at(i) != b.at(i)) {
                if (a.at(i) == '?') {
                    continue;
                } else if (a.at(i) == '0') {
                    zm++;
                } else {
                    om++;
                }
            }
        }
        
        int fin = qa;
        fin += min(zm, om) + abs(zm - om);
        cout << "Case " << t << ": " << fin << '\n';
        t++;
    }
}