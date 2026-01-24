#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, n, d, sum = 0;
    cin >> x;
    cin >> n;
    
    while (n--) {
        cin >> d;
        sum += x - d;
    }
    
    cout << sum + x << '\n';
}