#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        if (a == 0 && b == 0 && c == 0 && d == 0) {
            break;
        } 
        int tot = 360 * 3;
        if (a < b) {
            tot += ((40 + a - b) * 9);
        } else {
            tot += ((a - b) * 9);
        }
        
        if (c < b) {
            tot += ((40 + c - b) * 9);
        } else {
            tot += ((c - b) * 9);
        }
        
        if (c < d) {
            tot += ((40 + c - d) * 9);
        } else {
            tot += ((c - d) * 9);
        }
        cout << tot << '\n';
    }
}