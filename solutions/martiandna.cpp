#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, rr, id;
    int tot = 0;
    cin >> n >> k >> rr;
    vector<int> req(k);
    vector<int> nbs(n);
    
    for (int i=0;i<n;i++) {
        cin >> nbs[i];
    }
    
    for (int i=0;i<rr;i++) {
        cin >> id;
        cin >> req[id];
        tot += req[id];
    }
    

    int l = 0;
    int r = 0;
    
    // Greedily take until tot == 0
    while (r < n) {
        if (req[nbs[r]] > 0) tot--;
        --req[nbs[r]];
        if (tot == 0) break;
        ++r;
    }
    
    if (tot) {
        cout << "impossible\n";
        return 0;
    }
    
    int ans = (r - l) + 1;

    while ((r < n-1) || (req[nbs[l]] < 0)) {
        // Shrink left until not possible
        while (req[nbs[l]] < 0) {
            req[nbs[l]]++;
            l++;
        }

        // Increase right until left can be removed
        // Record
        ans = min(ans, ((r - l) + 1));
        
        while (r < n - 1) {
            r++;
            req[nbs[r]]--;
            if (req[nbs[r]] == req[nbs[l]]) break;
        }
    }
    
    ans = min(ans, ((r - l) + 1));
    cout << ans << '\n';
    return 0;
    
}