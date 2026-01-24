#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; 
    cin >> n;
    int arr[n];
    int tmp, d;
    int val = INT_MAX;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        if (i > 1) {
            tmp = max(arr[i], arr[i-2]);
            if (val > tmp) {
                val = tmp;
                d = i - 1;
            }
        }
    }
    cout << d << ' ' << val << '\n';
}