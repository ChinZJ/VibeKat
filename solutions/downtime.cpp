#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    int maxsz = 0;
    int t;
    priority_queue<int, vector<int>, greater<int>> pq;;
    
    while (n--) {
        cin >> t;
        while (pq.size() && pq.top() <= t) {
            pq.pop();
        }
        pq.push(t + 1000);
        maxsz = max(maxsz, (int)pq.size());
    }
    
    cout << (maxsz + k - 1) / k << '\n';
}