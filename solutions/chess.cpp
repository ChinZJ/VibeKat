#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    while (n--) {
        char s1, s2;
        int r1, r2;
        cin >> s1 >> r1 >> s2 >> r2;
        
        int c1 = s1 - 'A';
        int c2 = s2 - 'A';
        
        if ((c1 + r1) % 2 != (c2 + r2) % 2) {
            cout << "Impossible\n";
            continue;
        }
        
        if (s1 == s2 && r1 == r2) {
            cout << "0 " << s1 << ' ' << r1 << '\n';
        }
        else if (abs(c1 - c2) == abs(r1 - r2)) {
            cout << "1 " << s1 << ' ' << r1 << ' ' << s2 << ' ' << r2 << '\n';
        }
        else {
            int midc = (c1 + c2 - r1 + r2) / 2;
            int midr = (c2 + r2 - c1 + r1) / 2;
            
            if (midc < 0 || midc > 7 || midr < 1 || midr > 8) {
                midc = (c1 + c2 + r1 - r2) / 2;
                midr = (c1 - c2 + r1 + r2) / 2;
            }
            
            char mids =  midc + 'A';
            cout << "2 " << s1 << ' ' << r1 << ' ' 
                 << mids << ' ' << midr << ' ' 
                 << s2 << ' ' << r2 << '\n';
        }
    }
}