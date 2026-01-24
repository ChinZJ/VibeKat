#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    string cmd;
    char c;
    int sz, lpt, rpt;
    bool flip, valid;
    while (n--) {
        cin >> cmd >> sz;
        vector<int> arr(sz);
        
        cin >> c;
        for (int i=0;i<sz;i++) {
            if (i==0) cin >> arr[i];
            else cin >> c >> arr[i];
        }
        cin >> c;
        
        flip = false; valid = true;
        lpt = 0; rpt = sz - 1;
        for (char c : cmd) {
            if (c == 'R') flip = !flip; 
            else {
                if (lpt > rpt) {
                    valid = false;
                    break;
                }
                
                if (flip) {
                    rpt--;
                } else {
                    lpt++;
                }
            }
        }
        
        if (valid) {
            cout << '[';
            if (flip) {
                for (int i=rpt;i>=lpt;i--) {
                    if (i!=rpt) cout << ',';
                    cout << arr[i];
                }
            } else {
                for (int i=lpt;i<=rpt;i++) {
                    if (i!=lpt) cout << ',';
                    cout << arr[i];
                }
            }
            cout << "]\n";
        } else {
            cout << "error\n";
        }
        
    }
}