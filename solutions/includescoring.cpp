#include <bits/stdc++.h>
using namespace std;

vector<int> scores = {0, 100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24,
    22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
};

struct Player {
    int s, p, f, o, i;
    
    bool operator<(const Player& other) const {
        if (s != other.s) return s > other.s;
        if (p != other.p) return p < other.p;
        return f < other.f;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<Player> ps(n);
    vector<int> scs(n, 0);
    for (int i = 0; i < n; i++) {
        ps[i].i = i;
        cin >> ps[i].s >> ps[i].p >> ps[i].f >> ps[i].o;
    }
    
    sort(ps.begin(), ps.end());
    
    int rank = 1;
    int idx = 0;
    while (idx < n) {
        int tiest = idx;
        while (idx < n - 1 && 
               ps[idx].s == ps[idx + 1].s &&
               ps[idx].p == ps[idx + 1].p &&
               ps[idx].f == ps[idx + 1].f) {
            idx++;
        }
        
        int sz = idx - tiest + 1;
        int cum = 0;
        for (int r = rank; r < rank + sz && r < (int)scores.size(); r++) {
            cum += scores[r];
        }
        cum = (int)ceil((double)cum / sz);
        
        for (int a = tiest; a <= idx; a++) {
            scs[ps[a].i] = cum + ps[a].o;
        }
        
        rank += sz;
        idx++;
    }
    
    for (int i = 0; i < n; i++) {
        cout << scs[i] << '\n';
    }
    return 0;
}