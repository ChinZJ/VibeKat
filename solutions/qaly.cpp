#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    double q, y;
    double sum = 0;
    while (n--) {
        cin >> q >> y;
        sum += (q * y);
    }
    cout << sum << '\n';
}