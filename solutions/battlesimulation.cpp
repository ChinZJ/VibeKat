#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_map<char, char> hm;
    hm['R'] = 'S';
    hm['B'] = 'K';
    hm['L'] = 'H';
    
    string str, res;
    cin >> str;
    
    int i = 0;
    int n = str.length() - 1;
    res.reserve(n);
    while (i + 2 <= n) {
        if ((int)str.at(i) + (int)str.at(i+1) + (int)str.at(i+2) == (int)'R' + (int) 'B' + (int) 'L') {
            res.push_back('C');
            i += 3;
        } else {
            res.push_back(hm[str.at(i)]);
            i++;
        }
    }
    while (i <= n) {
        res.push_back(hm[str.at(i)]);
        i++;
    }
    cout << res << '\n';
}