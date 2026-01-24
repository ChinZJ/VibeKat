#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    if (n <= 2) {
        cout << 0 << '\n';
        return 0;
    }
    
    int tallest, mini = INT_MAX;
    int tmp;
    int dep = 0;
    cin >> tallest;
    for (int i=1;i<n;i++) {
        cin >> tmp;
        dep = max( min(tallest, tmp) - mini, dep );
        if (tmp > tallest) {
            tallest = tmp;
            mini = INT_MAX;
        }
        mini = min(mini, tmp);
    }
    cout << dep << '\n';
    return 0;
}