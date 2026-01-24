#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t, nm, ng, fg, fm;
    cin >> t;
    while (t--) {
        cin >> ng >> nm;
        if (ng == 0 && nm == 0) {
            cout << "uncertain\n";
            continue;
        }
        
        int godmx = -INT_MAX, gtmp, mechmx = -INT_MAX, mtmp;
        for (int i =0; i < ng; i++) {
            cin >> gtmp;
            godmx = max(godmx, gtmp);
        }
        for (int i =0; i < nm; i++) {
            cin >> mtmp;
            mechmx = max(mechmx, mtmp);
        }
        if (godmx >= mechmx) {
            cout << "Godzilla\n";
        } else {
            cout << "MechaGodzilla\n";
        }
        
    }
}