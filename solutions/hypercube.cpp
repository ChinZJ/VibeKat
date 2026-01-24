#include <bits/stdc++.h>
using namespace std;
unordered_map<string, long long> hm;

long long solve(string n) {
    if (hm.find(n) != hm.end()) {
        return hm[n];
    }
    
    if (n[0] == '0') {
        return hm[n] = solve(n.substr(1));
    } else {
        return hm[n] = ((1LL << n.length()) - 1) - solve(n.substr(1));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string str1, str2;
    cin >> n >> str1 >> str2;
    
    hm["0"] = 0; hm["1"] = 1;
    
    solve(str1); solve(str2);
    
    cout << hm[str2] - hm[str1] - 1 << '\n';
}