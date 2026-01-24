#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    double R, B, M;
    int i;
    while (n--) {
        cin >> R >> B >> M;
        
        ll b = llround(B * 100);     
        ll m = llround(M * 100);    
        ll r100 = llround(R * 100); 
        
        int i;
        for (i = 1; i <= 1200; i++) {
            ll interest = (b * r100 + 5000) / 10000;
            b += interest;
            b -= m;
            if (b <= 0) break;
        }
        if (i <= 1200) {
            cout << i << '\n';
        } else {
            cout << "impossible\n";
        }
    }
    return 0;
}