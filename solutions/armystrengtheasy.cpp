#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t, ng, nm;
    cin >> t;
    while (t--) {
        cin >> ng >> nm;
        
        if (ng == 0 && nm == 0) {
            cout << "uncertain\n";
            continue;
        }
        
        int god[ng];
        int mech[nm];
        for (int i=0; i<ng; i++) {
            cin >> god[i];
        }
        for (int i=0; i<nm; i++) {
            cin >> mech[i];
        } 
        
        sort(god, god + ng, greater<int>());
        sort(mech, mech + nm, greater<int>());
        
        int glptr = ng - 1;
        int mlptr = nm - 1;
        int gval, mval;
        
        while (1) {
            gval = god[glptr];
            mval = mech[mlptr];
            if (gval == mval) {
                mlptr--;
            } else if (gval > mval) {
                mlptr--;
            } else {
                glptr--;
            }
            
            if (glptr < 0) {
                cout << "MechaGodzilla\n";
                break;
            } else if (mlptr < 0) {
                cout << "Godzilla\n";
                break;
            }
        }
        
    }
}