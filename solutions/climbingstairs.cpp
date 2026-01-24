#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, r, k;
    cin >> n >> r >> k;
    
    int l1 = k + abs(k - r);
    if (l1 < n) {
        int d = n - l1;
        l1 += 2 * ((d + 1) / 2);
    }
    int t1 = l1 + r;
    
    int l2 = r;
    if (l2 < n) {
        int d = n - l2;
        l2 += 2 * ((d + 1) / 2);
    }
    int t2 = l2 + abs(k - r) + k;
    
    cout << min(t1, t2) << '\n';
    
}