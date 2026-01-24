#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        bool isTie = false;
        int hi = -INT_MAX, tot = 0, hid, tmp;
        for (int i=1; i <=n; i++) {
            cin >> tmp;
            tot += tmp;
            if (tmp > hi) {
                hi = tmp;
                hid = i;
                isTie = false;
            } else if (tmp == hi) {
                isTie = true;
            }
        }
        if (isTie) {
            cout << "no winner\n";
        } else {
            if (hi > tot/2) {
                cout << "majority winner " << hid <<'\n';
            } else {
                cout << "minority winner " << hid << '\n';
            }
        }
    }
}