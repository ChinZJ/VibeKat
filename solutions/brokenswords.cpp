#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int tb = 0, lr = 0;
    
    int n;
    string str;
    cin >> n;
    while (n--) {
        cin >> str;
        for (int i=0;i<2;i++) {
            if (str.at(i) == '0') {
                tb++;
            }
        }
        for (int i=2;i<4;i++) {
            if (str.at(i) == '0') {
                lr++;
            }
        }
    }
    
    int qty = min(tb/2, lr/2);
    int tbr = tb - (qty*2);
    int lrr = lr - (qty*2);
    
    cout << qty << ' ' << tbr << ' ' << lrr << '\n';
}