#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    
    string cmd;
    int val, val2;
    while (1) {
        cin >> n;
        if (n == 0) return 0;
        vector<char> ans(32, '?');
        while (n--) {
            cin >> cmd >> val;
            if (cmd == "CLEAR") {
                ans[val] = '0';
            } else if (cmd == "SET") {
                ans[val] = '1';
            } else if (cmd == "OR") {
                cin >> val2;
                if (ans[val] == '1' || ans[val2] == '1') {
                    ans[val] = '1';
                } else if (ans[val] == '0' && ans[val2] == '?') {
                    ans[val] = '?';
                }
            } else if (cmd == "AND") {
                cin >> val2;
                if (ans[val] == '0' || ans[val2] == '0') {
                    ans[val] = '0';
                } else if (ans[val] == '1' && ans[val2] == '?') {
                    ans[val] = '?';
                }
            }
        }
        for (int i=31;i>=0;i--) {
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}