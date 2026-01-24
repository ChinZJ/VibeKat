#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> P(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> P[i];
        }
        
        vector<int> suffix_min(n + 2);
        suffix_min[n + 1] = INT_MAX;
        for (int i = n; i >= 1; i--) {
            suffix_min[i] = min(P[i], suffix_min[i + 1]);
        }
        
        vector<int> result;
        for (int i = 1; i < n; i++) {
            if (P[i] > suffix_min[i + 1]) {
                result.push_back(P[i]);
            }
        }
        
        sort(result.begin(), result.end());
        cout << result.size() << '\n';
        for (int x : result) {
            cout << x << '\n';
        }
    }
    return 0;
}