#include <bits/stdc++.h>
using namespace std;
int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    int n; cin >> n;
    vector<int> b(n);
    int oct28 = 273+27;
    
    for (int i = 0; i < n; i++) {
        string s; int mm, dd; char dash;
        cin >> s >> mm >> dash >> dd;
        int d = dd;
        for (int j = 1; j < mm; j++) d += days[j];
        
        d = (d - oct28 + 365) % 365;
        if (d == 0) d = 365;
        b[i] = d;
    }
    
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    
    int best = 0, maxGap = 0;
    int sz = b.size();
    
    for (int i = 0; i < sz; i++) {
        int cur = b[i];
        int nxt = (i == sz - 1) ? b[0] + 365 : b[i + 1];
        int gap = nxt - cur - 1;
        int pick = nxt - 1;
        if (pick > 365) pick -= 365;
        
        if (gap > maxGap || (gap == maxGap && pick < best)) {
            maxGap = gap;
            best = pick;
        }
    }
    
    int d = (best + oct28 - 1) % 365 + 1;
    int mm = 1;
    while (d > days[mm]) d -= days[mm++];
    
    cout << (mm < 10 ? "0" : "") << mm << '-' << (d < 10 ? "0" : "") << d << '\n';
}