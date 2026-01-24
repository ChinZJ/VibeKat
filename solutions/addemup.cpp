#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 0, 1, 2, 5, 8 are rotatable
    // 6 <-> 9
    int rot[10] = {0, 1, 2, -1, -1, 5, 9, -1, 8, 6};
    
    unordered_map<int, int> smr;
    int n, s;
    string str;
    int tmp;
    cin >> n >> s;
    for (int i=0;i<n;i++) {
        cin >> str;
        tmp = stoi(str);
        if (smr.find(s - tmp) != smr.end()) {
            cout << "YES\n";
            return 0;
        }
        
        int rota = 0, val;
        int mag = 1;
        for (int j=0;j<str.length();j++) {
            val = rot[str[j] - '0'];
            if (val == -1) {
                rota = -1;
                break;
            }
            rota += (val * mag);
            mag *= 10;
        }
        if (rota != -1) {
            if (smr.find(s - rota) != smr.end()) {
                cout << "YES\n";
                return 0;
            }
            smr[rota] = 1;
        }
        smr[tmp] = 1;
    }
    cout << "NO\n";
    return 0;
}